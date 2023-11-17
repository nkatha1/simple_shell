char **parse_cmd(char *input)
{
	char **tokens;
	char *token;
	int n, bufsize = BUFSIZE;

	if (input == NULL)
		return (NULL);
	tokens = malloc(sizeof(char *) *bufsize);
	if (!tokens)
	{
		perror("hsh");
		return (NULL);
	}

	token = str_tok(input, "\n");
	for (n = 0; token; n++)
	{
		tokens[n] = token;
		token = str_tok(NULL, "\n");
	}
	tokens[n] = NULL;

	
	return(tokens);
}

