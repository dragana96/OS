/*
 * SEMAPHOR.CPP
 *
 *  Created on: Jul 5, 2018
 *      Author: OS1
 */
#include "SEMAPHOR.H"

Semaphore::Semaphore(int i) {
#ifndef BCC_BLOCK_IGNORE
	LOCK
	mySem = new KernelSe(i);
	UNLOCK
#endif
}

Semaphore::~Semaphore() {
#ifndef BCC_BLOCK_IGNORE
	LOCK
	if(mySem)
		delete mySem ;
	UNLOCK
#endif
}

void Semaphore::wait(){
#ifndef BCC_BLOCK_IGNORE
	LOCK
	mySem->wait();
	UNLOCK
#endif
}

void Semaphore::signal(){
#ifndef BCC_BLOCK_IGNORE
	LOCK
	mySem->signal();
	UNLOCK
#endif
}

int Semaphore:: val() const{
#ifndef BCC_BLOCK_IGNORE
	LOCK
	int ret = mySem->value();
	UNLOCK
	return ret;
#endif
}


