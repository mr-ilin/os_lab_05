#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include <dlfcn.h>

#define ERR_INV_INT 21
#define ERR_INV_ARGS 22

#define ERR_DL_CLOSE 30
#define ERR_DL_OPEN  31
#define ERR_DL_SYM 32

static const char* DL1 = "libtools1.so";
static const char* DL2 = "libtools2.so";

int dls_open(void** dl1_handle, void** dl2_handle) {
    *dl1_handle = dlopen(DL1, RTLD_LAZY);
    if (!*dl1_handle) {
        perror(dlerror());
        exit(ERR_DL_OPEN);
    }

    *dl2_handle = dlopen(DL2, RTLD_LAZY);
    if (!*dl2_handle) {
        perror(dlerror());
        exit(ERR_DL_OPEN);
    }

    return 0;
}

int dls_close(void** dl1_handle, void** dl2_handle) {
    int to_return = 0;
    
    if (dlclose(*dl1_handle) != 0) {
        perror(dlerror());
        to_return = ERR_DL_CLOSE;
    }
    if (dlclose(*dl2_handle) != 0) {
        perror(dlerror());
        to_return = ERR_DL_CLOSE;
    }
    if (to_return != 0) {
        exit(to_return);
    }
    return to_return;
}

int main() {
    void* dl1_handle = NULL;
    void* dl2_handle = NULL;
    char* error = NULL;

    dls_open(&dl1_handle, &dl2_handle);

    int (*read_strings)(char***, size_t*);
    read_strings = (int (*)(char***, size_t*))dlsym(dl1_handle, "read_strings");
    error = dlerror();
    if (error != NULL)  {
        perror(error);
        return ERR_DL_SYM;
    }
    void (*str_array_to_int)(char**, int*, size_t);
    str_array_to_int = (void (*)(char**, int*, size_t))dlsym(dl1_handle, "str_array_to_int");
    error = dlerror();
    if (error != NULL)  {
        perror(error);
        return ERR_DL_SYM;
    }
    float (*e)(int);
    e  = (float (*)(int))dlsym(dl1_handle, "e");
    error = dlerror();
    if (error != NULL)  {
        perror(error);
        return ERR_DL_SYM;
    }
    int* (*sort)(int*);
    sort = (int* (*)(int*))dlsym(dl1_handle, "sort");
    error = dlerror();
    if (error != NULL)  {
        perror(error);
        return ERR_DL_SYM;
    }

    int res_scanf = 1;
    char** strs = NULL;
    size_t size = 0;
    int dl_num = 1;
    printf("=== Using %s ===\n", DL1);

    while (res_scanf != EOF) {
        printf("Enter commad\n");
        res_scanf = (*read_strings)(&strs, &size); //DL1
        char* cmd = strs[0];

        if (!strcmp(cmd, "0")) {

            if (dl_num == 1) {
                e  = (float (*)(int))dlsym(dl2_handle, "e");
                error = dlerror();
                if (error != NULL)  {
                    perror(error);
                    return ERR_DL_SYM;
                }
                sort = (int* (*)(int*))dlsym(dl2_handle, "sort");
                error = dlerror();
                if (error != NULL)  {
                    perror(error);
                    return ERR_DL_SYM;
                }
                dl_num = 2;
                printf("=== Switched to %s ===\n", DL2);
            } else {
                e  = (float (*)(int))dlsym(dl1_handle, "e");
                error = dlerror();
                if (error != NULL)  {
                    perror(error);
                    return ERR_DL_SYM;
                }
                sort = (int* (*)(int*))dlsym(dl1_handle, "sort");
                error = dlerror();
                if (error != NULL)  {
                    perror(error);
                    return ERR_DL_SYM;
                }
                dl_num = 1;
                printf("=== Switched to %s ===\n", DL1);
            }

        } else if (!strcmp(cmd, "1")) {

            if (size > 2) {
                perror("Error: invalid args number\n");
                exit(ERR_INV_ARGS);
            }
            char* endptr = NULL;
            int num = strtoimax(strs[1], &endptr, 10);
            if (strcmp(endptr, "")) {
                printf("Error: invalid int value = %s\n", strs[1]);
                exit(ERR_INV_INT);
            }
            printf("e = %f\n", (*e)(num));

        } else if (!strcmp(cmd, "2")) {

            int nums[size];
            nums[0] = size;
            (*str_array_to_int)(&strs[1], &nums[1], size-1); // DL1
            (*sort)(nums);

            printf("arrray = {");
            for (size_t i = 1; i < size; i++) {
                printf("%d ", nums[i]);
            }
            printf("}\n");

        } else if (res_scanf != EOF) {
            printf("Invalid cmd: \"%s\"\n", cmd);
        }
    }

    return 0;
}
