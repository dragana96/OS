/*
 * THREAD.H
 *
 *  Created on: Jul 4, 2018
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;
class PCB;
// Kernel's implementation of a user's thread
class Thread {
public:
	void start();
	void waitToComplete();
	virtual ~Thread();
	static void sleep(Time timeToSleep);
protected:
	friend class PCB;
	friend class system;
	Thread(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual void run() { }
private:
	PCB* myPCB;
};
void dispatch();





#endif /* THREAD_H_ */
