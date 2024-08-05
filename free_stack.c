#include "monty.h"

/**
 * free_stack - Frees a stack_t stack
 * @stack: Pointer to top of stack
 */
void free_stack(stack_t *stack)
{
	stack_t *current = stack;
	stack_t *next;

	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}
