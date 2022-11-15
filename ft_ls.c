#include "minishell.h"

void	ft_ls(char **cmds)
{
	DIR *mydir;
	struct dirent *myfile;
	struct stat mystat;
	int			cont;
	int			aux01;
	int			aux02;

	cont = 0;
	if	(cmds[1])
		mydir = opendir(cmds[1]);
	else
		mydir = opendir(get_pwd());
	while((myfile = readdir(mydir)) != NULL)
	{
		if (myfile->d_name[0] != '.')
			cont++;
	}
	aux01 = cont / 5;
	if (cont % 5 != 0)
		aux01++;
	aux02 = aux01;
	if	(cmds[1])
		mydir = opendir(cmds[1]);
	else
		mydir = opendir(get_pwd());
	while((myfile = readdir(mydir)) != NULL)
	{
		stat(myfile->d_name, &mystat);
		//printf("%lld",mystat.st_size);
		if (myfile->d_name[0] != '.')
			printf("%s     ", myfile->d_name);
		aux01--;
		if	(aux01 == 0)
		{
			printf("\n");
			aux01 = aux02;
		}
		//printf("%15s", myfile->d_name);
		//printf("%-15s", "123"); 
		//printf("%s     ", myfile->d_name);
	}
	closedir(mydir);
}
