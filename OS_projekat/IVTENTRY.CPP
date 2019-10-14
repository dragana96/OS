#include "IVTENTRY.H"

#include "SYSTEM.h"
#include <dos.h>

#include "KERNEV.H"



IVTEntry* IVTEntry::IVT[256];

IVTEntry::IVTEntry(IVTNo intNo, pInterrupt newISR){
	ivtNo = intNo;
	IVT[ivtNo] = this;
	kernelEvent = 0;
	oldISR = 0;
	#ifndef BCC_BLOCK_IGNORE
		LOCK
		oldISR = getvect(intNo);
		setvect(intNo, newISR);
		UNLOCK
	#endif
}

IVTEntry::~IVTEntry(){
	IVT[ivtNo] = 0;
	#ifndef BCC_BLOCK_IGNORE
		LOCK
		setvect(ivtNo, oldISR);
		UNLOCK
	#endif
}
	

	
void IVTEntry::signal() {
	if (kernelEvent != 0) {
		kernelEvent->signal();
	}
	system::dispatch();
}

void IVTEntry::callOldR() {
	oldISR();
}

