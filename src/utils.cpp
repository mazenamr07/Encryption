#include "../include/utils.hpp"

std::string removeSpaces(std::string str)
{
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

void xor_cypher(const std::string &message, const std::string &key,
                std::string &cypher, std::string &hex_cypher)
{
    cypher = message;
    for (size_t i = 0; i < message.size(); i++)
    {
        cypher[i] = message[i] ^ key[i % key.size()];
    }

    hex_cypher = "";
    for (size_t i = 0; i < cypher.size(); i++)
    {
        char hex[3];
        sprintf(hex, "%02X", cypher[i]);
        hex_cypher += hex;
    }
}

void xor_decipher(const std::string &hex_cypher, const std::string &key,
                  std::string &message)
{
    std::string cypher;
    for (size_t i = 0; i < hex_cypher.size(); i += 2)
    {
        char byte = (char)strtol(hex_cypher.substr(i, 2).c_str(), NULL, 16);
        cypher += byte;
    }

    message = cypher;
    for (size_t i = 0; i < cypher.size(); i++)
    {
        message[i] = cypher[i] ^ key[i % key.size()];
    }
}

void poly_cypher(const std::string &text, const std::string &key, std::string &cyph_txt)
{
        // Making the alphabet table with key
    char table[5][5];
    int k = 97; // 'a' in ASCII
    for (char i : key)
    {
        int row = i - 49;
        for (char j : key)
        {
            int col = j - 49;
            if (k == 106)
            {
                k = 107;
            }
            table[row][col] = static_cast<char>(k);
            k++;
        }
    }

    // Cyphering text using table
    std::string cypher_txt;
    for (char i : text)
    {
        if (!isalpha(i))
        { // Skipping non-alphabetical characters
            cypher_txt += i;
            continue;
        }
        i |= 32; // forcing capitalized characters into lowercase

        if (i == 'j')
        { // 'j' to 'i' for cyphering
            i = 'i';
        }
        for (int j = 0; j < 5; j++)
        {
            for (int n = 0; n < 5; n++)
            {
                if (table[j][n] == i)
                {
                    cypher_txt += std::to_string(j + 1);
                    cypher_txt += std::to_string(n + 1);
                }
            }
        }
    }
    cyph_txt = cypher_txt;
}

void poly_decipher(const std::string &cyph_txt, const std::string &key, std::string &text)
{
    // Making the alphabet table with key
    char table[5][5];
    int k = 97; // 'a' in ASCII
    for (char i : key)
    {
        int row = i - 49;
        for (char j : key)
        {
            int col = j - 49;
            if (k == 106)
            {
                k = 107;
            }
            table[row][col] = static_cast<char>(k);
            k++;
        }
    }

    // Deciphering text using table
    std::string b_txt;
    int counter = 0, i_row, i_col;
    for (char i : cyph_txt)
    {
        if (!isdigit(i))
        { // Skipping non-digit characters
            b_txt += i;
            continue;
        }

        if (counter % 2 == 0)
        { // Taking the first digit as row number
            i_row = static_cast<char>(i) - 49;
        }
        else
        { // Taking the second digit as column number
            i_col = static_cast<char>(i) - 49;
        }
        counter++;
        if (counter % 2 == 0)
        { // Adding the character after every two digits
            b_txt += table[i_row][i_col];
        }
    }
    text = b_txt;
}