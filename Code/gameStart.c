#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "messages.h"
#define GRAVITY 10
#define PI 3.14519
#define TAU 6.28318
#define XLIMIT 25
#define YLIMIT 25
#define FPS 0.05

int gameStart(int Ammo, int WindSpeed) {

    int menuSelection, timeElapsed, totalScore;
    float a, F;
    float m = getAmmoMass(Ammo); 
    float Weight = m * GRAVITY;
    float* arrXandY;
    //V is final velocity.
    //a is angle in degrees.
    //u is initial velocity.
    //F is the launching force of projectile.
    //Fcomp[2] is an array containing the horizontal and vertical components of the force.
    //Vcomp[2] is an array containing the horizontal and vertical components of the velocity.
    //m is mass of projectile.
    //Weight is the gravitational force that brings the projectile down.
    int arrTarget[2];
    /*arrEdgeProj is a pointer to a pointer, creating a dynamically allocated memory to accept array from projEdgePoints containing
    x and y coordinates of the edge points of projectile.*/
    //arrTarget is an array containing the x and y coordinates of the Target.
    //r is the user's choice of the ammo type which, if minus one, gets the radius.
    int cnt;
    char* token;
    char** afterSplit = (char**)malloc(2 * sizeof(char*));
    for (int i=0; i<2; i++) {
        afterSplit[i] = (char*)malloc(20 * sizeof(char));
    }
    time_t currentTime;
    time_t startingTime;

    gameInstructions();
    startingTime = time(NULL);
    totalScore = 0;
    do {//while loop to initialise Target's coordinates
        arrTarget[0] = randNumGenerator();
        arrTarget[1] = randNumGenerator();
        arrXandY = 0;
        while (arrXandY != 1) {
            printf(">\tTarget's coordinates are\n\tx : %d\n\ty : %d\n", arrTarget[0], arrTarget[1]);
            printf("\nPick the angle of your trajectory from 0.00 to 90.00 degrees: ");
            if (scanf("%f", &a) == 0) break;
            a = a * PI / 180;
            printf("\nPick the launching force (in Newtons): ");
            if (scanf("%f", &F) == 0) break;
            arrXandY = calcXandY(F, a, Weight, WindSpeed, arrTarget, Ammo);
        }
        totalScore += 1;
        printf("\tYour score is: %d\n\n", totalScore);
        printf("===========================================================================================================\n");
    } while (totalScore <= 2);
    currentTime = time(NULL);
    timeElapsed = difftime(currentTime, startingTime);
    return timeElapsed;
}

float getAmmoMass(int Ammo) {

    float m;

    switch (Ammo) {
        case 1 :
            m = 1.5;
            break;
        case 2 :
            m = 1;
            break;
        case 3 :
            m = 0.5;
            break;
        default :
            printf("Error: Ammo undetected\n");
    }
    return m;
}

void countdown(int time) {
    while (time != 0) {
        printf("\t%d ", time);
        sleep(1);
        time--;
    }
}

int randNumGenerator(void) {
    
    static int visit = 2;
    time_t randomTime = time(&randomTime);
    int genNum;

    srand(randomTime * visit);
    genNum = rand() % XLIMIT; //Generates a number from 0 to 25

    visit++;
    return genNum;
}

