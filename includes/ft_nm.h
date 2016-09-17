#ifndef FT_NM_H
# define FT_NM_H

# include <libft.h>
# include <libargs.h>
# include <errors.h>

# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <unistd.h>
# include <stdio.h> /////

void	print_symtab(struct symtab_command *symtab, void *ptr);

#endif
