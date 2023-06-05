#include <stdio.h>
#include <time.h>
#include <string.h>

store finishGame(store st, int timeElapsed) {

    st.timeRecord = timeElapsed;
    char* name = (char*)malloc(sizeof(st.userName) * sizeof(char));
    printf("\n\t\t\t\t>>>>>ALL 3 TARGETS HIT<<<<<\n");
    printf("\t\t\t\t>>>>>CONGRATULATIONS<<<<<\n\n");
    fflush(stdin);
    printf("Enter your name in 3 letters at most: ");
    if (fgets(name, 4, stdin)) {
        name[strcspn(name, "\n") + 1] = 0;
        name[strcspn(name, "\n")] = '\t';   
    }
    st.userName = name;//since strings consists of addresses, must use malloc so that heap of memory can be referred to in main function.
    free(name);
    return st;
}

void updateRecord(store st) {

    char *concName = (char*)malloc(sizeof(st.userName) * sizeof(char));
    concName = combRecords(st);
    FILE *fa = fopen("userScores.txt", "a");
    fputs(concName, fa);
    free(concName);
    fclose(fa);
}

char* combRecords(store st) {

    char *concName = (char*)malloc(sizeof(st.userName) * sizeof(char));
    concName = st.userName;
    char time[5];
    sprintf(time, "%d", st.timeRecord);
    strcat(concName, time);
    concName[strlen(concName)] = '\n';
    concName[strcspn(concName, "\n") + 1] = 0;

    return concName;
}

void readRecord() {

    char churn[256];
    int j=1;
    
    FILE *fr = fopen("userScores.txt", "r+");
    printf("ATTEMPT\tNAME\tSCORE\n");
    printf("===========================================================================================================\n");
    while (fgets(churn, 256, fr)) {
        printf("[%d]\t%s\n", j, churn);
        j++;
    }
    fclose(fr);
}