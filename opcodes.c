#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * push - Pushes an element to the stack
 * @stack: Double pointer to top of stack
 * @line_number: Line number in the bytecode file
 * @arg: Argument to push into stack
 *
 * Description: Pushes an integer onto the stack
 * If argument is invalid, prints an error message and exits
 */
void push(stack_t **stack, unsigned int line_number, char *arg)
{
	stack_t *new_node; /* new node to be added to the stack */

	/* assume code to get argument from line_number */

	/* check if argument is valid */
	if (!arg || (atoi(arg) == 0 && strcmp(arg, "0") != 0))
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	/* allocate memory for the new node */
	new_node = malloc(sizeof(stack_t));
	if (!new_node)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	/* initialize new node */
	new_node->n = atoi(arg);
	new_node->next = *stack;
	new_node->prev = NULL;

	/* update previous top node */
	if (*stack)
		(*stack)->prev = new_node;

	/* set new node as top of stack */
	*stack = new_node;
}

/**
 * pall - Prints all the values on the stack
 * @stack: Double pointer to top of stack
 * @line_number: Line number in bytecode file
 *
 * Description: Prints all integers in the stack from top to bottom
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;
	
	(void)line_number; /* unused variable */

	/* traverse stack and print each element */
	while (current)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

/**
 * pint - Prints value at the top of stack
 * @stack: Double pointer to top of stack
 * @line_number: Line number in bytecode file
 *
 * Description: If the stack is empty, prints error message and exits
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (!stack || !*stack)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}

	printf("%d\n", (*stack)->n);
}
