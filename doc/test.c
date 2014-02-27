#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *logFile = "log", *logDict = "dict", *sysFile = "syscall", *sigFile = "signature", appName[100];

struct sysC {
	char *call;
	int count;
	struct sysC *next;
} headC[244];

struct sysC *headI = NULL, *tailI = NULL; // Initial list of log
struct sysC *headR = NULL, *tailR = NULL; // 1st time R=I,
struct sysC *headT = NULL, *tailT = NULL; // compare I R
struct sysC *headTMP = NULL, *tailTMP = NULL; // compare I R
struct sysC *headTD = NULL, *tailTD = NULL; // compare I R
struct sysC *headSIG = NULL, *tailSIG = NULL; // compare I R
struct sysC *headSIGBB = NULL, *tailSIGBB = NULL; // compare I R


int countC = 0, countI = 0, countR = 0, countT = 0, countTD = 0, countSIG = 0, countSIGBB = 0, flag = 0, continueFlag = 0;

void freeMem(struct sysC *headRef) {
        struct sysC *tmp = headRef, *tmp1=NULL;

        while(tmp) {
                tmp1 = tmp->next;
                free(tmp);
                tmp = tmp1;
        }
}

int countList(struct sysC *head) {
        int c=0;
        
        while(head) {
                c++;
                head = head->next;
        }

        return c;
}

void showList(struct sysC *tmp) {
        printf("\n");

        while(tmp) {
                printf(" %s %d\n", tmp->call, tmp->count);
                tmp = tmp->next;
        }
        printf("\n");
}

void writeSIG() {
        char tmp[100];
        //printf("\n %s \n", appName);
        sprintf(tmp, "%s.%s", appName, sigFile);
        //printf("\n %s \n", tmp);
        strcpy(appName, tmp);
        appName[sizeof(appName)-1] = '\0';

        FILE *file = fopen(appName, "w");
        
        while(headSIG) {
                fprintf(file, headSIG->call);
                fprintf(file, "\n");
                headSIG = headSIG->next;
        }

        fprintf(file, "\n");
        // printf("\n NEWLINE \n");
        
        while(headSIGBB) {
                fprintf(file, headSIGBB->call);
                fprintf(file, "\n");
                printf("\n sdfsdfdffff %s \n", headSIGBB->call);
                headSIGBB = headSIGBB->next;
        }

        // strcpy(appName, "");
        fclose(file);
}

int find_count(char call[20]) {
	int i = 0;
	while(i < countC) {
		if(strcmp(headC[i].call, call) == 0) {
			headC[i].count++;
			return headC[i].count;
		 }
		i++;
	}
	return 0;
}

void addNode(char call[20], int tag, struct sysC **headRef, struct sysC **tailRef) {
	struct sysC *tmp = (struct sysC *)malloc(sizeof(struct sysC *));
        memset(tmp, 0, sizeof(struct sysC));

	tmp->call = strdup(call);
	tmp->count = tag;
	tmp->next = NULL;

	if(!(*headRef)) {
		*headRef = tmp;
		*tailRef = tmp;
		return;
	}

	(*tailRef)->next = tmp;
	*tailRef = tmp;
}

void makeSyscallList() {
	char call[20];
	FILE *file = fopen(sysFile, "r");

	while(!feof(file)) {
		fscanf(file, "%s\n", call);
		headC[countC].call = strdup(call);
		headC[countC].count = 0;
		countC++;
	}
	
	fclose(file);
}


void makeList(char *fileName) {
	int i=0;
	char call[20];
        countI = 0;

	FILE *file = fopen(fileName, "r");
	int k=0;
        /*struct sysC *tmp = headI;
        struct sysC *tmp1 = NULL;
        while(!tmp)
        {
                tmp1=tmp;
                tmp=tmp->next;
                free(tmp1);
        }*/

	headI = NULL;
        tailI = NULL;
	while(!feof(file)) {
		fscanf(file, "%s\n", call);
		k = find_count(call);
		addNode(call, k, &headI, &tailI);
                countI++;
	}

        //printf("\nI %d\n", countI);
        // resetting the values
        for(i=0;i<countC;i++)
                headC[i].count=0;
	
        fclose(file);
}

