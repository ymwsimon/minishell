#include "includes/minishell.h"

int main(int arc, char **argv)
{
	DIR	*dir;
	struct dirent *folder;

	if (arc)
	{
		dir = opendir(".");
		if (dir)
		{
			folder = readdir(dir);
			while (folder)
			{
				printf("%s\n", folder->d_name);
				folder = readdir(dir);
			}
		}
	}
}

