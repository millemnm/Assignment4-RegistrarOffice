#include "Run.h"
#include "Student.h"
#include "Window.h"
#include "GenQueue.h"
#include "DList.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <stdio.h>
#include <limits>
#include <string>
#include <thread>
#include <chrono>
//#include <vector>

using namespace std;

Run::Run(){
	queue = new GenQueue<Student*>();
	history = new DList<int>();
	//window = new Window();
	numWindows = 0;
}

Run::~Run(){
	delete[] queue;
	delete[] history;
	delete window;
}

void Run::executeFile(){
	//Setting the file data comes from
	std::ifstream file;
	string fileName;
	std::cout << "What name of the map file? " << flush;
	while(true){
		file.close();
    	file.clear();
		getline(cin, fileName); //get the file name from terminal
		file.open(fileName.c_str()); //open the file
		if(file.is_open()){
			break;
		}
		std::cout << "Invalid file name, please enter a valid name: " << flush;
	}


	bool reading = true; //true if there is still information left to be read from the file
	bool helping = false; //true if any 1 window is being used
	int whenArive = -1;
	int time = 0; // Clock that counts in minutes from 0 when the program starts

	std::string line;
	getline(file, line);
	int input = std::stoi(line);
	numWindows = input; //set amount of open windows

	window = new Window[numWindows]; //an array holding each window

	while(reading || !(queue->isEmpty()) || helping){
		if((whenArive == -1) && reading){
			if(getline(file, line)){ //get when the students arive
				whenArive = std::stoi(line);
			}else{
				reading = false; //if there is nothing left to read for information
			}
		}

		if(whenArive == time && reading){
			getline(file, line); //get how many students arive
			int numArive = std::stoi(line);
			for(int i = 0; i < numArive; ++i){
				if(getline(file, line)){
					input = std::stoi(line);
					Student *newStu = new Student(input, whenArive);
					queue->insert(newStu);
				}
			}
			whenArive = -1; //set it back to be able to read the next group of students
		}

		helping = false; //set to false to be changed back once there is a used window

		for(int w = 0; w < numWindows; ++w){
			if(window[w].isOpen()){
				if(!(queue->isEmpty())){
					history->addSort(queue->peek()->fixWaitTime(time)); //Fix wait time and sort it into history
					window[w].help(queue->remove());
					helping = true;
				}
			}else{
				helping = true;
			}
		}

		++time;
	}
	file.close();
}

void Run::printData(){
	//Count for Students wait time
	int numStu = history->getSize();
	int totalWait = 0;
	int longestWait = history->getBack();
	int longerTen = 0;
	int median = 0;
	while(history->getSize() > 2){//remove both the front and back until there are 1 or 2 nodes left
		int wait = history->removeHead();
		totalWait += wait;
		if(wait > 10){
			++longerTen;
		}
		wait = history->removeTail();
		totalWait += wait;
		if(wait > 10){
			++longerTen;
		}
	}

	if(history->getSize() == 1){
		median = history->removeHead();
		totalWait += median;
		if(median > 10){
			++longerTen;
		}


	}else if(history->getSize() == 2){
		int med1 = history->removeHead();
		int med2 = history->removeTail();
		totalWait += med1 + med2;
		median = (med1 + med2) / 2;

		if(med2 > 10){
			++longerTen;
		}
		if(med1 > 10){
			++longerTen;
		}
	}
	int meanWait = totalWait / numStu;

	//count for Window idle time
	int totalIdle = 0;
	int longestIdle = 0;
	int longerFive = 0;
	for(int k = 0; k < numWindows; ++k){
		int idle = window[k].getIdleTime();
		totalIdle += idle;
		if(idle > longestIdle){
			longestIdle = idle;
		}
		if(idle > 5){
			++longerFive;
		}
	}
	int meanIdle = totalIdle / numWindows;

	//Print Data:
	std::cout << "1) Mean Student Wait Time:      |  " << meanWait<< '\n';
	std::cout << "2) Median Student Wait Time:    |  " << median<< '\n';
	std::cout << "3) Longest Student Wait Time:   |  " << longestWait<< '\n';
	std::cout << "4) Num Students Waited >10Min:  |  " << longerTen << '\n';
	std::cout << "5) Mean Window Idle Time:       |  " << meanIdle << '\n';
	std::cout << "6) Longest Window Idle Time:    |  " << longestIdle << '\n';
	std::cout << "7) Num Window Idle >5Min:       |  " << longerFive << '\n';

}