// return value: 1 ==> program continues
//               0 ==> program terminates
// Atleast 4 consecutive signatures should be same
int compareWithSIG() {
        int f = 1;

        if(continueFlag == 0) {
                continueFlag++;
                f = 1;
        }
        else if(countList(headR) == countList(headSIG)) {
                continueFlag++;
                if(continueFlag == 5) {
                        f = 0;
                }
        }
        else {
                continueFlag = 0;
        }

        return f;
}


void concat() { //struct sysC **tmpHTMP, struct sysC **tmpTTMP, struct sysC **tmpHSIGBB, struct sysC **tmpTSIGBB) {
        if(!headSIGBB) {
                headSIGBB = headTMP;
                tailSIGBB = tailTMP;
                return;
        }

        if(headTMP) {
        // printf("\n asfdsadsf \n");
                tailSIGBB->next = headTMP;
                tailSIGBB = tailTMP;
                // printf("\n TEST %s \n", headTMP->call);
        }
        headTMP = NULL;
        tailTMP = NULL;
        // printf("\n >>>> asfdsadsf \n");
        /*
        else {
        printf("\n TRY \n");
        }
        */
        // (*tmpTSIGBB)->next = *tmpHTMP;
}

void findSignature2() {
        struct sysC *tmp1 = headT, *tmp2 = headTD, *tmp3 = headT, *tmpSIG = NULL;
        int f = 0;
        countSIG = 0;

        // tmpSIG = headSIG;
        headSIG = NULL;

        // printf("\n sfsdfdfff \n");
        while(tmp1 && tmp2) {
                tmp3 = tmp1;
                f = 0;                  // added a flag to check for the comparison correctness
                while(tmp3) {
                        if(strcmp(tmp3->call, tmp2->call) == 0) { // && (tmp3->count == tmp2->count)) {
                                addNode(tmp3->call, tmp3->count, &headSIG, &tailSIG);
                                countSIG++;
                                f = 1;  // flag set to 1
                                break;
                        }
                        else {
                                addNode(tmp3->call, tmp3->count, &headTMP, &tailTMP);
                        }
                        tmp3 = tmp3->next;
                }

                // only if the flag is set to 1, there was a same value for the
                // head of both lists
                if(f) {
                        // printf("\n >>>>> try  \n");
                        concat(); //&headTMP, &tailTMP, &headSIGBB, &tailSIGBB);
                        tmp1 = tmp3->next;
                }
                else {
                        // printf("\n mmmm \n");
                        addNode(tmp2->call, tmp2->count, &headSIGBB, &tailSIGBB);
                        countSIGBB++;
                }
                tmp2 = tmp2->next;
        }
        
        concat(); //&headTMP, &tailTMP, &headSIGBB, &tailSIGBB);

        // showList(headSIG);
        if(!compareWithSIG()) {
                // showList(headSIG);
                printf("\nLog file generated in %s\n", appName);
                writeSIG();
                exit(0);
        }
        // printf("\nfindSignature2 I:%d    R:%d \n", countI, countR);
}

void findSignature() {
        printf("\nfindSignature\n");
        // compares headT and headTD and finds the intersection
        // puts dat as the signature if headSig is NULL
        // and along with dat puts headR as headSig
        
        struct sysC *tmp1 = headT, *tmp2 = headTD, *tmp3 = headT, *tmpSIG = NULL;
        int f = 0;
        countSIG = 0;

        // tmpSIG = headSIG;
        headSIG = NULL;

        while(tmp1 && tmp2) {
                tmp3 = tmp1;
                f = 0;                  // added a flag to check for the comparison correctness
                while(tmp3) {
                        if((strcmp(tmp3->call, tmp2->call) == 0) && (tmp3->count == tmp2->count)) {
                                addNode(tmp3->call, tmp3->count, &headSIG, &tailSIG);
                                countSIG++;
                                f = 1;  // flag set to 1
                                break;
                        }
                        tmp3 = tmp3->next;
                }

                // only if the flag is set to 1, there was a same value for the
                // head of both lists
                if(f) {

                        tmp1 = tmp1->next;
                }

                tmp2 = tmp2->next;
        }

        // compares tmpSIG and headSIG and puts the currect result in headSIG

        // showList(headSIG);
        if(!compareWithSIG()) {
                // showList(headSIG);
                writeSIG();
                printf("\nLog file generated in %s\n", appName);
                exit(0);
        }
}

