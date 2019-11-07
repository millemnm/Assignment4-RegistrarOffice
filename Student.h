
#ifndef STUDENT
#define STUDENT

class Student{
public:
	Student();
	Student(int time, int arive);
	~Student();

	int fixWaitTime(int t);
	int getWaitTime();
	int getWindowTime();
	int getFinishTime(); //How long they will be there (wait + window)


private:
	int waitTime; //How long they wait in line
	int windowTime; //How long they are at the window

};
#endif
