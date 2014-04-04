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
    return(lengthPoset(headRef2));
}

/*
struct sysCPS *locate(struct sysCPS *headRef, struct sysCPS tmp) {
	while(headRef) {
		if (!strcmp(headRef->call1, tmp.call1) && !strcmp(headRef->call2, tmp.call2)) {
			return headRef;
		}
		
		headRef = headRef->next;
	}
	return NULL;
}

// File name gives the process name
// the signature file contains the processname and an extension name
struct sysCPS *lcs(struct sysCPS *a, struct sysCPS *b, struct sysCPS *out) {
	int longest = 0;
	out = (struct sysCPS *)malloc();
	int match(struct sysCPS *a, struct sysCPS *b, int dep) {
		if ((a == NULL) || (b == NULL)) return 0;
		if (!*a || !*b) {
			if (dep <= longest) return 0;
			out[ longest = dep ] = NULL;
			return 1; 
		}
 
		if (!strcmp(a->call1, b->call1) && !strcmp(a->call2, b->call2))
			out[dep] = *a;
			return match(a->next, b->next, dep + 1); 
 
		return	match(a->next, b->next, dep) + 
			match(locate(a, *b), b, dep) +
			match(a, locate(b, *a), dep);
	}

	return match(a, b, 0) ? out : 0;
}
*/


// create a function to incorporate branches into the signature
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
            clean();
            printf("\nTRY  %s  %d \n", name, lengthPoset(head));
            if(flag == 0) {
                    list[n++] = process_sig(headSIG, head); //lengthPoset(headSIG);// findVal(mismatch, i);
                    headSIG = head;
                    head = NULL;
                    tailSIG = tail;
                    tail = NULL;
                    countSIG = countT;
                    countT = 0;
                    flag = 1;
	                fscanf(file, "%s", name);
			// this is just a temporary means to calculate the values
                    continue;
            }
            
            // n++;
            list[n++] = process_sig(headSIG, head); //lengthPoset(head); //process_sig(); // head and headSIG process signature
        // findVal(mismatch, i);
        fscanf(file, "%s", name);
    }

    // n++;
    fclose(file);
    strcat(sigFile, fileN);
    strcat(sigFile, ".sig");
    
    printf("\nEND  %d\n", list[0]);
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
