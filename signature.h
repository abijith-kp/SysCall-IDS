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
    mean = 0.0;
    dev = 0.0;
    
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

// returns the length of the larget common subsequnce in the two lists
int process_sig(struct sysCPS *headRef1, struct sysCPS *headRef2) {
    char *sig;
    FILE *file=fopen(".tmp", "w");
    int l=0;

    if(headRef1 == NULL) {
        printf("\n?? %d\n", lengthPoset(head));
        headSIG = head;
        return(lengthPoset(head));
    }

    sig = string_lcs(headRef1, headRef2);
    // fprintf(file, "%s", sig);
    fclose(file);

    
    makePoset(".tmp");
    headSIG = head;
    l = lengthPoset(headSIG);
    // printf("\n>> %d  %d\n", strlenN(sig), l);
    return(l);
}


// create a function to incorporate branches into the signature
void create(char *fileN) {
	FILE *file=fopen(fileN, "r");
    char sigFile[100], name[100];
    int mismatch=0, i=0, flag=0;
    struct sysCPS *tmp;

    headSIG = NULL;
    n = 0;
    mean = 0.0;
    dev = 0.0;

	fscanf(file, "%s", name);
    // i++;
	while(!feof(file)) {
    // printf("\n%s %d\n", name, i);
	        makePoset(name);
            clean();
            // printf("\nTRY  %s  %d \n", name, lengthPoset(head));
            if(flag == 0) {
                    list[n++] = process_sig(headSIG, head); //lengthPoset(headSIG);// findVal(mismatch, i);
                    // headSIG = head;
                    head = NULL;
                    tailSIG = tail;
                    tail = NULL;
                    countSIG = countT;
                    countT = 0;
                    flag = 1;
	                fscanf(file, "%s", name);
            // if(headSIG == NULL) {
            //}
			// this is just a temporary means to calculate the values
                    continue;
            }

    printf("\n>> %d %d\n", list[n-1], n-1);
            // printf("\nFFFFFFFFFFFFFFFFFFFFFFFFFFFFF %d  %d\n", lengthPoset(headSIG), lengthPoset(head));
            // n++;
            list[n++] = process_sig(headSIG, head); //lengthPoset(head); //process_sig(); // head and headSIG process signature
            // printf("\nFFFFFFFFFFFFFFFFFFFFFFFFFFFFF %d  %d\n", lengthPoset(headSIG), lengthPoset(head));
            head = NULL;
            tailSIG = tail;
            tail = NULL;
            countSIG = countT;
            countT = 0;
            fscanf(file, "%s", name);
    }

    // n++;
    fclose(file);
    strcat(sigFile, fileN);
    strcat(sigFile, ".sig");
    
    // printf("\nEND  %d\n", list[0]);
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
