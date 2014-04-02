/**
 * To make signature from the input sequence of system calls
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "data_structure.h"
#include "poset_manage.h"
#include "nodes_manage.h"
#include "clean.h"
#include "lcs.h"
#include "signature.h"
#include "check.h"

/**
 * list contains the names of the applications under consideration.
 * each file in list has another set of list of file names which are the data
 * set corresponding to that application.
 **/
    
/**
 * if argv[1] == make
 *      dataset is converted into signature
 * else if argv == test
 *      the input sequence is checked for anomaly
 **/

int main(int argc, char **argv) {
        FILE *file = fopen(".ids/list", "r");
        char *inputS=".ids/input";
        char fileN[10];
	    int flag=0, i, j;

        if(argc < 2) {
                printf("\nERROR: Usage: %s <arg>\n", argv[0]);
                exit(1);
        }

        if(!strcmp(argv[1], "make")) {
        // for signature creation
            fscanf(file, "%s", fileN);
            while(!feof(file)) {
                    printf("\nTEST\n");
                    create(fileN);
                    fscanf(file, "%s", fileN);
		    }
        }

        else if(!strcmp(argv[1], "test")) {
            check(inputS);
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
