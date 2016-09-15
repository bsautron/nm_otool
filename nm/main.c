#include <ft_nm.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <unistd.h>
#include <stdio.h>
#include <libargs.h>

static void print_output(uint32_t nsyms, uint32_t symoff, uint32_t stroff, void *ptr)
{
	uint32_t	i;
	char		*stringtable;
	struct nlist_64 *array;

	array = ptr + symoff;
	stringtable = ptr + stroff;

	i = 0;
	while (i < nsyms)
	{
		printf("%s\n", stringtable + array[i].n_un.n_strx);
		i++;
	}
}

static void	handler_64(void *ptr)
{
	uint32_t	ncmds;
	uint32_t			i;
	struct mach_header_64	*header;
	struct load_command		*load_commands;
	struct symtab_command	*sym;

	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	i = 0;
	load_commands = ptr + sizeof(*header);
	while (i < ncmds)
	{
		if (load_commands->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)load_commands;
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break;
		}
		load_commands = (void *)load_commands + load_commands->cmdsize;
		i++;
	}
}

static void	nm(void *ptr)
{
	uint32_t	magic_number;
	magic_number = *(int *)ptr;

	if (magic_number == MH_MAGIC_64)
		handler_64(ptr);
}

static int process_file(const char *filename, int extended)
{
	int		fd;
	char	*ptr;
	struct stat buf;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (EXIT_FAILURE);
	if (fstat(fd, &buf) < 0)
		return (EXIT_FAILURE);
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (EXIT_FAILURE);
	if (extended)
	{
		ft_putchar('\n');
		ft_putstr(filename);
		ft_putendl(":");
	}
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			main(int ac, const char **av)
{
	t_args	args;

	init_options(&args, "ft_nm");
	if (!parse_options(&args, ac, av))
		return (EXIT_SUCCESS);
	if (args.argc < 2)
		process_file("a.out", 0);
	else if (args.argc == 2)
		process_file(args.argv[1], 0);
	else
	{
		args.argv++;
		while (*args.argv)
		{
			process_file(*args.argv, 1);
			args.argv++;
		}
	}
	return (EXIT_SUCCESS);
}
