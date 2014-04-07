/**
 * to find the length of longest common subsequnce
 **/
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

/**
 * wrapper for strlen function to accept string which are NULL
 **/
int strlenN(char *str) {
    if(str) {
        return strlen(str);
    }

    return 0;
}

/**
 * to free the space allocated for the array during LCS identification
 **/
void freeArray(int l1, int l2) {
    int i=0, j=0;

    for(i=1; i<=l1; i++) {
        for(j=1; j<=l2; j++) {
            free(array[i][j].str);
        }
    }
}

/**
 * finds the longest common subsequnce; returns the string
 **/
char *string_lcs_v2(struct sysCPS *headRef1, struct sysCPS *headRef2, int l1, int l2) {
    int l3=0, l4=0, i=0, j=0; 
    char *t, *t1, *t2, *t3;

    if((headRef2 == NULL) || (headRef1 == NULL)) {
        return "";
    }

    l3 = strlenN(array[l1][l2].str);
    l4 = strlenN(headRef1->call1);

    if(l3 > 0) {
        return array[l1][l2].str;
    }

    if(!strcmp(headRef1->call1, headRef2->call1)) {
        t1 = string_lcs_v2(headRef1->next, headRef2->next, l1-1, l2-1);
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
    else if(strcmp(headRef1->call1, headRef2->call1)) {
        i = strlenN(t2 = string_lcs_v2(headRef1, headRef2->next, l1, l2-1));
        l4 = strlenN(t1 = string_lcs_v2(headRef1->next, headRef2, l1-1, l2));
        t =  (l4>i)?t1:t2;
        array[l1][l2].str = (l3>strlenN(t))?array[l1][l2].str:t;
    }
    
    return array[l1][l2].str;
}
