#ifndef WINDOW
#define WINDOW

#include "Student.h"

class Window{
public:
	Window();
	~Window();

	int getIdleTime();
	bool isOpen();
	void help(Student * help);

private:
	bool open;
	int idleTime; //The amount of time there is no one at the window
	int tLeft;

	Student *helping;
};
#endif
