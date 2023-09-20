#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info_struc: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info_struc)
{
	if (!info_struc->environ || info_struc->env_changed)
	{
		info_struc->environ = list_to_strings(info_struc->env);
		info_struc->env_changed = 0;
	}

	return (info_struc->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info_struc: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @str_var: the string env str_var property
 */
int _unsetenv(info_t *info_struc, char *str_var)
{
	list_t *node = info_struc->env;
	size_t x = 0;
	char *pp;

	if (!node || !str_var)
		return (0);

	while (node)
	{
		pp = starts_with(node->str, str_var);
		if (pp && *pp == '=')
		{
			info_struc->env_changed = delete_node_at_index(&(info_struc->env), x);
			x = 0;
			node = info_struc->env;
			continue;
		}
		node = node->next;
		x++;
	}
	return (info_struc->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info_struc: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @str_var: the string env str_var property
 * @val1: the string env str_var val1
 *  Return: Always 0
 */
int _setenv(info_t *info_struc, char *str_var, char *val1)
{
	char *buf = NULL;
	list_t *node;
	char *pp;

	if (!str_var || !val1)
		return (0);

	buf = malloc(_strlen(str_var) + _strlen(val1) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, str_var);
	_strcat(buf, "=");
	_strcat(buf, val1);
	node = info_struc->env;
	while (node)
	{
		pp = starts_with(node->str, str_var);
		if (pp && *pp == '=')
		{
			free(node->str);
			node->str = buf;
			info_struc->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info_struc->env), buf, 0);
	free(buf);
	info_struc->env_changed = 1;
	return (0);
}
