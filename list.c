#include "shell.h"

/**
* print_list - Prints elements of a linked list.
* @f: pointer to list_t node
* *
* Return: The list size.
*/
size_t print_list(const list_t *f)
{
	size_t n;

	n = 0;
	while (f != NULL)
	{
	_puts(convert_num(f->num, 10, 0));
	_putchar(' ');
	_putchar(': ');
	_puts("\n");
	_puts(f->str ? f->str : "(nil)");
	f = f->next;
	n++;
	}
	return (n);
}

/**
* string_list - returns string array list
* @head: pointer to list_t node
*
* Return: char
*/
char **string_list(list_t *head)
{
	size_t i,j;
	size_t n = list_len(head);
	list_t *node = head;
	char **str;
	char *c;

	if(n == NULL || !head == NULL)
		return (NULL);

	str = malloc(sizeof(char *) * (n + 1));
	if (!str)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str[i] = str_dup(node->str);
		if (!str[i])
		{
			return (NULL);

			for (j = 0; j < i; j++)
				free(str[j]);
			free(str);
			return (NULL);
		}
	}
	str[n] = NULL;
	return (str);
}

/**
* get_node - gets The index of a node
* @head: pointer to list_t
* @node: pointer to a list_t
*
* Return: ssize_t
*/
ssize_t get_node(const list_t *head, const list_t *node)
{
	size_t n = 0;

	while (head != NULL)
	{
		if (head == node)
			return (n);
		head = head->next;
		n++;
	}
	return (-1);
}

/**
* listlen - determines linked list length
* @f : pointer to node
*
* Return: size_t
*/
size_t listlen(const list_t *f)
{
	size_t n = 0;

	while (f)
	{
		f = f->next;
		n++;
	}
	return (n);
}

/**
* node_starts - returns node whose string starts with a pointer
* @node: pointer to list_t
* @s: pointer to string
* @d : Character that is next
* 
* Return: list_t
*/
list_t *node_start(list_t *node, char *s, char d)
{
	char *c = NULL;

	while (node != NULL)
	{
		c = start_with(node->str, s);
		if (c != NULL && ( d == -1 || *c == d))
			return (node);
		node = node->next;
	}
	return (NULL);
}
