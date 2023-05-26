#include "shell.h"

/**
 * printEnvironment - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int printEnvironment(info_t *info)
{
	printLinkedList(info->environment);
	return 0;
}

/**
 * getEnvironmentValue - gets the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *getEnvironmentValue(info_t *info, const char *name)
{
	list_t *node = info->environment;
	char *p;

	while (node)
	{
		p = startsWith(node->str, name);
		if (p && *p)
			return p;
		node = node->next;
	}
	return NULL;
}

/**
 * setEnvironmentValue - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int setEnvironmentValue(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return 1;
	}
	if (updateEnvironmentValue(info, info->argv[1], info->argv[2]))
		return 0;
	return 1;
}

/**
 * unsetEnvironmentValue - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int unsetEnvironmentValue(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return 1;
	}
	for (i = 1; i <= info->argc; i++)
		removeEnvironmentValue(info, info->argv[i]);

	return 0;
}

/**
 * populateEnvironmentList - populates environment linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populateEnvironmentList(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addNodeEnd(&node, environ[i], 0);
	info->environment = node;
	return 0;
}

int main(void)
{
	// Your main function code here
	return 0;
}
