#include <stdio.h>
#include <dlfcn.h>

int main() {
    // 加载共享库
    void *handle = dlopen("/opt/nokia/lib64/RT/libCCS_static.so.1.0.8", RTLD_LAZY);
    //void *handle = dlopen("/usr/lib64/libcommonio.so.1.35.0", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error loading library: %s\n", dlerror());
        return 1;
    }

    // 清除任何现有的错误
    dlerror();

    // 查找符号
    void (*em_ext_pktio_pre_init)() = dlsym(handle, "em_ext_pktio_pre_init");
    char *error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "Error finding symbol: %s\n", error);
        dlclose(handle);
        return 1;
    }

    printf("Symbol em_ext_pktio_pre_init found at address: %p\n", (void *)em_ext_pktio_pre_init);

    // 关闭共享库
    dlclose(handle);
    return 0;
}

