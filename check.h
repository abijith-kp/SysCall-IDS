struct sysCPS *inputHEAD = NULL;

void compare(struct sysCPS *inp, char *name1, char *name2) {
    char *str;
    int lS=0, lL=0, lI=0, n=0;
    FILE *file=fopen(tmpSigF, "w");
    float m=0.0, v=0.0;

    makePoset(name1);
    lS = lengthPoset(head);
    lI = lengthPoset(inp);
    str = string_lcs_v2(inp, head, lI, lS);
    
    fprintf(file, "%s", str);
    fclose(file);
    makePoset(tmpSigF);
    lL = lengthPoset(head);


    file = fopen(name2, "r");
    fscanf(file, "%d %f %f", &n, &m, &v);
    fclose(file);

    /*********************************
     * condition to check for anomaly
     * has to modify it some more
     *********************************/
    if(((lL < (lS + v)) && (lL > (lS - v))) || ((lL < (lI + v)) && (lL > (lI - v)))) {
        printf("\nNORMAL BEHAVIOUR\n");
    }
    else {
        printf("\nABNORMAL BEHAVIOUR\n");
    }
}

/**
 * void evalScore() {
 * userfeed back  can be included here
 * }
 **/

void check(char *input) {
    FILE *fileI = fopen(input, "r");
    FILE *fileS = fopen(siglist, "r");
    char name1[100], name2[100], name3[100];
     
    int i=0;
    makePoset(input);
    clean();
    inputHEAD = head;
    head = NULL;

    fscanf(fileI, "%s", name3);
    while(!feof(fileI)) {
        fileS = fopen(siglist, "r");
        fscanf(fileS, "%s %s", name1, name2);
        makePoset(name3);
        /**
         * for sig in list of signature
         **/
        while(!feof(fileS)) {
            compare(head, name1, name2);
            fscanf(fileS, "%s %s", name1, name2);
        }
        fclose(fileS);
    }

    fclose(fileI);

    /***********************************************************************************
     * evalScore(resut_score, );
     * find the number of mismatches usign the same algorithm to find mean and varience
     * then compare it with the signature values
     ***********************************************************************************/
}
