#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

#define ERR_MALLOC 3
#define ERR_REALLOC 4
#define ERR_READ 5
#define ERR_WRITE 6
#define ERR_INV_INT 21

int read_strings(char*** ptr_buffer, size_t* res_size); // Считывает строки через пробел до конца ввода
void str_array_to_int(char** strs, int nums[], size_t n); // Преобразует массив строк в массив int'ов
