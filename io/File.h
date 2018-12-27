//
// Created by louis on 21/12/2018.
//

#ifndef CRYPTOCHIFFRE_FILE_H
#define CRYPTOCHIFFRE_FILE_H

#include <fstream>
#include <string>
#include <iostream>
#include <inttypes.h>

class File {
public:
    File();
    ~File();

    void setPath(std::string path);

    bool loadData();
    bool saveData();
    bool unloadData();

    std::string getPath();
    char* getData();
    char* setData(char* data, uint64_t size);
    uint64_t getSize();
private:
    std::string _path;
    uint64_t _size;
    char* _data;
};


#endif //CRYPTOCHIFFRE_FILE_H
