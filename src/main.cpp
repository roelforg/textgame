#include <general.h>

using namespace std;

int main(int argc, char *argv[])
{
	try {
	Level *level = new Level("entry");
	} catch (string err) {
		cerr << "***ERROR*** " << err << endl;
	}
	return 0;
}

