
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
