int path_cmd(char **cmd)
{
	char *path, *value, *cmd_path;
	struct stat buf;

	path = _getenv("PATH");
	value = str_tok(path, ":");
	while (value != NULL)
	{
		cmd_path = build (*cmd, value);
		if (stat(cmd_path, &buf) == 0)
		{
			*cmd = str_dup(cmd_path);
			free(cmd_path);
			return (0);
		}
		free(cmd_path);
		value = str_tok(NULL, ":");
	}
	free(path);

	return (1);
}

/**
 * build - The build command
 * @token: The executable command
 * @value: The dir conatining command
 *
 * Return: Full of command parsed, NUKK case failed.
 */
char *build(char *token, char *value)
{
	size_t len;
	char *cmd;

	len = str_len(value) + str_len(token) + 2;
	cmd = malloc(sizeof(char) *len);
	if (cmd == NULL)
	{
		return (NULL);
	}

	memset(cmd, 0, len);

	cmd = str_cat(cmd, value);
	cmd = str_cat(cmd, "/");
	cmd = str_cat(cmd, token);

	return (cmd);
}

/**
 * get_env - The environment variable by name, it gets it.
 * @name: The variable name of the environment.
 * Return: Environment variable name or else NULL
 */
char *get_env(char *name)
{
	int i, x, j;
	char *value;
	size_t nl, vl;

	nl = str_len(name);
	for (i = 0; environ[i]; i++)
	{
		if(strn_cmp(name, environ[i] nl) == 0)
		{
			vl = str_len(environ[i] - nl;
			value = malloc(sizeof(char) 8 vl);
			if (!value)
			{
			free(value);
			perror("unable to alloc");
			return (NULL);
			}

		j = 0;
		for (x = nl + 1; environ[i][x];x+=, j++)
		{
			value[j] = environ[i][x];
		}
		value[j] = '\0';

		return (value);
	}

	}
	return (NULL);
}

