#include <stdio.h>
#include <stdlib.h>

FILE *openFile(char fileName[]) {

	FILE *file = fopen(fileName, "r+b");

	if (file == NULL)
		file = fopen(fileName, "w+b");

	return file;
}