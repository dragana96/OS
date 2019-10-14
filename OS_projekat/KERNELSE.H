/*
 * KERNELSE.H
 *
 *  Created on: Jul 5, 2018
 *      Author: OS1
 */

#ifndef KERNELSE_H_
#define KERNELSE_H_


#include "QUEUESEM.H"
#include "SYSTEM.H"
#include "PCB.H"

class KernelSe {
private:
	int count;
	QueueSem* queue;
public:
	KernelSe(int i);
	virtual ~KernelSe();


	int value() const{
		return count;
	}

	void wait();
	void signal();
};


#endif /* KERNELSE_H_ */
