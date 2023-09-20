#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info_struct: parameter struct
 * @buf_address: address of buffer
 * @len_address: address of len_address var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info_struct, char **buf_address, size_t *len_address)
{
	ssize_t o = 0;
	size_t len_p = 0;

	if (!*len_address) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info_struct->cmd_buf);*/
		free(*buf_address);
		*buf_address = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		o = getline(buf_address, &len_p, stdin);
#else
		o = _getline(info_struct, buf_address, &len_p);
#endif
		if (o > 0)
		{
			if ((*buf_address)[o - 1] == '\n')
			{
				(*buf_address)[o - 1] = '\0'; /* remove trailing newline */
				o--;
			}
			info_struct->linecount_flag = 1;
			remove_comments(*buf_address);
			build_history_list(info_struct, *buf_address, info_struct->histcount++);
			/* if (_strchr(*buf_address, ';')) is this a command chain? */
			{
				*len_address = o;
				info_struct->cmd_buf = buf_address;
			}
		}
	}
	return (o);
}

/**
 * get_input - gets a line minus the newline
 * @info_struct: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info_struct)
{
	static char *buf_address; /* the ';' command chain buffer */
	static size_t x, j, len_address;
	ssize_t o = 0;
	char **buf_p = &(info_struct->arg), *p;

	_putchar(BUF_FLUSH);
	o = input_buf(info_struct, &buf_address, &len_address);
	if (o == -1) /* EOF */
		return (-1);
	if (len_address)	/* we have commands left in the chain buffer */
	{
		j = x; /* init new iterator to current buf_address position */
		p = buf_address + x; /* get pointer for return */

		check_chain(info_struct, buf_address, &j, x, len_address);
		while (j < len_address) /* iterate to semicolon or end */
		{
			if (is_chain(info_struct, buf_address, &j))
				break;
			j++;
		}

		x = j + 1; /* increment past nulled ';'' */
		if (x >= len_address) /* reached end of buffer? */
		{
			x = len_address = 0; /* reset position and length */
			info_struct->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf_address; /* else not a chain, pass back buffer from _getline() */
	return (o); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info_struct: parameter struct
 * @buf_address: buffer
 * @x: size
 *
 * Return: o
 */
ssize_t read_buf(info_t *info_struct, char *buf_address, size_t *x)
{
	ssize_t o = 0;

	if (*x)
		return (0);
	o = read(info_struct->readfd, buf_address, READ_BUF_SIZE);
	if (o >= 0)
		*x = o;
	return (o);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info_struct: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info_struct, char **ptr, size_t *length)
{
	static char buf_address[READ_BUF_SIZE];
	static size_t x, len_address;
	size_t k;
	ssize_t o = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (x == len_address)
		x = len_address = 0;

	o = read_buf(info_struct, buf_address, &len_address);
	if (o == -1 || (o == 0 && len_address == 0))
		return (-1);

	c = _strchr(buf_address + x, '\n');
	k = c ? 1 + (unsigned int)(c - buf_address) : len_address;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf_address + x, k - x);
	else
		_strncpy(new_p, buf_address + x, k - x + 1);

	s += k - x;
	x = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @signal_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int signal_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
