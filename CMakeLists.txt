cmake_minimum_required(VERSION 3.12)
project(CryptoChiffre)

set(CMAKE_CXX_STANDARD 17)

add_executable(CryptoChiffre main.cpp io/File.cpp io/File.h crypto/Crypto.cpp crypto/Crypto.h crypto/historic/CaesarCode.cpp crypto/historic/CaesarCode.h crypto/modern/AdvancedEncryptionStandard.cpp crypto/modern/AdvancedEncryptionStandard.h)