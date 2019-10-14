/*
 * MAIN.CPP
 *
 *  Created on: Jul 5, 2018
 *      Author: OS1
 */
#include "SYSTEM.H"
#include "IDLE.H"

extern int userMain(int argc, char* argv[]);


int main(int argc, char* argv[]){

	system::inic();

	int i= userMain(argc, argv);

	system::restore();

	return i;

}