struct sysC *newList(struct sysC *head) {
        struct sysC *tmp;
        
        while(head) {
                tmp = head->next;
                addNode(head->call, head->count, &headR, &tailR);
                free(head);
                head = tmp;
        }

        return headR;
}

void compareList() {
        printf("\nCOMPARE_LIST\n");
        flag = 0;
        countT = 0;
        countTD = 0;
        // countR = 0;
        // printf("\nCOMPARE LIST: \n");
        // sleep(1);
        if(!headR) {
                headR = headI; //newList(headI);
                tailR = tailI;
                countR = countI;
                //printf("\nR %d\n", countI);
                tailI=NULL;
                headI=NULL;
                    return;
        }

        //printf("\nR %d\n", countR);
        struct sysC *tmp1 = headR, *tmp2 = headI, *tmp;

        tmp = NULL;
        while((tmp1 != NULL) && (tmp2 != NULL)) {
                // printf(" %d  %d \n", countList(tmp1), countList(tmp2));

                tmp = tmp2;
                flag=0;
                while(tmp) {
                        if(strcmp(tmp1->call, tmp->call)==0) { //&& (tmp1->count == tmp->count)) {
                                // printf(">>>> %d %d \n", countList(tmp), countT);
                                flag = 1;
                                addNode(tmp1->call, tmp1->count, &headT, &tailT);
                                countT++;
                                tmp1 = tmp1->next;
                                tmp2 = tmp->next;
                                break;
                        }
                        tmp = tmp->next;
                }

                if(!flag)
                        tmp1 = tmp1->next;
        }

        // exit(1);
        //printf("\nT %d\n", countT);

        tmp = NULL;
        tmp1 = headI;
        tmp2 = headR;
        
        while(tmp1 && tmp2) {
                tmp = tmp2;
                flag=0;
                // printf(" %d  %d \n", countList(tmp1), countList(tmp2));
                while(tmp) {
                        if(strcmp(tmp1->call, tmp->call)==0) { // && (tmp1->count == tmp->count)) {
                                // printf("%d %d \n", countList(tmp), countTD);
                                flag = 1;
                                addNode(tmp1->call, tmp1->count, &headTD, &tailTD);
                                countTD++;
                                tmp1 = tmp1->next;
                                tmp2 = tmp->next;
                                break;
                        }
                        tmp = tmp->next;
                }

                if(!flag)
                        tmp1 = tmp1->next;
        }
        
        // exit(1);
        //printf("\nTD %d\n", countTD);
        
        // since old headR and headI are not needed anymore
        // freeMem(headR);
        // freeMem(&headI);
/*
        printf("\nheadI: ");
        showList(headI);
        printf("\nheadR: ");
        showList(headR);
        printf("\nheadT: ");
        showList(headT);
        printf("\nheadTD: ");
        showList(headTD);
*/      
        printf("\n START TEST \n");
        findSignature2();
        printf("\n END TEST \n");
        //temporary adjustment
        //printf("\nSIG %d \n", countSIG);
        headR = headSIG;
        countR = countSIG;
         /*struct sysC *tmp = headI;
        struct sysC *tmp1 = NULL;
        while(!tmp)
        {
                tmp1=tmp;
                tmp=tmp->next;
                free(tmp1);
        }*/

	headT = NULL;
        tailT = NULL;
        headTD = NULL;
        tailTD = NULL;

        //after finding signature remove headT and headTD
        // freeMem(&headTD);
}

int main(int argc, char **argv) {
        strcpy(appName, argv[1]);

        FILE *file = fopen(".ids/list", "r");
        char fileN[200];
	makeSyscallList();

        while(!feof(file)) {
                fscanf(file, "%s\n", fileN);
                printf("\n %s \n", fileN);
                makeList(fileN);
                compareList();
                // printf("\n >>>>><<<<< \n");
        }
      
        // printf("\n START TEST2 \n");
        writeSIG();
        // printf("\n END TEST2 \n");
        //printf("\nLog file generated in %s\n", appName);
        // showList(headSIG);
        // printf("\n %d \n", countList(headSIG));
	return 0;
}
