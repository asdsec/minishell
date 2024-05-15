#include "minishell.h"
#include <unistd.h>

void	print_err(const char *file, int err_flag)
{
	write(2, "minishell: ", 11);
	write(2, file, ft_strlen(file));
	if (err_flag == ERR_FILE_NOT_FOUND)
		write(2, ": No such file or directory\n", 29);
	else if (err_flag == ERR_FILE_PERMISSION_DENIED)
		write(2, ": Permission denied\n", 21);
	else if (err_flag == ERR_FILE_OPEN)
		write(2, ": \n",4); // todo(hkizrak-): errno
}
