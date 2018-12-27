#ifndef CRYPTOCHIFFRE_AES192_H
#define CRYPTOCHIFFRE_AES192_H


#include "AdvancedEncryptionStandard.h"

class AES192 : public AdvancedEncryptionStandard{
public:
    AES192() : AdvancedEncryptionStandard(24, 11) {}
};



#endif //CRYPTOCHIFFRE_AES192_H
