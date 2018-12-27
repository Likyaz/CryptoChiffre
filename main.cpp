#include <iostream>
#include "io/File.h"
#include "crypto/historic/CaesarCode.h"
#include "crypto/modern/AdvancedEncryptionStandard.h"



int main() {
    File in;
    File out;;
    File result;

    in.setPath("../test.txt");
    out.setPath("../testChiffrerWhithAES.cry");
    result.setPath("../testDechiffrerWhithAES.txt");

    in.loadData();

    AdvancedEncryptionStandard code(16, 9);
    uint8_t key[32] = {00};
    code.setClef(key);
    uint8_t* pkey = code.getKey();


    code.setFileIn(&in);
    code.setFileOut(&out);

    code.crypt();

    out.saveData();

    code.setFileIn(&out);
    code.setFileOut(&result);

    code.decrypt();

    result.saveData();


    return 0;
}