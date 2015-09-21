//********************************************************************
//
// File : decrease.cpp
// Description : Function for decrease size of picture
// Created : 31 april 2015
// Author : Alexandra Bogdanova
//
//********************************************************************

#ifndef SCALING_CPP
#define SCALING_CPP

#include "scaling.h"

pictureStruct decrease (pictureStruct picture, int scale) {

    pictureStruct resize_picture;

    // Declare new size
    int newW = picture.width / scale;
    int newH = picture.high / scale;
    resize_picture.width = newW;
    resize_picture.high = newH;

    resize_picture.image.resize(newW*newH);

    // Decrease picture
    for (int i = 0; i < newH; i++)
        for (int j = 0; j < newW; j++) {
            resize_picture[i][j].blue = picture[i*scale][j*scale].blue;
            resize_picture[i][j].green = picture[i*scale][j*scale].green;
            resize_picture[i][j].red = picture[i*scale][j*scale].red;
            resize_picture[i][j].a = picture[i*scale][j*scale].a;
        }

    return resize_picture;  
}

#endif