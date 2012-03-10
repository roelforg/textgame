#include <level.h>
#include "ex.h"
#include <vector>

#define CMD(x) } else if (args[0] == x) {
#define ADDV(x,y) x.push_back(y);
#define FIND(x) cout << "Found item: " << x << endl; \
items.push_back(x);
#define ACHIEVE(x) achievements.push_back(EA_##x);

vector<string> items;

enum EA_achieve {
	EA_DOOR_OPEN
};
vector<EA_achieve> achievements;

bool has_item(string item)
{
	bool rc = false;
	for (unsigned i = 0; i < items.size(); i++)
		if (items[i] == item)
		{
			rc = true;
			break;
		}
	return rc;
}

bool has_achievement(EA_achieve ach)
{
	bool rc = false;
	for (unsigned i = 0; i < achievements.size(); i++)
		if (achievements[i] == ach)
		{
			rc = true;
			break;
		}
	return rc;
}

vector<string> parse_args(string cmd)
{
	vector<string> rc;
	string tmp;
	size_t found = 0, of = 0;
	found = cmd.find(' ', found);
	if (found != string::npos)
	while (found != string::npos)
	{
		tmp = cmd.substr((of == 0)?0:of+1, found-of);
		ADDV(rc,tmp);
		of = found;
		found = cmd.find(' ', found+1);
	}
	ADDV(rc,cmd.substr((of == 0)?0:of+1,found-of));

	return rc;
}

vector<string> stuff;

void handleCommand(string command)
{
	vector<string> args = parse_args(command);

	if (0) { //hack for the CMD macro

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
				enterLevel("entry");
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

	} else {
		throw E_CMDNOTFOUND;
	}
}
void init()
{
	ADDV(stuff, "a door");
	ADDV(stuff, "a flowerpot");
}
void exit()
{
}

