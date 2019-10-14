/*
 * SYSTEM.CPP
 *
 *  Created on: Jul 4, 2018
 *      Author: OS1
 */

#include "SYSTEM.H"
#include <dos.h>
#include "PCB.h"
#include "SCHEDULE.H"

#include <iostream.h>
#include "THREAD.H"

#include "IDLE.H"

extern void tick();
Queue* system::sleepingQueue;
PCB* system::idlePCB = 0;
idle* system::idleThr = 0;

int system::MAXstack = 65535;
PCB* system::running = 0;
pInterrupt system::oldISR;
int system::idleFlag = 1;

volatile int system::cnt = 20;
volatile int system::explicit_dispatch = 0;
unsigned tempSP, tempSS, tempBP;

void system::inic(){ //cuvanje stare i postavljanje nove prekidne rutine
#ifndef BCC_BLOCK_IGNORE
	LOCK

	system::sleepingQueue = new Queue();
	system::idleThr = new idle();
	system::idleThr->start();
	system::running = new PCB();
	system::running->state = RUN;
	system::running->createStack();

	oldISR = getvect(0x08);
		setvect(0x08,timer);





	UNLOCK


#endif


}

void system::restore(){ //vracanje stare prekidne rutine
#ifndef BCC_BLOCK_IGNORE
	LOCK
	setvect(0x08,oldISR);


	system::running->state = FINISHED;
	delete idleThr;
	delete idlePCB;
	delete sleepingQueue;
	delete system::running;

	UNLOCK
#endif

}

void interrupt system::timer(...){ //nova prekidna rutina

#ifndef BCC_BLOCK_IGNORE

		if (!explicit_dispatch)
		{
			system::oldISR();

			if(sleepingQueue->getCount())
				sleepingQueue->wake_up();
			tick();
		}
		if (!explicit_dispatch)
			if(running->timeslice != 0){
						if(cnt>0)
							cnt--;
					}

		if ((cnt == 0 && running->timeslice != 0) || explicit_dispatch)
		{
			asm{
				mov tempSP, sp
				mov tempSS, ss
				mov tempBP, bp
			}

			running->sp = tempSP;
			running->ss = tempSS;
			running->bp = tempBP;

			if ((running->state == RUN) && (running != idleThr->idlePCB)){
				running->state = RUNNABLE;
				Scheduler::put(running);
			}
			running = Scheduler::get();
			if(running)
				running->state = RUN;
			else
				running = idleThr->idlePCB;

			tempSP = running->sp;
			tempSS = running->ss;
			tempBP = running->bp;

				cnt = running->timeslice;

				asm{
					mov sp, tempSP
					mov ss, tempSS
					mov bp, tempBP
				}


			explicit_dispatch = 0;
		}


#endif

}


void system::dispatch(){
#ifndef BCC_BLOCK_IGNORE
	LOCK
	explicit_dispatch = 1;
	timer();
	UNLOCK
#endif
}


