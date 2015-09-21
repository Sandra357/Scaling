//********************************************************************
//
// File : double_scaling.cpp
// Description : Scaling function "Double method"
// Created : 31 april 2015
// Author : Alexandra Bogdanova
//
//********************************************************************

#ifndef SCALING_CPP
#define SCALING_CPP

#include "scaling.h"

pictureStruct double_scaling (pictureStruct picture, int scale_up, int scale_down, FILE* RESIZE_FILE) {

    pictureStruct resize_picture;

    // Declare new size
    int newW = picture.width * scale_up;
    int newH = picture.high * scale_up;
    resize_picture.width = newW;
    resize_picture.high = newH;
    resize_picture.image.resize(newW*newH);

    // Resize picture
    for (int i = 0; i < newH; i++)
        for (int j = 0; j < newW; j++) {
            resize_picture[i][j].blue = picture[i/scale_up][j/scale_up].blue;
            resize_picture[i][j].green = picture[i/scale_up][j/scale_up].green;
            resize_picture[i][j].red = picture[i/scale_up][j/scale_up].red;
            resize_picture[i][j].a = picture[i/scale_up][j/scale_up].a;
        }

    // Send resize picture to write function
    pictureStruct decrease_picture = decrease(resize_picture, scale_down);
    writePicture(RESIZE_FILE, decrease_picture);

    return decrease_picture;
}


#endif