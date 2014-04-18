/**
*** functions used are addNode_node makelist 
*
**/

void addNode_node(char call[20], struct sysCPS **headRef, struct sysCPS **tailRef) {
	struct sysCPS *tmp = (struct sysCPS *)malloc(sizeof(struct sysCPS));
        memset(tmp, 0, sizeof(struct sysCPS));

	tmp->call1 = strdup(call);
	tmp->next = NULL;

	if(!(*headRef)) {
		*headRef = tmp;
		*tailRef = tmp;
		return;
	}

	(*tailRef)->next = tmp;
	*tailRef = tmp;
}

struct sysCPS *makeList(char *fileName) {
	char call[20];
        countI = 0;

	FILE *file = fopen(fileName, "r");

	struct sysCPS *tmpH = NULL;
	struct sysCPS *tmpT = NULL;
        tmpT = NULL;
	while(!feof(file)) {
		fscanf(file, "%s\n", call);
		addNode_node(call, &tmpH, &tmpT);
	}

        fclose(file);
        return tmpH;
}
