#include <iostream>
#include "io/File.h"
#include "crypto/historic/CaesarCode.h"
#include "crypto/modern/AES128.hpp"
#include "crypto/modern/AES192.hpp"
#include "crypto/modern/AES256.hpp"


int main() {
    File in;
    File out;;
    File result;

    in.setPath("../test.txt");
    out.setPath("../testChiffrerWhithAES.cry");
    result.setPath("../testDechiffrerWhithAES.txt");

    in.loadData();

    AES128 code;
    uint8_t key[32] = {00};
    code.setClef(key);


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