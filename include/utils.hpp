#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <algorithm>

std::string removeSpaces(std::string str);

void xor_cypher(const std::string &message, const std::string &key,
                std::string &cypher, std::string &hex_cypher);

void xor_decipher(const std::string &hex_cypher, const std::string &key,
                  std::string &message);

void poly_cypher(const std::string &text, const std::string &key, std::string &cyph_txt);

void poly_decipher(const std::string &cyph_txt, const std::string &key, std::string &text);

#endif