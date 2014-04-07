// void loadSig(char *siglist) {
// 
// }
struct sysCPS *inputHEAD = NULL;

// void compare(struct sysCPS *inp, char *name1, char *name2) {
void compare(struct sysCPS *inp, struct sysCPS *name1, char *name2) {
    char *str;
    int lS=0, lL=0, lI=0, n=0;
    FILE *file=fopen(".tmpSig", "w");
    float m=0.0, v=0.0;

    // loading signatures
    // makePoset(name1);
    str = string_lcs(inputHEAD, name1); //head);
    printf("\n%d %d\n", lengthPoset(inputHEAD), lengthPoset(head));
    lS = lengthPoset(name1);
    lI = lengthPoset(inp);
    printf("\n>>>><<<\n");
    // freeArray(lI, lS);
    printf("\n>>>>#######<<<\n");
    // freeNode(head);
    fprintf(file, "%s", str);
    fclose(file);
    makePoset(".tmpSig");
    lL = lengthPoset(head);


    printf("\nLS:%d LL:%d LI:%d\n", lS, lL, lI);
    file = fopen(name2, "r");
    fscanf(file, "%d %f %f", &n, &m, &v);
    fclose(file);

    // condition to check for anomaly
    if(((lL < (lS + v)) && (lL > (lS - v))) || ((lL < (lI + v)) && (lL > (lI - v)))) {
        printf("\nNORMAL BEHAVIOUR\n");
    }
    else {
        printf("\nABNORMAL BEHAVIOUR\n");
    }
    // return 0;
}

void evalScore() {
// userfeed back  can be included here
}

void check(char *input) {
    FILE *file=fopen(input, "r");
    char name1[100], name2[100];
     
    int i=0;
    makePoset(input);
    clean();
    inputHEAD = head;
    head = NULL;
    // loadSig(".ids/siglist");

    file = fopen(".ids/siglist", "r");
    fscanf(file, "%s %s", name1, name2);
    // for sig in list of signature
    while(!feof(file)) {
        // compare(inputHEAD, name1, name2);
        makePoset(name1);
        printf("\n%s %s %d\n", name1, name2, lengthPoset(head));
        compare(inputHEAD, head, name2);
        fscanf(file, "%s %s", name1, name2);
        // i++;
    }

    // evalScore(resut_score, );
    // find the number of mismatches usign the same algorithm to find mean and varience
    // then compare it with the signature values
}
