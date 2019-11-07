#include "Window.h"
#include <iostream>

using namespace std;

//constructor
Window::Window(){
	open = true;
	idleTime = 0;
	tLeft = 0;
}
//destructor
Window::~Window(){
}

int Window::getIdleTime(){
	return idleTime;
}

bool Window::isOpen(){
	if(open){
		++idleTime;
	}else{
		--tLeft;
		if(tLeft == 0){
			open = true;
		}
	}
	return open;
}

void Window::help(Student * help){
	open = false;
	helping = help;
	tLeft = helping->getWindowTime();
}
