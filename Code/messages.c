#include <stdio.h>
#include <stdlib.h>

void welcomeMessage() {//Welcome Message

    
    printf("====================================================================\n");
    printf("|                            _____                       ___ ____  |\n");
    printf("| ___            __         / ___/ _________ _________  | | / /    |\n");
    printf("| | |           /  \\       / /__   |__   __| |__   __|  | |/ /     |\n");
    printf("| | |          / __ \\      \\___ \\     | |       | |     |   /      |\n");
    printf("| | |         / /__\\ \\         \\ \\    | |       | |     |    \\     |\n");
    printf("| | |____    / ______ \\    ____/ /    | |    ___| |___  | |\\  \\    |\n");
    printf("| |______|  /_/      \\_\\  |_____/     |_|    |_______|  |_| \\__\\   |\n");
    printf("|                                                                  |\n");
    printf("|==================================================================|\n\n");
    printf("Welcome to the game! Please select which option to pick below: \n");
}

void gameInstructions() {//Game's Storyline/Instructions

    printf("\n==========STARTING GAME==========\n");
    printf(">\tYou are operating a slingshot in a cartesian coordinate graph.\n");
    printf(">\tYour position is (0,0).\n");
    printf(">\t3 Targets will randomly appear.\n");
    printf(">\tAdjust the angle and the velocity of your projectile to hit your target.\n");
    printf(">\tGame will begin in \n"); 
    countdown(5);//Delay 20 secs for user to read storyline/instructions
    printf("\n\t\t\t\t>>>>>BEGIN!<<<<<\n\n");
}