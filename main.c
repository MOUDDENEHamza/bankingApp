#include <stdio.h>
#include <string.h>

void main() {

	FILE *fp;
	char path[64] = "~/Desktop/bankingApp";
	char str[64] = "echo -n \"ADMIN\" | md5sum | cut -d \"-\" -f1 -";

	fp = popen(str, "r");


	while (fgets(path, 64, fp) != NULL)
    		printf("%s", path);

	pclose(fp);

}
