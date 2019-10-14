/*
 * KERNELSE.CPP
 *
 *  Created on: Jul 5, 2018
 *      Author: OS1
 */

#include "KERNELSE.H"
#include <iostream.h>

KernelSe::KernelSe(int i){

	count = i;
	queue = new QueueSem();

}

KernelSe::~KernelSe() {

	while (count < 0)
		signal();

	delete queue;

}

void KernelSe::wait(){
	count--;
	if(count < 0){
		queue->put(system::running);
		system::running->state = BLOCKED;
		system::dispatch();
	}

}

void KernelSe::signal(){
	count++;
	if(count <= 0){
		PCB* tmp = queue->get();
		if(tmp){
			tmp->state = RUNNABLE;
			Scheduler::put(tmp);
		}
	}
}


