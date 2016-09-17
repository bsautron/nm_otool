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
#include <errors.h>

static void print_output(uint32_t nsyms, uint32_t symoff, uint32_t stroff, void *ptr)
{
	uint32_t	i;
	char		*stringtable;
	struct nlist_64 *array;

	array = ptr + symoff;
	stringtable = ptr + stroff;

	i = 0;
	printf("%4s %4s %4s %4s %10s %s\n", "strx", "type", "sect",  "desc", "val", "string"); 
	while (i < nsyms)
	{
		printf("%4d %4u %4u %4u %10llx %s\n", array[i].n_un.n_strx, array[i].n_type, array[i].n_sect, array[i].n_desc, array[i].n_value, stringtable + array[i].n_un.n_strx);
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

	fd = open(filename, O_RDONLY);
	if (fstat(fd, &buf) < 0)
	{

		if (S_ISDIR(buf.st_mode))
			return error_is_a_directory(filename);
		error_no_such_file_or_directory(filename);
		return (EXIT_FAILURE);
	}
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
	int		ret;

	ret = EXIT_SUCCESS;
	init_options(&args, "ft_nm");
	if (!parse_options(&args, ac, av))
		ret = EXIT_FAILURE;
	if (args.argc < 2)
		ret = process_file("a.out", 0);
	else if (args.argc == 2)
		ret = process_file(args.argv[1], 0);
	else
	{
		args.argv++;
		while (*args.argv)
		{
			if (process_file(*args.argv, 1) != EXIT_SUCCESS)
				ret = EXIT_FAILURE;
			args.argv++;
		}
	}
	return (ret);
}
