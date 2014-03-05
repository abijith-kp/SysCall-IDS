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
        char fileN[10];
	int flag=0;

        makePoset("input2");
	clean();
        printPoset(head);
/*
	printf("\n\n");
        makePoset("input1");
	clean();
        printPoset(head);
*/
/*
        while(!feof(file)) {
                fscanf(file, "%s\n", fileN);
                makePoset(fileN);
		printf("\n%s\n", fileN);
		if(flag == 0) {
			headSIG = head;
			head = NULL;
			tailSIG = tail;
			tail = NULL;
			countSIG = countT;
			countT = 0;
			flag = 1;
			continue;
		}
		
                // compareSet();  // compares headSIG and head (temparary head) and puts the signature in headSIG and the next temparary list in head
		// interchanges the list values
        }
*/	
        return 0;
}
