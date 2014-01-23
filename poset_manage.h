struct sysCPS* random;   

void addNode(char *call1, char *call2, struct sysCPS **headref){ 
        struct sysCPS t, *tmp = (struct sysCPS *)malloc(sizeof(struct sysCPS));
        memset(tmp, 0, sizeof(struct sysCPS));

	tmp->call1 = strdup(call1);
	tmp->call2 = strdup(call2);
	tmp->next = NULL;

        t = (*headRef);
	if(!t) {
		*headRef = tmp;
		//*tailRef = tmp;
		return;
	}

        while(t->next) {
                t = t->next;
        }
        t->next = tmp;
}

void addNode(struct sysCPS **tmpRef, struct sysCPS **headRef) {
        struct sysCPS *tmp = *headRef;

        if(tmp) {
                tmp = tmp->next;
        }

        while(tmp->next) {
                tmp = tmp->next;
        }

        tmp->next = (*tmpRef);
}
	
/*
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
*/

void makePoset(char *fileName) {
	int i=0;
	char call[20];
        countI = 0;

	FILE *file = fopen(fileName, "r");
	int k=0;

	head = NULL;
	
        while(!feof(file)) {
		fscanf(file, "%s\n", call);
		k++; // = find_count(call);

                if(k == 1) {
                        random = (struct sysCPS*)malloc(sizeof(struct sysCPS));
                        memset(random, 0, sizeof(struct sysCPS));
                        random->call1 = strdup(call);
                        k++;
                }
                if(k == 2) {
                        random->call2 = strdup(call);
                        random->next = NULL;
                        addNode(&random, &head); //, &tailI);
                        k = 0;
                        // countI++;
                }
	}

        fclose(file);
}
