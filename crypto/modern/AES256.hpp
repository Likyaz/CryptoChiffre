#ifndef CRYPTOCHIFFRE_AES256_H
#define CRYPTOCHIFFRE_AES256_H


#include "AdvancedEncryptionStandard.h"

class AES256 : public AdvancedEncryptionStandard{
public:
    AES256() : AdvancedEncryptionStandard(32, 13) {}
};


#endif //CRYPTOCHIFFRE_AES256_H
