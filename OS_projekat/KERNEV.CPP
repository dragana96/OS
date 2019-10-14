#include "KERNEV.H"

#include "IVTENTRY.H"
#include "SCHEDULE.H"
#include "SYSTEM.H"
#include "PCB.H"

KernelEv::KernelEv(IVTNo ivtNo){
	creator = system::running;
	blocked = 0;
	value = 1;
	Event* myEvent;
	this->ivtNo = ivtNo;
	IVTEntry::IVT[ivtNo]->kernelEvent= this; //cuvamo u IVT u dati ulaz event

}

KernelEv::~KernelEv(){
	IVTEntry::IVT[ivtNo]->kernelEvent= 0;
}

void KernelEv::wait(){
	if(system::running == creator) {
		if (value = 0) {
			system::running->state = BLOCKED;
			blocked = system::running;
		}
		else value = 0;
	}
}

void KernelEv::signal(){
	if (blocked == 0)
			value = 1;

	else {
		blocked->state = RUNNABLE;
		Scheduler::put(blocked);
		blocked = 0;
	}
}

