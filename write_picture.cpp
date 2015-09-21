//********************************************************************
//
// File : write_picture.cpp
// Description : Function for writing resize picture into new file
// Created : 31 april 2015
// Author : Alexandra Bogdanova
//
//********************************************************************

#ifndef WRITE_PICTURE
#define WRITE_PICTURE

#include "scaling.h"

void writePicture(FILE *newPicture, pictureStruct picture) {

    std::ostringstream ost;

    // Define new size of final picture
    int size = 18 + picture.width * picture.high * 4;
    ost.str("");
    ost << (int)size;
    write_log_file("*INFO writePicture : size = " + ost.str() + "\n");

    // Memory allocation for final picture
    unsigned char *result;
    result = new unsigned char[size];

    // Make header
	for (int i = 0; i < 18; i++) {
        switch (i) {
        	case 2:
        		result[i] = 2;
                ost.str("");
                ost << (int)result[i];
                write_log_file("*INFO writePicture : head =  " + ost.str() + "\n");
                break;
            case 12:
                result[i] = picture.width & 0xFF;
                ost.str("");
                ost << (int)result[i];
                write_log_file("*INFO writePicture : head =  " + ost.str() + "\n");
                break;
            case 13:
                result[i] = (picture.width >> 8) & 0xFF;
                ost.str("");
                ost << (int)result[i];
                write_log_file("*INFO writePicture : head =  " + ost.str() + "\n");
                break;
            case 14:
                result[i] = picture.high & 0xFF;
                ost.str("");
                ost << (int)result[i];
                write_log_file("*INFO writePicture : head =  " + ost.str() + "\n");
                break;
            case 15:
                result[i] = (picture.high >> 8) & 0xFF;
                ost.str("");
                ost << (int)result[i];
                write_log_file("*INFO writePicture : head =  " + ost.str() + "\n");
                break;
            case 16:
            	result[i] = 32;
                ost.str("");
                ost << (int)result[i];
                write_log_file("*INFO writePicture : head =  " + ost.str() + "\n");
                break;
            case 17:
                result[i] = 40;
                ost.str("");
                ost << (int)result[i];
                write_log_file("*INFO writePicture : head =  " + ost.str() + "\n");
                break;
            default:
                result[i] = 0;
                ost.str("");
                ost << (int)result[i];
                write_log_file("*INFO writePicture : head =  " + ost.str() + "\n");
                break;
        }
    }

    // Copy bytes of picture
    int k = 18;

    memcpy(result+k, &picture.image[0], size - k);

    // Write final picture to file
    if (!fwrite(result, 1, size, newPicture))
    	write_log_file("*ERROR writePicture : can't write resize picture\n");

    // Clear memory
    fclose(newPicture);
    delete[] result;


    return;
}

#endif