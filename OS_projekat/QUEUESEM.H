/*
 * QUEUESEM.H
 *
 *  Created on: Jul 5, 2018
 *      Author: OS1
 */

#ifndef QUEUESEM_H_
#define QUEUESEM_H_


#include "SCHEDULE.H"

class PCB;

class QueueSem{
	friend class PCB;
	friend class Thread;


public:
	struct El{
		PCB* pcb;
		El* next;
		El(PCB* newPCB){
			pcb = newPCB;
			next = 0;
		}
		~El(){}
	};

	QueueSem();
	~QueueSem();
	void put(PCB* pcb);
	PCB* get();
	int getCount() const;

	El *first, *last;
	int count;



};


#endif /* QUEUESEM_H_ */
