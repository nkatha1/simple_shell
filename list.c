#include "shell.h"

/**
 * free_l - frees nodes of a list
 * @headptr: pointer to pointer to list_t
 */
void free_l(list_t **headptr)
{
	list_t *node, *next_node, *head;

	if (!headptr || !*headptr)
		return;
	head = *headptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*headptr = NULL;
}

/**
 * print_str_list - prints elements of a linked list
 * @n: pointer to list_t
 *
 * Return: size_t
 */
size_t print_str_list(const list_t *n)
{
	size_t j;

	j = 0;
	while (n != NULL)
	{
		_puts(n->str ? n->str : "(nil)");
		_puts("\n");
		n = n->next;
		j++;
	}
	return (j);
}

/**
 * add_node - Add a node at the start of a list
 * @head: Pointer to pointer to list_t
 * @str: pointer to constant char
 * @n: Index node
 *
 * Return: list_t
 */
list_t *add_node(list_t **head, const char *str, int n)
{
	list_t *newhead;

	if (head == NULL)
		return (NULL);
	newhead = malloc(sizeof(list_t));
	if (newhead == NULL)
		return (NULL);

	set_mem((void *)newhead, 0, sizeof(list_t));
	newhead->num = n;
	if (str)
	{
		newhead->str = str_dup(str);
		if (!newhead->str)
		{
			free(newhead);
			return (NULL);
		}
	}
	newhead->next = *head;
	*head = newhead;
	return (newhead);
}

/**
 * delete_node - At a given index, it deletes a node
 * @head: First node pointer address
 * @index: Node index to delete
 *
 * Return: int
 */
int delete_node(list_t **head, unsigned int index)
{
	unsigned int n;
	list_t *node, *prev_node;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}

	n = 0;
	node = *head;
	while (node != NULL)
	{
		if (n == index)
		{
			prev_node->next = node->next;
			free(node);
			free(node->str);
			return (1);
		}
		n++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * add_endnode - adds a node To the end of a list
 * @head: Head node pointer adress
 * @f: Field node's string
 * @n : Index node used by history
 *
 * Return: list_t
 */
list_t *add_endnode(list_t **head, const char *str, int n)
{
	list_t *newnode;
	list_t *node;

	if (!head)
		return (NULL);

	node = *head;
	newnode = malloc(sizeof(list_t));
	if (!newnode)
		return (NULL);

	set_mem((void *)newnode, 0, sizeof(list_t));
	newnode->num = n;

	newnode->str;
	set_mem((void *)newnode, 0, sizeof(list_t));
	newnode->num = n;
	if (str)
	{
		newnode->str = str_dup(str);
		if (!newnode->str)
		{
			free(newnode);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newnode;
	}
	else
		*head = newnode;

	newnode->next = NULL;
	return (newnode);
}
