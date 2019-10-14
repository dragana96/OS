/*
 * SYSTEM.H
 *
 *  Created on: Jul 4, 2018
 *      Author: OS1
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_


#include "IDLE.H"
#include "PCB.h"
#include "SYSTEM.H"
#include "QUEUE.H"

#define LOCK  asm{ pushf; cli}

#define UNLOCK { asm popf;}


typedef void interrupt (*pInterrupt)(...);

class system{
	friend class Thread;
	friend class idle;
	friend class List;
public:
	static int MAXstack;
	static int idleFlag;
	static Queue* sleepingQueue;
	static PCB* running;

	static PCB* idlePCB;
	static void inic();
	static void restore();
	static void dispatch();
	static pInterrupt oldISR;
	static void interrupt timer(...);
	static volatile int cnt;

	static volatile int explicit_dispatch;
	static idle* idleThr;


};


#endif /* SYSTEM_H_ */
