#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "data_structure.h"
#include "poset_manage.h"

int main(int argc, char **argv) {
        // strcpy(appName, argv[1]);

        // FILE *file = fopen(".ids/list", "r");
        char fileN[5];
	// makeSyscallList();

        makePoset("input");
        printPoset(head);
        /*
        while(!feof(file)) {
                fscanf(file, "%s\n", fileN);
                // printf("\n %s \n", fileN);
                makePoset(fileN); // created poset can be obtained using the variables head and tail
                compareSet();
        }
      */
	
        return 0;
}
