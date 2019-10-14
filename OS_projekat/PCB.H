/*
 * PCB.H
 *
 *  Created on: Jul 4, 2018
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

enum status { RUN, RUNNABLE, BLOCKED, SLEEPING, IDLE, LOADING, NEW, FINISHED };
#include "system.h"
#include "queue.h"

class PCB{
	friend class system;
	friend class Thread;
	friend class idle;
public:
	unsigned int ss;
	unsigned int sp;
	unsigned int bp;
	status state;
	unsigned timeslice;
	unsigned long stackSize;
	int timeToSleep;

	Thread* myThread;
	unsigned* myStack;
	Queue*  waitQueue;

	int id;

	~PCB();
	static void wrapper();
	void createStack();
};




#endif /* PCB_H_ */
