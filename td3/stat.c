#include <pwd.h>
#include "stat.h"

char	type(const struct stat s)
{
	if (S_ISREG(s.st_mode))
		return '-'; // regular file
	else if (S_ISSOCK(s.st_mode))
		return 's'; // socket
	else if (S_ISLNK(s.st_mode))
		return 'l'; // symbolic link
	else if (S_ISBLK(s.st_mode))
		return 'c'; // character device
	else if (S_ISDIR(s.st_mode))
		return 'd'; // directory
	else if (S_ISFIFO(s.st_mode))
		return 'p'; // named pipe
	else
		return '?'; // ???
}

void	mod(const struct stat s, char *buf)
{
	for (int i = 0; i < 9; i++)
		if (! (s.st_mode & (1 << (8 - i))))
			buf[i] = '-';
}

char*	owner(const struct stat s)
{
	return getpwuid(s.st_uid)->pw_name;
}

off_t	size(const struct stat s)
{
	return s.st_size;
}