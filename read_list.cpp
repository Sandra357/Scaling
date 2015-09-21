//********************************************************************
//
// File : read_list.cpp
// Description : Function for read file with list of pictures and their scales
// Created : 31 april 2015
// Author : Alexandra Bogdanova
//
//********************************************************************

#ifndef READ_LIST_CPP
#define READ_LIST_CPP

#include "scaling.h"

listStruct read_list () {
  
    // Open list of pictures 
    std::ifstream ifs(LIST_FILE_NAME);
    if(!ifs) {
        write_log_file("*ERROR main : Cannot open listPictures file\n");
        ifs.close();
    }

    // Read list of pictures names and write to string array 
    string str;
    vector <string> arr;
    while(!ifs.eof()) {
        getline(ifs, str);
        arr.push_back(str);
    }
    ifs.close();

    char* ch = NULL;
    string words [3];
    int k = 0;
    int j = 0;

    // Copy strings to structure
    listStruct list;
    char* for_tok;
    vector <string>::iterator i;
    int amount = 0;
    for (i = arr.begin(); i != arr.end(); i++)
        amount++;
    list.pic.resize(amount);
    for (i = arr.begin(); i != arr.end(); i++) {

        // Memory allocate
        for_tok = new char[(*i).length()+1];
        strcpy(for_tok, (*i).c_str());

        // Separation string to words
        ch = strtok(for_tok, " ");
        while (ch != NULL) {
            // Save words to words array
            words[k] = ch;
            k++;
            ch = strtok(NULL, " ");
        }

        list[j].scale_up = atoi(words[2].c_str());
        list[j].scale_down = atoi(words[1].c_str());
        list[j].file_name = words[0];
        j++;

        // Delete memory
    	ch = NULL;
    	k = 0;
    	delete[] for_tok;
    }

    list.amount = j;

    return list;
}

#endif
