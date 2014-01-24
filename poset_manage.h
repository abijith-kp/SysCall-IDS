struct sysCPS* random;   

void addNode(char *call1, char *call2, struct sysCPS **headRef, struct sysCPS **tailRef){ 
        struct sysCPS t, *tmp = (struct sysCPS *)malloc(sizeof(struct sysCPS));
        memset(tmp, 0, sizeof(struct sysCPS));

	tmp->call1 = strdup(call1);
	tmp->call2 = strdup(call2);
	tmp->next = NULL;

        if(!(*headRef)) {
		*headRef = tmp;
		*tailRef = tmp;
		return;
	}

        /*
        while(t->next) {
                t = t->next;
        }
        t->next = tmp;
        */
        // modified by adding tailRef
        (*tailRef)->next = tmp;
        *tailRef = tmp;
}

// this also modified with tailRef
void addNode(struct sysCPS **tmpRef, struct sysCPS **headRef) {
        struct sysCPS *tmp = *headRef;

        if(!(*headRef)) {
                //tmp = tmp->next;
                *headRef = *tmpRef;
                *tailRef = *tmpRef;
        }

        (*tailRef)->next = (*tmpRef);
        (*tailRef) = (*tmpRef);
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
	char tmp[5] = "";
	char call[5];
        // countI = 0;

	FILE *file = fopen(fileName, "r");
	int k=0;

	head = NULL;
	
        while(!feof(file)) {
		fscanf(file, "%s\n", call);
		k++; // = find_count(call);

                if(k == 1) {
                        random = (struct sysCPS*)malloc(sizeof(struct sysCPS));
                        memset(random, 0, sizeof(struct sysCPS));
                        random->call1 = (strcmp(tmp, "") == 0)?strdup(call):strdup(tmp);
                        k++;
                }
                else if(k == 2) {
                        random->call2 = strdup(call);
                        tmp = strdup(call);
                        random->next = NULL;
                        addNode(&random, &head, &tail); //, &tailI);
                        k = 0;
                        // countI++;
                }
	}

        fclose(file);
}
