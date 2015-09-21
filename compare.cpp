//********************************************************************
//
// File : compair.cpp
// Description : Function for analyze scaling quality
// Created : 31 april 2015
// Author : Alexandra Bogdanova
//
//********************************************************************

#ifndef COMPARE_CPP
#define COMPARE_CPP

#include "scaling.h"

void compare (unsigned char *source, unsigned char *biline, unsigned char *doubl, int size) {
	
	//*******************************RMS****************************
	uint32_t RMS_bil, RMS_double;
	RMS_bil = RMS_double = 0;
        
    for (uint32_t i = 0; i < size; i++) {
        RMS_bil += (((uint32_t)source[i] - (uint32_t)biline[i])*((uint32_t)source[i] - (uint32_t)biline[i]));
        RMS_double += (((uint32_t)source[i] - (uint32_t)doubl[i])*((uint32_t)source[i] - (uint32_t)doubl[i]));
    }

    RMS_bil = sqrt(RMS_bil/size);
    std::ostringstream ost;
    ost << RMS_bil; 
    write_log_file("*INFO Compare : RMS of bilining = " + ost.str() + "\n");

    RMS_double = sqrt(RMS_double/size);
    ost.str("");
    ost << RMS_double; 
    write_log_file("*INFO Compare : RMS of double = " + ost.str() + "\n");

    //*******************************D****************************
    uint32_t d_bil, d_double;
    d_bil = d_double = 0;

    for (uint32_t i = 0; i < size; i++) {
    	d_bil += (((uint32_t)source[i] - (uint32_t)biline[i])*((uint32_t)source[i] - (uint32_t)biline[i]));
    	d_double += (((uint32_t)source[i] - (uint32_t)doubl[i])*((uint32_t)source[i] - (uint32_t)doubl[i]));
    }

    if (d_bil == 0) { 

    	write_log_file("*INFO Compare : D of bilining = 0\n");
    	write_log_file("*INFO Compare : D of double = 0\n");
    	return;
    }

    else {

    	d_bil = 10 * log10(255 * 255 * size * size / d_bil);
    	ost.str("");
    	ost << d_bil; 
    	write_log_file("*INFO Compare : D of bilining = " + ost.str() + "\n");

    	d_double = 10 * log10(255 * 255 * size * size / d_double);
    	ost.str("");
    	ost << d_double; 
    	write_log_file("*INFO Compare : D of double = " + ost.str() + "\n");

    	return;
    }
  
}

#endif