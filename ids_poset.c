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
        FILE *file = fopen(lists, "r");
        char fileN[60];

        if(argc < 2) {
                printf("\nERROR: Usage: %s <arg>\n", argv[0]);
                exit(1);
        }

        if(!strcmp(argv[1], "make")) {
        /**
         * for signature creation
         * details regarding branches also need to b added for completion
         **/
            fscanf(file, "%s", fileN);
            while(!feof(file)) {
                    create(fileN);
                    fscanf(file, "%s", fileN);
		    }
        }

        /**
         * inputS contains list of files which is to be compared for anomality check
         **/
        else if(!strcmp(argv[1], "test")) {
            check(inputS);
        }

        return 0;
}
