#ifndef fileProcess
#define fileProcess

typedef struct {

    char* userName;
    int timeRecord;

} store;

char* combRecords(store);
store finishGame(store, int);
void updateRecord(store);
void readRecord();

#endif