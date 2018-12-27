#include "File.h"

File::File() :
     _path(),  _size(0), _data(nullptr)
{}

File::~File()
{
    delete _data;
}

void File::setPath(std::string path)
{
    _path = path;
}

bool File::loadData()
{
    std::ifstream file(_path.c_str(), std::ios::binary);

    if(file)
    {

        file.seekg (0, file.end);
        _size = (uint64_t) file.tellg();
        file.seekg (0, file.beg);

        _data = new char[_size];
        file.read(_data, _size);

        file.close();
        return true;
    }
    else
    {
        std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
        return false;
    }
}

bool File::saveData()
{
    std::ofstream file(_path.c_str(), std::ios::binary);

    if(file)
    {
        file.write(_data, _size);

        file.close();
        return true;
    }
    else
    {
        std::cout << "Impossible d'ouvrir le fichier !" << std::endl;
        return false;
    }
}

bool File::unloadData()
{
    delete _data;
    _data = nullptr;
    _size = 0;
}

char* File::setData(char* data, uint64_t size)
{
    delete _data;
    _data = data;
    _size = size;
}

std::string File::getPath()
{
    return _path;
}

char* File::getData()
{
    return _data;
}

uint64_t File::getSize()
{
    return _size;
}