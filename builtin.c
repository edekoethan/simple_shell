
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











builtin1.c


#include "shell.h"

/**
 * display_history - Displays the history list, one command per line,
 *                   preceded by line numbers starting at 0.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int display_history(info_t *info)
{
	print_list(info->history);
	return 0;
}

/**
 * remove_alias - Removes an alias from the alias list.
 * @info: Parameter struct.
 * @str: The alias string.
 *
 * Return: Always 0 on success, 1 on error.
 */
int remove_alias(info_t *info, char *str)
{
	char *equal_sign, temp;
	int ret;

	equal_sign = _strchr(str, '=');
	if (!equal_sign)
		return 1;

	temp = *equal_sign;
	*equal_sign = '\0';

	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));

	*equal_sign = temp;
	return ret;
}

/**
 * set_alias - Adds an alias to the alias list.
 * @info: Parameter struct.
 * @str: The alias string.
 *
 * Return: Always 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
	char *equal_sign;

	equal_sign = _strchr(str, '=');
	if (!equal_sign)
		return 1;

	if (!*++equal_sign)
		return remove_alias(info, str);

	remove_alias(info, str);
	return add_node_end(&(info->alias), str, 0) == NULL;
}

/**
 * print_alias - Prints an alias string.
 * @node: The alias node.
 *
 * Return: Always 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
	char *equal_sign = NULL, *alias = NULL;

	if (node)
	{
		equal_sign = _strchr(node->str, '=');
		for (alias = node->str; alias <= equal_sign; alias++)
			_putchar(*alias);

		_putchar('\'');
		_puts(equal_sign + 1);
		_puts("'\n");
		return 0;
	}
	return 1;
}

/**
 * handle_alias - Mimics the alias built-in command (man alias).
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int handle_alias(info_t *info)
{
	int i = 0;
	char *equal_sign = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return 0;
	}

	for (i = 1; info->argv[i]; i++)
	{
		equal_sign = _strchr(info->argv[i], '=');
		if (equal_sign)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return 0;
}
