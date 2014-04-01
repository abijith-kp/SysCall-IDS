void process_sig() {

}

// File name gives the process name
// the signature file contains the processname and an extension name
void create(char *fileN) {
	FILE *file=fopen(fileN);

	char name[100];

	fscanf(file, "%s", name);
	while(!feof(file)) {
		makePoset(file);
                clean();
                if(flag == 0) {
                        headSIG = head;
                        head = NULL;
                        tailSIG = tail;
                        tail = NULL;
                        countSIG = countT;
                        countT = 0;
                        flag = 1;
                        continue;
		}

		process_sig(); // head and headSIG
		// process signature
	}

	// write it into a file
}
