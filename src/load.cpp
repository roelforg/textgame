#include <general.h>
#include <dlfcn.h>

extern Level *curr_level;

extern "C" {
void enterLevel(string);
}

void enterLevel(string level)
{
	curr_level->exit_level();
	curr_level->load_level(level);
}

Level::Level(string name)
{
	this->load_level(name);
}

void Level::load_level(string name)
{
	cout << "Loading " << name << "...";
	this->filename = name;
	this->hnd = dlopen(string(string(LVL_LOC)+"/"+name+".so").c_str(), RTLD_NOW);
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
	cout << "OK!" << endl << "You've entered \"" << name << "\"!" << endl;
	this->FnInit();
}

void Level::exit_level()
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

Level::~Level()
{
	this->exit_level();
}

