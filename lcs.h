/**
 *** function are LENGHT_LCS STRINGLCSV2 FREEARRAY STRLENN
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
            free(array[i][j].str1);
        }
    }
}

/**
 * finds the longest common subsequnce; returns the string
 **/
struct sStruct *string_lcs_v2(struct sysCPS *headRef1, struct sysCPS *headRef2, int l1, int l2) {
    int l3=0, l4=0, l5=0, i=0, j=0, tmp=0; 
    struct sStruct *t, *t1, *t2, *t3, *t4;
    char temp[15];

    sprintf(temp, "%d %d\n", l1, l2);
    tmp = strlen(temp);

    if((headRef2 == NULL) || (headRef1 == NULL)) {
        return NULL;
    }

    l3 = strlenN(array[l1][l2].str1);
    l4 = strlenN(headRef1->call1);
    l5 = strlenN(array[l1][l2].str2);

    if(l3 > 0) {
        t = (struct sStruct *)malloc(sizeof(struct sStruct));
        t->str1 = array[l1][l2].str1;
        t->str2 = array[l1][l2].str2;
        // t->l = lengthPoset(headRef2);
        // j = lengthPoset(headRef2);
        // t->l = array[l1][l2].l;
        return t;
    }

    if(!strcmp(headRef1->call1, headRef2->call1)) {
        t1 = string_lcs_v2(headRef1->next, headRef2->next, l1-1, l2-1);
        
        if(t1) {
            if(l3 <= (1 + l4 + strlenN(t1->str1))) {
                if(array[l1][l2].str1) {
                    t4->str1 = malloc((2 + l3 + strlenN(t1->str1) + l4) * sizeof(char *));
                    memset(t4->str1, 0, sizeof(t4));
                    sprintf(t4->str1, "%s%s\n%s", array[l1][l2].str1, headRef1->call1, t1->str1);
                    array[l1][l2].str1 = t4->str1;

           //          array[l1][l2].l = t4->l + 1;

                    t4->str2 = malloc((2 + l5 + strlenN(t1->str2) + tmp) * sizeof(char *));
                    memset(t4->str2, 0, sizeof(t4));
                    sprintf(t4->str2, "%s%s%s", array[l1][l2].str1, temp, t1->str1);
                    array[l1][l2].str1 = t4->str2;
                }
                else {
                    array[l1][l2].str1 = malloc((1 + strlenN(t1->str1) + l4) * sizeof(char *));
                    memset(array[l1][l2].str1, 0, sizeof(array[l1][l2].str1));
                    sprintf(array[l1][l2].str1, "%s\n%s", headRef1->call1, t1->str1);

                    array[l1][l2].str2 = malloc((1 + strlenN(t1->str2) + l4) * sizeof(char *));
                    memset(array[l1][l2].str2, 0, sizeof(array[l1][l2].str2));
                    sprintf(array[l1][l2].str2, "%s%s", temp, t1->str2);
                }
            }
        }
        else {
            if(l3 <= (1 + l4)) {
                if(array[l1][l2].str1) {
                    /**************************************************************************
                    array[l1][l2].str = malloc((2 + l3 + l4) * sizeof(char *));
                    memset(array[l1][l2].str, 0, sizeof(array[l1][l2].str));
                    sprintf(array[l1][l2].str, "%s%s", array[l1][l2].str, headRef1->call1);
                    ****************************************************************************/
                    t4->str1 = malloc((2 + l3 + l4) * sizeof(char *));
                    memset(t4->str1, 0, sizeof(t4));
                    sprintf(t4->str1, "%s%s", array[l1][l2].str1, headRef1->call1);
                    array[l1][l2].str1 = t4->str1;

                    t4->str2 = malloc((2 + l5 + tmp) * sizeof(char *));
                    memset(t4->str2, 0, sizeof(t4->str2));
                    sprintf(t4->str2, "%s%s", array[l1][l2].str2, temp);
                }
                else {
                    array[l1][l2].str1 = strdup(headRef1->call1);
                    strcat(array[l1][l2].str1, "\n");

                    array[l1][l2].str2 = strdup(temp);
                    // strcat(array[l1][l2].str, "\n");
                }
            }
        }
    }
    else if(strcmp(headRef1->call1, headRef2->call1)) {
        global_len++;
	
printf("\n>>>>>>><<<<<<<<<<\n");
	t2 = string_lcs_v2(headRef1, headRef2->next, l1, l2-1);
        if(t2)
            i = strlenN(t2->str1);
        else
            i = 0;

        t1 = string_lcs_v2(headRef1->next, headRef2, l1-1, l2);
        if(t1)
            l4 = strlenN(t1->str1);
        else
            l4 = 0;
        t =  (l4>i)?t1:t2;
        
        if(t) {
            if(l3 <= strlenN(t->str1)) {
                array[l1][l2].str1 = t->str1;
                array[l1][l2].str2 = t->str2;
              //  array[l1][l2].l = (array[l1][l2].l>(t->l))?(t->l):array[l1][l2].l;
            }
        }
        else {
                array[l1][l2].str1 = "";
                array[l1][l2].str2 = "";
                // array[l1][l2].l = 0;
        }
    }
    
