#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * struct_stack_s - Doubly linked list representation of a stack (or queue)
 * @n: Integer
 * @prev: Points to the previous element of the stack (or queue)
 * @next: Points to the next element of the stack (or queue)
 *
 * Description: Doubly linked list node structure for stacks,
 * queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - Opcode and its function
 * @opcode: The opcode
 * @f: Function to handle the opcode
 *
 * Description: Opcode and its function for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/**
 * instruction_with_arg_s - Opcode and its function with argument
 * @opcode: The opcode
 * @f: Function to handle opcode with additional argument
 *
 * Description: Used to map opcodes to their corresponding functions
 * that require an additional argument. Specifically for opcodes like
 * "push" that need an extra argument to operate.
 */
typedef struct instruction_with_arg_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number, char *arg);
} instruction_with_arg_t;

void push(stack_t **stack, unsigned int line_number, char *arg);
void pall(stack_t **stack, unsigned int line_number);

void execute_instruction(char *opcode, char *arg, stack_t **stack, unsigned int line_number);
void free_stack(stack_t *stack);

#endif
