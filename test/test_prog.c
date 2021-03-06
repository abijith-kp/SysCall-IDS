#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../data_structure.h"
#include "../poset_manage.h"
#include "../clean.h"

//struct sysCPS *head;
/*
char* lcs(const char *a, const char *b, char *out)
{
	int longest = 0;
	int match(const char *a, const char *b, int dep) {
		if (!a || !b) return 0;
		if (!*a || !*b) {
			if (dep <= longest) return 0;
			out[ longest = dep ] = 0;
			return 1;
		}
 
		if (*a == *b)
			return match(a + 1, b + 1, dep + 1) && (out[dep] = *a);
 
		return	match(a + 1, b + 1, dep) + 
			match(strchr(a, *b), b, dep) +
			match(a, strchr(b, *a), dep);
	}
 
	return match(a, b, 0) ? out : 0;
}
*/
struct sysCPS *locate(struct sysCPS *headRef, struct sysCPS tmp) {
    while(headRef) {
        if (!strcmp(headRef->call1, tmp.call1)) { // && !strcmp(headRef->call2, tmp.call2)) {
            return headRef;
        }
        
        headRef = headRef->next;
    }
    return NULL;
}


// KMP algo or similar type of algo
char* lcs(struct sysCPS *a, struct sysCPS *b, char *out)
{
	int longest = 0;
	int match(struct sysCPS *a, struct sysCPS *b, int dep) {
		// if (!a || !b) return 0;
		if ((a == NULL) || (b == NULL)) return 0;
		if (((a->next) == NULL) || ((b->next) == NULL)) {
			if (dep <= longest) return 0;
			out[ longest = dep ] = 0;
			return 1;
		}
 
		if (!strcmp(a->call1, b->call1)) {
            out[dep] = atoi(a->call1);
    printf("\nTRY %s\n", a->call1);
			return match(a->next, b->next, dep + 1);
        }

		return	match(a->next, b->next, dep) + 
			match(locate(a, *b), b, dep) +
			match(a, locate(b, *a), dep);
	}
 
	return match(a, b, 0) ? out : 0;
}

;
/*
int *lcs2(struct sysCPS *a, struct sysCPS *b, int *out)
{
	int longest = 0;
    struct sStruct array[1000][1000];

	int match(struct sysCPS *a, struct sysCPS *b, int dep) {
		// if (!a || !b) return 0;
		if ((a == NULL) || (b == NULL)) return 0;
		if (((a->next) == NULL) || ((b->next) == NULL)) {
			if (dep <= longest) return 0;
			out[ longest = dep ] = 0;
			return 1;
		}
 
		if (!strcmp(a->call1, b->call1)) {
            strcat(array[lengthPoset(a)][lengthPoset(b)], a->call1);
    printf("\nTRY %s\n", a->call1);
			return match(a->next, b->next, dep + 1);
        }

		return	match(a->next, b->next, dep) + 
			match(locate(a, *b), b, dep) +
			match(a, locate(b, *a), dep);
	}
 
	return match(a, b, 0) ? out : 0;
}
*/

struct sStruct {
    char *str;
};
struct sStruct array[1000][1000];

int strlenN(char *str) {
    if(str) {
        return strlen(str);
    }

    return 0;
}

void freeArray(int l1, int l2) {
    int i=0, j=0;

    printf("\ndfdfdfdfdf\n");
    for(i=1; i<=l1; i++) {
        for(j=1; j<=l2; j++) {
            array[i][j].str = "";
        }
    }
}

