//********************************************************************
//
// File : bilining_interpolation.cpp
// Description : Scale function "bilining interpolation"
// Created : 31 april 2015
// Author : Alexandra Bogdanova
//
//********************************************************************

#ifndef BILINING_INTERPOLATION_CPP
#define BILINING_INTERPOLATION_CPP

#include "scaling.h"

pictureStruct bilining_interpolation (pictureStruct picture, int scale_up, int scale_down, FILE* RESIZE_FILE) {

    pictureStruct resize_picture;

    // Declare new size
    int newW = picture.width * scale_up;
    int newH = picture.high * scale_up;
    resize_picture.width = newW;
    resize_picture.high = newH;

    resize_picture.image.resize(newW*newH);
    
    // Declare coefficients
    int k1, k2, k3, k4,
        ind1, ind2, jnd1, jnd2;

    // Copy start points
    for (int i = 0; i < newH; i++)
        for (int j = 0; j < newW; j++)
            if (i%scale_up == 0 and j%scale_up == 0) {
            resize_picture[i][j].blue = picture[i/scale_up][j/scale_up].blue;
            resize_picture[i][j].green = picture[i/scale_up][j/scale_up].green;
            resize_picture[i][j].red = picture[i/scale_up][j/scale_up].red;
            resize_picture[i][j].a = picture[i/scale_up][j/scale_up].a;
            }

    // Add new points
    for (int i = 0; i < newH; i++)
        for (int j = 0; j < newW; j++)
            if (!(i%scale_up == 0 and j%scale_up ==0))
                if (scale_up * (1 + i/scale_up) < newH - 1)
                    if (scale_up * (1 + j/scale_up) < newW - 1) {
                        k1 = ((i/scale_up) * scale_up + scale_up - i) * ((j/scale_up) * scale_up + scale_up - j);
                        k2 = (i - (i/scale_up) * scale_up) * ((j/scale_up) * scale_up + scale_up - j);
                        k3 = ((i/scale_up) * scale_up + scale_up - i) * (j - (j/scale_up) * scale_up);
                        k4 = (i - (i/scale_up) * scale_up) * (j - (j/scale_up) * scale_up);
                        ind1 = (i/scale_up) * scale_up;
                        ind2 = (i/scale_up) * scale_up + scale_up;
                        jnd1 = (j/scale_up) * scale_up;
                        jnd2 = (j/scale_up) * scale_up + scale_up;
                        resize_picture[i][j].blue = (resize_picture[ind1][jnd1].blue*k1 + resize_picture[ind2][jnd1].blue*k2 + resize_picture[ind1][jnd2].blue*k3 + resize_picture[ind2][jnd2].blue*k4) / (scale_up*scale_up);
                        resize_picture[i][j].green = (resize_picture[ind1][jnd1].green*k1 + resize_picture[ind2][jnd1].green*k2 + resize_picture[ind1][jnd2].green*k3 + resize_picture[ind2][jnd2].green*k4) / (scale_up*scale_up);
                        resize_picture[i][j].red = (resize_picture[ind1][jnd1].red*k1 + resize_picture[ind2][jnd1].red*k2 + resize_picture[ind1][jnd2].red*k3 + resize_picture[ind2][jnd2].red*k4) / (scale_up*scale_up);
                        resize_picture[i][j].a = (resize_picture[ind1][jnd1].a*k1 + resize_picture[ind2][jnd1].a*k2 + resize_picture[ind1][jnd2].a*k3 + resize_picture[ind2][jnd2].a*k4) / (scale_up*scale_up);
                    }
                    else {
                        k1 = ((i/scale_up) * scale_up + scale_up - i) * ((j/scale_up) * scale_up + scale_up - j);
                        k2 = (i - (i/scale_up) * scale_up) * ((j/scale_up) * scale_up + scale_up - j);
                        k3 = ((i/scale_up) * scale_up + scale_up - i) * (j - (j/scale_up) * scale_up);
                        k4 = (i - (i/scale_up) * scale_up) * (j - (j/scale_up) * scale_up);
                        ind1 = (i/scale_up) * scale_up;
                        ind2 = (i/scale_up) * scale_up + scale_up;
                        jnd1 = (j/scale_up) * scale_up;
                        resize_picture[i][j].blue = (resize_picture[ind1][jnd1].blue*k1 + resize_picture[ind2][jnd1].blue*k2 + 255*k3 + 255*k4) / (scale_up*scale_up);
                        resize_picture[i][j].green = (resize_picture[ind1][jnd1].green*k1 + resize_picture[ind2][jnd1].green*k2 + 255*k3 + 255*k4) / (scale_up*scale_up);
                        resize_picture[i][j].red = (resize_picture[ind1][jnd1].red*k1 + resize_picture[ind2][jnd1].red*k2 + 255*k3 + 255*k4) / (scale_up*scale_up);
                        resize_picture[i][j].a = (resize_picture[ind1][jnd1].a*k1 + resize_picture[ind2][jnd1].a*k2 + 255*k3 + 255*k4) / (scale_up*scale_up);
                   }
                else
                    if (scale_up * (1 + j/scale_up) < newW - 1) {
                        k1 = ((i/scale_up) * scale_up + scale_up - i) * ((j/scale_up) * scale_up + scale_up - j);
                        k3 = ((i/scale_up) * scale_up + scale_up - i) * (j - (j/scale_up) * scale_up);
                        k2 = (i - (i/scale_up) * scale_up) * ((j/scale_up) * scale_up + scale_up - j);
                        k4 = (i - (i/scale_up) * scale_up) * (j - (j/scale_up) * scale_up);
                        ind1 = (i/scale_up) * scale_up;
                        jnd1 = (j/scale_up) * scale_up;
                        jnd2 = (j/scale_up) * scale_up + scale_up;
                        resize_picture[i][j].blue = (resize_picture[ind1][jnd1].blue*k1 + resize_picture[ind1][jnd2].blue*k3 + 255*k2 + 255*k4) / (scale_up*scale_up);
                        resize_picture[i][j].green = (resize_picture[ind1][jnd1].green*k1 + resize_picture[ind1][jnd2].green*k3 + 255*k2 + 255*k4) / (scale_up*scale_up);
                        resize_picture[i][j].red = (resize_picture[ind1][jnd1].red*k1 + resize_picture[ind1][jnd2].red*k3 + 255*k2 + 255*k4) / (scale_up*scale_up);
                        resize_picture[i][j].a = (resize_picture[ind1][jnd1].a*k1 + resize_picture[ind1][jnd2].a*k3 + 255*k2 + 255*k4) / (scale_up*scale_up);
                    }
                    else {
                        k1 = ((i/scale_up) * scale_up + scale_up - i) * ((j/scale_up) * scale_up + scale_up - j);
                        k3 = ((i/scale_up) * scale_up + scale_up - i) * (j - (j/scale_up) * scale_up);
                        k2 = (i - (i/scale_up) * scale_up) * ((j/scale_up) * scale_up + scale_up - j);
                        k4 = (i - (i/scale_up) * scale_up) * (j - (j/scale_up) * scale_up);
                        ind1 = (i/scale_up) * scale_up;
                        jnd1 = (j/scale_up) * scale_up;
                        resize_picture[i][j].blue = (resize_picture[ind1][jnd1].blue*k1 + 255*k2 + 255*k3 + 255*k4) / (scale_up*scale_up);
                        resize_picture[i][j].green = (resize_picture[ind1][jnd1].green*k1 + 255*k2 + 255*k3 + 255*k4) / (scale_up*scale_up);
                        resize_picture[i][j].red = (resize_picture[ind1][jnd1].red*k1 + 255*k2 + 255*k3 + 255*k4) / (scale_up*scale_up);
                        resize_picture[i][j].a = (resize_picture[ind1][jnd1].a*k1 + 255*k2 + 255*k3 + 255*k4) / (scale_up*scale_up);
                    }

    // Send resize picture to write function
    pictureStruct decrease_picture = decrease(resize_picture, scale_down);
    writePicture(RESIZE_FILE, decrease_picture);

    return decrease_picture;

}

#endif



