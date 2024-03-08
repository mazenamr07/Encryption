// FCAI – Structured Programming – 2024 - Assignment 2
// Program Name: CS112_A2_T2_SectionNum_20230308_***_***.cpp
// Program Description: This is a tool to cypher and decipher messages using:
//                      1- *** Cypher, 2- *** Cypher, 3- XOR Cypher
// Last Modification Date: 10/3/2024
// Author 1: Mazen Amr Mohammed Morsy - ID: 20230308 - Section: 28
// Author 2: *** *** *** - ID: *** - Section: 28
// Author 3: *** *** *** - ID: *** - Section: 28
// Teaching Assistant: xxxxx xxxxx
// Who did what:
//      Mazen Amr: Worked on the menu and algorithm and code for XOR Cypher
//      *** ***:
//      *** ***:

#include <iostream>
#include <bitset>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cctype>

using namespace std;

// Function for erasing spaces from a string
string removeSpaces(string str) {
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

// Function for encrypting using the XOR Cypher
void xor_cypher(const string& message, const string& key, string& cypher, string& hex_cypher) {
    vector<bitset<8>> bin_list;
    vector<bitset<8>> key_list;

    // turn key into a set of 8 bits
    for (char i : key) {
        bitset<8> bin_key(i);
        key_list.push_back(bin_key);
    }

    // turn each character of the message into a set of 8 bits
    int kcnt = 0;
    for (char i : message) {
        bitset<8> bin_char(i);
        bitset bin_cypher = bin_char ^ key_list[kcnt];
        kcnt++;
        if (kcnt == key.size()) {
            kcnt = 0;
        }

        // store each binary set in a vector
        bin_list.push_back(bin_cypher);
    }
    // use each binary set for encryption
    for (bitset i : bin_list) {
        unsigned long cypher_char = i.to_ulong(); // turn binary set to ASCII then convert it to character
        cypher += static_cast<char>(cypher_char); // add each character to a string for later display
        string temp_str = i.to_string(); // turn binary set to string of numbers

        // slicing the string into two halves
        string front_temp_str;
        for (int j = 0; j < 4; j++) {
            front_temp_str.push_back(temp_str[j]);
        }
        string back_temp_str;
        for (int j = 0; j < 4; j++) {
            back_temp_str.push_back(temp_str[j + 4]);
        }

        // converting each half to its hexadecimal representation
        int k = 0;
        double sum_1 = 0, sum_2 = 0;
        for (int j = 3; j >= 0; j--, k++) {
            sum_1 += pow(2, j) * (front_temp_str[k] - 48);
            sum_2 += pow(2, j) * (back_temp_str[k] - 48);
        }
        // first half letter check
        if (sum_1 == 10) {
            hex_cypher += 'A';
        } else if (sum_1 == 11) {
            hex_cypher += 'B';
        } else if (sum_1 == 12) {
            hex_cypher += 'C';
        } else if (sum_1 == 13) {
            hex_cypher += 'D';
        } else if (sum_1 == 14) {
            hex_cypher += 'E';
        } else if (sum_1 == 15) {
            hex_cypher += 'F';
        } else {
            hex_cypher += static_cast<char>(sum_1 + 48);
        }
        // second half letter check
        if (sum_2 == 10) {
            hex_cypher += 'A';
        } else if (sum_2 == 11) {
            hex_cypher += 'B';
        } else if (sum_2 == 12) {
            hex_cypher += 'C';
        } else if (sum_2 == 13) {
            hex_cypher += 'D';
        } else if (sum_2 == 14) {
            hex_cypher += 'E';
        } else if (sum_2 == 15) {
            hex_cypher += 'F';
        } else {
            hex_cypher += static_cast<char>(sum_2 + 48);
        } hex_cypher += ' ';
    }

}

// Function for decrypting Hexadecimal Hash using the XOR Cypher
void xor_decipher(const string& hex_cypher, const string& key, string& message) {
    vector<string> bin_list;
    vector<bitset<8>> key_list;

    // turn key into a set of 8 bits
    for (char i : key) {
        bitset<8> bin_key(i);
        key_list.push_back(bin_key);
    }

    // Taking each Hexadecimal pair and converting them to a string of 8 characters
    string sp_hex_cypher = removeSpaces(hex_cypher); // removing spaces from the hash

    int hcnt = 0;
    string temp_str;
    for (char i : sp_hex_cypher) {
        if (i == '1') {
            temp_str.append("0001");
        } else if (i == '2') {
            temp_str.append("0010");
        } else if (i == '3') {
            temp_str.append("0011");
        } else if (i == '4') {
            temp_str.append("0100");
        } else if (i == '5') {
            temp_str.append("0101");
        } else if (i == '6') {
            temp_str.append("0110");
        } else if (i == '7') {
            temp_str.append("0111");
        } else if (i == '8') {
            temp_str.append("1000");
        } else if (i == '9') {
            temp_str.append("1001");
        } else if (i == 'A' or i == 'a') {
            temp_str.append("1010");
        } else if (i == 'B' or i == 'b') {
            temp_str.append("1011");
        } else if (i == 'C' or i == 'c') {
            temp_str.append("1100");
        } else if (i == 'D' or i == 'd') {
            temp_str.append("1101");
        } else if (i == 'E' or i == 'e') {
            temp_str.append("1110");
        } else if (i == 'F' or i == 'f') {
            temp_str.append("1111");
        }
        hcnt++; // to loop every two characters
        if (hcnt == 2) {
            hcnt = 0;
            bin_list.push_back(temp_str);
            temp_str = "";
        }
    }

    // using each string for decryption
    int kcnt = 0;
    for (const string& j : bin_list) {
        bitset<8> bin(j);
        bitset<8> xor_bin = bin ^ key_list[kcnt];
        kcnt++;
        if (kcnt == key.size()) {
            kcnt = 0;
        }

        unsigned long asc = xor_bin.to_ulong(); // turn string to bitset then convert it to ASCII
        message += static_cast<char>(asc); // add each character to a string for later display
    }
}

int main() {
    // menu start and choice
    cout << "Ahlan ya user ya habibi.\n"
            "What would you like to do today?\n";

    while (true) {
        string choice_1, choice_2, choice_3;

        cout << "1- Cipher a message\n"
                "2- Decipher a message\n"
                "3- End\n" << ">>";

        getline(cin, choice_1);
        // checking if input is valid
        while (choice_1 != "1" and choice_1 != "2" and choice_1 != "3") {
            cout << "Please select a valid option:\n" << ">>";
            getline(cin, choice_1);
        }

        if (choice_1 == "3") {
            cout << "Bye bye!";
            return 0;
        }

        cout << "\nWhich Cipher would you like to choose?" << endl;
        cout << "1- First cypher\n"
                "2- Second cypher\n"
                "3- XOR Cypher\n"
                "4- Return\n" << ">>";

        getline(cin, choice_2);
        // checking if input is valid
        while (choice_2 != "1" and choice_2 != "2" and choice_2 != "3" and choice_2 != "4") {
            cout << "Please select a valid option:\n" << ">>";
            getline(cin, choice_2);
        }

        if (choice_2 == "4") {
            cout << "Choose again:" << endl;
            continue;
        }

        if (choice_1 == "1") { // Encrypting messages
            if (choice_2 == "1") { // First cypher
                cout << "1 and 1";
            }
            else if (choice_2 == "2") { // Second cypher
                cout << "1 and 2";
            }
            else { // XOR cypher
                string message, key, cypher, hex_cypher;
                cout << "Enter the message you wish to encrypt:" << endl << ">>";
                getline(cin, message);

                bool check; // setting a bool for if the input is empty
                for (char i : message) {
                    if (!isspace(i)) {
                        check = true;
                    } else {
                        check = false;
                    }
                }

                // checking if the input is empty
                while (!check) {
                    cout << "Message can't be empty, enter again:" << endl << ">>";
                    getline(cin, message);

                    // adjusting the bool for a recheck
                    for (char i : message) {
                        if (!isspace(i)) {
                            check = true;
                        } else {
                            check = false;
                        }
                    }
                }

                cout << "Enter your key:" << endl << ">>";
                getline(cin, key);

                bool check2; // setting a bool for if the input is empty
                for (char i : key) {
                    if (!isspace(i)) {
                        check2 = true;
                    } else {
                        check2 = false;
                    }
                }

                // checking if the input is empty
                while (!check2) {
                    cout << "Key can't be empty, enter again:" << endl << ">>";
                    getline(cin, key);

                    // adjusting the bool for a recheck
                    for (char i : key) {
                        if (!isspace(i)) {
                            check2 = true;
                        } else {
                            check2 = false;
                        }
                    }
                }

                xor_cypher(message, key, cypher, hex_cypher);
                cout << "Your encrypted message is:" << ' ' << cypher << endl;
                cout << "Hexadecimal hash for encryption:" << ' ' << hex_cypher << endl << endl;
                check = check2 = false; // check reset
            }
        }
        if (choice_1 == "2") { // Decrypting messages
            if (choice_2 == "1") { // First cypher
                cout << "2 and 1";
            }
            else if (choice_2 == "2") { // Second cypher
                cout << "2 and 2";
            }
            else { // XOR cypher
                string choice_xor;
                // choice between decrypting a message or a hexadecimal hash
                cout << "What would you like to decipher:\n"
                        "1- Encrypted message\n"
                        "2- Hexadecimal hash" << endl << ">>";

                getline(cin, choice_xor);
                // checking if input is valid
                while (choice_xor != "1" and choice_xor != "2") {
                    cout << "Please select a valid option:\n" << ">>";
                    getline(cin, choice_xor);
                }

                if (choice_xor == "1"){
                    string message, key, cypher, hex_cypher;
                    cout << "Enter the message you wish to encrypt:" << endl << ">>";
                    getline(cin, message);

                    bool check; // setting a bool for if the input is empty
                    for (char i : message) {
                        if (!isspace(i)) {
                            check = true;
                        } else {
                            check = false;
                        }
                    }

                    // checking if the input is empty
                    while (!check) {
                        cout << "Message can't be empty, enter again:" << endl << ">>";
                        getline(cin, message);

                        // adjusting the bool for a recheck
                        for (char i : message) {
                            if (!isspace(i)) {
                                check = true;
                            } else {
                                check = false;
                            }
                        }
                    }

                    cout << "Enter your key:" << endl << ">>";
                    getline(cin, key);

                    bool check2; // setting a bool for if the input is empty
                    for (char i : key) {
                        if (!isspace(i)) {
                            check2 = true;
                        } else {
                            check2 = false;
                        }
                    }

                    // checking if the input is empty
                    while (!check2) {
                        cout << "Key can't be empty, enter again:" << endl << ">>";
                        getline(cin, key);

                        // adjusting the bool for a recheck
                        for (char i : key) {
                            if (!isspace(i)) {
                                check2 = true;
                            } else {
                                check2 = false;
                            }
                        }
                    }

                    xor_cypher(message, key, cypher, hex_cypher);
                    cout << "Your message is:" << ' ' << cypher << endl << endl;
                    check = check2 = false; // check reset
                }
                else {
                    vector<char> char_list = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
                                              'A', 'B', 'C', 'D', 'E', 'F',
                                              'a', 'b', 'c', 'd', 'e', 'f'};
                    string hex_cypher, key, message;
                    cout << "Enter the hexadecimal hash you wish to decipher:" << endl << ">>";
                    getline(cin, hex_cypher);
                    hex_cypher = removeSpaces(hex_cypher);

                    bool check = true; // setting a bool for if the input is invalid
                    for (char i : hex_cypher) {
                        if (find(char_list.begin(), char_list.end(), i) == char_list.end()) {
                            check = false;
                            break;
                        }
                    }
                    while (!check or hex_cypher.empty()) {
                        if (!check and !hex_cypher.empty()) {
                            cout << "Hash can't contain special characters,\n"
                                    "and letters must be from [A, B, C, D, E, F], enter again:" << endl << ">>";
                        } else {
                            cout << "Hash can't be empty, enter again:" << endl << ">>";
                        }
                        getline(cin, hex_cypher);
                        hex_cypher = removeSpaces(hex_cypher);

                        // adjusting the bool for a recheck
                        for (char i : hex_cypher) {
                            if (find(char_list.begin(), char_list.end(), i) == char_list.end()) {
                                check = false;
                                break;
                            } else {
                                check = true;
                            }
                        }
                    }

                    cout << "Enter your key:" << endl << ">>";
                    getline(cin, key);

                    bool check2; // setting a bool for if the input is empty
                    for (char i : key) {
                        if (!isspace(i)) {
                            check2 = true;
                        } else {
                            check2 = false;
                        }
                    }

                    // checking if the input is empty
                    while (!check2) {
                        cout << "Key can't be empty, enter again:" << endl << ">>";
                        getline(cin, key);

                        // adjusting the bool for a recheck
                        for (char i : key) {
                            if (!isspace(i)) {
                                check2 = true;
                            } else {
                                check2 = false;
                            }
                        }
                    }

                    xor_decipher(hex_cypher, key, message);
                    cout << "Your message is:" << ' ' << message << endl << endl;
                }
            }
        }

        // choice for reusing the program or exiting
        cout << "Would you like to do something else?" << endl;
        cout << "1- Yes, use again\n"
                "2- No, exit\n" << ">>";
        getline(cin, choice_3);
        // checking if input is valid
        while (choice_3 != "1" and choice_3 != "2") {
            cout << "Please select a valid option:\n" << ">>";
            getline(cin, choice_3);
        }

        if (choice_3 == "2") {
            cout << "Bye bye!";
            return 0;
        }


    }
}

int dmain() {
    string a, b, c, d, e;
    getline(cin, a);
    getline(cin ,b);
    xor_cypher(a, b, d, e);
    cout << d << endl;
    cout << e;
}

int smain() {
    string a, b, c, d, e;
    getline(cin, a);
    getline(cin ,b);
    xor_decipher(a, b, c);
    cout << c << endl;
}