    t = (struct sStruct *)malloc(sizeof(struct sStruct));
    t->str1 = array[l1][l2].str1;
    t->str2 = array[l1][l2].str2;
    // t->l = (array[l1][l2].l>(t->l))?(t->l):array[l1][l2].l;
    return t;
}

void string_lcs(struct sysCPS *headRef1, struct sysCPS *headRef2, int l1, int l2) {
    struct sStruct *t;
    char *tc, temp1[15], temp2[15];
    int tmp1=0, tmp2=0, i;

    

    if((headRef2 == NULL) || (headRef1 == NULL)) {
        array[l1][l2].str1 = "";
        array[l1][l2].str2 = "";
        array[l1][l2].l = 0;
        return;
    }

    if(array[l1][l2].l >= 0) {
        return;
    }

    sprintf(temp1, "%s %s\n", headRef1->call1, headRef1->call2);
    sprintf(temp2, "%d %d\n", l1, l2);
    tmp1 = strlen(temp1);
    tmp2 = strlen(temp2);
    
    if(!strcmp(headRef1->call1, headRef2->call1)) {
        string_lcs(headRef1->next, headRef2->next, l1-1, l2-1);
        // array[l1][l2].l = (array[l1][l2].l > (1 + array[l1-1][l2-1].l))?array[l1][l2]:(1 + array[l1-1][l2-1]);
        if(array[l1][l2].l < (1 + array[l1-1][l2-1].l)) {
            array[l1][l2].l = 1 + array[l1-1][l2-1].l;
            i = tmp1 + strlenN(array[l1][l2].str1) + strlenN(array[l1-1][l2-1].str1);
            tc = (char *)malloc(i * sizeof(char) + 1);
            sprintf(tc, "%s%s", array[l1-1][l2-1].str1, temp1);
            array[l1][l2].str1 = tc;
            
            i = tmp2 + strlenN(array[l1][l2].str2) + strlenN(array[l1-1][l2-1].str2);
            tc = (char *)malloc(i * sizeof(char) + 1);
            sprintf(tc, "%s%s", array[l1-1][l2-1].str2, temp2);
            array[l1][l2].str2 = tc;
        }
    }
    else {
        string_lcs(headRef1, headRef2->next, l1, l2-1);
        string_lcs(headRef1->next, headRef2, l1-1, l2);
        t = (array[l1][l2-1].l > array[l1-1][l2].l)?(&array[l1-1][l2]):(&array[l1][l2-1]);
        // array[l1][l2].l = (array[l1][l2].l>(t->l))?array[l1][l2].l:(t->l);
        if(array[l1][l2].l < (t->l)) {
            array[l1][l2].str1 = strdup(t->str1);
            array[l1][l2].str2 = strdup(t->str2);
            array[l1][l2].l = t->l;
        }
    }
}

struct sStruct *string_lcs_v3(struct sysCPS *headRef1, struct sysCPS *headRef2) {
    int l1=0, l2=0, i=0, j=0;
    struct sStruct *t;

    l1 = lengthPoset(headRef1);
    l2 = lengthPoset(headRef2);


    for(i=0; i<=l1; i++) {
        for(j=0; j<=l2; j++) {
            array[i][j].l = -1;
        }
    }

    string_lcs(headRef1, headRef2, l1, l2);

    t = (struct sStruct *)malloc(sizeof(struct sStruct));
    t->str1 = strdup(array[l1][l2].str1);
    t->str2 = strdup(array[l1][l2].str2);
    t->l = array[l1][l2].l;
    
    return t;
}
