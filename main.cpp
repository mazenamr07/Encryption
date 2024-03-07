#include <iostream>
#include <cstring>
#include <bitset>
#include <vector>
#include <cmath>

using namespace std;

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

// Function for decrypting using the XOR Cypher
void xor_decipher(const string& cypher, const string& hex_cypher, char key, string& message) {

}

int smain() {
    // menu start and choice
    cout << "Ahlan ya user ya habibi.\n"
            "What would you like to do today?\n";

    while (true) {
        string choice_1;
        string choice_2;

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

        if (choice_1 == "1") {
            if (choice_2 == "1") {
                cout << "1 and 1";
            }
            else if (choice_2 == "2") {
                cout << "1 and 2";
            }
            else {
                cout << "1 and 3";
            }
        }
        if (choice_1 == "2") {
            if (choice_2 == "1") {
                cout << "2 and 1";
            }
            else if (choice_2 == "2") {
                cout << "2 and 2";
            }
            else {
                cout << "2 and 3";
            }
        }
    }
}

int main() {
    string a, b;
    xor_cypher("abcdefgh_ABCDEFG", "mazen", a, b);
    cout << a << endl;
    cout << b;
    return 0;
}