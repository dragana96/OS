/*
 * MAKRO.H
 *
 *  Created on: Jul 6, 2018
 *      Author: OS1
 */

#ifndef MAKRO_H_
#define MAKRO_H_

#define PREPAREENTRY(numEntry, callOld)\
void interrupt inter##numEntry(...);\
IVTEntry newEntry##numEntry(numEntry,&inter##numEntry);\
void interrupt inter##numEntry(...){\
newEntry##numEntry.signal();\
if (callOld == 1)\
newEntry##numEntry.callOld();\
dispatch();\
}


#endif /* MAKRO_H_ */
