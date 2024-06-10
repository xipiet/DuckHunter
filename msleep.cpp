#include <unistd.h>
#include "module.h"

void msleep(float ms){
    int us = ms*1000;
    usleep(us);
}
