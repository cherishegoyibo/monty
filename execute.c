#include "monty.h"
/**
 * execute - executes opcode
 * @function: the opcode
 * @opcode: string opcode
 * @value: string value
 * @line_counter: line
 * @format: Format specifier
 */
void execute(op_func function, char *opcode, char *value, int line_counter, int format)
{
	stack_t *node;
	int flag;
	int i;

	flag = 1;
	if (strcmp(opcode, "push") == 0)
	{
		if (value != NULL && value[0] == '-')
		{
			value = value + 1;
			flag = -1;
		}
		if (value == NULL)
			fprintf(stderr, "L%d: usage: push integer\n", line_counter);

		for (i = 0; value[i] != '\0'; i++)
		{
			if (isdigit(value[i]) == 0)
			{
				fprintf(stderr, "L%d: usage: push integer\n", line_counter);
			}
		}
		node = new_node(atoi(value) * flag);
		if (format == 0)
			function(&node, line_counter);
		if (format == 1)
			add_queue(&node, line_counter);
	}
	else
		function(&head, line_counter);
}
/**
 * get_function - get opcode function
 * @opcode: opcode
 * @value: argument passed
 * @format:  storage format
 * @line_counter: line counter
 * Return: void
 */
void get_function(char *opcode, char *value, int line_counter, int format)
{
	int i;
	int flag;

	instruction_t ops_list[] = {
		{"push", f_push},
		{"pall", f_pall},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	flag = 1;
	i = 0;
	while (ops_list[i].opcode != NULL)
	{
		if (strcmp(opcode, ops_list[i].opcode) == 0)
		{
			execute(ops_list[i].f, opcode, value, line_counter, format);
			flag = 0;
		}
		i++;
	}
	if (flag == 1)
		fprintf(stderr, "L%d: unknown instruction %s\n", line_counter, opcode);
}
/**
 * tokenize - tokenizes argument using delimiter
 * @buffer_line: line from the file
 * @line_number: line number
 * @format:  storage format
 * Return: Returns 0 if opcode is stack. 1 if queue
 */
int tokenize(char *buffer_line, int line_number, int format)
{
	char *opcode, *value;
	const char *delim = "\t\n ";

	if (buffer_line == NULL)
		fprintf(stderr, "Error: malloc failed\n");

	opcode = strtok(buffer_line, delim);
	if (opcode == NULL)
		return (format);
	value = strtok(NULL, delim);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	get_function(opcode, value, line_number, format);
	return (format);
}
/**
 * new_node - Create a new node
 * @n: node to add
 * Return: pointer to the node, else NULL
 */
stack_t *new_node(int n)
{
	stack_t *node;

	node = malloc(sizeof(stack_t));
	if (node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
	}
	node->next = NULL;
	node->prev = NULL;
	node->n = n;
	return (node);
}
/**
 * add_queue - Add node to queue
 * @new_node: node to add
 * @line_number: line number
 */
void add_queue(stack_t **new_node, unsigned int line_number)
{
	stack_t *tmp;
	(void)line_number;

	if (new_node == NULL || *new_node == NULL)
	{
		fprintf(stderr, "Error: invalid new_node\n");
		exit(EXIT_FAILURE);
	}
	if (head == NULL)
	{
		head = *new_node;
		return;
	}
	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = *new_node;
	(*new_node)->prev = tmp;

}
