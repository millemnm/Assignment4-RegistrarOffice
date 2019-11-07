#ifndef RUN_H
#define RUN_H

#include "Student.h"
#include "Window.h"
#include "GenQueue.h"
#include "DList.h"

//#include <vector>

using namespace std;

class Run
{
public:
	Run();
	~Run();

	void executeFile();
	void printData();

private:
	int numWindows; //Number of windows open during simulation

	GenQueue<Student*> *queue; //the line of students
	DList<int> *history; //history of all the wait time sorted from smallest to largest
	Window *window;
};

#endif
