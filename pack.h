#ifndef PACK_H
#define PACK_H

#include <cstdint>
#include <string>

uint32_t packWord(const std::string& word);
const std::string unpackWord(uint32_t packedWord);

#endif