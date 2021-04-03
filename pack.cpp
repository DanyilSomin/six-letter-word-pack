#include "pack.h"

#include <stdexcept>

constexpr const uint16_t gWordLen = 6;
constexpr const uint16_t gLetterShiftBitSize = 5;

// not case sensitive
uint16_t getLetterShift(char ch)
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
        "Invalid character passed into getLetterShift(). "
        "Latin letter expected." };
}

char restoreLetterByShift(uint16_t shift)
{
    if (shift > 'z' - 'a')
    {
        throw std::invalid_argument{ 
            "To large shift passed to restoreLetterByShift()." };
    }

    return 'a' + shift;
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
        packedWord <<= gLetterShiftBitSize; // no effect on the first iteration
        packedWord += getLetterShift(*ch);
    }

    return packedWord;
}

const std::string unpackWord(uint32_t packedWord)
{
    char unpackedWord[gWordLen];
    uint32_t lowerLetterMask = 31; // 5 least significant bits

    for (size_t i = 0; i < gWordLen; ++i)
    {
        unpackedWord[i] = restoreLetterByShift(packedWord & lowerLetterMask);

        packedWord >>= gLetterShiftBitSize;
    }

    return std::string{ unpackedWord, gWordLen };
}