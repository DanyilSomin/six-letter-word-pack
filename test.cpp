#include <stdexcept>

#include "pack.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(WordPack, InvalidStringLength)
{   
    EXPECT_THROW(
    {
        try
        {
            unpackWord(packWord("short"));
        }
        catch(const std::invalid_argument& e)
        {
            EXPECT_STREQ( "String of invalid length passed to packWord().", e.what() );
            throw;
        }
    }, std::invalid_argument);

    EXPECT_THROW(
    {
        try
        {
            unpackWord(packWord("verylong"));
        }
        catch(const std::invalid_argument& e)
        {
            EXPECT_STREQ( "String of invalid length passed to packWord().", e.what() );
            throw;
        }
    }, std::invalid_argument);
}

TEST(WordPack, InvalidCharacter)
{   
    EXPECT_THROW(
    {
        try
        {
            unpackWord(packWord("aaaaa1"));
        }
        catch(const std::invalid_argument& e)
        {
            EXPECT_STREQ( "Invalid character passed into getLetterShift(). "
                          "Latin letter expected.", e.what() );
            throw;
        }
    }, std::invalid_argument);

    EXPECT_THROW(
    {
        try
        {
            unpackWord(packWord("2aaaaa"));
        }
        catch(const std::invalid_argument& e)
        {
            EXPECT_STREQ( "Invalid character passed into getLetterShift(). "
                          "Latin letter expected.", e.what() );
            throw;
        }
    }, std::invalid_argument);

    EXPECT_THROW(
    {
        try
        {
            unpackWord(packWord("2-==-7"));
        }
        catch(const std::invalid_argument& e)
        {
            EXPECT_STREQ( "Invalid character passed into getLetterShift(). "
                          "Latin letter expected.", e.what() );
            throw;
        }
    }, std::invalid_argument);
}

TEST(WordPack, UpperCaseLettersBecameLowerCase)
{   
    EXPECT_EQ( unpackWord(packWord("wWordd")), "wwordd" );
    EXPECT_EQ( unpackWord(packWord("wwORdd")), "wwordd" );
    EXPECT_EQ( unpackWord(packWord("Wwordd")), "wwordd" );
    EXPECT_EQ( unpackWord(packWord("wwordD")), "wwordd" );
    EXPECT_EQ( unpackWord(packWord("WWORDD")), "wwordd" );
}

TEST(WordPack, RegularWork)
{   
    EXPECT_EQ( unpackWord(packWord("aaaaaa")), "aaaaaa" );
    EXPECT_EQ( unpackWord(packWord("zzzzzz")), "zzzzzz" );
    EXPECT_EQ( unpackWord(packWord("abcdef")), "abcdef" );
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}