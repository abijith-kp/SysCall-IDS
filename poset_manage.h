// this also modified with tailRef
void addNode_poset(struct sysCPS **tmpRef, struct sysCPS **headRef, struct sysCPS **tailRef) {
        struct sysCPS *tmp = *headRef;

        if(!(*headRef)) {
                //tmp = tmp->next;
                *headRef = *tmpRef;
                *tailRef = *tmpRef;
        }

        (*tailRef)->next = (*tmpRef);
        (*tailRef) = (*tmpRef);
}
	
struct sysCPS *makeNode(char *call, int t, struct sysCPS *tmpN) {
        struct sysCPS *tmp;

        if(t == 1) {
        // printf("\n %s %d \n", call, t);
                tmp = (struct sysCPS *)malloc(sizeof(struct sysCPS));
                tmp->call1 = strdup(call);
                tmp->next = NULL;
                return tmp;
        }
        else {
        // printf("\n %s %d %s \n", call, t, tmpN->call1);
                tmpN->call2 = strdup(call);
                return tmpN;
        }
}

void makePoset(char *fileName) {
	char *tmp = "";
	char call[5];
        // countI = 0;

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
                        //random_var = makeNode(call, 1, NULL);
                        /*
                        random_var = (struct sysCPS*)malloc(sizeof(struct sysCPS));
                        memset(random_var, 0, sizeof(struct sysCPS));
                        random_var->call1 = (strcmp(tmp, "") == 0)?strdup(call):strdup(tmp);
                        */
                        // tmp = strdup(call);
                        random_var = (struct sysCPS*)malloc(sizeof(struct sysCPS));
                        
                        random_var->call1 = tmp;
                        random_var->call2 = strdup(call);
                        random_var->next = NULL;
                        
                        tmp = strdup(call);
                        addNode_poset(&random_var, &head, &tail);
                        k++;
                        // printf("\n TEST %s %d \n", call, k);
                }
                else if(k == 2) {
                        // random_var = makeNode(call, 2, random_var);
                        
                        random_var = (struct sysCPS*)malloc(sizeof(struct sysCPS));
                        
                        random_var->call1 = tmp;
                        random_var->call2 = strdup(call);
                        random_var->next = NULL;
                        
                        tmp = strdup(call);
                        addNode_poset(&random_var, &head, &tail);
                        
                        // printf("\n %s %s \n", random_var->call1, call);
                        k = 1;
                        // printf("\n TEST %s %d \n", call, k);
                        // countI++;
                }
                // printf("\n TEST %s %d \n", call, k);
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
                printf("%s \t %s \n", headRef->call1, headRef->call2);
                headRef = headRef->next;
        }
}
