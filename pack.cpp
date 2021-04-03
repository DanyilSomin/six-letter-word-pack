#include "pack.h"

#include <stdexcept>

constexpr const uint16_t gWordLen = 6;
constexpr const uint16_t gLetterBitSize = 5;

// not case sensitive
uint16_t getLetterOffset(char ch)
{
    if (ch >= 'a' && ch <= 'z')
    {
        return ch - 'a';
    } 
    
    if (ch >= 'A' && ch <= 'Z')
    {
        return ch - 'A';
    }
    
    throw std::invalid_argument{ 
        "Invalid character passed into getLetterOffset(). "
        "Latin letter expected." };
}

char restoreLetterByOffset(uint16_t offset)
{
    if (offset > 'z' - 'a')
    {
        throw std::invalid_argument{ 
            "To large offset passed to restoreLetterByOffset()." };
    }

    return 'a' + offset;
}

uint32_t packWord(const std::string& word)
{
    if (word.size() != gWordLen)
    {
        throw std::invalid_argument{ 
            "String of invalid length passed to packWord()." };
    }
    
    uint32_t packedWord = 0;

    for (auto ch = rbegin(word); ch < rend(word); ++ch)
    {
        packedWord <<= gLetterBitSize; // no effect on the first iteration
        packedWord += getLetterOffset(*ch);
    }

    return packedWord;
}

const std::string unpackWord(uint32_t packedWord)
{
    char unpackedWord[gWordLen];
    uint32_t lowerLetterMask = 31; // 5 least significant bits

    for (size_t i = 0; i < gWordLen; ++i)
    {
        unpackedWord[i] = restoreLetterByOffset(packedWord & lowerLetterMask);

        packedWord >>= gLetterBitSize;
    }

    return std::string{ unpackedWord, gWordLen };
}