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
#include "lcs.h"
#include "signature.h"

/**
 * list contains the names of the applications under consideration.
 * each file in list has another set of list of file names which are the data
 * set corresponding to that application.
 **/
    
int main(int argc, char **argv) {
        FILE *file = fopen(".ids/list", "r");
        char fileN[10];
	    int flag=0, i, j;

        // for signature creation
        fscanf(file, "%s", fileN);
        while(!feof(file)) {
            printf("\nTEST\n");
                create(fileN);
                fscanf(file, "%s", fileN);
		}

/*
//        printPoset(head);

        while(!feof(file)) {
                fscanf(file, "%s", fileN);
                makePoset(fileN);
                clean();
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

        clear_val();
		printf("\n%d\n", length_lcs(head, headSIG));
        break;
                // compareSet();  // compares headSIG and head (temparary head) and puts the 
                                  // signature in headSIG and the next temparary list in head
		// interchanges the list values
        }

        printf("\n>> %d \n", lengthPoset(headSIG));
        printf("\n>> %d \n", lengthPoset(head));
*/        
        return 0;
}
