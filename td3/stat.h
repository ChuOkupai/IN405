#ifndef _SOCKET_H
# define _SOCKET_H

#include <errno.h>
#include <sys/stat.h>

/* Get file type */
char	type(const struct stat s);

/* Get file permission */
/** buf of size 10 **/
void	mod(const struct stat s, char *buf);

/* Get file owner */
/** Returns a char* **/
char*	owner(const struct stat s);

/* Get file size */
/** Returns a off_t (long int) **/
off_t	size(const struct stat s);

#endif