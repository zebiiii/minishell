#include "../minishell.h"

int    cd(char **argv)
{
	char *s;

	s = getcwd(NULL, 0);
    printf("%s\n", s);
	if (!argv[0])
		
    if (chdir(argv[0]) == -1)
	{
		ft_putstr_fd("no such file or directory", 2);
		exit(EXIT_FAILURE);
	}
	s = getcwd(NULL, 0);
    printf("%s\n", s);
    return (0);
}

/*int main(int argc, char **argv, char **env)
{
	int i;
	i = 0;
    cd(argv + 1, env);
    return (0);
}*/