/**
 * To make signature from the input sequence of system calls
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "data_structure.h"
#include "poset_manage.h"
#include "nodes_manage.h"
#include "clean.h"

int main(int argc, char **argv) {
        FILE *file = fopen(".ids/list", "r");
        char fileN[5];

        makePoset("input");
        // printPoset(head);

	// printf("\n %d \n", countPS);

	clean();
        printPoset(head);

        while(!feof(file)) {
                fscanf(file, "%s", fileN);
                makePoset(fileN);
		headSIG = head;
		head = NULL;
		tailSIG = tail;
		tail = NULL;
		countSIG = countT;
		countT = 0;
                // compareSet();
        }
	
        return 0;
}
