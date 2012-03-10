#include <level.h>

//uncomment to disable achievements
//#define NOEA

#ifndef NOEA
enum EA_achieve {
	EA_CAPTCHA,
	EA_COMMENT,
	EA_DOOR_OPEN
};
#endif

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
			if (has_item("key"))
			{
				cout << "The door opened!" << endl;
				ACHIEVE(DOOR_OPEN);
				goNextLevel();
			}
			else
				cout << "The door is locked!" << endl;
	CMD("take")
		if (args[1] == "comment")
		{
			if (has_achievement(EA_CAPTCHA)) {
				FIND("comment");
			} else
				cout << "You can't! It's not your's!" << endl;
		}
		if (args[1] == "captcha")
			FIND("captcha");
	CMD("say")
		if (args[1] == "captcha")
			if (has_item("captcha"))
			{
				cout << "Man, that captcha was lamer than i thought!" << endl;
				ACHIEVE(CAPTCHA);
			}
			else
				cout << "What does that captcha say? I don't know!" << endl;
	CMD("post")
		if (args[1] == "comment")
			if (has_item("comment"))
			{
				FIND("key");
				ACHIEVE(COMMENT);
			}
			else
				cout << "You can't! It's not your's!" << endl;
	CMD("help")
		cout << "The following commands are availeble:" << endl << " * look\n * open\n * take\n * say\n * post\n";

	hC_end
}
void init()
{
	ADDV(stuff, "A door");
	ADDV(stuff, "A comment\n   A load of comments are lying on the floor in disarray. What a mess!");
	ADDV(stuff, "A lame captcha");
	cout << "Type \"help\" for help!" << endl;
}
void exit()
{
}

