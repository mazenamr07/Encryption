#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <cmath>

using namespace std;

// Function for encrypting with the XOR Cypher
string xor_cypher(const string& message, char key) {
    vector<bitset<8>> bin_list;
    string cypher;
    // turn key into a set of 8 bits
    bitset<8> bin_key(key);

    // turn each character of the message into a set of 8 bits
    for (char i : message) {
        bitset<8> bin_char(i);
        bitset bin_cypher = bin_char ^ bin_key;
        // store each binary set in a vector
        bin_list.push_back(bin_cypher);
    }
    // use each binary set for encryption
    for (bitset i : bin_list) {
        unsigned long cypher_char = i.to_ulong(); // turn each binary set into ASCII then convert it to character
        cypher += static_cast<char>(cypher_char); // add each character to a string for later display
        string temp_char = i.to_string(); // turn binary set to string of numbers

        int digit;
        double sum = 0;
        int power = 7;

        for (char j : temp_char) {
            if (j == '0') {
                digit = 0;
            } else {
                digit = 1;
            }
            double hama = pow(16, power) * digit;
            power -= 1;
            cout << hama << endl;
        }
    }

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
    cout << xor_cypher("mazen", 'P');
    return 0;
}