#ifndef IVTENTRY_H_
#define IVTENTRY_H_


#include "SYSTEM.H"




typedef unsigned char IVTNo;

class IVTEntry{
	friend class KernelEv;

private:
	pInterrupt oldISR;
	IVTNo ivtNo;

	static IVTEntry* IVT[];

public:
	IVTEntry(IVTNo intNo, pInterrupt oldISR);
	~IVTEntry();
	
	void signal();
	void callOldR();
	KernelEv* kernelEvent;
	

};

#endif



