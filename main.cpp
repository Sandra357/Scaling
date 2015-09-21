//********************************************************************
//
// File : main.cpp
// Description : Program for scaling pictures 
//               by bilining interpolation and double methods.
// Created : 31 april 2015
// Author : Alexandra Bogdanova
//
//********************************************************************


#include "scaling.h"

int main () {

    // Declare files for pictures
    FILE* ID_BILINING;
    FILE* ID_DOUBLE;

    // Declare structs
    pictureStruct source_pic, 
                  bilining_pic_up, bilining_pic_down,
                  double_pic_up, double_pic_down;

    // DELETE LOG FILE
    size_t result = remove(LOG_FILE_NAME);

    // Read list of pictures
    listStruct list = read_list();

    // Declare file name and scales 
    string file_name, name;
    int m0, n0, m1, n1;

    // Define variables for compare quality of pictures
    int size;
    unsigned char *source;
    unsigned char *biline;
    unsigned char *doubl;

    // Resize
    for (int i = 0; i < list.amount; i++) {

        file_name = list[i].file_name;
        write_log_file("************************" + file_name + "******************************\n");
        m0 = n1 = list[i].scale_up;
        n0 = m1 = list[i].scale_down;
            
        // read source picture
        name = "pictures/" + file_name;
        source_pic = readPicture(name, source_pic);

        //**************************BILINING*************************************

        // DECREASE
        name = "pictures/SMALL_BILINING_" + file_name;
        ID_BILINING = fopen(name.c_str(), "wb");
        bilining_pic_down = bilining_interpolation(source_pic, m0, n0, ID_BILINING);

        // INCREASE 
        name = "pictures/BIG_BILINING_" + file_name;
        ID_BILINING = fopen(name.c_str(), "wb");
        bilining_pic_up = bilining_interpolation(bilining_pic_down, m1, n1, ID_BILINING);

        //**************************DOUBLING*************************************

        // DECREASE
        name = "pictures/SMALL_DOUBLE_" + file_name;
        ID_DOUBLE = fopen(name.c_str(), "wb");
        double_pic_down = double_scaling(source_pic, m0, n0, ID_DOUBLE);

        // INCREASE 
        name = "pictures/BIG_DOUBLE_" + file_name;
        ID_DOUBLE = fopen(name.c_str(), "wb");
        double_pic_up = double_scaling(double_pic_down, m1, n1, ID_DOUBLE);
        
        //*************** Compare scaling quality**********************

        // Allocate memory and copy source picture bytes for future compare
        size = source_pic.width * source_pic.high * 4;
        source = new unsigned char[size];
        memcpy(source, &source_pic.image[0], size);

        // Allocate memory and copy biline picture bytes for future compare 
        biline = new unsigned char[size];
        memcpy(biline, &bilining_pic_up.image[0], size);

        // Allocate memory and copy double picture bytes for future compare
        doubl = new unsigned char[size];
        memcpy(doubl, &double_pic_up.image[0], size);

        //Compare
        compare (source, biline, doubl, size);

        // Free memory
        delete[] source;
        delete[] biline;
        delete[] doubl;
    }

    return 0;
 
 }
 