/*
 * THREAD.CPP
 *
 *  Created on: Jul 4, 2018
 *      Author: OS1
 */
#include "THREAD.H"
#include "PCB.H"
#include "SCHEDULE.H"
#include "SYSTEM.H"


Thread::Thread (StackSize stackSize, Time timeSlice){

#ifndef BCC_BLOCK_IGNORE
	LOCK
	//pravimo objekat PCB-a
	myPCB = new PCB();

	//definisanje osnovnih parametara u PCB-u
	myPCB->timeslice = timeSlice;
	myPCB->myThread = this;
	myPCB->waitQueue = new Queue();
	myPCB->state = NEW;

	//provera da li je data velicina steka veca od maksimalno dozvoljene
	if(stackSize > system::MAXstack)
			myPCB->stackSize = system::MAXstack;
	else myPCB->stackSize = stackSize;


		if (system::idleFlag == 1) {		//postavljanje idle niti
				system::idleFlag = 0;
				system::idlePCB = myPCB;
			}

		UNLOCK
		#endif
}

Thread::~Thread(){
#ifndef BCC_BLOCK_IGNORE
	LOCK
	delete myPCB;
	UNLOCK
#endif
}

void Thread::waitToComplete(){
/*
	 Moramo napraviti i dodati polje u svakom PCB-u, pokazivac na listu svih PCB-ova
	 koji cekaju na zavrsetak.
	 Sve sto treba uraditi u metodi je ubaciti running PCB u tu listu,
	 staviti mu status na blokiran i promeniti kontekst.
	 */

#ifndef BCC_BLOCK_IGNORE
	LOCK
	if (system::running == this->myPCB) return;
			if(this->myPCB->state == FINISHED){

				UNLOCK
				return;
			}
			if(this == system::idleThr){
				UNLOCK
				return;
			}

			system::running->state = BLOCKED;
				myPCB->waitQueue->put(system::running);
				system::dispatch();
				UNLOCK
				#endif

}

void Thread::start(){ //oznacimo status kao READY i stavimo u scheduler pri cemu obracamo paznju na to da li se radi o idle niti
#ifndef BCC_BLOCK_IGNORE
	LOCK
	myPCB->createStack();
	myPCB->state = RUNNABLE;
	if (this->myPCB != system::idlePCB) //idle nit ne sme  scheduler
			Scheduler::put(myPCB);
	UNLOCK
#endif
}

void dispatch(){
#ifndef BCC_BLOCK_IGNORE
	LOCK
	system::dispatch();
	UNLOCK
#endif
}

void Thread::sleep(Time timeToSleep){
	//smesti running PCB u jednu listu i obelezi ga kao spavajuci
#ifndef BCC_BLOCK_IGNORE
	LOCK
	system::running->timeToSleep = timeToSleep;
	system::sleepingQueue->put_to_sleep(system::running);
	system::running->state = SLEEPING;
	system::dispatch();
	UNLOCK
#endif
}



