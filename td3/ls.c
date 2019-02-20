#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "stat.h"

void	printstat(char *path)
{
	struct stat s;
	char	buf[10] = "rwxrwxrwx";
	
	if (stat(path, &s) == -1)
	{
		printf("%s: cannot access '%s': %s\n", path, path, strerror(errno));
		return;
	}
	mod(s, buf);
	printf("%c%s %s %ld %s\n", type(s), buf, owner(s), size(s), path);
}

int	main(int argc, char **argv)
{
	DIR *dir;
	struct dirent *file;
	
	for (int i = 1; i < argc; i++)
	{
		dir = opendir(argv[i]);
		if (dir)
		{
			while ((file = readdir(dir)))
				printstat(file->d_name);
			closedir(dir);
		}
		else
			printstat(argv[i]);
	}
	return 0;
}