float* calcXandY(float F, float a, float Weight, int WindSpeed, int* arrTarget, int r) {
    //a recursive Function that calculates flight path of the projectile until it misses or hits target.

    int i;
    float Fx, Fy, Vx, Vy;
    int** arrEdgeProj;
    static float cnt = 0.05;
    static float x0 = 0;//Since the slingshot always starts at point (0,0), no need to accept values from main function.
    static float y0 = 0;
    static float u = 0;
    float acceleration = F/(Weight / GRAVITY);//Change of velocity between two frames.
    float V = acceleration * FPS - u;//Resultant Velocity in the next frame.

    Fx = (F * cos(a)) - WindSpeed;
    Fy = (F * sin(a)) - Weight;
    F = sqrt((Fx * Fx) + (Fy * Fy));
    Vx = V * cos(a);
    Vy = V * sin(a);
    x0 = Vx * FPS + x0;
    y0 = Vy * FPS + y0;
    a = atan2(Fy, Fx);

    float* arrXandY = (float*)malloc(5 * sizeof(float));
    arrXandY[0] = a;
    arrXandY[1] = F;
    arrXandY[2] = V;
    arrXandY[3] = x0;
    arrXandY[4] = y0;
    //A pointer that allocate a heap of memory to store 5 floats: a, F after minused by resistive forces, V, the new x and y coordinates.
    printf("Second (%.2f) : angle is %.2f  Force is %.2f   Resultatant velocity is %.2f\t x is %d  y is %d\n", cnt, a * 180 / PI, F, V, abs(x0), abs(y0));
    arrEdgeProj = projEdgePoints(x0, y0, r);
    closestDistanceToTarget(arrTarget, x0, y0);//To show distance between projectile and target per timeframe.
    for (i=0; i<(4 * (r-1)); i++) {
        if (arrTarget[0] == arrEdgeProj[i][0] && arrTarget[1] == arrEdgeProj[i][1]) {
            printf("\n\t\t\t\t>>>>>TARGET HIT!<<<<<\n\n");
            for (int j=0; j<(4 * (r-1)); j++) {
                free(arrEdgeProj[j]);
            }
            cnt = 0.05;
            x0 = 0;
            y0 = 0;
            u = 0; //Resetting the static values to zero.
            free(arrEdgeProj);
            free(arrXandY);
            return 1;
        }
    }
    for (int j=0; j<(4 * (r-1)); j++) {
        free(arrEdgeProj[j]);
    }
    free(arrEdgeProj);
    if ((0 < F < 1) || (y0 <= 0) || (x0 <= 0) || (x0 > XLIMIT) || (y0 > YLIMIT)) {
        printf("\n\t\t\t\t>>>>>TARGET MISSED!<<<<<\n\n");
        cnt = 0.05;
        x0 = 0;
        y0 = 0;
        u = 0; //Resetting the static values to zero.
        return 0; // Remember to free the array in the main function
    }
    else {
    cnt += 0.05;
    return calcXandY(F, a, Weight, WindSpeed, arrTarget, r);
    }
}

int** projEdgePoints(float x0,float y0, int Ammo) {
    //                 *     
    //Ball sizes are  ***            *
    //               *****          ***         *
    //                ***            *
    //                 *
    //              PLASTIC(Ammo=3)  WOOD(Ammo=2)  IRON(Ammo=1)
    int i;
    int x=0, y=0;
    float numerator;
    float radius = Ammo - 1; //Ammo is the user's choice, must minus one to get projectile's radius.
    float quadrants = 4 * radius;
    if (quadrants == 0) quadrants = 1;
    int** arr = (int**)malloc((quadrants) * sizeof(int*)); //Making a dynamic array that has "quadrants" rows consisting of 2 columns each.
    for (i=0; i<quadrants; i++) {
        arr[i] = (int*)malloc(2 * sizeof(int));
    }
    for (numerator=0; numerator<quadrants; numerator++) {//This for loop is to get the x and y coordinates for each edge quadrant. 
        x = x0 + round(radius * cos(numerator * TAU / quadrants));
        y = y0 + round(radius * sin(numerator * TAU / quadrants));
        arr[(int) numerator][0] = x;
        arr[(int) numerator][1] = y;
    }
    return arr;
}

void closestDistanceToTarget(int* arrTarget, int x0, int y0) {

    int xdelta = arrTarget[0] - x0;
    int ydelta = arrTarget[1] - y0;
    printf("x-coordinates required to reach target: %d\n", xdelta);
    printf("y-coordinates required to reach target: %d\n", ydelta);
    printf("===========================================================================================================\n");
}