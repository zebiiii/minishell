#include "../minishell.h"

int	ft_check_option(char **argv)
{
	int i;
    int j;
    int indic;
    int indic2;

    i = -1;
    while (argv[++i])
    {
        j = 0;
        indic = 0;
        indic2 = 0;
        while(argv[i][j])
        {
            if(argv[i][j] == '-' && indic == 0)
            {
                j++;
                indic++;
            }
            if(argv[i][j] == 'n' && indic != 0)
                j++;
            else
            {
                indic2++;
                break;
            }
        }
        if (indic2 == 1)
            break;
    }
    return (i);
}

int    ft_echo(int argc, char **argv)
{
    int i;
    int len;
    int with_option;

    i = 0;
    len = argc - 1;
    with_option = 0;
    if (!argv[i])
	{
		write(1, "\n", 1);
		exit(EXIT_SUCCESS);
	}
    i = ft_check_option(argv);
    if (i <= len && i != 0)
        with_option++;
    while(argv[i])
    {
        ft_putstr_fd(argv[i], STDOUT_FILENO);
        if (!(argv[i + 1] == '\0'))
            write(1, " ", 1);
        i++;
    }
    if (with_option == 0)
        write(1, "\n", 1);
    exit(EXIT_SUCCESS);
}