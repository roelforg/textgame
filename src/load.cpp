#include <general.h>
#include <dlfcn.h>

extern Level *curr_level;

extern "C" {
void enterLevel(string);
}

void enterLevel(string level)
{
	delete curr_level;
	curr_level = new Level(level);
}

Level::Level(string name)
{
	this->filename = name;
	this->hnd = dlopen(string("/data/textgame/lib/"+name+".so").c_str(), RTLD_NOW);
	void* init = dlsym(this->hnd,"init");
	if (init == NULL)
		throw string("Symbol init not found!");
	else
		this->FnInit = (vD)init;
	init = dlsym(this->hnd,"exit");
	if (init == NULL)
		throw string("Symbol exit not found!");
	else
		this->FnExit = (vD)init;
	init = dlsym(this->hnd,"handleCommand");
	if (init == NULL)
		throw string("Symbol handleCommand not found!");
	else
		this->FnHandle = (hC)init;
	init = dlsym(this->hnd,"shared_init");
	vD tmp;
	if (init == NULL)
		throw string("Symbol shared_init not found!");
	else
		tmp = (vD)init;
	tmp();
	this->FnInit();
}

Level::~Level()
{
	void *init;
	this->FnExit();
	init = dlsym(this->hnd,"shared_exit");
	vD tmp;
	if (init == NULL)
		throw string("Symbol shared_exit not found!");
	else
		tmp = (vD)init;
	tmp();
	dlclose(this->hnd);
}

