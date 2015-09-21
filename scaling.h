//********************************************************************
//
// File : scaling.h
// Description : Header file for scaling program
// Created : 31 april 2015
// Author : Alexandra Bogdanova
//
//********************************************************************

#ifndef SCALING_HEADER
#define SCALING_HEADER

#define LOG_FILE_NAME "text_files/debug.log"
#define LIST_FILE_NAME "text_files/list.log"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include <string>
#include <math.h>
#include <cmath>
#include <stdlib.h>
#include <vector>

using namespace std;

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

struct  listStruct {
    int amount;

    struct line {
        int scale_up;
        int scale_down;
        string file_name;
    };

    std::vector<line> pic;

    line& operator[](int i) {
        return pic[i];
    }

};

struct pictureStruct {
    int width;
    int high;

    struct pixel {
        uint8_t blue;
        uint8_t green;
        uint8_t red;
        uint8_t a;       
    };

    std::vector<pixel> image;

    struct scanline {
        int width;
        pixel* p;

        pixel& operator[](int i) {
            return p[i];
        }
    };

    scanline operator[](int i) {
        scanline w;
        w.width = width;
        w.p = &image[i*width];
        return w;
    }
};

void writePicture(FILE*, pictureStruct);
pictureStruct readPicture (string, pictureStruct);
listStruct read_list();
pictureStruct double_scaling (pictureStruct , int, int, FILE*);
pictureStruct bilining_interpolation (pictureStruct, int, int, FILE*);
pictureStruct decrease (pictureStruct, int);
void compare(uint8_t*, uint8_t*, uint8_t*, int);
void write_log_file (string);

#endif