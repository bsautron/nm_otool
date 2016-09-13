#include <ft_nm.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <unistd.h>
#include <stdio.h>

static void print_output(uint32_t nsyms, uint32_t symoff, uint32_t stroff, char *ptr)
{
	uint32_t	i;
	char		*stringtable;
	struct nlist_64 *array;

	array = (void *)ptr + symoff;
	stringtable = (void *)ptr + stroff;

	i = 0;
	while (i < nsyms)
	{
		printf("%s\n", stringtable + array[i].n_un.n_strx);
		i++;
	}
}

static void	handler_64(char *ptr)
{
	uint32_t	ncmds;
	uint32_t			i;
	struct mach_header_64	*header;
	struct load_command		*load_commands;
	struct symtab_command	*sym;

	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	i = 0;
	load_commands = (void *)ptr + sizeof(*header);
	while (i < ncmds)
	{
		if (load_commands->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)load_commands;
			ft_putnbr(sym->nsyms);
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
			ft_putchar('\n');
			break;
		}
		load_commands = (void *)load_commands + load_commands->cmdsize;
		i++;
	}
}

static void	nm(char *ptr)
{
	uint32_t	magic_number;
	magic_number = *(int *)ptr;

	// Read 4 first byte (magic number)
	if (magic_number == MH_MAGIC_64)
		handler_64(ptr);
}

int			main(int ac, char **av)
{
	char	*filename;
	int		fd;
	char	*ptr;
	struct stat buf;

	filename = av[1];
	ft_putendl(filename);
	if (ac != 2)
		return (EXIT_FAILURE);
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (EXIT_FAILURE);
	if (fstat(fd, &buf) < 0)
		return (EXIT_FAILURE);
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (EXIT_FAILURE);
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
