/*
 * QUEUESEM.CPP
 *
 *  Created on: Jul 5, 2018
 *      Author: OS1
 */



#include "QUEUESEM.H"
#include "PCB.h"
#include "SCHEDULE.H"
#include <iostream.h>

QueueSem::QueueSem(){
	first = 0;
	last = 0;
	count = 0;
}

QueueSem::~QueueSem(){
	while (getCount() > 0){
			get();
	}
}

void QueueSem::put(PCB* p){
	El *el = new El(p);

	if (first == 0)
		first = el;
	else
		last->next = el;
	last = el;

	count++;
}

PCB* QueueSem::get(){

	if (first == 0)
		return 0;

	El *oldElem = first;
	PCB *oldPCB = first->pcb;

	first = first->next;
	if (first == 0)
		last = 0;
	oldElem->next = 0;
	delete oldElem;

	count--;

	return oldPCB;
}

int QueueSem::getCount() const{
	return count;
}

