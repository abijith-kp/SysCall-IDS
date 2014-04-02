int n=0, list[1000];
double mean=0.0, dev=0.0;

// this only works at runtime feed back system
void findVal(int mismatch, int i) {
    double var, t;

    t = ((mean * n) + mismatch) / i;
    var = (dev * dev) + ((mismatch - t) * (mismatch - mean));
    dev = sqrt(var);
    mean = t;
    n = i;
}

void findMeanVar() {
    int i=0, t=0;

    for(i=0; i<n; i++) {
        mean += list[i];
    }
    mean /= n;

    for(i=0; i<n; i++) {
        t = mean - list[i];
        // t = t * t;
        dev += (t * t);
    }
    dev = sqrt(dev/n);
}

// returns the number of mismatches
int process_sig() {

}

// File name gives the process name
// the signature file contains the processname and an extension name
void create(char *fileN) {
	FILE *file=fopen(fileN, "r");
    char sigFile[100], name[100];
    int mismatch=0, i=0, flag=0;

    struct sysCPS *tmp;

    n = 0;
    mean = 0.0;
    dev = 0.0;

	fscanf(file, "%s", name);
    // i++;
	while(!feof(file)) {
    // printf("\n%s %d\n", name, i);
		    makePoset(name);
            // printf("\nTRY  %s\n", head->call2);
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
                        list[n] = lengthPoset(headSIG);// findVal(mismatch, i);
                        continue;
		}
        
        n++;
		list[n] = lengthPoset(headSIG); //process_sig(); // head and headSIG process signature
        // findVal(mismatch, i);
	    fscanf(file, "%s", name);
	}

    fclose(file);
    strcat(sigFile, fileN);
    strcat(sigFile, ".sig");
    
    printf("\nEND  %d\n", mismatch);
    tmp = headSIG;
    file = fopen(sigFile, "w");
    while(tmp) {
        // printf("\nEND %s\n", sigFile);
        fprintf(file, "%s %s\n", tmp->call1, tmp->call2);
        tmp = tmp->next;
    }
    fclose(file);
    
    strcpy(sigFile, fileN);
    strcat(sigFile, ".val");
    
    findMeanVar();
    printf("\n%d %f %f\n", n, mean, dev);
    
    file = fopen(sigFile, "w");
    fprintf(file, "%d %f %f\n", n, mean, dev);
    fclose(file);
}
