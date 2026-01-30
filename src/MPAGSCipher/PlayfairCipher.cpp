#include "PlayfairCipher.hpp"

#include <algorithm>
#include <iostream>
#include <map>
#include <string>

/**
 * \file PlayfairCipher.cpp
 * \brief Contains the implementation of the PlayfairCipher class
 */

PlayfairCipher::PlayfairCipher(const std::string& key)
{
    this->setKey(key);
}

void PlayfairCipher::setKey(const std::string& key)
{
    // Store the original key
    key_ = key;

    // Append the alphabet to the key
    key_ += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Make sure the key is upper case
    std::transform(std::begin(key_), std::end(key_), std::begin(key_),
                   ::toupper);

    // Remove non-alphabet characters
    // - lambda notIsAlpha
    auto notIsAlpha = [](const char c) { return !std::isalpha(c); };
    // - use std::remove_if and string::erase
    key_.erase(std::remove_if(std::begin(key_), std::end(key_), notIsAlpha),
               std::end(key_));

    // Change J -> I
    std::transform(std::begin(key_), std::end(key_), std::begin(key_),
                   [](const char c) { return (c == 'J') ? 'I' : c; });

    // Remove duplicated letters
    std::string seenBefore{};
    auto isDuplicate = [&seenBefore](const char c) {
        if (seenBefore.find(c) != std::string::npos) {    // if not no matches
            return true;
        } else {
            seenBefore += c;
            return false;
        }
    };
    key_.erase(std::remove_if(std::begin(key_), std::end(key_), isDuplicate),
               std::end(key_));

    // Store the coordinates of each letter
    using CharToCoordsMap = std::map<char, std::pair<int, int>>;
    CharToCoordsMap charToCoords{};
    for (const char c : key_) {
        const int index = key_.find(c);
        const int row = index / 5;    // integer division is floor division
        const int col = index % 5;
        charToCoords[c] = std::make_pair(row, col);
    };
    // invert the map by pulling pairs directly
    using CoordsToCharMap = std::map<std::pair<int, int>, char>;
    CoordsToCharMap coordsToChar{};
    for (const auto& pair : charToCoords) {
        coordsToChar[pair.second] = pair.first;
    }
}

std::string PlayfairCipher::applyCipher(const std::string& inputText,
                                        const CipherMode /*cipherMode*/) const
{
    // Create the output string, initially a copy of the input text
    std::string outputText{inputText};

    // Change J -> I

    // Find repeated characters and add an X (or a Q for repeated X's)

    // If the size of the input is odd, add a trailing Z

    // Loop over the input bigrams

    // - Find the coordinates in the grid for each bigram

    // - Apply the rules to these coords to get new coords

    // - Find the letters associated with the new coords

    // - Make the replacements

    // Return the output text
    return outputText;
}
