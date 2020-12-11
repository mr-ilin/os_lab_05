#include "stack.h"

void s_init(stack* s)
{
	s->head = NULL;
}

void s_destroy(stack* s)
{
	while(!s_is_empty(s))
	{
		s_pop(s);
	}
}

bool s_is_empty(stack* s)
{
	return s->head == NULL;
}

bool s_push(stack* s, _arr val)
{
	stack_el *element = (stack_el*)malloc(sizeof(stack_el));
	if (element == NULL)
	{
		return false;
	}
	
	element->next = s->head;
	element->val = val;
	s->head = element;
	return true;
}

_arr s_pop(stack* s)
{
	stack_el* e = s->head;
	_arr v = e->val;
	s->head = e->next;
	free(e);
	return v;
}
