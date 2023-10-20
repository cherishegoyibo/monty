#include "monty.h"
/**
 * f_pint - prints the value at the top of the stack
 * @stack: top of stack
 * @line_counter: line counter
 */
void f_pint(stack_t **stack, unsigned int line_counter)
{
	if (stack == NULL || *stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_counter);
		free_stack();
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}

/**
 * f_pop - removes the top element of the stack
 * @stack: Top of stack.
 * @line_counter: line counter
 */
void f_pop(stack_t **stack, unsigned int line_counter)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_counter);
		free_stack();
		exit(EXIT_FAILURE);
	}
	tmp = *stack;
	*stack = tmp->next;
	if (*stack != NULL)
		(*stack)->prev = NULL;
	free(tmp);
}
