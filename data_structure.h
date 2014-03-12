char *logFile = "log", *logDict = "dict", *sysFile = "syscall", *sigFile = "signature", appName[100];


int countC = 0, countI = 0, countR = 0, countT = 0, countTD = 0, countSIG = 0, countSIGBB = 0, flag = 0, continueFlag = 0;

// node for the poset is System Call PoSet
struct sysCPS {
	char *call1;
	char *call2;
	struct sysCPS *next;
};

// for converting files to posets and making the signature during iteration
struct sysCPS *head = NULL, *tail = NULL;
int countPS=0;

// for the current status of signature which will be written to a file later on
struct sysCPS *headSIG = NULL, *tailSIG = NULL;

// for temporary storage of input
struct sysCPS *tmpHead = NULL, *tmpTail = NULL;

// a random variable as a helper for making posets
struct sysCPS* random_var;   

int val[5000][5000];
