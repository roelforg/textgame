#ifndef __LEVEL_H__
#define __LEVEL_H__
#include <string>
#include <iostream>
#include <ex.h>
#include <vector>

using namespace std;

extern "C" {

void enterLevel(string);
string getNextLevel();
void goNextLevel();
void handleCommand(string);
void init();
void exit();

}

#endif

