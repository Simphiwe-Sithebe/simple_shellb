#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info_P: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info_P)
{
	print_list(info_P->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info_P: parameter struct
 * @str_prov: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info_P, char *str_prov)
{
	char *p1, c1;
	int returnedd;

	p1 = _strchr(str_prov, '=');
	if (!p1)
		return (1);
	c1 = *p1;
	*p1 = 0;
	returnedd = delete_node_at_index(&(info_P->alias),
		get_node_index(info_P->alias, node_starts_with(info_P->alias, str_prov, -1)));
	*p1 = c1;
	return (returnedd);
}

/**
 * set_alias - sets alias to string
 * @info_P: parameter struct
 * @str_prov: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info_P, char *str_prov)
{
	char *p1;

	p1 = _strchr(str_prov, '=');
	if (!p1)
		return (1);
	if (!*++p1)
		return (unset_alias(info_P, str_prov));

	unset_alias(info_P, str_prov);
	return (add_node_end(&(info_P->alias), str_prov, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @nodeN1: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *nodeN1)
{
	char *p1 = NULL, *aa = NULL;

	if (nodeN1)
	{
		p1 = _strchr(nodeN1->str_prov, '=');
		for (aa = nodeN1->str_prov; aa <= p1; aa++)
			_putchar(*aa);
		_putchar('\'');
		_puts(p1 + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info_P: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info_P)
{
	int x = 0;
	char *p1 = NULL;
	list_t *nodeN1 = NULL;

	if (info_P->argc == 1)
	{
		nodeN1 = info_P->alias;
		while (nodeN1)
		{
			print_alias(nodeN1);
			nodeN1 = nodeN1->next;
		}
		return (0);
	}
	for (x = 1; info_P->argv[x]; x++)
	{
		p1 = _strchr(info_P->argv[x], '=');
		if (p1)
			set_alias(info_P, info_P->argv[x]);
		else
			print_alias(node_starts_with(info_P->alias, info_P->argv[x], '='));
	}

	return (0);
}
