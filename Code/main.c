//MIKAYL_BIN_ABDUL_JALAL
//TP065957
#include <stdio.h>
#include "messages.h"
#include "messages.c"
#include "gameConf.h"
#include "gameConf.c"
#include "fileProcess.h"
#include "fileProcess.c"
#include "gameStart.h"
#include "gameStart.c"

void main() {

    welcomeMessage();//A welcome message showing the game name in huge characters.

    int menuSelection;
    gameConfiguration userConf; //A struct from gameConf.h to configure the Ammo Type and Wind Speed
    store userAttempt;
    defaultConf(&userConf);//Defaults the Ammo Type to WOOD and Wind Speed to LIGHT WINDS

    while (menuSelection != 4) {//Start While
        printf("\n==========MAIN MENU==========\n");
        printf("1.\tConfigure game\n");
        printf("2.\tStart game\n");
        printf("3.\tView scores\n");
        printf("4.\tExit game\n");
        printf("Enter Selection: ");
        if (scanf("%d", &menuSelection) == 0) break; //If input is not integer, an infinite loop will occur 

        switch (menuSelection) {//Start Switch
            case 1 :
                gameConfMenu(&userConf);
                break;
            case 2 :
                userAttempt.timeRecord = gameStart(userConf.conf_Ammo, userConf.conf_WindSpeed);
                userAttempt = finishGame(userAttempt, userAttempt.timeRecord);
                updateRecord(userAttempt);
                readRecord();
                break;
            case 3 :
                readRecord();
                break;
            case 4 :
                break;
            default :
                printf("\n%d was an invalid input\n", menuSelection);

        } //End Switch
    }//End While
    printf("\nYou are exiting the program.\nThank you for using!"); //Exit program
}