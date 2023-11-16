#include "shell.h"
/**
 * print_list - prints element of a linked list.
 * @f: pointer to list_t node
 *
 * Return: list size
 */
size_t print_list(const list_t *f)
{
	size_t n;

	n = 0;
	while (f != NULL)
	{
		_puts(convert_num(f->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(f->str ? f->str : "(nil)");
		_puts("\n");
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
char  **string_list(list_t *head)
{
	size_t j;
	size_t n = listlen(head);
	list_t *node = head;
	char **str;
	char *c;

	if (!n || !head)
		return (NULL);

	str = malloc(sizeof(char *) * (n + 1));
	if (!str)
		return (NULL);
	for (n = 0; node; node = node->next, n++)
	{
		c = malloc(str_len(node->str) + 1);
		if (!c)
		{
			for (j = 0; j < n; j++)
				free(str[j]);
			free(str);
			return (NULL);
		}
		c = str_cpy(c, node->str);
		str[n] = c;
	}
	str[n] = NULL;
	return (str);
}

/**
 * get_node - gets the index of a node
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
 * @f: pointer to node
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
 * node_start - returns node whose string starts with a pointer
 * @node: pointer to list_t
 * @s: pointer to string
 * @d: next character
 *
 * Return: list_t
 */
list_t *node_start(list_t *node, char *s, char d)
{
	char *c = NULL;

	while (node != NULL)
	{
		c = start_with(node->str, s);
		if (c && ((d == -1 || *c == d)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
