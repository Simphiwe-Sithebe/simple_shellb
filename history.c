#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info_struct: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *info_struct)
{
	char *buff, *dirr;

	dirr = _getenv(info_struct, "HOME=");
	if (!dirr)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dirr) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dirr);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info_struct: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info_struct)
{
	ssize_t fd;
	char *filename = get_history_file(info_struct);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info_struct->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @info_struct: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info_struct)
{
	int x, last = 0, linescount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = get_history_file(info_struct);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (x = 0; x < fsize; x++)
		if (buff[x] == '\n')
		{
			buff[x] = 0;
			build_history_list(info_struct, buff + last, linescount++);
			last = x + 1;
		}
	if (last != x)
		build_history_list(info_struct, buff + last, linescount++);
	free(buff);
	info_struct->histcount = linescount;
	while (info_struct->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info_struct->history), 0);
	renumber_history(info_struct);
	return (info_struct->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info_struct: Structure containing potential arguments. Used to maintain
 * @buff: buffer
 * @linescount: the history linescount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info_struct, char *buff, int linescount)
{
	list_t *node = NULL;

	if (info_struct->history)
		node = info_struct->history;
	add_node_end(&node, buff, linescount);

	if (!info_struct->history)
		info_struct->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info_struct: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info_struct)
{
	list_t *node = info_struct->history;
	int x = 0;

	while (node)
	{
		node->num = x++;
		node = node->next;
	}
	return (info_struct->histcount = x);
}
