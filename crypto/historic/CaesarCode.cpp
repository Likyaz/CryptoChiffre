//
// Created by louis on 22/12/2018.
//

#include "CaesarCode.h"


CaesarCode::CaesarCode() :
        Crypto(), _clef(0)
{}

void CaesarCode::setClef(int clef)
{
    _clef = clef % 128;
}

bool CaesarCode::crypt()
{
    _out->setData(new char[_in->getSize()], _in->getSize());
    int t;
    for(int i(0); i < _in->getSize(); i++)
    {
        t = _in->getData()[i] + _clef;
        if(t > 128)
            t -= 255;
        else if(t < -128)
            t += 255;
        _out->getData()[i] = (char) t;
    }
    return true;
}

bool CaesarCode::decrypt()
{
    _out->setData(new char[_in->getSize()], _in->getSize());
    int t;
    for(int i(0); i < _in->getSize(); i++)
    {
        t = _in->getData()[i] - _clef;
        if(t > 128)
            t -= 255;
        else if(t < -128)
            t += 255;
        _out->getData()[i] = (char) t;
    }
    return true;
}
