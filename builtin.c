#include "shell.h"

/**
 * _myexit - exits the shell
 * @infoStruct: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if infoStruct.argv[0] != "exit"
 */
int _myexit(info_t *infoStruct)
{
	int exitC;

	if (infoStruct->argv[1])  /* If there is an exit arguement */
	{
		exitC = _erratoi(infoStruct->argv[1]);
		if (exitC == -1)
		{
			infoStruct->status = 2;
			print_error(infoStruct, "Illegal number: ");
			_eputs(infoStruct->argv[1]);
			_eputchar('\n');
			return (1);
		}
		infoStruct->err_num = _erratoi(infoStruct->argv[1]);
		return (-2);
	}
	infoStruct->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @infoStruct2: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mycd(info_t *infoStruct2)
{
	char *s1, *directoryy, buffer[1024];
	int chdirRRet;

	s1 = getcwd(buffer, 1024);
	if (!s1)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!infoStruct2->argv[1])
	{
		directoryy = _getenv(infoStruct2, "HOME=");
		if (!directoryy)
			chdirRRet = /* TODO: what should this be? */
				chdir((directoryy = _getenv(infoStruct2, "PWD=")) ? directoryy : "/");
		else
			chdirRRet = chdir(directoryy);
	}
	else if (_strcmp(infoStruct2->argv[1], "-") == 0)
	{
		if (!_getenv(infoStruct2, "OLDPWD="))
		{
			_puts(s1);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(infoStruct2, "OLDPWD=")), _putchar('\n');
		chdirRRet = /* TODO: what should this be? */
			chdir((directoryy = _getenv(infoStruct2, "OLDPWD=")) ? directoryy : "/");
	}
	else
		chdirRRet = chdir(infoStruct2->argv[1]);
	if (chdirRRet == -1)
	{
		print_error(infoStruct2, "can't cd to ");
		_eputs(infoStruct2->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(infoStruct2, "OLDPWD", _getenv(infoStruct2, "PWD="));
		_setenv(infoStruct2, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @infoStruct3: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhelp(info_t *infoStruct3)
{
	char **argumentsArray;

	argumentsArray = infoStruct3->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argumentsArray); /* temp att_unused workaround */
	return (0);
}
