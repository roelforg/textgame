#include <general.h>
using namespace std;

class Level {
	public:

	typedef void (*hC)(string);
	typedef void (*vD)();
	void* hnd;
	vD FnInit, FnExit;
	hC FnHandle;
	string filename;

	Level(string);
	~Level();
};

