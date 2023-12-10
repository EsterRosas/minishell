#include "../inc/minishell.h"

int	assign_infile(char	*file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file %s", file);
		return (-1);
	}
	else
		return (fd);
}

int	assign_outfile(char	*file)
{
	int	fd;

	fd = open(file, O_RDWR);
	if (fd == -1)
	{
		printf("Error opening file %s", file);
		return (-1);
	}
	else
		return (fd);
}
