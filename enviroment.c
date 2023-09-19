#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info_pa: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info_pa)
{
	print_list_str(info_pa->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info_pa: Structure containing potential arguments. Used to maintain
 *			 constant function prototype.
 * @env_name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *info_pa, const char *env_name)
{
	list_t *node = info_pa->env;
	char *pp;

	while (node)
	{
		pp = starts_with(node->str, env_name);
		if (pp && *pp)
			return (pp);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info_pa: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info_pa)
{
	if (info_pa->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info_pa, info_pa->argv[1], info_pa->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info_pa: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t *info_pa)
{
	int x;

	if (info_pa->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (x = 1; x <= info_pa->argc; x++)
		_unsetenv(info_pa, info_pa->argv[x]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info_pa: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info_pa)
{
	list_t *node = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
		add_node_end(&node, environ[x], 0);
	info_pa->env = node;
	return (0);
}
