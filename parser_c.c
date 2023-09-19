#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info_struct: the info_struct struct
 * @file_path: file_path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info_struct, char *file_path)
{
	struct stat st;

	(void)info_struct;
	if (!file_path || stat(file_path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr_: the PATH string
 * @start_: starting index
 * @stop_: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr_, int start_, int stop_)
{
	static char buf[1024];
	int x = 0, l = 0;

	for (l = 0, x = start_; x < stop_; x++)
		if (pathstr_[x] != ':')
			buf[l++] = pathstr_[x];
	buf[l] = 0;
	return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info_struct: the info_struct struct
 * @pathstr_: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full file_path of cmd if found or NULL
 */
char *find_path(info_t *info_struct, char *pathstr_, char *cmd)
{
	int x = 0, cur_position = 0;
	char *file_path;

	if (!pathstr_)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info_struct, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr_[x] || pathstr_[x] == ':')
		{
			file_path = dup_chars(pathstr_, cur_position, x);
			if (!*file_path)
				_strcat(file_path, cmd);
			else
			{
				_strcat(file_path, "/");
				_strcat(file_path, cmd);
			}
			if (is_cmd(info_struct, file_path))
				return (file_path);
			if (!pathstr_[x])
				break;
			cur_position = x;
		}
		x++;
	}
	return (NULL);
}
