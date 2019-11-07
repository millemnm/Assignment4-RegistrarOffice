#include "Student.h"

using namespace std;

//constructor
Student::Student(){
	waitTime = 0;
	windowTime = 0;
}
//Overloaded constructor
Student::Student(int time, int arive){
	waitTime = arive; //do math once its out of the queue in fixWaitTime.
	windowTime = time;
}
//destructor
Student::~Student(){
}

int Student::getWaitTime(){
	return waitTime;
}

int Student::fixWaitTime(int t){
	waitTime = t - waitTime;
	return waitTime;
}

int Student::getWindowTime(){
	return windowTime;
}

int Student::getFinishTime(){
	return (waitTime + windowTime);
}
