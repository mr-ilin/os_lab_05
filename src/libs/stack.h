#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct stack stack;
typedef struct stack_el stack_el;
typedef struct _arr _arr;

struct _arr
{
    int* array;
    int n;
};

struct stack_el
{
	_arr val;
	stack_el* next;
};

struct stack
{
	stack_el* head;
};

void s_init(stack* s);
void s_destroy(stack* s);
bool s_is_empty(stack* s);
_arr s_pop(stack* s);
bool s_push(stack* s, _arr val);
