//
// Created by louis on 22/12/2018.
//

#ifndef CRYPTOCHIFFRE_CRYPTO_H
#define CRYPTOCHIFFRE_CRYPTO_H

#include "../io/File.h"

class Crypto {
public:
    Crypto();
    virtual ~Crypto();

    virtual bool crypt() = 0;
    virtual bool decrypt() = 0;

    bool setFileIn(File* file);
    bool setFileOut(File* file);



protected:
    File* _in;
    File* _out;
};


#endif //CRYPTOCHIFFRE_CRYPTO_H
