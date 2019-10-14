/*
 * EVENT.CPP
 *
 *  Created on: Jul 6, 2018
 *      Author: OS1
 */


#include "Event.h"

#include "KERNEV.H"
#include "SYSTEM.h"

Event::Event(IVTNo ivtNo){
#ifndef BCC_BLOCK_IGNORE
	LOCK
	myImpl = new KernelEv(ivtNo);
	UNLOCK
#endif
}

Event::~Event(){
#ifndef BCC_BLOCK_IGNORE
	LOCK
	delete myImpl;
	UNLOCK
#endif
}

void Event::wait(){
#ifndef BCC_BLOCK_IGNORE
	LOCK
	myImpl->wait();
	UNLOCK
#endif
}

void Event::signal(){
#ifndef BCC_BLOCK_IGNORE
	LOCK
	myImpl->signal();
	UNLOCK
#endif
}


