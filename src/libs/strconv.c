#include "strconv.h"

int read_strings(char*** ptr_buffer, size_t* res_size) { // Считывает строки через пробел до конца ввода
    char c; // Текущий считываемый символ
    int str_idx = 0; // Индекс текущего слова
    size_t buffer_size = 1; // Кол-во строк
    char** buffer = malloc(sizeof(char*) * buffer_size);
    if (!buffer) {
        perror("Malloc error");
        exit(ERR_MALLOC);
    }
    int* lengths = malloc(sizeof(int) * buffer_size);
    if (!lengths) {
        perror("Malloc error");
        exit(ERR_MALLOC);
    }

    lengths[0] = 0;
    int str_size = 1; // Длина текущей строки
    buffer[0] = malloc(sizeof(char) * str_size);
    if (!buffer[0]) {
        perror("Malloc error");
        exit(ERR_MALLOC);
    }
    
    //size_t read_bytes = 0;
    //while ((read_bytes = read(fd, &c, sizeof(char))) > 0) {
    bool is_start = true;
    int res_scanf;
    while ((res_scanf = scanf("%c", &c)) == 1) {
        // if ((read_bytes != sizeof(char)) && (read_bytes != 0)) {
        //     perror("Read error");
        //     exit(ERR_READ);
        // }

        if (c == '\n') { // Конец ввода слов
            break;
        }
        if (c == ' ') { // Следующее слово
            if (is_start) {
                continue;
            }
            ++str_idx;
            str_size = 1;
            continue;
        }
        is_start = false;

        // Увеличиваем буфер строк и длин
        if (str_idx >= buffer_size) {
            //printf("Increasing buffer\n");
            ++buffer_size;
            str_size = 1;

            buffer = realloc(buffer, sizeof(char*) * buffer_size);
            if (!buffer) {
                perror("Realloc error");
                exit(ERR_REALLOC);
            }

            buffer[buffer_size - 1] = malloc(sizeof(char) * str_size);
            if (!buffer[buffer_size - 1]) {
                perror("Malloc error");
                exit(ERR_MALLOC);
            }
            for (size_t i = 0; i < str_size; ++i) {
                buffer[buffer_size - 1][i] = 0;
            }

            lengths = realloc(lengths, sizeof(int) * buffer_size);
            if (!lengths) {
                perror("Realloc error");
                exit(ERR_REALLOC);
            }
            lengths[buffer_size - 1] = 0;
        }

        // Увеличиваем длину строки
        if (lengths[str_idx] == str_size) {
            //printf("Increasing str len\n");
            str_size += 16;
            buffer[str_idx] = realloc(buffer[str_idx], sizeof(char) * str_size);
            if (!buffer[str_idx]) {
                perror("Realloc error");
                exit(ERR_REALLOC);
            }
        }
        
        buffer[str_idx][lengths[str_idx]] = c;
        ++lengths[str_idx];

        // printf(">>> Read '%c'\n", c);
        // printf("buffer[str_idx] = %s\n", buffer[str_idx]);
        // printf("str_idx = %d\n", str_idx);
        // printf("buffer_size = %zu\n", buffer_size);
        // printf("str_size = %d\n", str_size);
        // printf("length[str_idx] = %d\n",lengths[str_idx]);
    }

    for (int i = 0; i < buffer_size; ++i) {
        buffer[i] = realloc(buffer[i], sizeof(char) * lengths[i]);
        if (!buffer[i]) {
            perror("Realloc error");
            exit(ERR_REALLOC);
        }
        buffer[i][lengths[i]] = '\0';
    }
    *res_size = buffer_size;
    *ptr_buffer = buffer;

    // printf("Result from read_strings func:\n");
    // for (int i = 0; i < *res_size; ++i) {
    //     printf("%d) \"%s\"\n", i, buffer[i]);
    // }
    return res_scanf;
}

void str_array_to_int(char** strs, int nums[], size_t n) { // Преобразует массив строк в массив int'ов
    for (size_t i = 0; i < n; ++i) {
        ///nums[i] = atoi(strs[i]);
        char* p = strs[i];
        bool is_negative = false;
        int result = 0;
        while(*p != '\0') {
            if (*p == '-' || *p == '+') {
                if (p != strs[i]) {
                    perror("Invalid int");
                    exit(ERR_INV_INT);
                }
                if (*p == '-') {
                    is_negative = true;
                }
            } else if ('0' <= *p && *p <= '9') {
                result = result * 10 + (*p - '0');
            } else {
                perror("Invalid int");
                exit(ERR_INV_INT);
            }
            ++p;
        }
        if (is_negative) {
            result *= -1;
        }
        nums[i] = result;
    }
}
