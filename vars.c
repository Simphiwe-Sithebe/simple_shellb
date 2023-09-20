#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info_struct: the parameter struct
 * @char_buf: the char buffer
 * @cur_pos: address of current position in char_buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info_struct, char *char_buf, size_t *cur_pos)
{
	size_t k = *cur_pos;

	if (char_buf[k] == '|' && char_buf[k + 1] == '|')
	{
		char_buf[k] = 0;
		k++;
		info_struct->cmd_buf_type = CMD_OR;
	}
	else if (char_buf[k] == '&' && char_buf[k + 1] == '&')
	{
		char_buf[k] = 0;
		k++;
		info_struct->cmd_buf_type = CMD_AND;
	}
	else if (char_buf[k] == ';') /* found end of this command */
	{
		char_buf[k] = 0; /* replace semicolon with null */
		info_struct->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*cur_pos = k;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @info_struct: the parameter struct
 * @char_buf: the char buffer
 * @cur_pos: address of current position in char_buf
 * @start_pos: starting position in char_buf
 * @lenght: length of char_buf
 *
 * Return: Void
 */
void check_chain(info_t *info_struct, char *char_buf, size_t *cur_pos, size_t start_pos, size_t lenght)
{
	size_t k = *cur_pos;

	if (info_struct->cmd_buf_type == CMD_AND)
	{
		if (info_struct->status)
		{
			char_buf[start_pos] = 0;
			k = lenght;
		}
	}
	if (info_struct->cmd_buf_type == CMD_OR)
	{
		if (!info_struct->status)
		{
			char_buf[start_pos] = 0;
			k = lenght;
		}
	}

	*cur_pos = k;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info_struct: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info_struct)
{
	int x;
	list_t *node;
	char *cur_pos;

	for (x = 0; x < 10; x++)
	{
		node = node_starts_with(info_struct->alias, info_struct->argv[0], '=');
		if (!node)
			return (0);
		free(info_struct->argv[0]);
		cur_pos = _strchr(node->str, '=');
		if (!cur_pos)
			return (0);
		cur_pos = _strdup(cur_pos + 1);
		if (!cur_pos)
			return (0);
		info_struct->argv[0] = cur_pos;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info_struct: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info_struct)
{
	int x = 0;
	list_t *node;

	for (x = 0; info_struct->argv[x]; x++)
	{
		if (info_struct->argv[x][0] != '$' || !info_struct->argv[x][1])
			continue;

		if (!_strcmp(info_struct->argv[x], "$?"))
		{
			replace_string(&(info_struct->argv[x]),
				_strdup(convert_number(info_struct->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info_struct->argv[x], "$$"))
		{
			replace_string(&(info_struct->argv[x]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info_struct->env, &info_struct->argv[x][1], '=');
		if (node)
		{
			replace_string(&(info_struct->argv[x]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info_struct->argv[x], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old_str: address of old_str string
 * @new_str: new_str string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;
	return (1);
}
