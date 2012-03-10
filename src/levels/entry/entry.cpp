#include <level.h>
#include "ex.h"
#include <vector>

enum EA_achieve {
	EA_DOOR_OPEN
};

#include <level_shared.h>

vector<string> stuff;

void handleCommand(string command)
{
	hC_begin

	CMD("look")
		cout << "You see:" << endl;
		for (unsigned i = 0; i < stuff.size(); i++)
			cout << " * " << stuff[i] << endl;
	CMD("open")
		if (args[1] == "door")
		{
			if (has_item("key"))
			{
				cout << "The door opened!" << endl;
				ACHIEVE(DOOR_OPEN);
				goNextLevel();
			}
			else
			{
				cout << "The door is locked." << endl;
			}
		}
		else
			throw E_CMDNOTFOUND;
	CMD("lift")
		if (args[1] == "flowerpot")
			FIND("key");

	hC_end
}
void init()
{
	ADDV(stuff, "a door");
	ADDV(stuff, "a flowerpot");
}
void exit()
{
	cout << "Congrats!" << endl << "You've started your trip through the many, many levels!" << endl << "Have fun!" << endl;
}

