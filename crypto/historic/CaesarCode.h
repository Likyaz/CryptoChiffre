//
// Created by louis on 22/12/2018.
//

#ifndef CRYPTOCHIFFRE_CAESARCODE_H
#define CRYPTOCHIFFRE_CAESARCODE_H


#include "../Crypto.h"

class CaesarCode : public Crypto {
public:
    CaesarCode();
    virtual ~CaesarCode() = default;

    void setClef(int clef);
    bool crypt() override;
    bool decrypt() override;

private :
    int _clef;
};


#endif //CRYPTOCHIFFRE_CAESARCODE_H