char *string_lcs(struct sysCPS *headRef1, struct sysCPS *headRef2) {
    int l1=0, l2=0; 
    char *t, *t1, *t2, *t3;

    l1 = lengthPoset(headRef1);
    l2 = lengthPoset(headRef2);

    if((headRef2 == NULL) || (headRef1 == NULL)) {
        return NULL;
    }

    if(strlenN(array[l1][l2].str) > 0) {
        return array[l1][l2].str;
    }
    else {
        array[l1][l2].str = "";
    }


    // printf("\n>>>> %s -- %s -- %s -- %s\n", headRef1->call1, headRef1->call2, headRef2->call1, headRef2->call2);
    if(!strcmp(headRef1->call1, headRef2->call1)) { //&& (!strcmp(headRef1->call2, headRef2->call2))) {
        t1 = string_lcs(headRef1->next, headRef2->next);
        if(strlenN(array[l1][l2].str) <= (1 + strlenN(headRef2->call1) + strlenN(t1))) {
            // if(strlenN(array[l1][l2].str) == 0) {
                // printf("\nFFFFFF\n");
                // array[l1][l2].str = malloc((3 + strlenN(t1) + strlenN(headRef1->call1)) * sizeof(char *));
            // }

            // printf("\n%s -- %s -- %s\n", array[l1][l2].str, headRef1->call1, t1);

            if(t1) {
                if(array[l1][l2].str) {
                    array[l1][l2].str = malloc((2 + strlenN(array[l1][l2].str) + strlenN(t1) + strlenN(headRef1->call1)) * sizeof(char *));
                        memset(array[l1][l2].str, 0, sizeof(array[l1][l2].str));
                    sprintf(array[l1][l2].str, "%s%s\n%s", array[l1][l2].str, headRef1->call1, t1);
                }
                else {
                    array[l1][l2].str = malloc((1 + strlenN(t1) + strlenN(headRef1->call1)) * sizeof(char *));
                        memset(array[l1][l2].str, 0, sizeof(array[l1][l2].str));
                    sprintf(array[l1][l2].str, "%s\n%s", headRef1->call1, t1);
                }
            }
            else {
                if(array[l1][l2].str) {
                    array[l1][l2].str = malloc((2 + strlenN(array[l1][l2].str) + strlenN(headRef1->call1)) * sizeof(char *));
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
        t2 = string_lcs(headRef1, headRef2->next);
        t1 = string_lcs(headRef1->next, headRef2);
        t =  (strlenN(t1)>strlenN(t2))?t1:t2;
        array[l1][l2].str = (strlenN(array[l1][l2].str)>strlenN(t))?array[l1][l2].str:t;
    }
    
    t = array[l1][l2].str;
    return t;
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


int main(int argc, char **argv) {
    struct sysCPS *headRef=NULL;
    char buf1[500], buf2[500], *tmp;
    int l1=0, l2=0, i=0, t, j=0, buf[500];
    FILE *file = fopen("input", "r");
/*
    fscanf(file, "%s", buf1);
    makePoset(buf1);
    while(!feof(file)) {
    printf("\n%s\n", buf1);
        if(i == 0) {
    printf("\nJUST %d %d\n", lengthPoset(head), lengthPoset(headRef));
            headRef = head;
            head = NULL;
            fscanf(file, "%s", buf1);
            i = 1;
            continue;
        }
        // head = NULL;
        */
        // makePoset("a1");
        // makePoset("input2");
        makePoset("../dataset/login2");
        clean();
        headRef = head;
        // makePoset("a2");
        makePoset("../dataset/attack1");
        clean();
    
    // tmp = lcs2(headRef, head, buf);
        // makePoset(buf1);
    l2 = lengthPoset(head);
    l1 = lengthPoset(headRef);
    printf("\nJUST %d %d\n", l2, l1);
        // headRef = head;
        tmp = string_lcsV2(headRef, head, l1, l2);
        makePoset("../dataset/login1");
        // tmp = string_lcs(headRef, head);
/*
    for(i=0; i<=l1; i++) {
        for(j=0; j<=l2; j++) {
            printf("\t[%s]", array[i][j].str);
        }
        printf("\n----------------------------------\n");
    }
*/

        freeArray(lengthPoset(headRef), lengthPoset(head));
            // printf("\n dfdsf %s\n", tmp);
            /*
        headRef = head;
        head = NULL;
        fscanf(file, "%s", buf1);
        // i++;
    // freeArray(lengthPoset(headRef), lengthPoset(head));
        // if(tmp)
            printf("\n>>>> JUST %d %d\n", lengthPoset(head), lengthPoset(headRef));
    }
    // sscanf(tmp, "%d", &t);
    // pri
    // while()
    // printf("\n%d\n", tmp[4]);

    // fprintf(file, "%s", tmp);
    */
    fclose(file);
    return 0;
}
