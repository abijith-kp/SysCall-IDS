struct sysCPS *inputHEAD = NULL;

/***********************************************************
 * has to add branches to the signature
 * identify a metric to identify attack
 * currently mean and varience are used to calculate the abnormality in the process behaviour
 ***********************************************************/

void compare(struct sysCPS *inp, char *name1, char *name2) {
    int lS=0, lL=0, lI=0, n=0;
    FILE *file=fopen(tmpSigF, "w");
    float m=0.0, v=0.0;
    struct sStruct *str;

    makePoset(name1);
    lS = lengthPoset(head);
    lI = lengthPoset(inp);
    str = string_lcs_v2(inp, head, lI, lS);
    
    fprintf(file, "%s", str->str1);
    fclose(file);
    makePoset(tmpSigF);
    lL = lengthPoset(head);


    file = fopen(name2, "r");
    fscanf(file, "%d %f %f", &n, &m, &v);
    fclose(file);

    printf("\nLS:%d  LI:%d  LL:%d\n", lS, lI, lL);
    /*********************************
     * condition to check for anomaly
     * has to modify it some more
     *********************************/
    if(((lL < (lS + v)) && (lL > (lS - v))) || ((lL < (lI + v)) && (lL > (lI - v)))) {
        printf("\t\tNORMAL BEHAVIOUR\n");
    }
    else {
        printf("\t\tABNORMAL BEHAVIOUR\n");
    }
}

/**
 * void evalScore() {
 * userfeed back  can be included here
 * }
 **/

void check(char *input) {
    FILE *fileI = fopen(input, "r");
    FILE *fileS; // = fopen(siglist, "r");
    char name1[100], name2[100], name3[100];

    printf("\nProcessing input file: %s\n", input);
     
    /**
     * int i=0;
     * makePoset(input);
     * clean();
     * inputHEAD = head;
     * head = NULL;
     **/

    fscanf(fileI, "%s", name3);
    while(!feof(fileI)) {
        printf("\tFile: %s\n", name3);
        fileS = fopen(siglist, "r");
        fscanf(fileS, "%s %s", name1, name2);
        makePoset(name3);
	clean();
	inputHEAD = head;
        /**
         * for sig in list of signature
         **/
        while(!feof(fileS)) {
            printf("\t\tSigFile: %s %d\n", name1, lengthPoset(inputHEAD));
            compare(inputHEAD, name1, name2);
            fscanf(fileS, "%s %s", name1, name2);
        }
    	fscanf(fileI, "%s", name3);
        fclose(fileS);
    }

    fclose(fileI);

    /***********************************************************************************
     * evalScore(resut_score, );
     * find the number of mismatches usign the same algorithm to find mean and varience
     * then compare it with the signature values
     ***********************************************************************************/
}
