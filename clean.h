/**
 * stage1
**/

void freeNode(struct sysCPS *headRef) {
    struct sysCPS *tmp=headRef;
    
    printf("\ndfdsfdf\n");
    while(tmp) {
        headRef = headRef->next;
        free(tmp);
        tmp = headRef;
    }
}

void clear_val() {
    int i=0, j=0;

    for(i=0; i<5000; i++) {
        for(j=0; j<5000; j++) {
            if((i == 0) || (j == 0)) {
                val[i][j] = 0;
            }
            else {
            val[i][j] = -1;
            }
        }
    }
}

struct sysCPS *getNNode(int n, struct sysCPS *headRef) {
	struct sysCPS *tmp = headRef;

	while(n) {
		if(!tmp) {
			return NULL;
		}

		n--;
		tmp = tmp->next;
	}

	return tmp;
}

void clean() {
	if(head == NULL) {
		return;
	}
	
	struct sysCPS *tmp, *tmpH, *prev, *tmpT;
	int countT=2, i=0;
	
	// for one term repatition
	while(1) {
		if(strcmp(head->call1, head->call2) == 0) {
			head = head->next;
			continue;
		}
		break;
	}
	
	tmp = head;
	while(tmp->next) {
		if(strcmp((tmp->next)->call1, (tmp->next)->call2) == 0) {
			tmp->next = (tmp->next)->next;
			continue;
		}
		tmp = tmp->next;
	}

	// for generalizing more than one term repatition
	while(countT <= (lengthPoset(head)/2)) {
		tmpH = head;
		prev = NULL;
		tmp = NULL;
		tmpT = NULL;
		while((tmp=getNNode(countT, tmpH)) != NULL) {
			for(i=0; i<(countT-1); i++) {
				tmpT = getNNode(i, tmpH);
				if((!tmpT) || (!tmp)) {
					break;
				}
				if((strcmp(tmpT->call1, tmp->call1) == 0) && (strcmp(tmpT->call2, tmp->call2) == 0)) {
					tmp = tmp->next;
				}
				else {
					break;
				}
			}
			if(i == (countT-1)) {
				if(tmpH == head) {
					head = getNNode(countT, head);
					tmpH = head;
				}
				else {
					prev->next = getNNode(countT, tmpH);
					tmpH = prev->next;
				}
			}
			else {
				prev = tmpH;
				tmpH = tmpH->next;
			}

		}
		countT++;
	}
}
