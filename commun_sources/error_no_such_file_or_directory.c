#include <libft.h>

int	error_no_such_file_or_directory(const char *filename)
{
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": No such file or directory.", 2);
	ft_putchar_fd('\n', 2);
	return (EXIT_FAILURE);
}
