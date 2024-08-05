#include "monty.h"

/**
 * execute_instruction - Executes a given opcode with its argument
 * @opcode: Opcode to execute
 * @arg: Argument for opcode (if any)
 * @stack: Pointer to the stack
 * @line_number: Current line number in bytecode file
 *
 * Description: Matches the opcode with corresponding function & executes it,
 * if opcode is unknown, prints error message & exits
 */
void execute_instruction(char *opcode, char *arg, stack_t **stack,
unsigned int line_number)
{
	int i; /* loop counter */
	/* store argument globally for use in push_wrapper */
	global_arg = arg;

	instruction_t instructions[] = {
		{"push", push_wrapper},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"nop", nop}
		{NULL, NULL}
	};

	for (i = 0; instructions[i].opcode; i++)
	{
		if (strcmp(instructions[i].opcode, opcode) == 0)
		{
			/* call function without arg if not needed */
			instructions[i].f(stack, line_number);
			return;
		}
	}

	/* print error if opcode unknown and exit */
	fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
	exit(EXIT_FAILURE);
}

/**
 * main - Entry point of Monty interpreter
 * @argc: Number of command line arguments
 * @argv: Array of command line arguments
 *
 * Description: Opens the bytecode file, reads it line by line, and 
 * executes each instruction
 * Handles errors related to file opening and argument count
 *
 * Return: Always 0 (success)
 */
int main(int argc, char **argv)
{
	FILE *file; /* file pointer for the bytecode file */
	char *line = NULL; /* buffer for reading lines */
	size_t len = 0; /* length of buffer */
	ssize_t read; /* number of characters read */
	unsigned int line_number = 0; /*line number in bytecode file */
	stack_t *stack = NULL; /* pointer to stack */
	char *opcode; /* pointer to opcode */
	char *arg; /* pointer to argument */

	if (argc != 2) /* check if exactly one argument provided */
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r"); /* open file for reading */
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, file)) != -1) /* read line by line */
	{
		line_number++; /* increment line number */
		opcode = strtok(line, " \t\n"); /* extract opcode */
		arg = strtok(NULL, " \t\n"); /* extract argument */

		if (opcode && opcode[0] != '#') /* ignore comments */
			execute_instruction(opcode, arg, &stack, line_number);
	}

	free(line); /* free allocated memory */
	fclose(file); /* close file */
	free_stack(stack);
	return (0); 
}
