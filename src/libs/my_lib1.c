#include "my_lib1.h"

// (1 + 1/x) ^ x
float e(int x) {
    return pow((1 + 1.0/(float)x), x);
}

void _swap(int *lhs, int *rhs) 
{
    int tmp = *lhs; 
    *lhs = *rhs; 
    *rhs = tmp; 
} 

// Пузырек
int* sort(int* array) {
    int n = array[0] ;
    for (int i = 1; i < n - 1; ++i) {
        for (int j = 1; j < n-i; ++j) {
            if (array[j] > array[j+1]) {
                _swap(&array[j], &array[j+1]);
            }
        }
    }
    return array;
}
