#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../data_structure.h"
#include "../poset_manage.h"

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

struct sStruct {
    char *str;
};
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

int strlenN(char *str) {
    if(str) {
        return strlen(str);
    }

    return 0;
}
struct sStruct array[1000][1000];
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


    if(!strcmp(headRef1->call1, headRef2->call1)) { // && (!strcmp(headRef1->call2, headRef2->call2))) {
        t1 = string_lcs(headRef1->next, headRef2->next);
        if(strlenN(array[l1][l2].str) <= (1 + strlenN(t1))) {
            if(strlenN(array[l1][l2].str) == 0) {
                printf("\nFFFFFF\n");
                // array[l1][l2].str = malloc((3 + strlenN(t1) + strlenN(headRef1->call1)) * sizeof(char *));
            }

            printf("\n%s -- %s -- %s\n", array[l1][l2].str, headRef1->call1, t1);

            if(t1) {
                if(array[l1][l2].str) {
                    array[l1][l2].str = malloc((2 + strlenN(array[l1][l2].str) + strlenN(t1) + strlenN(headRef1->call1)) * sizeof(char *));
                    sprintf(array[l1][l2].str, "%s %s %s", array[l1][l2].str, headRef1->call1, t1);
                }
                else {
                    array[l1][l2].str = malloc((1 + strlenN(t1) + strlenN(headRef1->call1)) * sizeof(char *));
                    sprintf(array[l1][l2].str, "%s %s", headRef1->call1, t1);
                }
            }
            else {
                if(array[l1][l2].str) {
                    array[l1][l2].str = malloc((2 + strlenN(array[l1][l2].str) + strlenN(headRef1->call1)) * sizeof(char *));
                    sprintf(array[l1][l2].str, "%s %s", array[l1][l2].str, headRef1->call1);
                }
                else {
                    array[l1][l2].str = strdup(headRef1->call1);
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
    
    return array[l1][l2].str;
}


int main(int argc, char **argv) {
    struct sysCPS *headRef;
    char buf1[500][5], *tmp;
    int t, buf[500];
    FILE *file = fopen("testfile", "w");

    makePoset("input1");
    headRef = head;
    head = NULL;
    makePoset("input2");
    
    // printf("\nJUST %d %d\n", lengthPoset(head), lengthPoset(headRef));
    // tmp = lcs2(headRef, head, buf);
    tmp = string_lcs(headRef, head);
    if(tmp)
    printf("\nJUST %d %d\n", lengthPoset(head), lengthPoset(headRef));
    // sscanf(tmp, "%d", &t);
    // pri
    // while()
    // printf("\n%d\n", tmp[4]);

    fprintf(file, "%s", tmp);
    fclose(file);
    return 0;
}
