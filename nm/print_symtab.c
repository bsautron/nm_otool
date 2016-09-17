#include <stdio.h>//
#include <ft_nm.h>

// Dont push that
// TODO: add fn to sort in params

void	print_symtab(struct symtab_command *symtab, void *ptr)
{
	uint32_t			i;
	char				*stringtable;
	struct nlist_64		*array;

	array = ptr + symtab->symoff;
	stringtable = ptr + symtab->stroff;

	i = 0;
	printf("%4s %4s %4s %4s %10s %s\n", "strx", "type", "sect",  "desc", "val", "string");
	while (i < symtab->nsyms)
	{
		printf("%4d %4u %4u %4u %10llx %s\n", array[i].n_un.n_strx, array[i].n_type, array[i].n_sect, array[i].n_desc, array[i].n_value, stringtable + array[i].n_un.n_strx);
		i++;
	}
}
