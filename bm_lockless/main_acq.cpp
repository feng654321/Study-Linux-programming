//include header files
#include <benchmark/benchmark.h>    //benchmark library
#include <vector>                   //vector library
#include <algorithm>                //algorithm library
#include <cstdlib>                  //cstdlib library
#include <cstdint>                  //cstdint library

#include <stdbool.h>
#include <string.h>
#include <sys/cdefs.h>
#include <random>
#include "rte_eal.h"
#include "rte_malloc.h"
#include "rte_memcpy.h"
#include "rte_mempool.h"
#include "rte_ring.h"
#define MEM_SIZE 1024  // 1KB 内存区域
#define ALIGNMENT 64   // 64 字节对齐


//=======================================================================

typedef enum {
    DPDK_LOCKLESS_RING_STATE_FREE,
    DPDK_LOCKLESS_RING_STATE_BUSY,
} dpdk_lockless_ring_state_e;

typedef struct {
    dpdk_lockless_ring_state_e state;
    void * obj;
} dpdk_lockless_ring_elt_t;

typedef struct {
    char name[RTE_RING_NAMESIZE];
    uint32_t prod_idx;
    uint32_t cons_idx;
    uint32_t mask;
    uint32_t size;
    const struct rte_memzone * mz;
    struct rte_mempool * mp;
    dpdk_lockless_ring_elt_t elts[];
} dpdk_lockless_ring;

#define EM_LOCKLESS_RING_SIZE (16 * 1024)
#define NUM 10000
dpdk_lockless_ring *g_test_ring;
void *g_obj_table[NUM];


//=======================================================================

#define _DPDK_LOCKLESS_RING_ENQUEUE(elt, in_obj) \
    do { \
        __atomic_store_n(&elt.obj, in_obj, __ATOMIC_RELEASE); \
        __atomic_store_n(&elt.state, DPDK_LOCKLESS_RING_STATE_BUSY, __ATOMIC_RELEASE); \
    } while (0)

#define _DPDK_LOCKLESS_RING_DEQUEUE(out_obj, elt) \
    do { \
        __atomic_store_n(&out_obj, elt.obj, __ATOMIC_RELEASE); \
        __atomic_store_n(&elt.state, DPDK_LOCKLESS_RING_STATE_FREE, __ATOMIC_RELEASE); \
    } while (0)

//=======================================================================

/**
 * enqueue n objects to ring.
 *
 * @param ring          target ring.
 * @param prod_idx      current ring producer header.
 * @param obj_table     source object table.
 * @param  n            number of objects to be enqueued.
 */
static inline void _dpdk_lockless_ring_enqueue_bulk(dpdk_lockless_ring * ring, uint32_t prod_idx,
                                                    void * const * obj_table, uint32_t n)
{
    uint32_t i;
    uint32_t idx = prod_idx & ring->mask;
    if (likely(idx + n < ring->size)) {
        for (i = 0; i < (n & ((~(unsigned)0x3))); i += 4, idx += 4) {
            _DPDK_LOCKLESS_RING_ENQUEUE(ring->elts[idx], obj_table[i]);
            _DPDK_LOCKLESS_RING_ENQUEUE(ring->elts[idx + 1], obj_table[i + 1]);
            _DPDK_LOCKLESS_RING_ENQUEUE(ring->elts[idx + 2], obj_table[i + 2]);
            _DPDK_LOCKLESS_RING_ENQUEUE(ring->elts[idx + 3], obj_table[i + 3]);
        }
        for (; i < n; i++, idx++) {
            _DPDK_LOCKLESS_RING_ENQUEUE(ring->elts[idx], obj_table[i]);
        }
    } else {
        for (i = 0; idx < ring->size; i++, idx++) {
            _DPDK_LOCKLESS_RING_ENQUEUE(ring->elts[idx], obj_table[i]);
        }
        for (idx = 0; i < n; i++, idx++) {
            _DPDK_LOCKLESS_RING_ENQUEUE(ring->elts[idx], obj_table[i]);
        }
    }
}

/**
 * dequeue n objects from ring.
 *
 * @param ring          source ring.
 * @param cons_idx      current ring consumer header.
 * @param obj_table     target object table.
 * @param  n            number of objects to be enqueued.
 */
