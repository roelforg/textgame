#include <general.h>
#include <signal.h>

using namespace std;

Level *curr_level;

void main_loop()
{
	bool running = 1;
	string command;
	#define CMD(x) } else if (command == x) {

	while (running)
	{
		cout << "> ";
		getline(cin,command);
		try {
			if (command == "") { //hack for the CMD macro --- EDIT: nice way to handle emptry commands ;)
			CMD("exit" || command == "quit")
				cout << "Exit!" << endl;
				running = 0;
			CMD("save" || command == "load")
				cerr << "Not implemented!" << endl;
			} else {
				curr_level->FnHandle(command); //not a system command, if let the level-cmd-handler handle it
			}
		} catch (E_ERROR e) {
			switch (e)
			{
				case E_CMDNOTFOUND: //get's thrown by the level-cmd-handler incase it can't find it either
				cout << "You can't do that!" << endl;
				break;
				case E_SWLVL:
				try {switchLevel();} catch (E_ERROR er) {
					switch(er) {
						case E_EOG:
						cout << "*** GAME OVER ***" << endl;
						running = 0;
						break;
						default:
						throw er;
						break;
					}
				}
				break;
				default:
				//don't know this one, rethrow to other handlers
				throw e;
				break;
			}
		}
	}
	#undef CMD
}

int main(int argc, char *argv[])
{
	init_error(); //initialize error handling
	init_level(); //start level-tracker
	try {
		cout << "Welcome to TEXTGAME (" << VERSION << ")!" << endl;
		curr_level = new Level("entry"); //load the first level
		main_loop();
	} catch (string err) {
		cerr << endl << "***ERROR*** " << err << endl;
		raise(SIGUSR1);
	} catch (exception e) {
		cerr << endl << "***ERROR*** Exception!" << endl;
		raise(SIGUSR2);
	}
	return 0;
}

