/*
 * PCB.CPP
 *
 *  Created on: Jul 4, 2018
 *      Author: OS1
 */

#include "PCB.h"
#include "THREAD.H"
#include <dos.h>
#include <iostream.h>
#include "SYSTEM.H"


PCB::~PCB(){
#ifndef BCC_BLOCK_IGNORE
	LOCK
	delete waitQueue;
	delete myStack;
 myThread = 0;
	UNLOCK
#endif
}

void PCB::createStack(){
#ifndef BCC_BLOCK_IGNORE
	LOCK
	static int n = system::running->stackSize;
	myStack = new unsigned[n/sizeof(unsigned int)];

			#ifndef BCC_BLOCK_IGNORE
			myStack[n-1] = 0x200;
			myStack[n-2] = FP_SEG(&(wrapper));; //ubacujemo segmentni i ofsetni deo tela niti u stek
			myStack[n-3] = FP_OFF(&(wrapper));
			sp = FP_OFF(myStack+n-12);
			ss = FP_SEG(myStack+n-12);
			bp = sp;
			#endif
UNLOCK
#endif
			system::running->myStack = myStack;
}

void PCB::wrapper(){

	system::running->myThread->run();

#ifndef BCC_BLOCK_IGNORE
	LOCK
	system::running->state = FINISHED;

		while (system::running->waitQueue->first){
				PCB* tmp = system::running->waitQueue->get();
				tmp->state = RUNNABLE;
				Scheduler::put(tmp);
	}

	system::dispatch();

	UNLOCK
#endif

}


