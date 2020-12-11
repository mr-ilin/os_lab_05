#include "my_lib2.h"
#include "stack.h"

long long _fact(int x) {
    long long to_return = 1;
    for (int i = 1; i <= x; ++i) {
        to_return *= i;
    }
    return to_return;
}

// - Сумма ряда по n от 0 до x, где элементы ряда равны: (1/(n!))
float e(int x) {
    float to_return = 0;
    for (int n = 0; n < x; ++n) {
        to_return += ( (float)1 / _fact(n) );
    }
    return to_return;
}

void _swap(int *lhs, int *rhs) 
{
    int tmp = *lhs; 
    *lhs = *rhs; 
    *rhs = tmp; 
} 

int _pick_pivot(int* a, int n)
{
	//медиана из первого, последнего и серединного элементов, если элементов < 3 — береться последний
	if (n <= 2)
		return a[n-1];

	int x = a[0];
	int y = a[(n-1)/2];
	int z = a[n-1];

	if ((x - y) * (z - x) >= 0) // (x >= y && x <= z) || (x <= y && x >= z)       
    	return x;
	else if ((y - x) * (z - y) >= 0) // (y >= x && y <= z) || (y <= x && y >= z)   
    	return y;
	else
		return z;
}

// Сортировка Хоара
int* sort(int* array) {
    int* a = &array[1];
    int n = array[0] - 1;
    stack s;
	s_init(&s);
	_arr ar = {a, n};
	s_push(&s, ar);

	while (!s_is_empty(&s)) {
		ar = s_pop(&s);
		a = ar.array;
		n = ar.n;

		if (n < 2)
			continue;

		int i = 0;
        int j = n - 1;
		double pivot = _pick_pivot(a, n); 

		do {
            while (a[i] < pivot)
                i++;
            while (a[j] > pivot)
                j--;

            if (i <= j) {
                if (a[i] > a[j])
                    _swap(&a[i], &a[j]);
                i++;
                j--;
            }
        } while (i <= j);

		ar.array = a;
		ar.n = j + 1;
		s_push(&s, ar);

		ar.array = a + i;
		ar.n = n - i;
		s_push(&s, ar);
	}
	s_destroy(&s);
    return array;
}
