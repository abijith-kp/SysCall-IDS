void process_sig() {

}

// File name gives the process name
// the signature file contains the processname and an extension name
void create(char *fileN) {
	FILE *file=fopen(fileN, "r");
    char sigFile[100], name[100];

    struct sysCPS *tmp;

	fscanf(file, "%s", name);
	while(!feof(file)) {
    printf("\n%s\n", name);
		makePoset(name);
                clean();
                if(flag == 0) {
                        headSIG = head;
                        head = NULL;
                        tailSIG = tail;
                        tail = NULL;
                        countSIG = countT;
                        countT = 0;
                        flag = 1;
	                    fscanf(file, "%s", name);
                        continue;
		}

		process_sig(); // head and headSIG
		// process signature
	    fscanf(file, "%s", name);
	}

    fclose(file);
    strcat(sigFile, fileN);
    strcat(sigFile, ".sig");
    
    printf("\nEND\n");
    tmp = headSIG;
    file = fopen(sigFile, "w");
    while(tmp) {
    printf("\nEND %s\n", sigFile);
        fprintf(file, "%s %s\n", tmp->call1, tmp->call2);
        tmp = tmp->next;
    }
    fclose(file);
	// write it into a file
}
