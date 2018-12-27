#include "AdvancedEncryptionStandard.h"

AdvancedEncryptionStandard::AdvancedEncryptionStandard(int keyLength, int numberOfRounds):
        _keyLength(keyLength), _numberOfRounds(numberOfRounds)
{

}

AdvancedEncryptionStandard::~AdvancedEncryptionStandard()
{
    delete _key;
}


void AdvancedEncryptionStandard::setClef(unsigned char* key)
{
    delete _key;

    int keyInIntLength = _keyLength >> 2;
    uint32_t* keyTemp = (uint32_t*) key;
    uint32_t* resKey = new uint32_t[(_numberOfRounds + 2) * 4];

    int it = 1;
    for(int i(0); i < (_numberOfRounds + 2) * 4; i++)
    {
        resKey[i] = 0;
        if(i < keyInIntLength) {
            resKey[i] = keyTemp[i];
        }
        else if(i % keyInIntLength == 0) {
            resKey[i] = (_sBox[(uint8_t) resKey[i - 1] & 0xFF] | (_sBox[(uint8_t) (resKey[i - 1] >> 8) & 0xFF] << 8) | (_sBox[(uint8_t) (resKey[i - 1] >> 16) & 0xFF] << 16) | (_sBox[(uint8_t) (resKey[i - 1] >> 24) & 0xFF] << 24));
            resKey[i] = resKey[i] << 24 | resKey[i] >> 8;
            resKey[i] ^= resKey[i - keyInIntLength] ^ rcon(it++);
        }
        else if(i % keyInIntLength == 4 && keyInIntLength > 6) {
            resKey[i] = resKey[i - keyInIntLength] ^ (_sBox[(uint8_t) resKey[i - 1] & 0xFF] | (_sBox[(uint8_t) (resKey[i - 1] >> 8) & 0xFF] << 8) | (_sBox[(uint8_t) (resKey[i - 1] >> 16) & 0xFF] << 16) | (_sBox[(uint8_t) (resKey[i - 1] >> 24) & 0xFF] << 24));
        }
        else {
            resKey[i] = resKey[i - keyInIntLength] ^ resKey[i - 1];
        }
    }
    _key = (uint8_t*) resKey;
}

bool AdvancedEncryptionStandard::crypt()
{
    int nbBlock = (int) _in->getSize() / 16;
    if(_in->getSize() != nbBlock)
        nbBlock++;
    _out->setData(new char[nbBlock * 16], (uint64_t) nbBlock * 16);

    for(int i(0); i < nbBlock; i++)
    {
        for(int y(0); y < 4; y++)
            for(int x(0); x < 4; x++)
            {
                if((i * 16) + (y * 4) + x >= _in->getSize())
                {
                    _data[y][x] = 0;
                } else
                {
                    _data[y][x] = (uint8_t) _in->getData()[(i * 16) + (y * 4) + x];
                }
            }

        addRoundKey(0);
        for(int it(1); it <= _numberOfRounds;it++)
        {
            subBytes();
            shiftRows();
            mixColumns();
            addRoundKey(it);
        }
        subBytes();
        shiftRows();
        addRoundKey(_numberOfRounds + 1);

        for(int y(0); y < 4; y++)
            for(int x(0); x < 4; x++)
                _out->getData()[(i * 16) + (y * 4) + x] = (char) _data[y][x];
    }
    return true;
}

bool AdvancedEncryptionStandard::decrypt()
{
    int nbBlock = (int) _in->getSize() / 16;
    _out->setData(new char[nbBlock * 16], (uint64_t) nbBlock * 16);
    for(int i(0); i < nbBlock; i++)
    {
        for(int y(0); y < 4; y++)
            for(int x(0); x < 4; x++)
                _data[y][x] = (uint8_t) _in->getData()[(i * 16) + (y * 4) + x];

        addRoundKey(_numberOfRounds + 1);
        invShiftRows();
        invSubBytes();
        for(int it(_numberOfRounds); it >= 1;it--)
        {
            addRoundKey(it);
            invMixColumns();
            invShiftRows();
            invSubBytes();
        }

        addRoundKey(0);


        for(int y(0); y < 4; y++)
            for(int x(0); x < 4; x++)
                _out->getData()[(i * 16) + (y * 4) + x] = (char) _data[y][x];
    }
    return true;
}


void AdvancedEncryptionStandard::subBytes()
{
    for(int i(0); i < 4; i++)
        for(int j(0); j < 4; j++)
            _data[i][j] = AdvancedEncryptionStandard::_sBox[_data[i][j]];
}

