#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <err.h>
#include <string.h>

void
usage(void)
{
	fprintf(stderr, "usage: myls\n");
	exit(EXIT_FAILURE);
}

void

printtypeinode(struct stat file_info)
{
	switch (file_info.st_mode & S_IFMT) {
	case S_IFREG:
		printf("f   ");
		break;
	case S_IFDIR:
		printf("d   ");
		break;
	case S_IFLNK:
		printf("l   ");
		break;
	default:
		printf("o   ");
		break;
	}
}

void
printuid(struct stat file_info)
{
	printf("%d  ", file_info.st_uid);
}

void
printgid(struct stat file_info)
{
	printf("%d  ", file_info.st_gid);
}

void
printsize(struct stat file_info)
{
	printf("%lld  ", (long long)file_info.st_size);
}

void
printparameters()
{
	DIR *d;
	struct dirent *directory_parameters;
	struct stat file_info;

	d = opendir(".");
	if (d == NULL) {
		err(EXIT_FAILURE, "can't open directory\n");
	}
	while ((directory_parameters = readdir(d)) != NULL) {
		if (lstat(directory_parameters->d_name, &file_info) == -1) {
			perror("stat");
			continue;
		}
		printtypeinode(file_info);
		printuid(file_info);
		printgid(file_info);
		printsize(file_info);
		printf("%s\n", directory_parameters->d_name);
	}
	closedir(d);
}

int
main(int argc, char *argv[])
{
	if (argc > 1) {
		usage();
	}
	printparameters();
	exit(EXIT_SUCCESS);
}
