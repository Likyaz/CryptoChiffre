//
// Created by louis on 22/12/2018.
//

#include "Crypto.h"

Crypto::Crypto() :
        _in(nullptr), _out(nullptr)
{}

Crypto::~Crypto()
{}

bool Crypto::setFileIn(File* file)
{
    _in = file;
}

bool Crypto::setFileOut(File* file)
{
    _out = file;
}