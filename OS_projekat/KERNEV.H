#ifndef KERNEV_H_
#define KERNEV_H_

#include "EVENT.H"

class KernelEv{
	friend class Event;
public:
	friend class IVTEntry;
	friend class PCB;
	
	KernelEv(IVTNo ivtNo);
	~KernelEv();
	void wait();
	void signal();
	
private:
	int value;
	PCB* blocked; //pamtimo pokazivac na blokiranu nit
	PCB* creator;
	IVTNo ivtNo;
	IVTEntry *entry;
};

#endif
