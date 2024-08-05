#include "monty.h"

void push_wrapper(stack_t **stack, unsigned int line_number)
{
	push(stack, line_number, global_arg);
}
