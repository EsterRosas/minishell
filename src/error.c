#include "../includes/minishell.h"

void    handle_error(const char *message)
{
    perror(message);
/*     const char *error_message = strerror(errno);
    printf("%s: %s\n", message, error_message); */
    exit(EXIT_FAILURE);
}