#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>

void add_arrays(float *a, float *b, float *c, int n) {
    int i;
    int simd_width = 8; // AVX 是 256 位，每次处理 8 个 float
    int simd_end = n - (n % simd_width); // 处理剩余元素的起始位置

    // 主循环：处理 8 个元素的块
    for (i = 0; i < simd_end; i += simd_width) {
        __m256 vec_a = _mm256_loadu_ps(&a[i]);
        __m256 vec_b = _mm256_loadu_ps(&b[i]);
        __m256 vec_c = _mm256_add_ps(vec_a, vec_b);
        _mm256_storeu_ps(&c[i], vec_c);
    }

    // 处理剩余元素
    for (; i < n; i++) {
        c[i] = a[i] + b[i];
    }
}

int main() {
    int n = 16000000;
    float *a = (float*) malloc(n * sizeof(float));
    float *b = (float*) malloc(n * sizeof(float));
    float *c = (float*) malloc(n * sizeof(float));

    for (int i = 0; i < n; i++) {
        a[i] = i * 1.0f;
        b[i] = i * 2.0f;
    }

    add_arrays(a, b, c, n);

    // 可选：打印结果的一部分来验证正确性
    for (int i = 0; i < 10; i++) {
        printf("%f\n", c[i]);
    }

    free(a);
    free(b);
    free(c);

    return 0;
}

