#include "minishell.h"

void print_str_lst(char **lst)
{
	int i = 0;
	while (lst && lst[i])
	{
		printf("\033[0;93m%i:\033[0;92m%s\n\033[0;39m", i, lst[i]);
		i++;
	}
}