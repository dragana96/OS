/*
 * IDLE.CPP
 *
 *  Created on: Jul 4, 2018
 *      Author: OS1
 */
#include "idle.h"
#include "PCB.h"
#include "system.h"
#include "thread.h"

idle::idle() : Thread(1024, 1) {
	idlePCB = system::idlePCB;
}

void idle::run(){
	while(1){

	}
}




