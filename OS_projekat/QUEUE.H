/*
 * QUEUE.H
 *
 *  Created on: Jul 4, 2018
 *      Author: OS1
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "SCHEDULE.H"

class PCB;

class Queue{
	friend class PCB;
	friend class Thread;


public:
	struct Elem{
		PCB* pcb;
		Elem* next;
		Elem(PCB* newPCB){
			pcb = newPCB;
			next = 0;
		}
		~Elem(){}
	};

	Queue();
	~Queue();
	void put(PCB* pcb);
	PCB* get();
	int getCount() const;

	void put_to_sleep(PCB* pcb);
	void wake_up();

	Elem *first, *last;
	int count;
	int wake_up_all;


};




#endif /* QUEUE_H_ */
