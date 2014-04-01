int length_lcs(struct sysCPS *headRef1, struct sysCPS *headRef2) {
    int l1=0, l2=0, t=0, t1=0, t2=0, t3=0;
    
    l1 = lengthPoset(headRef1);
    l2 = lengthPoset(headRef2);

    if((headRef2 == NULL) || (headRef1 == NULL)) {
        return 0;
    }

    if(val[l1][l2] >= 0) {
        return val[l1][l2];
    }

    if((!strcmp(headRef1->call1, headRef2->call1)) && (!strcmp(headRef1->call2, headRef2->call2))) {
        t1 = length_lcs(headRef1->next, headRef2->next);
        val[l1][l2] = (val[l1][l2] > (1 + t1))?val[l1][l2]:(1+t1);
    }
    else if((strcmp(headRef1->call1, headRef2->call1)) || (strcmp(headRef1->call2, headRef2->call2))) {
        t2 = length_lcs(headRef1, headRef2->next);
        t1 = length_lcs(headRef1->next, headRef2);
        t =  (t1>t2)?t1:t2;
        val[l1][l2] = (val[l1][l2]>t)?val[l1][l2]:t;
    }
    
    return val[l1][l2];
}

char *string_lcs(struct sysCPS *headRef1, struct sysCPS *headRef2) {
	int l1=0, l2=0, t=0, t1=0, t2=0, t3=0;

	l1 = lengthPoset(headRef1);
	l2 = lengthPoset(headRef2);
 
	if((headRef2 == NULL) || (headRef1 == NULL)) {
        	return 0;
    	}

	
}
