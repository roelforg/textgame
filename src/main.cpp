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
		//cout << command << endl;
		try {
			if (0) { //hack for the CMD macro
			CMD("exit" || command == "quit")
				cout << "Exit!" << endl;
				running = 0;
			CMD("save" || command == "load")
				cerr << "Not implemented!" << endl;
			} else {
				curr_level->FnHandle(command);
			}
		} catch (E_ERROR e) {
			switch (e)
			{
				case E_CMDNOTFOUND:
				cout << "You can't do that!" << endl;
				break;
				default:
				//don't know this one, rethrow to other handlers
				throw e;
				break;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	init_error(); //initialize error handling
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

