//********************************************************************
//
// File : read_picture.cpp
// Description : Function for read file with source picture
// Created : 31 april 2015
// Author : Alexandra Bogdanova
//
//********************************************************************

#ifndef READ_PICTURE
#define READ_PICTURE

#include "scaling.h"

pictureStruct readPicture (string file_name, pictureStruct picture) {
    
    long lSize = 0;
    unsigned char *buffer;
    int result = 0;
    FILE* ID_LOG_FILE;
    FILE* ID_SOURCE_IMAGE;
    
    // Open source picture for read
    ID_SOURCE_IMAGE = fopen (file_name.c_str(), "rb");
    write_log_file("*INFO readPicture : open file " + file_name + "\n");   
    if (ID_SOURCE_IMAGE == NULL) {
        write_log_file("*INFO readPicture : file for read " + file_name + "can't open\n");
    }

    // Find a size of file
    fseek(ID_SOURCE_IMAGE , 0 , SEEK_END);
    lSize = ftell(ID_SOURCE_IMAGE);
    std::ostringstream ost;
    ost << lSize; 
    write_log_file("*INFO readPicture : lSize = " + ost.str() + "\n");
    rewind(ID_SOURCE_IMAGE);
    
    // Memmory allocation for buffer
    buffer = (unsigned char*) malloc(sizeof(unsigned char) * lSize + 1);
    if (buffer == NULL)
        write_log_file("*ERROR readPicture : Memory error\n");

    // Copy file to buffer
    result = fread(buffer, 1, lSize, ID_SOURCE_IMAGE);
    if (result != lSize)
        write_log_file("*ERROR readPicture : Reading error\n");

    // Close source file
    fclose (ID_SOURCE_IMAGE);

    // Copy buffer to array
    unsigned char img [lSize];
    for (int i = 0; i < lSize; i++) {
        img[i] = *(buffer);
        buffer++;
    }

    for (int i = 0; i < 18; i++) {
        ost.str("");
        ost << (int)img[i];
        write_log_file("*INFO readPicture : head =  " + ost.str() + "\n");
    }

    // Find a width
    picture.width = (int)img[13]*256 + (int)img[12];
    ost.str("");
    ost << picture.width;
    write_log_file("*INFO readPicture : width = " + ost.str() + "\n");

    // Find a high
    picture.high = (int)img[15]*256 + (int)img[14];
    ost.str("");
    ost << picture.high;
    write_log_file("*INFO readPicture : high = " + ost.str() + "\n");

    // Find a type
    int type = (int)img[17];
    ost.str("");
    ost << type;
    write_log_file("*INFO readPicture : type = " + ost.str() + "\n");

    // CREATE 2-dimensional arrays of different colours
    int k = 18;
    int oldW = picture.width;
    int oldH = picture.high;
    picture.image.resize(oldW*oldH);

    if (type == 24) {
        for (int i = oldH - 1; i >= 0; i--)
            for (int j = oldW - 1; j >= 0; j--) {
                picture[i][j].blue = img[k];
                picture[i][j].green = img[k+1];
                picture[i][j].red = img[k+2];
                picture[i][j].a = img[k+3];
                k+=4;
            }
    }
    else if (type == 40) {
        for (int i = 0; i < oldH; i++)
            for (int j = 0; j < oldW; j++) {
                picture[i][j].blue = img[k];
                picture[i][j].green = img[k+1];
                picture[i][j].red = img[k+2];
                picture[i][j].a = img[k+3];
                k+=4;
            }
    }
    else if (type == 8) {
        for (int i = oldH - 1; i >= 0; i--)
            for (int j = 0; j < oldW; j++) {
                picture[i][j].blue = img[k];
                picture[i][j].green = img[k+1];
                picture[i][j].red = img[k+2];
                picture[i][j].a = img[k+3];
                k+=4;
            }
    }
    else if (type == 56) {
        for (int i = 0; i < oldH; i++)
            for (int j = oldW - 1; j >= 0; j--) {
                picture[i][j].blue = img[k];
                picture[i][j].green = img[k+1];
                picture[i][j].red = img[k+2];
                picture[i][j].a = img[k+3];
                k+=4;
            }
    }
    else
        write_log_file("*ERROR readPicture: wrong 17th byte of head\n");

    return picture;
}


#endif