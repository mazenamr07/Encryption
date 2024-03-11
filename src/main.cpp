#include <iostream>
#include <vector>
#include <cmath>
#include <cctype>
#include "../include/utils.hpp"

int main()
{
    // menu start and choice
    std::cout << "Ahlan ya user ya habibi.\nWhat would you like to do today?\n";

    while (true)
    {
        std::string choice_1, choice_2, choice_3;

        std::cout << "1- Cipher a message\n"
                     "2- Decipher a message\n"
                     "3- End\n"
                  << ">>";

        getline(std::cin, choice_1);
        // checking if input is valid
        while (choice_1 != "1" and choice_1 != "2" and choice_1 != "3")
        {
            std::cout << "Please select a valid option:\n"
                      << ">>";
            getline(std::cin, choice_1);
        }

        if (choice_1 == "3")
        {
            std::cout << "Bye bye!";
            return 0;
        }

        std::cout << "\nWhich Cipher would you like to choose?" << std::endl;
        std::cout << "1- First cypher\n"
                     "2- Second cypher\n"
                     "3- XOR Cypher\n"
                     "4- Return\n"
                  << ">>";

        getline(std::cin, choice_2);
        // checking if input is valid
        while (choice_2 != "1" and choice_2 != "2" and choice_2 != "3" and choice_2 != "4")
        {
            std::cout << "Please select a valid option:\n"
                      << ">>";
            getline(std::cin, choice_2);
        }

        if (choice_2 == "4")
        {
            std::cout << "\nChoose again:" << std::endl;
            continue;
        }

        if (choice_1 == "1")
        { // Encrypting messages
            if (choice_2 == "1")
            { // Enc First cypher
                std::cout << "1 and 1";
            }
            else if (choice_2 == "2")
            { // Enc Second cypher
                std::cout << "1 and 2";
            }
            else
            { // Enc XOR cypher
                std::string message, key, cypher, hex_cypher;
                std::cout << "Enter the message you wish to encrypt:" << std::endl
                          << ">>";
                getline(std::cin, message);

                bool check; // setting a bool for if the input is empty
                for (char i : message)
                {
                    if (!isspace(i))
                    {
                        check = true;
                    }
                    else
                    {
                        check = false;
                    }
                }

                // checking if the input is empty
                while (!check)
                {
                    std::cout << "Message can't be empty, enter again:" << std::endl
                              << ">>";
                    getline(std::cin, message);

                    // adjusting the bool for a recheck
                    for (char i : message)
                    {
                        if (!isspace(i))
                        {
                            check = true;
                        }
                        else
                        {
                            check = false;
                        }
                    }
                }

                std::cout << "Enter your key:" << std::endl
                          << ">>";
                getline(std::cin, key);

                bool check2; // setting a bool for if the input is empty
                for (char i : key)
                {
                    if (!isspace(i))
                    {
                        check2 = true;
                    }
                    else
                    {
                        check2 = false;
                    }
                }

                // checking if the input is empty
                while (!check2)
                {
                    std::cout << "Key can't be empty, enter again:" << std::endl
                              << ">>";
                    getline(std::cin, key);

                    // adjusting the bool for a recheck
                    for (char i : key)
                    {
                        if (!isspace(i))
                        {
                            check2 = true;
                        }
                        else
                        {
                            check2 = false;
                        }
                    }
                }

                xor_cypher(message, key, cypher, hex_cypher);
                std::cout << "Your encrypted message is:" << ' ' << cypher << std::endl;
                std::cout << "Hexadecimal hash for encryption:" << ' ' << hex_cypher << std::endl
                          << std::endl;
                check = check2 = false; // check reset
            }
        }
        if (choice_1 == "2")
        { // Decrypting messages
            if (choice_2 == "1")
            { // Dec First cypher
                std::cout << "2 and 1";
            }
            else if (choice_2 == "2")
            { // Dec Second cypher
                std::cout << "2 and 2";
            }
            else
            { // Dec XOR cypher
                std::string choice_xor;
                // choice between decrypting a message or a hexadecimal hash
                std::cout << "What would you like to decipher:\n"
                             "1- Encrypted message\n"
                             "2- Hexadecimal hash"
                          << std::endl
                          << ">>";

                getline(std::cin, choice_xor);
                // checking if input is valid
                while (choice_xor != "1" and choice_xor != "2")
                {
                    std::cout << "Please select a valid option:\n"
                              << ">>";
                    getline(std::cin, choice_xor);
                }

                if (choice_xor == "1")
                {
                    std::string message, key, cypher, hex_cypher;
                    std::cout << "Enter the message you wish to encrypt:" << std::endl
                              << ">>";
                    getline(std::cin, message);

                    bool check; // setting a bool for if the input is empty
                    for (char i : message)
                    {
                        if (!isspace(i))
                        {
                            check = true;
                        }
                        else
                        {
                            check = false;
                        }
                    }

                    // checking if the input is empty
                    while (!check)
                    {
                        std::cout << "Message can't be empty, enter again:" << std::endl
                                  << ">>";
                        getline(std::cin, message);

                        // adjusting the bool for a recheck
                        for (char i : message)
                        {
                            if (!isspace(i))
                            {
                                check = true;
                            }
                            else
                            {
                                check = false;
                            }
                        }
                    }

                    std::cout << "Enter your key:" << std::endl
                              << ">>";
                    getline(std::cin, key);

                    bool check2; // setting a bool for if the input is empty
                    for (char i : key)
                    {
                        if (!isspace(i))
                        {
                            check2 = true;
                        }
                        else
                        {
                            check2 = false;
                        }
                    }

                    // checking if the input is empty
                    while (!check2)
                    {
                        std::cout << "Key can't be empty, enter again:" << std::endl
                                  << ">>";
                        getline(std::cin, key);

                        // adjusting the bool for a recheck
                        for (char i : key)
                        {
                            if (!isspace(i))
                            {
                                check2 = true;
                            }
                            else
                            {
                                check2 = false;
                            }
                        }
                    }

                    xor_cypher(message, key, cypher, hex_cypher);
                    std::cout << "Your message is:" << ' ' << cypher << std::endl
                              << std::endl;
                    check = check2 = false; // check reset
                }
                else
                {
                    std::vector<char> char_list = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
                                                   'A', 'B', 'C', 'D', 'E', 'F',
                                                   'a', 'b', 'c', 'd', 'e', 'f'};
                    std::string hex_cypher, key, message;
                    std::cout << "Enter the hexadecimal hash you wish to decipher:" << std::endl
                              << ">>";
                    getline(std::cin, hex_cypher);
                    hex_cypher = removeSpaces(hex_cypher);

                    bool check = true; // setting a bool for if the input is invalid
                    for (char i : hex_cypher)
                    {
                        if (find(char_list.begin(), char_list.end(), i) == char_list.end())
                        {
                            check = false;
                            break;
                        }
                    }
                    while (!check or hex_cypher.empty())
                    {
                        if (!check and !hex_cypher.empty())
                        {
                            std::cout << "Hash can't contain special characters,\n"
                                         "and letters must be from [A, B, C, D, E, F], enter again:"
                                      << std::endl
                                      << ">>";
                        }
                        else
                        {
                            std::cout << "Hash can't be empty, enter again:" << std::endl
                                      << ">>";
                        }
                        getline(std::cin, hex_cypher);
                        hex_cypher = removeSpaces(hex_cypher);

                        // adjusting the bool for a recheck
                        for (char i : hex_cypher)
                        {
                            if (find(char_list.begin(), char_list.end(), i) == char_list.end())
                            {
                                check = false;
                                break;
                            }
                            else
                            {
                                check = true;
                            }
                        }
                    }

                    std::cout << "Enter your key:" << std::endl
                              << ">>";
                    getline(std::cin, key);

                    bool check2; // setting a bool for if the input is empty
                    for (char i : key)
                    {
                        if (!isspace(i))
                        {
                            check2 = true;
                        }
                        else
                        {
                            check2 = false;
                        }
                    }

                    // checking if the input is empty
                    while (!check2)
                    {
                        std::cout << "Key can't be empty, enter again:" << std::endl
                                  << ">>";
                        getline(std::cin, key);

                        // adjusting the bool for a recheck
                        for (char i : key)
                        {
                            if (!isspace(i))
                            {
                                check2 = true;
                            }
                            else
                            {
                                check2 = false;
                            }
                        }
                    }

                    xor_decipher(hex_cypher, key, message);
                    std::cout << "Your message is:" << ' ' << message << std::endl
                              << std::endl;
                }
            }
        }

        // choice for reusing the program or exiting
        std::cout << "Would you like to do something else?" << std::endl;
        std::cout << "1- Yes, use again\n"
                     "2- No, exit\n"
                  << ">>";
        getline(std::cin, choice_3);
        // checking if input is valid
        while (choice_3 != "1" and choice_3 != "2")
        {
            std::cout << "Please select a valid option:\n"
                      << ">>";
            getline(std::cin, choice_3);
        }

        if (choice_3 == "2")
        {
            std::cout << "Bye bye!";
            return 0;
        }
    }
}