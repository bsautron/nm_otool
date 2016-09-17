#include <libft.h>

int	error_is_a_directory(const char *filename)
{
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": Is a directory.", 2);
	ft_putchar_fd('\n', 2);
	return (EXIT_FAILURE);
}