static inline void _dpdk_lockless_ring_dequeue_bulk(dpdk_lockless_ring * ring, uint32_t cons_idx, void ** obj_table,
                                                    uint32_t n)
{
    uint32_t i;
    uint32_t idx = cons_idx & ring->mask;
    if (likely(idx + n < ring->size)) {
        for (i = 0; i < (n & (~(unsigned)0x3)); i += 4, idx += 4) {
            _DPDK_LOCKLESS_RING_DEQUEUE(obj_table[i], ring->elts[idx]);
            _DPDK_LOCKLESS_RING_DEQUEUE(obj_table[i + 1], ring->elts[idx + 1]);
            _DPDK_LOCKLESS_RING_DEQUEUE(obj_table[i + 2], ring->elts[idx + 2]);
            _DPDK_LOCKLESS_RING_DEQUEUE(obj_table[i + 3], ring->elts[idx + 3]);
        }
        for (; i < n; i++, idx++) {
            _DPDK_LOCKLESS_RING_DEQUEUE(obj_table[i], ring->elts[idx]);
        }
    } else {
        for (i = 0; idx < ring->size; i++, idx++) {
            _DPDK_LOCKLESS_RING_DEQUEUE(obj_table[i], ring->elts[idx]);
        }
        for (idx = 0; i < n; i++, idx++) {
            _DPDK_LOCKLESS_RING_DEQUEUE(obj_table[i], ring->elts[idx]);
        }
    }
}

/**
 * enqueue n objects to ring.
 *
 * @param ring          target ring.
 * @param obj_table     source object table.
 * @param  n            number of objects to be enqueued.
 *
 * @return actual object count enqueued.
 */
static inline unsigned dpdk_lockless_ring_enqueue_burst(dpdk_lockless_ring * ring, void * const * obj_table, unsigned n)
{
    uint32_t success, i, prod_idx, cons_idx, next_idx, idx;

try_again:
    do {
        prod_idx = __atomic_load_n(&ring->prod_idx, __ATOMIC_ACQUIRE);
        cons_idx = __atomic_load_n(&ring->cons_idx, __ATOMIC_ACQUIRE);

        if (unlikely(ring->size == prod_idx - cons_idx)) {
            return 0;
        }

        for (i = 0; i < n; i++) {
            idx = (prod_idx + i) & ring->mask;
            if (unlikely(__atomic_load_n(&ring->elts[idx].state, __ATOMIC_ACQUIRE) != DPDK_LOCKLESS_RING_STATE_FREE)) {
                if (i) {
                    break;
                } else if (prod_idx != __atomic_load_n(&ring->prod_idx, __ATOMIC_ACQUIRE)) {
                    goto try_again;
                } else {
                    return 0;
                }
            }
        }
        next_idx = prod_idx + i;
        success = __atomic_compare_exchange(&ring->prod_idx, &prod_idx, &next_idx, true, __ATOMIC_ACQ_REL,
                                            __ATOMIC_RELAXED);
    } while (unlikely(success == 0));
    _dpdk_lockless_ring_enqueue_bulk(ring, prod_idx, obj_table, i);
    return i;
}

/**
 * enqueue n objects to ring.
 *
 * @param ring          target ring.
 * @param obj_table     source object table.
 * @param  n            number of objects to be enqueued.
 *
 * @return 0, or n successfully enqueued.
 */
static inline unsigned dpdk_lockless_ring_enqueue_bulk(dpdk_lockless_ring * ring, void * const * obj_table, unsigned n)
{
    uint32_t success, prod_idx, cons_idx, next_idx, idx;

try_again:
    do {
        prod_idx = __atomic_load_n(&ring->prod_idx, __ATOMIC_ACQUIRE);
        cons_idx = __atomic_load_n(&ring->cons_idx, __ATOMIC_ACQUIRE);

        if (unlikely((ring->size - (prod_idx - cons_idx)) < n)) {
            return 0;
        }

        for (uint32_t i = 0; i < n; i++) {
            idx = (prod_idx + i) & ring->mask;
            if (unlikely(__atomic_load_n(&ring->elts[idx].state, __ATOMIC_ACQUIRE) != DPDK_LOCKLESS_RING_STATE_FREE)) {
                if (__atomic_load_n(&ring->prod_idx, __ATOMIC_ACQUIRE) != prod_idx) {
                    goto try_again;
                } else {
                    return 0;
                }
            }
        }

        next_idx = prod_idx + n;
        success = __atomic_compare_exchange(&ring->prod_idx, &prod_idx, &next_idx, true, __ATOMIC_ACQ_REL,
                                            __ATOMIC_RELAXED);
    } while (unlikely(success == 0));
    _dpdk_lockless_ring_enqueue_bulk(ring, prod_idx, obj_table, n);
    return n;
}

