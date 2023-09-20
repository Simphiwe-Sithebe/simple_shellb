#include "shell.h"
/**
 * list_len - determines length of linked list
 * @m: pointer to first list_node
 * Return: size of list
 */
size_t list_len(const list_t *m)
{
	size_t i = 0;

	while (m)
	{
		m = m->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head_node: pointer to first list_node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head_node)
{
	list_t *list_node = head_node;
	size_t i = list_len(head_node), j;
	char **str1;
	char *str;

	if (!head_node || !i)
		return (NULL);
	str1 = malloc(sizeof(char *) * (i + 1));
	if (!str1)
		return (NULL);
	for (i = 0; list_node; list_node = list_node->next, i++)
	{
		str = malloc(_strlen(list_node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(str1[j]);
			free(str1);
			return (NULL);
		}

		str = _strcpy(str, list_node->str);
		str1[i] = str;
	}
	str1[i] = NULL;
	return (str1);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @m: pointer to first list_node
 *
 * Return: size of list
 */
size_t print_list(const list_t *m)
{
	size_t i = 0;

	while (m)
	{
		_puts(convert_number(m->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(m->str ? m->str : "(nil)");
		_puts("\n");
		m = m->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - returns list_node whose string starts with prefix_
 * @list_node: pointer to list list_node
 * @prefix_: string to match
 * @cc: the next character after prefix_ to match
 *
 * Return: match list_node or null
 */
list_t *node_starts_with(list_t *list_node, char *prefix_, char cc)
{
	char *p = NULL;

	while (list_node)
	{
		p = starts_with(list_node->str, prefix_);
		if (p && ((cc == -1) || (*p == cc)))
			return (list_node);
		list_node = list_node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a list_node
 * @head_node: pointer to list head_node
 * @list_node: pointer to the list_node
 *
 * Return: index of list_node or -1
 */
ssize_t get_node_index(list_t *head_node, list_t *list_node)
{
	size_t i = 0;

	while (head_node)
	{
		if (head_node == list_node)
			return (i);
		head_node = head_node->next;
		i++;
	}
	return (-1);
}
