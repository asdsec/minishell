#include "minishell.h"
#include "termios.h"
#include "signal.h"
#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"

void	set_termios(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) != 0)
		exit((perror("error"), -1));
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
		exit((perror("error"), -1));
}

void	signal_handler_ctrl_c(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void signals(void)
{
	set_termios();
	signal(SIGINT, signal_handler_ctrl_c);
}
