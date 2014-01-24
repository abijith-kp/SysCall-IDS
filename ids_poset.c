#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "data_structure.h"
#include "poset_manage.h"

int main(int argc, char **argv) {
        strcpy(appName, argv[1]);

        FILE *file = fopen(".ids/list", "r");
        char fileN[200];
	// makeSyscallList();

        while(!feof(file)) {
                fscanf(file, "%s\n", fileN);
                printf("\n %s \n", fileN);
                makeList(fileN);
                compareList();
        }
      
        writeSIG();
	
        return 0;
}
