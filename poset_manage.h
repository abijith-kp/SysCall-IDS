// this also modified with tailRef
void addNode_poset(struct sysCPS **tmpRef, struct sysCPS **headRef, struct sysCPS **tailRef) {
        if(!(*headRef)) {
                *headRef = *tmpRef;
                *tailRef = *tmpRef;
        }

        (*tailRef)->next = (*tmpRef);
        (*tailRef) = (*tmpRef);
}
	
struct sysCPS *makeNode(char *call, int t, struct sysCPS *tmpN) {
        struct sysCPS *tmp;

        if(t == 1) {
                tmp = (struct sysCPS *)malloc(sizeof(struct sysCPS));
                tmp->call1 = strdup(call);
                tmp->next = NULL;
                return tmp;
        }
        else {
                tmpN->call2 = strdup(call);
                return tmpN;
        }
}

void makePoset(char *fileName) {
	char *tmp = "";
	char call[5];

	FILE *file = fopen(fileName, "r");
	int k=1;

	head = NULL;
	
        while(!feof(file)) {
                memset(call, 0, sizeof(call));
		fscanf(file, "%s\n", call);
		countPS++; // length of the poset members

                if(strcmp(tmp, "") == 0) {
                        tmp = strdup(call);
                        k = 2;
                        continue;
                }

                if(k == 1) {
                        random_var = (struct sysCPS*)malloc(sizeof(struct sysCPS));
                        
                        random_var->call1 = tmp;
                        random_var->call2 = strdup(call);
                        random_var->next = NULL;
                        
                        tmp = strdup(call);
                        addNode_poset(&random_var, &head, &tail);
                        k++;
                }
                else if(k == 2) {
                        
                        random_var = (struct sysCPS*)malloc(sizeof(struct sysCPS));
                        
                        random_var->call1 = tmp;
                        random_var->call2 = strdup(call);
                        random_var->next = NULL;
                        
                        tmp = strdup(call);
                        addNode_poset(&random_var, &head, &tail);
                        
                        k = 1;
                }
	}

        fclose(file);
}

int lengthPoset(struct sysCPS *headRef) {
	int l=0;

	while(headRef) {
		l++;
		headRef = headRef->next;
	}

	return l;
}

void printPoset(struct sysCPS *headRef) {
        while(headRef) {
                printf("%s\t%s\n", headRef->call1, headRef->call2);
                headRef = headRef->next;
        }
}
