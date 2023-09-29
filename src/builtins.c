#include "../includes/minishell.h"
#include "../includes/defines.h"
#include "../lib/libft/libft.h"

void    ft_echo(const char *message)
{
    printf("%s\n", message);
}

void    ft_pwd()
{
    char *buf = NULL;
    
    getcwd(NULL, 0);
    printf("%s", buf);
}
