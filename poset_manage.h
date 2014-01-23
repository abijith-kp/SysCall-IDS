struct sysCPS* random;   

void addNode(char *call1, char *call2, struct sysCPS **headref){ 
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

void addNode()
	

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


void makePoset(char *fileName) {
	int i=0;
	char call[20];
        countI = 0;

	FILE *file = fopen(fileName, "r");
	int k=0;

	head = NULL;
        // tailI = NULL;
	while(!feof(file)) {
		fscanf(file, "%s\n", call);
		k++; // = find_count(call);

                if(k == 1) {
                        random = (struct sysCPS*)malloc(sizeof(struct sysCPS));
                        strdup(random->call1, call);
                        k++;
                }
                if(k == 2) {
                ran
                        addNode(&random, &head); //, &tailI);
                        k = 0;
                        countI++;
                }
	}

        fclose(file);
}
