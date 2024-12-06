#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>

// 对齐内存分配
void* aligned_malloc(size_t size, size_t alignment) {
    void* ptr;
    if (posix_memalign(&ptr, alignment, size)) {
        return NULL; // Allocation failed
    }
    return ptr;
}

// 对齐内存释放
void aligned_free(void* ptr) {
    free(ptr);
}

void add_arrays(float *a, float *b, float *c, int n) {
    int i;
    int simd_width = 8; // AVX 是 256 位，每次处理 8 个 float
    int simd_end = n - (n % simd_width); // 处理剩余元素的起始位置

    // 主循环：处理 8 个元素的块
    for (i = 0; i < simd_end; i += simd_width) {
        __m256 vec_a = _mm256_load_ps(&a[i]); // 假设内存对齐
        __m256 vec_b = _mm256_load_ps(&b[i]); // 假设内存对齐
        __m256 vec_c = _mm256_add_ps(vec_a, vec_b);
        _mm256_store_ps(&c[i], vec_c);
    }

    // 处理剩余元素
    for (; i < n; i++) {
        c[i] = a[i] + b[i];
    }
}

int main() {
    int n = 16000000;
    float *a = (float*) aligned_malloc(n * sizeof(float), 32);
    float *b = (float*) aligned_malloc(n * sizeof(float), 32);
    float *c = (float*) aligned_malloc(n * sizeof(float), 32);

    if (a == NULL || b == NULL || c == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // 初始化数组
    for (int i = 0; i < n; i++) {
        a[i] = i * 1.0f;
        b[i] = i * 2.0f;
    }

    add_arrays(a, b, c, n);

    // 可选：打印结果的一部分来验证正确性
    for (int i = 0; i < 10; i++) {
        printf("%f\n", c[i]);
    }

    // 释放对齐内存
    aligned_free(a);
    aligned_free(b);
    aligned_free(c);

    return 0;
}

