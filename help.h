void help(char *name) {
    printf("\nSys-IDS is a signature and anomaly based signature which checks an anomaly\
            \nin the sequnce od system calls created by a process while it runs.\
            \n\
            \nUsage:\
            \n======\
            \n\t%s [make|test|help]\
            \n\
            \nOptions\
            \n=======\
            \n\t> make:\
            \n\t\tTo make the signature files in .ids folder. A list of the newly\
            \n\t\tcreated file if made and saved for later usage in sigfile. Before\
            \n\t\trunning the program a second time REMOVE sigfile.\
            \n\t> test\
            \n\t\tTo test the input seuence of system calls for anomaly. the input \
            \n\t\tis obtained from the file .ids/input.\
            \n\t> help\
            \n\t\tPrints this help and returns.\n", name);
}
