#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head_addr: address of pointer to head_addr node
 * @str_node: str_node field of node
 * @num_index: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head_addr, const char *str_node, int num_index)
{
	list_t *new_head;

	if (!head_addr)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num_index = num_index;
	if (str_node)
	{
		new_head->str_node = _strdup(str_node);
		if (!new_head->str_node)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head_addr;
	*head_addr = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head_addr: address of pointer to head_addr node
 * @str_node: str_node field of node
 * @num_index: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head_addr, const char *str_node, int num_index)
{
	list_t *new_node, *node;

	if (!head_addr)
		return (NULL);

	node = *head_addr;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num_index = num_index;
	if (str_node)
	{
		new_node->str_node = _strdup(str_node);
		if (!new_node->str_node)
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
		*head_addr = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the str_node element of a list_t linked list
 * @n: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *n)
{
	size_t x = 0;

	while (n)
	{
		_puts(n->str_node ? n->str_node : "(nil)");
		_puts("\n");
		n = n->next;
		x++;
	}
	return (x);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head_addr: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head_addr, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int x = 0;

	if (!head_addr || !*head_addr)
		return (0);

	if (!index)
	{
		node = *head_addr;
		*head_addr = (*head_addr)->next;
		free(node->str_node);
		free(node);
		return (1);
	}
	node = *head_addr;
	while (node)
	{
		if (x == index)
		{
			prev_node->next = node->next;
			free(node->str_node);
			free(node);
			return (1);
		}
		x++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head_addr node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head_addr;

	if (!head_ptr || !*head_ptr)
		return;
	head_addr = *head_ptr;
	node = head_addr;
	while (node)
	{
		next_node = node->next;
		free(node->str_node);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
