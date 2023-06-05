#ifndef GAMESTART
#define GAMESTART

int gameStart(int Ammo, int WindSpeed);
float getAmmoMass(int Ammo);
void countdown(int time);
int randNumGenerator(void);
int** projEdgePoints(float x0, float y0, int r);
float* calcXandY(float F, float a, float Weight, int WindSpeed, int* arrTarget, int r);
void closestDistanceToTarget(int* arrTarget, int x0, int y0);
char* nama(int timeElapsed);

#endif