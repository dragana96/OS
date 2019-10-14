/*
 * IDLE.H
 *
 *  Created on: Jul 4, 2018
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_

#include "PCB.h"
#include "thread.h"

class idle: public Thread {
	public:
				idle();
		        virtual void run();
				PCB* idlePCB;
};





#endif /* IDLE_H_ */