void AdvancedEncryptionStandard::shiftRows()
{
    unsigned char temp = 0;

    temp = _data[1][0];
    _data[1][0] = _data[1][1];
    _data[1][1] = _data[1][2];
    _data[1][2] = _data[1][3];
    _data[1][3] = temp;

    temp = _data[2][0];
    _data[2][0] = _data[2][2];
    _data[2][2] = temp;
    temp = _data[2][1];
    _data[2][1] = _data[2][3];
    _data[2][3] = temp;

    temp = _data[3][3];
    _data[3][3] = _data[3][2];
    _data[3][2] = _data[3][1];
    _data[3][1] = _data[3][0];
    _data[3][0] = temp;
};

void AdvancedEncryptionStandard::mixColumns()
{
    uint8_t temp[4] = {0};
    for(int i(0); i < 4; i++)
    {
        temp[0] = (uint8_t) (gMul(2, _data[i][0]) ^ gMul(3, _data[i][1]) ^ _data[i][2] ^ _data[i][3]);
        temp[1] = (uint8_t) (_data[i][0] ^ gMul(2, _data[i][1]) ^ gMul(3, _data[i][2]) ^ _data[i][3]);
        temp[2] = (uint8_t) (_data[i][0] ^ _data[i][1] ^ gMul(2, _data[i][2]) ^ gMul(3, _data[i][3]));
        temp[3] = (uint8_t) (gMul(3, _data[i][0]) ^ _data[i][1] ^ _data[i][2] ^ gMul(2, _data[i][3]));

        _data[i][0] = temp[0];
        _data[i][1] = temp[1];
        _data[i][2] = temp[2];
        _data[i][3] = temp[3];
    }

}

void AdvancedEncryptionStandard::addRoundKey(int turn)
{
    for(int i(0); i < 4; i++)
        for(int j(0); j < 4; j++)
            _data[i][j] ^= _key[(turn * 16) + (i * 4) + j];
}


void AdvancedEncryptionStandard::invSubBytes()
{
    for(int i(0); i < 4; i++)
        for(int j(0); j < 4; j++)
            _data[i][j] = AdvancedEncryptionStandard::_invSBox[_data[i][j]];
}

void AdvancedEncryptionStandard::invShiftRows()
{
    unsigned char temp = 0;

    temp = _data[1][3];
    _data[1][3] = _data[1][2];
    _data[1][2] = _data[1][1];
    _data[1][1] = _data[1][0];
    _data[1][0] = temp;

    temp = _data[2][0];
    _data[2][0] = _data[2][2];
    _data[2][2] = temp;
    temp = _data[2][1];
    _data[2][1] = _data[2][3];
    _data[2][3] = temp;

    temp = _data[3][0];
    _data[3][0] = _data[3][1];
    _data[3][1] = _data[3][2];
    _data[3][2] = _data[3][3];
    _data[3][3] = temp;
}

void AdvancedEncryptionStandard::invMixColumns()
{
    uint8_t temp[4] = {0};
    for(int i(0); i < 4; i++)
    {
        temp[0] = (uint8_t) (gMul(0x0E, _data[i][0]) ^ gMul(0x0B, _data[i][1]) ^ gMul(0x0D, _data[i][2]) ^ gMul(0x09, _data[i][3]));
        temp[1] = (uint8_t) (gMul(0x09, _data[i][0]) ^ gMul(0x0E, _data[i][1]) ^ gMul(0x0B, _data[i][2]) ^ gMul(0x0D, _data[i][3]));
        temp[2] = (uint8_t) (gMul(0x0D, _data[i][0]) ^ gMul(0x09, _data[i][1]) ^ gMul(0x0E, _data[i][2]) ^ gMul(0x0B, _data[i][3]));
        temp[3] = (uint8_t) (gMul(0x0B, _data[i][0]) ^ gMul(0x0D, _data[i][1]) ^ gMul(0x09, _data[i][2]) ^ gMul(0x0E, _data[i][3]));

        _data[i][0] = temp[0];
        _data[i][1] = temp[1];
        _data[i][2] = temp[2];
        _data[i][3] = temp[3];
    }
}

uint8_t AdvancedEncryptionStandard::gMul(uint8_t a, uint8_t b)
{
    uint8_t p = 0;

    for (int i = 0; i < 8; i++) {
        if ((b & 1) != 0) {
            p ^= a;
        }

        bool hi_bit_set = (a & 0x80) != 0;
        a <<= 1;
        if (hi_bit_set) {
            a ^= 0x1B;
        }
        b >>= 1;
    }

    return p;
}

uint8_t AdvancedEncryptionStandard::rcon(uint8_t in) {
    unsigned char c=1;
    if(in == 0)
        return 0;
    while(in != 1) {
        unsigned char b;
        b = c & 0x80;
        c <<= 1;
        if(b == 0x80) {
            c ^= 0x1b;
        }
        in--;
    }
    return c;
}