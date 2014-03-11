int length_lcs(struct sysCPS *headRef1, struct sysCPS *headRef2) {
    int t=0, t1=0, t2=0, t3=0;
    
    if((headRef2 == NULL) || (headRef1 == NULL)) {
        return 0;
    }

    if((headRef1->call1 == headRef1->call1) && (headRef1->call2 == headRef1->call2)) {
        printf("%s\t%s\n", headRef1->call1, headRef1->call2);
        t = 1 + length_lcs(headRef1->next, headRef2->next);
    }
    else if((headRef1->call1 != headRef1->call1) || (headRef1->call2 != headRef1->call2)) {
        t1 = length_lcs(headRef1->next, headRef2);
        t2 = length_lcs(headRef1, headRef2->next);
        t = (t1>t2)?t1:t2;
    }
    
    return t;
}
