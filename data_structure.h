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
int countSIG=0;

// for temporary storage of input
struct sysCPS *tmpHead = NULL, *tmpTail = NULL;

// a random variable as a helper for making posets
struct sysCPS* random_var;   

/*
struct sysC *headI = NULL, *tailI = NULL; // Initial list of log
struct sysC *headR = NULL, *tailR = NULL; // 1st time R=I,
struct sysC *headT = NULL, *tailT = NULL; // compare I R
struct sysC *headTMP = NULL, *tailTMP = NULL; // compare I R
struct sysC *headTD = NULL, *tailTD = NULL; // compare I R
struct sysC *headSIG = NULL, *tailSIG = NULL; // compare I R
struct sysC *headSIGBB = NULL, *tailSIGBB = NULL; // compare I R
*/
