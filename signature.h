int n, nA, list[1000];
double mean, dev, meanA, devA;

/**
 ***functions are FINDVAL FINDMEANVAR PROCESS_SIG and CREATE
 * this only works at runtime feed back system
 **/
void findVal(int mismatch, int i) {
    double var, t;

    t = ((mean * n) + mismatch) / i;
    var = (dev * dev) + ((mismatch - t) * (mismatch - mean));
    dev = sqrt(var);
    mean = t;
    n = i;
}

void findMeanVar(int o) {
    int i=0, t=0;

   
    if(o == 1) {
    mean = 0.0; 
    dev = 0.0; 
    n -= 1; 
    	for(i=0; i<n; i++) {
        	mean += list[i];
    	}
    	mean /= n;

    	for(i=0; i<n; i++) {
        	t = mean - list[i];
        	dev += (t * t);
    	}
    	dev = sqrt(dev/n);
    }
    else {
nA -=1;
devA=0.0;
meanA=0.0;
 
    	for(i=0; i<nA; i++) {
        	meanA += list[i];
    	}
    	meanA /= nA;

    	for(i=0; i<nA; i++) {
        	t = meanA - list[i];
        	devA += (t * t);
    	}
    	devA = sqrt(devA/nA);
    }
}

/**
 * returns the length of the larget common subsequnce in the two lists
 **/
int process_sig(struct sysCPS *headRef1, struct sysCPS *headRef2) {
    FILE *file=fopen(tmpF, "w");
    int l=0;
    struct sStruct *sig;

    if(headRef1 == NULL) {
        headSIG = head;
        return(lengthPoset(head));
    }

    /***************************************************************
     * string_lcs needs is replaced with the optimised version v2
     ***************************************************************/
    // sig = string_lcs_v3(headRef1, headRef2);
    global_len = 0;
    sig = string_lcs_v2(headRef1, headRef2, lengthPoset(headRef1), lengthPoset(headRef2));
    fprintf(file, "%s", sig->str1);
    fclose(file);
    
    makePoset(tmpF);
    headSIG = head;
    l = lengthPoset(headRef2) - sig->l + 1;
    // printf("\n>>> [%d] [%d] [%d] [%d]\n", lengthPoset(headRef1), lengthPoset(headRef2), lengthPoset(head), l);
    return(global_len); //l - lengthPoset(head));
}


/**
 * create a function to incorporate branches into the signature
 **/
// void create(char *fileN) {
void create(char *fileN, char *fileA) {
    FILE *file=fopen(fileN, "r");
    char sigFile[250], name[100];
    int mismatch=0, i=0, flag=0, l1=0, l2=0;
    struct sysCPS *tmp;

//////////////////////////////////////////////////////////////
    strcpy(sigFile, "");
    headSIG = NULL;
    n = 0;
    mean = 0.0;
    dev = 0.0;

    printf("\nProcessing dataset: %s\n", fileN);
	fscanf(file, "%s", name);
	while(!feof(file)) {
	        makePoset(name);
            clean();
            l1 = lengthPoset(head);
            if(flag == 0) {
                    // list[n++] = process_sig(headSIG, head);
                    headSIG = head;
                    head = NULL;
                    tailSIG = tail;
                    tail = NULL;
                    countSIG = countT;
                    countT = 0;
                    flag = 1;
                    printf("\tProcessed file: %s\n\tProcessed value: %d\n", name, list[n-1]);
	                fscanf(file, "%s", name);
                    continue;
            }

            list[n++] = process_sig(headSIG, head);
            printf("\tProcessed file: %s\n\tProcessed value: %d\n", name, list[n-1]);
            head = NULL;
            tailSIG = tail;
            tail = NULL;
            countSIG = countT;
            countT = 0;
            fscanf(file, "%s", name);
    }

    fclose(file);
    strcat(sigFile, fileN);
    strcat(sigFile, ".sig");
    
    /**
     * signature file format:
     *          call1 call2
     **/
    tmp = headSIG;
    file = fopen(sigFile, "w");
    while(tmp) {
        fprintf(file, "%s %s\n", tmp->call1, tmp->call2);
        tmp = tmp->next;
    }
    fclose(file);
   
/**
    strcpy(name, sigFile);
    strcpy(sigFile, fileN);
    strcat(sigFile, ".val");
**/
    
    /**
     * value file format
     *          n       mean            dev
     *        number    mean of the   deviation of the
     *                  list          list
     **/
    findMeanVar(1);
    
//////////////////////////////////////////////////////////////////////

    strcpy(sigFile, "");
    headSIG = NULL;
    nA = 0;
    meanA = 0.0;
    devA = 0.0;
    flag = 0;

    file=fopen(fileA, "r");
    fscanf(file, "%s", name);

	while(!feof(file)) {
	        makePoset(name);
            clean();
            l1 = lengthPoset(head);
            if(flag == 0) {
                    // list[n++] = process_sig(headSIG, head);
                    headSIG = head;
                    head = NULL;
                    tailSIG = tail;
                    tail = NULL;
                    countSIG = countT;
                    countT = 0;
                    flag = 1;
                    printf("\tProcessed file: %s\n\tProcessed value: %d\n", name, list[nA-1]);
	                fscanf(file, "%s", name);
                    continue;
            }

            list[nA++] = process_sig(headSIG, head);
            printf("\tProcessed file: %s\n\tProcessed value: %d\n", name, list[nA-1]);
            head = NULL;
            tailSIG = tail;
            tail = NULL;
            countSIG = countT;
            countT = 0;
            fscanf(file, "%s", name);
    }

    fclose(file);
    strcat(sigFile, fileN);
    strcat(sigFile, ".sigA");
    
    /**
     * signature file format:
     *          call1 call2
     **/
    tmp = headSIG;
    file = fopen(sigFile, "w");
    while(tmp) {
        fprintf(file, "%s %s\n", tmp->call1, tmp->call2);
        tmp = tmp->next;
    }
    fclose(file);

    findMeanVar(2);
/////////////////////////////////////////////////////////////////////////////////

    strcpy(name, sigFile);
    strcpy(sigFile, fileN);
    strcat(sigFile, ".val");
    
    file = fopen(sigFile, "w");
    fprintf(file, "%d %f %f\n%d %f %f", n, mean, dev, nA, meanA, devA);
    fclose(file);

    file = fopen(siglist, "a");
    fprintf(file, "%s %s\n", name, sigFile);
    fclose(file);

    /**
     * siglist file format
     *          <sig file name> <val file name>
     **/
    printf("\tn: %d\tmean: %f\tdev: %f\n\tnA: %d\tmeanA: %f\tdevA: %f\n", n, mean, dev, nA, meanA, devA);
}
