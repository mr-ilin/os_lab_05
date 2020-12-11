#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include <dlfcn.h>

#include "./libs/my_lib1.h"
#include "./libs/strconv.h"

#define ERR_INV_ARGS 22

int main() {
    int res_scanf = 1;
    char** strs = NULL;
    size_t size = 0;

    while (res_scanf != EOF) {
        printf("Enter commad\n");
        res_scanf = read_strings(&strs, &size); //DL1
        char* cmd = strs[0];

        if (!strcmp(cmd, "1")) {

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
            printf("e = %f\n", e(num));

        } else if (!strcmp(cmd, "2")) {

            int nums[size];
            nums[0] = size;
            str_array_to_int(&strs[1], &nums[1], size-1); // DL1
            sort(nums);

            printf("arrray = {");
            for (size_t i = 1; i < size; i++) {
                printf("%d, ", nums[i]);
            }
            printf("}\n");

        } else if (res_scanf != EOF) {
            printf("Invalid cmd: \"%s\"\n", cmd);
        }
    }

    return 0;
}
