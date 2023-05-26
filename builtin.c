#include "shell.h"

/**
 * my_exit - Exits the shell.
 * @info: Structure containing potential arguments.
 *
 * Return: Exits with a given exit status (0) if info->args[0] != "exit".
 */
int my_exit(info_t *info)
{
	int exit_status;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exit_status = err_atoi(info->argv[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			e_puts(info->argv[1]);
			e_putchar('\n');
			return 1;
		}
		info->err_num = err_atoi(info->argv[1]);
		return -2;
	}
	info->err_num = -1;
	return -2;
}

/**
 * my_cd - Changes the current directory of the process.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int my_cd(info_t *info)
{
	char *cwd, *dir, buffer[1024];
	int chdir_ret;

	cwd = getcwd(buffer, 1024);
	if (!cwd)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = get_env(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: What should this be? */
				chdir((dir = get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (str_cmp(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			_puts(cwd);
			_putchar('\n');
			return 1;
		}
		_puts(get_env(info, "OLDPWD="));
		_putchar('\n');
		chdir_ret = /* TODO: What should this be? */
			chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "Can't change directory to ");
		e_puts(info->argv[1]);
		e_putchar('\n');
	}
	else
	{
		set_env(info, "OLDPWD", get_env(info, "PWD="));
		set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return 0;
}

/**
 * my_help - Provides help information for the shell.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int my_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("Help call works. Function not yet implemented.\n");
	if (0)
		_puts(*arg_array); /* Temporary unused workaround */
	return 0;
}
