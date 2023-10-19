#include "monty.h"
stack_t *head = NULL;

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: always 0
 */
int main(int argc, char *argv[])
{
	FILE *file;
	int line_number, format = 0;
	char *buffer_line = NULL;
	size_t len = 0;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	line_number = 0;
	while (getline(&buffer_line, &len, file) != -1)
	{
		format = tokenize(buffer_line, line_number, format);
		line_number++;
		free(buffer_line);
	}

	fclose(file);
	free_stack();
	return (0);
}
/**
 * free_stack - Frees a double linked list.
 * @head: head of the stack
 */
void free_stack(void)
{
	stack_t *tmp;

	if (head == NULL)
		return;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	head = NULL;
}
