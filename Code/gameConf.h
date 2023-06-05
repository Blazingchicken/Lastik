#ifndef gameConf
#define gameConf

typedef struct {

    int conf_Ammo;
    int conf_WindSpeed;

} gameConfiguration;

gameConfiguration *gameConfMenu(gameConfiguration *confSt);
void showConf(int Ammo, int windSpeed);
int changeAmmoType();
int changeWindSpeed();
gameConfiguration *defaultConf(gameConfiguration *st);

#endif