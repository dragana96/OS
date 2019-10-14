/*
 * QUEUE.CPP
 *
 *  Created on: Jul 4, 2018
 *      Author: OS1
 */

#include "QUEUE.H"
#include "PCB.h"
#include "SCHEDULE.H"
#include <iostream.h>

Queue::Queue(){
	first = 0;
	last = 0;
	count = 0;
	wake_up_all = 0;
}

Queue::~Queue(){
	while (getCount() > 0){

			get();

	}
}

void Queue::put(PCB* p){ //ubacivanje elementa na kraj liste
	Elem *el = new Elem(p);

	if (first == 0)
		first = el;
	else
		last->next = el;
	last = el;

	count++;
}

PCB* Queue::get(){

	if (first == 0)
		return 0;

	Elem *oldElem = first;
	PCB *oldPCB = first->pcb;

	first = first->next;
	if (first == 0)
		last = 0;
	oldElem->next = 0;
	delete oldElem;

	count--;

	return oldPCB;
}

int Queue::getCount() const{
	return count;
}







void Queue::put_to_sleep(PCB* pcb){

	Elem *temp = new Elem(pcb);

	Elem *prethodni = 0, *trenutni = first;

	while (trenutni && trenutni->pcb->timeToSleep < temp->pcb->timeToSleep) {

		temp->pcb->timeToSleep -= trenutni->pcb->timeToSleep;
		prethodni = trenutni;
		trenutni= trenutni->next;
	}

	if (trenutni) {
		trenutni->pcb->timeToSleep -= temp->pcb->timeToSleep;
	}

	temp->next = trenutni;
	if (prethodni)
		prethodni->next = temp;
	else
		first = temp;

	count++;
}

void Queue::wake_up(){

	if (first && first->pcb->timeToSleep)
		first->pcb->timeToSleep--;

	while (first && first->pcb->timeToSleep == 0) {
		Elem *old = first;
		first = first->next;
		old->next = 0;

		old->pcb->state = RUNNABLE;
		Scheduler::put(old->pcb);

		count--;

		delete old;
	}
}


