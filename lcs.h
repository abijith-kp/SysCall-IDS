int length_lcs(struct sysCPS *headRef1, struct sysCPS *headRef2) {
    int t = 0;
    
    if((headRef2 == NULL) || (headRef1 == NULL)) {
        return 0;
    }

    if((headRef1->call1 == headRef1->call1) && (headRef1->call2 == headRef1->call2)) {
        t = 1 + length_lcs(headRef1->next, headRef2->next);
        return t;
    }
    else if((headRef1->call1 != headRef1->call1) || (headRef1->call2 != headRef1->call2)) {
        t = length_lcs(headRef1->next, headRef2->next);
        return t;
    }
}
