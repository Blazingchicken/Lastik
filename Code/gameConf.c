#include <stdio.h>

gameConfiguration *gameConfMenu(gameConfiguration *confSt) {

    int menuSelection;

    while (menuSelection != 4) {//Begin While
        printf("\n==========CONFIGURATION MENU==========\n");
        printf("What would you like to configure?\n");
        printf("1.\tAmmo Type\n");
        printf("2.\tWind speed\n");
        printf("3.\tShow Current Configuration\n");
        printf("4.\tReturn to Main Menu\n");
        printf("Enter selection: ");
        if (scanf("%d", &menuSelection) == 0) break;//Break to prevent infinite scanf loop
        switch (menuSelection) {//Start Configuration Menu Switch
            case 1 :
                confSt->conf_Ammo = changeAmmoType();
                break;
            case 2 :
                confSt->conf_WindSpeed = changeWindSpeed();
                break;
            case 3 :
                showConf(confSt->conf_Ammo, confSt->conf_WindSpeed);
                break;
            case 4 :
                break;
            default :
                printf("\n%d was an invalid input\n", menuSelection);
        }//End Configuration Menu Switch
    }//End While
    printf("Returning to Main Menu\n");
    return confSt;
}

gameConfiguration *defaultConf(gameConfiguration *st) { //A Function to configure Used pointer to reduce memory traffic
    st->conf_Ammo = 2;
    st->conf_WindSpeed = 2;

    return st;
}

int changeAmmoType() {
    
    int menuSelection;
    int ammo;
    
    printf("\n==========PICK YOUR AMMO==========\n");
    printf("=======================================\n");
    printf("|NO | AMMO TYPE  |  WEIGHT  |  SIZE   |\n");
    printf("|-------------------------------------|\n");
    printf("| 1 |   IRON     |  HEAVY   | SMALL   |\n");
    printf("| 2 |   WOOD     | AVERAGE  | AVERAGE |\n");
    printf("| 3 |  PLASTIC   |  LIGHT   |  BIG    |\n");
    printf("=======================================\n");
    printf("Enter selection: ");
    scanf("%d", &menuSelection);

    switch (menuSelection) {//Begin Ammo Selection Switch
        case 1 :
            ammo = 1;
            printf("You picked IRON\n");
            break;
        case 2 :
            ammo = 2;
            printf("You picked WOOD\n");
            break;
        case 3 :
            ammo = 3;
            printf("You picked PLASTIC\n");
            break;
        default :
            ammo = 2;
            printf("\nInvalid selection, default ammo type is WOOD\n");
    }//End Ammo Selection Switch
    return ammo;
}

int changeWindSpeed() {

    int menuSelection;
    int windSpeed;

    printf("\n==========WIND SPEED==========\n");
    printf("1.\tLight Breeze\n");
    printf("2.\tLight Winds\n");
    printf("3.\tHeavy Winds\n");
    printf("Enter selection: ");
    scanf("%d", &menuSelection);

    switch (menuSelection) {//Begin Wind Selection Switch
        case 1 :
            windSpeed = 1;
            printf("You picked LIGHT BREEZE\n");
            break;
        case 2 :
            windSpeed = 2;
            printf("You picked LIGHT WINDS\n");
            break;
        case 3 :
            windSpeed = 3;
            printf("You picked HEAVY WINDS\n");
            break;
        default :
            windSpeed = 2;
            printf("Invalid selection, default wind speed is LIGHT WINDS\n");
    }//End Wind Selection Switch
    return windSpeed;
}

void showConf(int Ammo, int windSpeed) {

    char *displayAmmo;
    char *displaywindSpeed;

    switch (Ammo) {
        case 1 :
            displayAmmo = "IRON";
            break;
        case 2 :
            displayAmmo = "WOOD";
            break;
        case 3 :
            displayAmmo = "PLASTIC";
            break;
        default :
            printf("Error: Ammo Type undetected\n");
    }

    switch (windSpeed) {
        case 1 :
            displaywindSpeed = "LIGHT BREEZE";
            break;
        case 2 :
            displaywindSpeed = "LIGHT WINDS";
            break;
        case 3 :
            displaywindSpeed = "HEAVY WINDS";
            break;
        default :
            printf("Error: Wind Speed undetected\n");
    }

    if (displayAmmo != NULL || displaywindSpeed != NULL) {
        printf("\n==========CURRENT CONFIGURATION==========\n");
        printf("AMMO TYPE: %s\n", displayAmmo);
        printf("WIND SPEED: %s\n", displaywindSpeed);
    }
}