/**
 * dequeue n objects from ring.
 *
 * @param ring          source ring.
 * @param obj_table     target object table.
 * @param n             max number of objects to be dequeued.
 *
 * @return number of objected successfully dequeued.
 */
static inline unsigned dpdk_lockless_ring_dequeue_burst(dpdk_lockless_ring * ring, void ** obj_table, unsigned n)
{
    uint32_t success, i, prod_idx, cons_idx, next_idx, idx;

try_again:
    do {
        prod_idx = __atomic_load_n(&ring->prod_idx, __ATOMIC_ACQUIRE);
        cons_idx = __atomic_load_n(&ring->cons_idx, __ATOMIC_ACQUIRE);

        if (unlikely(prod_idx == cons_idx)) {
            return 0;
        }

        for (i = 0; i < n; i++) {
            idx = (cons_idx + i) & ring->mask;
            if (unlikely(__atomic_load_n(&ring->elts[idx].state, __ATOMIC_ACQUIRE) != DPDK_LOCKLESS_RING_STATE_BUSY)) {
                if (i != 0) {
                    break;
                } else if (cons_idx != __atomic_load_n(&ring->cons_idx, __ATOMIC_ACQUIRE)) {
                    goto try_again;
                } else {
                    return 0;
                }
            }
        }

        next_idx = cons_idx + i;
        success = __atomic_compare_exchange(&ring->cons_idx, &cons_idx, &next_idx, true, __ATOMIC_ACQ_REL,
                                            __ATOMIC_RELAXED);
    } while (unlikely(success == 0));
    _dpdk_lockless_ring_dequeue_bulk(ring, cons_idx, obj_table, i);
    return i;
}

/**
 * dequeue n objects from ring.
 *
 * @param ring          source ring.
 * @param obj_table     target object table.
 * @param n             number of objects to be dequeued.
 *
 * @return 0 on failure, n on success.
 */
static inline unsigned dpdk_lockless_ring_dequeue_bulk(dpdk_lockless_ring * ring, void ** obj_table, unsigned n)
{
    uint32_t success, prod_idx, cons_idx, next_idx, idx;

try_again:
    do {
        prod_idx = __atomic_load_n(&ring->prod_idx, __ATOMIC_ACQUIRE);
        cons_idx = __atomic_load_n(&ring->cons_idx, __ATOMIC_ACQUIRE);

        if (unlikely(n > prod_idx - cons_idx)) {
            return 0;
        }

        for (uint32_t i = 0; i < n; i++) {
            idx = (cons_idx + i) & ring->mask;
            if (unlikely(__atomic_load_n(&ring->elts[idx].state, __ATOMIC_ACQUIRE) != DPDK_LOCKLESS_RING_STATE_BUSY)) {
                if (cons_idx != __atomic_load_n(&ring->cons_idx, __ATOMIC_ACQUIRE)) {
                    goto try_again;
                } else {
                    return 0;
                }
            }
        }

        next_idx = cons_idx + n;
        success = __atomic_compare_exchange(&ring->cons_idx, &cons_idx, &next_idx, true, __ATOMIC_ACQ_REL,
                                            __ATOMIC_RELAXED);
    } while (unlikely(success == 0));
    _dpdk_lockless_ring_dequeue_bulk(ring, cons_idx, obj_table, n);
    return n;
}

/**
 * enqueue an object to ring.
 *
 * @param ring  target ring.
 * @param obj   source object.
 *
 * @return 0 on success, -ENOBUFS on failure.
 */
static inline int dpdk_lockless_ring_enqueue(dpdk_lockless_ring * ring, void * obj)
{
    return dpdk_lockless_ring_enqueue_bulk(ring, &obj, 1) ? 0 : -ENOBUFS;
}

/**
 * dequeue an object from ring.
 *
 * @param ring  target ring.
 * @param obj_p source object.
 *
 * @return 0 on success, -ENOBUFS on failure.
 */
static inline int dpdk_lockless_ring_dequeue(dpdk_lockless_ring * ring, void ** obj_p)
{
    return dpdk_lockless_ring_dequeue_bulk(ring, obj_p, 1) ? 0 : -ENOBUFS;
}

/**
 * get current object count in ring.
 *
 * @param ring  lockless ring.
 *
 * @return object count.
 */
