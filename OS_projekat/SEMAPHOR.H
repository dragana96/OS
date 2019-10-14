/*
 * SEMAPHOR.H
 *
 *  Created on: Jul 5, 2018
 *      Author: OS1
 */

#ifndef SEMAPHOR_H_
#define SEMAPHOR_H_

#include "KERNELSE.H"


class Semaphore {
private:
	KernelSe* mySem;
public:
	Semaphore(int init = 1);
	virtual ~Semaphore();

	virtual void wait();
	virtual void signal();

	int val() const;


};




#endif /* SEMAPHOR_H_ */
