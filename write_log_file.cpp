//********************************************************************
//
// File : write_log_file.cpp
// Description : Function for writing errors and information about
//               intermidiate results about work of programm
// Created : 31 april 2015
// Author : Alexandra Bogdanova
//
//********************************************************************

#ifndef WRITE_LOG_FILE
#define WRITE_LOG_FILE

#include "scaling.h"

void write_log_file (string message) {

	FILE* FILE_LOG ; // pointer to log file

	// open log file
	FILE_LOG = fopen(LOG_FILE_NAME, "ab");

	// write info to debug file
	if (!fwrite(message.c_str(), 1, message.size(), FILE_LOG))
		cout << "*ERROR write_debug_file : Can not open debug file\n";
	
	// close log file
	fclose(FILE_LOG);
	return;
}

#endif