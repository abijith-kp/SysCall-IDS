struct sStruct {
    char *str;
};

struct sStruct array[1000][1000];

int length_lcs(struct sysCPS *headRef1, struct sysCPS *headRef2) {
    int l1=0, l2=0, t=0, t1=0, t2=0;
    
    l1 = lengthPoset(headRef1);
    l2 = lengthPoset(headRef2);

    if((headRef2 == NULL) || (headRef1 == NULL)) {
        return 0;
    }

    if(val[l1][l2] >= 0) {
        return val[l1][l2];
    }

    if((!strcmp(headRef1->call1, headRef2->call1)) && (!strcmp(headRef1->call2, headRef2->call2))) {
        t1 = length_lcs(headRef1->next, headRef2->next);
        val[l1][l2] = (val[l1][l2] > (1 + t1))?val[l1][l2]:(1+t1);
    }
    else if((strcmp(headRef1->call1, headRef2->call1)) || (strcmp(headRef1->call2, headRef2->call2))) {
        t2 = length_lcs(headRef1, headRef2->next);
        t1 = length_lcs(headRef1->next, headRef2);
        t =  (t1>t2)?t1:t2;
        val[l1][l2] = (val[l1][l2]>t)?val[l1][l2]:t;
    }
    
    return val[l1][l2];
}

int strlenN(char *str) {
    if(str) {
        return strlen(str);
    }

    return 0;
}
/*
void freeArray(int l1, int l2) {
    int i=0, j=0;

    for(i=1, i<=l1; i++) {
        for(j=1, j<=l2; j++) {
            free(array[i][j].str);
        }
    }
}
*/
void freeArray(int l1, int l2) {
    int i=0, j=0;

    printf("\ndfdfdfdfdf\n");
    for(i=1; i<=l1; i++) {
        for(j=1; j<=l2; j++) {
            free(array[i][j].str); // = NULL;
        }
    }
}

char *string_lcs(struct sysCPS *headRef1, struct sysCPS *headRef2) {
    int l1=0, l2=0; 
    char *t, *t1, *t2;

    l1 = lengthPoset(headRef1);
    l2 = lengthPoset(headRef2);

    if((headRef2 == NULL) || (headRef1 == NULL)) {
        return "";
    }

    if(strlenN(array[l1][l2].str) > 0) {
        return array[l1][l2].str;
    }
    else {
        array[l1][l2].str = (char *)malloc(sizeof(char *));
        memset(array[l1][l2].str, 0, sizeof(array[l1][l2].str));
        strcpy(array[l1][l2].str, "");
    }


    // printf("\n>>>> %s -- %s -- %s -- %s\n", headRef1->call1, headRef1->call2, headRef2->call1, headRef2->call2);
    if(!strcmp(headRef1->call1, headRef2->call1)) { //&& (!strcmp(headRef1->call2, headRef2->call2))) {
        t1 = string_lcs(headRef1->next, headRef2->next);
        if(strlenN(array[l1][l2].str) <= (1 + strlenN(t1))) {
            // if(strlenN(array[l1][l2].str) == 0) {
                // printf("\nFFFFFF\n");
                // array[l1][l2].str = malloc((3 + strlenN(t1) + strlenN(headRef1->call1)) * sizeof(char *));
            // }

            // printf("\n%s -- %s -- %s\n", array[l1][l2].str, headRef1->call1, t1);

            if(t1) {
                if(array[l1][l2].str) {
                    free(array[l1][l2].str);
                    array[l1][l2].str = (char *)malloc((2 + strlenN(array[l1][l2].str) + strlenN(t1) + strlenN(headRef1->call1)) * sizeof(char *));
                        memset(array[l1][l2].str, 0, sizeof(array[l1][l2].str));
                    sprintf(array[l1][l2].str, "%s%s\n%s", array[l1][l2].str, headRef1->call1, t1);
                }
                else {
                    array[l1][l2].str = (char *)malloc((1 + strlenN(t1) + strlenN(headRef1->call1)) * sizeof(char *));
                        memset(array[l1][l2].str, 0, sizeof(array[l1][l2].str));
                    sprintf(array[l1][l2].str, "%s\n%s", headRef1->call1, t1);
                }
            }
            else {
                if(array[l1][l2].str) {
                    free(array[l1][l2].str);
                    array[l1][l2].str = (char *)malloc((2 + strlenN(array[l1][l2].str) + strlenN(headRef1->call1)) * sizeof(char *));
                        memset(array[l1][l2].str, 0, sizeof(array[l1][l2].str));
                    sprintf(array[l1][l2].str, "%s%s", array[l1][l2].str, headRef1->call1);
                }
                else {
                    array[l1][l2].str = (char *)malloc(strlen(headRef1->call1) * sizeof(char *));
                    memset(array[l1][l2].str, 0, sizeof(array[l1][l2].str));
                    strcat(array[l1][l2].str, "\n");
                }
            }
        }
    }
    else if(strcmp(headRef1->call1, headRef2->call1)) { // || (strcmp(headRef1->call2, headRef2->call2))) {
        t2 = string_lcs(headRef1, headRef2->next);
        t1 = string_lcs(headRef1->next, headRef2);
        t =  (strlenN(t1)>strlenN(t2))?t1:t2;
        array[l1][l2].str = (strlenN(array[l1][l2].str)>strlenN(t))?array[l1][l2].str:t;
    }
   /*
    t = strdup(array[l1][l2].str);
    free(array[l1][l2].str);
    return t;
    */return array[l1][l2].str;
}

