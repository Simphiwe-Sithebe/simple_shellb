#include "shell.h"

/**
 * main - entry point
 * @arg_ocunt: arg count
 * @arg_vec: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int arg_ocunt, char **arg_vec)
{
	info_t info1[] = { INFO_INIT };
	int filedesc = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (filedesc)
		: "r" (filedesc));

	if (arg_ocunt == 2)
	{
		filedesc = open(arg_vec[1], O_RDONLY);
		if (filedesc == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(arg_vec[0]);
				_eputs(": 0: Can't open ");
				_eputs(arg_vec[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info1->readfd = filedesc;
	}
	populate_env_list(info1);
	read_history(info1);
	hsh(info1, arg_vec);
	return (EXIT_SUCCESS);
}
