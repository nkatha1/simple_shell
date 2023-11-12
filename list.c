#include "shell.h"

/**
 * free_list - All nodes of a list, it frees them.
 * @head_ptr: Pointer adress to thr head node.
 *
 * Return: It is void.
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head ptr = NULL;
}

/**
 * print_list_str -  Only the elements of a list_t linked list it prints them
 * @h: The first node's pointer
 *
 * Return: The list size
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * add_node - At the start of a list, it adds a node
 * @head: Pointer adress to thr head node
 * @ft: Field of node string
 * @num: Index node used by history
 *
 * Return: The list size
 */
list_t *add_node(list_t **head, const char *ft, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->ft=_strdup(ft);
		if (!new_head->ft)
		{
			free(new_head);
			return(NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * delete_node_at_index - At a given index, it deletes a node
 * @head: First node pointer adress
 * @index: Node index to delete
 *
 * Return: On success 1, on failure 0
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

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
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node);
			free(node->str);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * add_node_end - To the end of a list, it adds a node
 * @head: Head node pointer adress
 * @ft: Field node's string
 * @num : Index node used by history
 *
 * Return: The list size
 */
list_t *add_node_end(list_t **head, const char *ft, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str;
		_memset((void *)new_node, 0, sizeof(list_t));
		new_node->num = num;
		if (str)
		{
			new_node->str = _strdup(str);
			if (!new_node->str)
			{
				free(new_node);
				return (NULL);
			}
		}
		if (node)
		{
			while (node->next)
				node = node->next;
			node->next = new_node;
		}
		else
			*heda = new_node;
		return (new_node);
	}
}


	
				


