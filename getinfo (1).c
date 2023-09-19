#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @infoStruct_addr: struct address
 */
void clear_info(info_t *infoStruct_addr)
{
	infoStruct_addr->arg = NULL;
	infoStruct_addr->argv = NULL;
	infoStruct_addr->path = NULL;
	infoStruct_addr->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @infoStruct_addr: struct address
 * @arg_vect: argument vector
 */
void set_info(info_t *infoStruct_addr, char **arg_vect)
{
	int x = 0;

	infoStruct_addr->fname = arg_vect[0];
	if (infoStruct_addr->arg)
	{
		infoStruct_addr->argv = strtow(infoStruct_addr->arg, " \t");
		if (!infoStruct_addr->argv)
		{

			infoStruct_addr->argv = malloc(sizeof(char *) * 2);
			if (infoStruct_addr->argv)
			{
				infoStruct_addr->argv[0] = _strdup(infoStruct_addr->arg);
				infoStruct_addr->argv[1] = NULL;
			}
		}
		for (x = 0; infoStruct_addr->argv && infoStruct_addr->argv[x]; x++)
			;
		infoStruct_addr->argc = x;

		replace_alias(infoStruct_addr);
		replace_vars(infoStruct_addr);
	}
}

/**
 * free_info - frees info_t struct fields
 * @infoStruct_addr: struct address
 * @allfields: true if freeing allfields fields
 */
void free_info(info_t *infoStruct_addr, int allfields)
{
	ffree(infoStruct_addr->argv);
	infoStruct_addr->argv = NULL;
	infoStruct_addr->path = NULL;
	if (allfields)
	{
		if (!infoStruct_addr->cmd_buf)
			free(infoStruct_addr->arg);
		if (infoStruct_addr->env)
			free_list(&(infoStruct_addr->env));
		if (infoStruct_addr->history)
			free_list(&(infoStruct_addr->history));
		if (infoStruct_addr->alias)
			free_list(&(infoStruct_addr->alias));
		ffree(infoStruct_addr->environ);
			infoStruct_addr->environ = NULL;
		bfree((void **)infoStruct_addr->cmd_buf);
		if (infoStruct_addr->readfd > 2)
			close(infoStruct_addr->readfd);
		_putchar(BUF_FLUSH);
	}
}