char *string_lcsV2(struct sysCPS *headRef1, struct sysCPS *headRef2, int l1, int l2) {
    int l3=0, l4=0, i=0, j=0; 
    char *t, *t1, *t2, *t3;

    // l1 = lengthPoset(headRef1);
    // l2 = lengthPoset(headRef2);
    /*
    for(i=0; i<=l1; i++) {
        for(j=0; j<=l2; j++) {
            array[i][j].str = "";
        }
    }
    */
    if((headRef2 == NULL) || (headRef1 == NULL)) {
        return "";
    }

    l3 = strlenN(array[l1][l2].str);
    l4 = strlenN(headRef1->call1);

    if(l3 > 0) {
        // printf("\n%d  %d\n", l1, l2);
        return array[l1][l2].str;
    }
    else {
        // array[l1][l2].str = "";
    }


    if(!strcmp(headRef1->call1, headRef2->call1)) { //&& (!strcmp(headRef1->call2, headRef2->call2))) {
        t1 = string_lcsV2(headRef1->next, headRef2->next, l1-1, l2-1);
        if(l3 <= (1 + l4 + strlenN(t1))) {
            if(t1) {
                if(array[l1][l2].str) {
                    array[l1][l2].str = malloc((2 + l3 + strlenN(t1) + l4) * sizeof(char *));
                        memset(array[l1][l2].str, 0, sizeof(array[l1][l2].str));
                    sprintf(array[l1][l2].str, "%s%s\n%s", array[l1][l2].str, headRef1->call1, t1);
                }
                else {
                    array[l1][l2].str = malloc((1 + strlenN(t1) + l4) * sizeof(char *));
                        memset(array[l1][l2].str, 0, sizeof(array[l1][l2].str));
                    sprintf(array[l1][l2].str, "%s\n%s", headRef1->call1, t1);
                }
            }
            else {
                if(array[l1][l2].str) {
                    array[l1][l2].str = malloc((2 + l3 + l4) * sizeof(char *));
                        memset(array[l1][l2].str, 0, sizeof(array[l1][l2].str));
                    sprintf(array[l1][l2].str, "%s%s", array[l1][l2].str, headRef1->call1);
                }
                else {
                    array[l1][l2].str = strdup(headRef1->call1);
                    strcat(array[l1][l2].str, "\n");
                }
            }
        }
    }
    else if(strcmp(headRef1->call1, headRef2->call1)) { // || (strcmp(headRef1->call2, headRef2->call2))) {
        i = strlenN(t2 = string_lcsV2(headRef1, headRef2->next, l1, l2-1));
        l4 = strlenN(t1 = string_lcsV2(headRef1->next, headRef2, l1-1, l2));
        t =  (l4>i)?t1:t2;
        array[l1][l2].str = (l3>strlenN(t))?array[l1][l2].str:t;
    }
    
    t = array[l1][l2].str;
    return t;
}
