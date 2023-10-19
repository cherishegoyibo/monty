#include "monty.h"

/**
 * f_push - Add node to the stack
 * @new_node: top of stack
 * @line_counter: line number of opcode
 */
void f_push(stack_t **new_node, unsigned int line_counter)
{
	stack_t *tmp;
	(void)line_counter;

	if (head == NULL)
	{
		head = *new_node;
		return;
	}
	tmp = head;
	head = *new_node;
	head->next = tmp;
	tmp->prev = head;
}
/**
 * f_pall - print the stack
 * @stack: top of stack
 * @line_counter: line number of opcode
 */
void f_pall(stack_t **stack, unsigned int line_counter)
{
	stack_t *tmp;
	(void)line_counter;

	tmp = *stack;
	if (tmp == NULL)
		return;
	while (tmp != NULL)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
}
