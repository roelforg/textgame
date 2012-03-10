#include <general.h>

using namespace std;

Level *curr_level;

void main_loop()
{
	try {

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

int main(int argc, char *argv[])
{
	try {
		cout << "Welcome to TEXTGAME (" << VERSION << ")!" << endl;
		cout << "Loading entry...";
		curr_level = new Level("entry");
		cout << "OK!" << endl;
		main_loop();
	} catch (string err) {
		cerr << endl << "***ERROR*** " << err << endl;
	}
	return 0;
}

