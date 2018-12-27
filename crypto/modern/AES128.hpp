//
// Created by louis on 27/12/2018.
//

#ifndef CRYPTOCHIFFRE_AES128_H
#define CRYPTOCHIFFRE_AES128_H


#include "AdvancedEncryptionStandard.h"

class AES128 : public AdvancedEncryptionStandard{
public:
    AES128() : AdvancedEncryptionStandard(16, 9) {}
};



#endif //CRYPTOCHIFFRE_AES128_H
