#ifndef __LEVEL_H__
#define __LEVEL_H__
#include <string>
#include <iostream>

using namespace std;

extern "C" {

void enterLevel(string);
void handleCommand(string);
void init();
void exit();

}

#endif

