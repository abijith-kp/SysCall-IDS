/**
 * To make signature from the input sequence of system calls
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int val[5000][5000];

#include "data_structure.h"
#include "poset_manage.h"
#include "nodes_manage.h"
#include "clean.h"
#include "lcs.h"


int main(int argc, char **argv) {
        FILE *file = fopen(".ids/list", "r");
        char fileN[10];
	int flag=0, i, j;

        //makePoset(".ids/p1");
        //printf("\ndsfdsf\n");
	    // clean();
        // printPoset(head);

/*        makePoset("input1");
	clean();
        printPoset(head);
*/

        while(!feof(file)) {
                fscanf(file, "%s", fileN);
	//printf("\n %s \n", fileN);
                makePoset(fileN);
                clean();
		// printf("\n%s\n", fileN);
                // printPoset(head);
        printf("\n\n");
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
        
        for(i=0; i<200; i++) {
            for(i=0; i<200; i++) {
                printf("%d ", val[i][j]);
            }
            printf("\n");
        }

        return 0;
}