static inline unsigned dpdk_lockless_ring_get_count(const dpdk_lockless_ring * ring)
{
    uint32_t prod_idx = __atomic_load_n(&ring->prod_idx, __ATOMIC_RELAXED);
    uint32_t cons_idx = __atomic_load_n(&ring->cons_idx, __ATOMIC_RELAXED);
    return prod_idx - cons_idx;
}

/**
 * create lockless ring.
 *
 * @param name  ring name.
 * @param size  ring size.
 *
 * @return NULL on failure, ring on success.
 */
static dpdk_lockless_ring * dpdk_lockless_ring_alloc(const char * name, uint32_t size)
{
    char ring_name[RTE_MEMZONE_NAMESIZE] = { 0 };

    if (!rte_align32pow2(size)) {
        return NULL;
    }

    snprintf(ring_name, sizeof(ring_name), "LR_%s", name);
    const struct rte_memzone * mz_ring = rte_memzone_reserve(
        ring_name, sizeof(dpdk_lockless_ring) + sizeof(dpdk_lockless_ring_elt_t) * size, SOCKET_ID_ANY, 0);
    if (!mz_ring) {
        return NULL;
    }

    dpdk_lockless_ring * ring = (dpdk_lockless_ring *)mz_ring->addr;
    snprintf(ring->name, sizeof(ring->name), "%s", name);
    ring->size = size;
    ring->mask = size - 1;
    ring->mz = mz_ring;

    return ring;
}

/**
 * release a ring.
 *
 * @param ring lockless ring.
 */
static inline void dpdk_lockless_ring_free(dpdk_lockless_ring * ring)
{
    if (ring) {
        rte_memzone_free(ring->mz);
    }
}

//=======================================================================

void table_alloc(void)
{
    // 使用随机设备作为种子，生成一个高质量的随机数生成器
    std::random_device rd;
    std::mt19937 gen(rd());  // Mersenne Twister 19937 生成器
    std::uniform_int_distribution<int> dist(0, 1000000);  // 定义随机数范围

    // 生成 n 个随机数，并将它们存储在 obj_table 中
    for (int i = 0; i < NUM; ++i) {
        int random_value = dist(gen);  // 生成随机数
        g_obj_table[i] = (void*)(uintptr_t)random_value;  // 将随机数存储为指针
    }
}

static inline void alloc_ring(void)
{
   int ret = 0;
   char *argv_temp[] = {"./dd", "-c", "0x8", "-n", "4", "--proc-type","secondary", "--file-prefix","l2hi", "--base-virtaddr=0x2aaa2aa0000" };
   int argc_temp = sizeof(argv_temp)/sizeof(char *);
   
    ret = rte_eal_init(argc_temp, argv_temp);
	printf("rte_eal_init success\n");

/*
    g_test_ring = (dpdk_lockless_ring *)rte_malloc("test", sizeof(dpdk_lockless_ring), ALIGNMENT);
    if (!g_test_ring) {
        rte_free(g_test_ring);
        printf("dpdk_lockless_ring_alloc failed\n");
        return;
    }
	*/

    g_test_ring = dpdk_lockless_ring_alloc("NRT_to_RT_ring_test_mp_acq", EM_LOCKLESS_RING_SIZE);
	if (!g_test_ring) {
        
        printf("dpdk_lockless_ring_alloc failed\n");
        return;
    }
	table_alloc();
    
}


//test dpdk_lockless_ring_dequeue_burst
void BM_lockless(benchmark::State& state){
    for (auto _ : state) {
        benchmark::DoNotOptimize(dpdk_lockless_ring_dequeue_burst(g_test_ring, g_obj_table, NUM));
    }

}

//main function to run the benchmark
//BENCHMARK(BM_no_data_dependency)->DenseRange(1, 100);
//BENCHMARK(BM_lockless)->DenseRange(1, 100);
// 参数化基准测试，测试从 1 到 100 的不同范围
BENCHMARK(BM_lockless)->DenseRange(1, 20)->Threads(1);   // 单线程基准测试
BENCHMARK(BM_lockless)->DenseRange(1, 20)->Threads(2);   // 双线程基准测试
BENCHMARK(BM_lockless)->DenseRange(1, 20)->Threads(4);   // 四线程基准测试
BENCHMARK(BM_lockless)->DenseRange(1, 20)->Threads(8);   // 八线程基准测试


int main(int argc, char** argv) {
  benchmark::Initialize(&argc, argv);
  alloc_ring();
  benchmark::RunSpecifiedBenchmarks();
}