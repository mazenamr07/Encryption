#include <iostream>
#include <bitset>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <cctype>

using namespace std;

// Function for erasing spaces from a string
string removeSpaces(string str) {
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

// Function to check choice validity
bool choiceCheck(const string& choice) {
    vector<string> choices = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};

    for (const string& i : choices) {
        if (choice == i) {
            return true;
        }
    }
    return false;
}

// Function for encrypting text using the XOR Cipher
void xorCipher(const string& message, const string& key, string& cipher, string& hex_cipher) {
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
        bitset bin_cipher = bin_char ^ key_list[kcnt];
        kcnt++;
        if (kcnt == key.size()) {
            kcnt = 0;
        }

        // store each binary set in a vector
        bin_list.push_back(bin_cipher);
    }
    // use each binary set for encryption
    for (bitset i : bin_list) {
        unsigned long cipher_char = i.to_ulong(); // turn binary set to ASCII then convert it to character
        cipher += static_cast<char>(cipher_char); // add each character to a string for later display
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
            hex_cipher += 'A';
        } else if (sum_1 == 11) {
            hex_cipher += 'B';
        } else if (sum_1 == 12) {
            hex_cipher += 'C';
        } else if (sum_1 == 13) {
            hex_cipher += 'D';
        } else if (sum_1 == 14) {
            hex_cipher += 'E';
        } else if (sum_1 == 15) {
            hex_cipher += 'F';
        } else {
            hex_cipher += static_cast<char>(sum_1 + 48);
        }
        // second half letter check
        if (sum_2 == 10) {
            hex_cipher += 'A';
        } else if (sum_2 == 11) {
            hex_cipher += 'B';
        } else if (sum_2 == 12) {
            hex_cipher += 'C';
        } else if (sum_2 == 13) {
            hex_cipher += 'D';
        } else if (sum_2 == 14) {
            hex_cipher += 'E';
        } else if (sum_2 == 15) {
            hex_cipher += 'F';
        } else {
            hex_cipher += static_cast<char>(sum_2 + 48);
        } hex_cipher += ' ';
    }

}

// Function for decrypting Hexadecimal Hash using the XOR Cipher
void xorDecipher(const string& hex_cipher, const string& key, string& message) {
    vector<string> bin_list;
    vector<bitset<8>> key_list;

    // turn key into a set of 8 bits
    for (char i : key) {
        bitset<8> bin_key(i);
        key_list.push_back(bin_key);
    }

    // Taking each Hexadecimal pair and converting them to a string of 8 characters
    string sp_hex_cipher = removeSpaces(hex_cipher); // removing spaces from the hash

    int hcnt = 0;
    string temp_str;
    for (char i : sp_hex_cipher) {
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

// Function for encrypting text using the Polybius Square Cipher
void polyCipher(const string& text, const string& key, string& cyph_txt) {
    // Making the alphabet table with key
    char table[5][5];
    int k = 97; // 'a' in ASCII
    for (char i : key) {
        int row = i - 49;
        for (char j : key) {
            int col = j - 49;
            if (k == 106) {
                k = 107;
            }
            table[row][col] = static_cast<char>(k);
            k++;
        }
    }

    // Ciphering text using table
    string cipher_txt;
    for (char i : text) {
        if (!isalpha(i)) { // Skipping non-alphabetical characters
            cipher_txt += i;
            continue;
        }
        i |= 32; // forcing capitalized characters into lowercase

        if (i == 'j') { // 'j' to 'i' for ciphering
            i = 'i';
        }
        for (int j = 0; j < 5; j++) {
            for (int n = 0; n < 5; n++) {
                if (table[j][n] == i) {
                    cipher_txt += to_string(j + 1);
                    cipher_txt += to_string(n + 1);
                }
            }
        }
    }
    cyph_txt = cipher_txt;
}

// Function for decrypting text using the Polybius Square Cipher
void polyDecipher(const string& cyph_txt, const string& key, string& text) {
    // Making the alphabet table with key
    char table[5][5];
    int k = 97; // 'a' in ASCII
    for (char i : key) {
        int row = i - 49;
        for (char j : key) {
            int col = j - 49;
            if (k == 106) {
                k = 107;
            }
            table[row][col] = static_cast<char>(k);
            k++;
        }
    }

    // Deciphering text using table
    string b_txt;
    int counter = 0, i_row, i_col;
    for (char i : cyph_txt) {
        if (!isdigit(i)) { // Skipping non-digit characters
            b_txt += i;
            continue;
        }

        if (counter % 2 == 0) { // Taking the first digit as row number
            i_row = static_cast<char>(i) - 49;
        } else { // Taking the second digit as column number
            i_col = static_cast<char>(i) - 49;
        }
        counter++;
        if (counter % 2 == 0) { // Adding the character after every two digits
            b_txt += table[i_row][i_col];
        }
    }
    text = b_txt;
}

// Function for encrypting text using Morse Code
void morseCipher(const string& message, string& cipher) {
    // Making a Morse Code list
    vector<string> morseList = {"-----", ".----", "..---", "...--", "....-", ".....",
                                "-....", "--...", "---..", "----.",
                                ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
                                "....", "..", ".---", "-.-", ".-..", "--", "-.",
                                "---", ".--.", "--.-", ".-.", "...", "-", "..-",
                                "...-", ".--", "-..-", "-.--", "--.."};

    // Ciphering text using the list
    for (char i : message) {
        if (!isdigit(i) and !isalpha(i) and i != 32) {
            cipher += i;
            continue;
        }
        if (i == 32) {
            cipher += "  ";
            continue;
        }
        if (i > 96) {
            i -= 87;
            cipher += morseList[i];
            cipher += ' ';
            continue;
        }
        if (i > 64) {
            i -= 55;
            cipher += morseList[i];
            cipher += ' ';
            continue;
        }
        i -= 48;
        cipher += morseList[i];
        cipher += ' ';
    }
}

// Function for decrypting text using Morse Code
void morseDecipher(string cipher, string& message) {
    cipher += ' ';
    // Making a Morse Code list
    vector<string> morseList = {"-----", ".----", "..---", "...--", "....-", ".....",
                                "-....", "--...", "---..", "----.",
                                ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
                                "....", "..", ".---", "-.-", ".-..", "--", "-.",
                                "---", ".--.", "--.-", ".-.", "...", "-", "..-",
                                "...-", ".--", "-..-", "-.--", "--.."};

    // Deciphering text using the list
    string temp;
    int tempSpace = 0;
    for (char i : cipher) {
        if (i != '.' and i != '-' and i != ' ') {
            message += i;
//            tempSpace = 0;
            continue;
        }
        if (i == 32) {
            if (tempSpace == 1) {
                tempSpace++;
                continue;
            }
            else if (tempSpace == 2) {
                message += " ";
                tempSpace = 0;
                continue;
            }
            tempSpace++;

            auto it = find(morseList.begin(), morseList.end(), temp);
            if (it != morseList.end()) {
                int index = it - morseList.begin();
                if (index < 10) {
                    message += static_cast<char>(index + 48);
                }
                else {
                    message += static_cast<char>(index + 87);
                }
            }
            temp = "";
            continue;
        }
        temp += i;
        tempSpace = 0;
    }
}

void menu() {
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

        if (choice_1 == "3") { // Exiting the program
            cout << "Bye bye!";
            break;
        }

        cout << "\nWhich Cipher would you like to choose?" << endl;
        cout << "1- Morse Cipher\n"
                "2- Polybius Square Cipher\n"
                "3- XOR Cipher\n"
                "4- Fourth Cipher\n"
                "0- Return\n" << ">>";
        getline(cin, choice_2);

        // checking if input is valid
        while (!choiceCheck(choice_2)) {
            cout << "Please select a valid option:\n" << ">>";
            getline(cin, choice_2);
        }

        // Encrypting messages
        if (choice_1 == "1") {
            switch(stoi(choice_2)) {
                case 1: // Enc Morse Cipher
                {
                    string message, cipher;

                }
                    break;

                case 2: // Enc Polybius Cipher
                {
                    string message, key, cipher;
                    cout << "Enter the message you wish to encrypt:" << endl << ">>";
                    getline(cin, message);

                    bool onlySpaces = all_of(message.begin(), message.end(), [](char i) { return i == ' '; });
                    bool aDigit = any_of(message.begin(), message.end(), [](char i) { return isdigit(i); });

                    while (message.empty() or onlySpaces or aDigit) {
                        if (message.empty() or onlySpaces) {
                            cout << "Message can't be empty, enter again:" << endl << ">>";
                            getline(cin, message);

                            aDigit = any_of(message.begin(), message.end(), [](char i) { return isdigit(i); });
                            onlySpaces = all_of(message.begin(), message.end(), [](char i) { return i == ' '; });
                        } else {
                            cout << "Message can't contain numbers, enter again:" << endl << ">>";
                            getline(cin, message);

                            onlySpaces = all_of(message.begin(), message.end(), [](char i) { return i == ' '; });
                            aDigit = any_of(message.begin(), message.end(), [](char i) { return isdigit(i); });
                        }
                    }

                    cout << "Enter your key:" << endl << ">>";
                    getline(cin, key);

                    onlySpaces = all_of(key.begin(), key.end(), [](char i) { return i == ' '; });
                    bool limitDigit = any_of(key.begin(), key.end(), [](char i) { return i < 49 or i > 53; });

                    while (key.empty() or onlySpaces or key.size() != 5 or limitDigit) {
                        if (key.empty() or onlySpaces) {
                            cout << "Key can't be empty, enter again:" << endl << ">>";
                            getline(cin, key);

                            limitDigit = any_of(key.begin(), key.end(), [](char i) { return i < 49 or i > 53; });
                            onlySpaces = all_of(key.begin(), key.end(), [](char i) { return i == ' '; });
                        } else {
                            cout << "Key must consist of 5 digits from (1-5),\n"
                                    "e.g. 12435, enter again:" << endl << ">>";
                            getline(cin, key);

                            limitDigit = any_of(key.begin(), key.end(), [](char i) { return i < 49 or i > 53; });
                            onlySpaces = all_of(message.begin(), message.end(), [](char i) { return i == ' '; });
                        }
                    }

                    polyCipher(message, key, cipher);
                    cout << "Your encrypted message is:" << ' ' << cipher << endl << endl;
                }
                    break;

                case 3: // Enc XOR Cipher
                {
                    string message, key, cipher, hex_cipher;
                    cout << "Enter the message you wish to encrypt:" << endl << ">>";
                    getline(cin, message);

                    bool onlySpaces = all_of(message.begin(), message.end(), [](char i) {return i == ' ';});

                    while (message.empty() or onlySpaces) { // Checking if input is empty
                        cout << "Message can't be empty, enter again:" << endl << ">>";
                        getline(cin, message);

                        onlySpaces = all_of(message.begin(), message.end(), [](char i) {return i == ' ';});
                    }

                    cout << "Enter your key:" << endl << ">>";
                    getline(cin, key);

                    onlySpaces = all_of(key.begin(), key.end(), [](char i) {return i == ' ';});

                    while (key.empty() or onlySpaces) { // Checking if input is empty
                        cout << "Key can't be empty, enter again:" << endl << ">>";
                        getline(cin, key);

                        onlySpaces = all_of(key.begin(), key.end(), [](char i) {return i == ' ';});
                    }

                    xorCipher(message, key, cipher, hex_cipher);
                    cout << "Your encrypted message is:" << ' ' << cipher << endl;
                    cout << "Hexadecimal hash for encryption:" << ' ' << hex_cipher << endl << endl;
                }
                    break;

                case 4: // Enc XOR Cipher
                {

                }
                    break;

                case 5: // Enc XOR Cipher
                {

                }
                    break;

                case 6: // Enc XOR Cipher
                {

                }
                    break;

                case 7: // Enc XOR Cipher
                {

                }
                    break;

                case 8: // Enc XOR Cipher
                {

                }
                    break;

                case 9: // Enc XOR Cipher
                {

                }
                    break;

                case 10: // Enc XOR Cipher
                {

                }
                    break;

                default:
                    cout << "\nChoose again:" << endl;
                    continue;
            }
        }
            // Decrypting messages
        else if (choice_1 == "2") {
            if (choice_2 == "1") { // Dec First cipher
                cout << "2 and 1";
            }
            else if (choice_2 == "2") { // Dec Second cipher
                cout << "2 and 2";
            }
            else { // Dec XOR cipher
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
                    string message, key, cipher, hex_cipher;
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

//                    xorDecipher(message, key, cipher, hex_cipher);
                    cout << "Your message is:" << ' ' << cipher << endl << endl;
                    check = check2 = false; // check reset
                }
                else {
                    vector<char> char_list = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
                                              'A', 'B', 'C', 'D', 'E', 'F',
                                              'a', 'b', 'c', 'd', 'e', 'f'};
                    string hex_cipher, key, message;
                    cout << "Enter the hexadecimal hash you wish to decipher:" << endl << ">>";
                    getline(cin, hex_cipher);
                    hex_cipher = removeSpaces(hex_cipher);

                    bool check = true; // setting a bool for if the input is invalid
                    for (char i : hex_cipher) {
                        if (find(char_list.begin(), char_list.end(), i) == char_list.end()) {
                            check = false;
                            break;
                        }
                    }
                    while (!check or hex_cipher.empty()) {
                        if (!check and !hex_cipher.empty()) {
                            cout << "Hash can't contain special characters,\n"
                                    "and letters must be from [A, B, C, D, E, F], enter again:" << endl << ">>";
                        } else {
                            cout << "Hash can't be empty, enter again:" << endl << ">>";
                        }
                        getline(cin, hex_cipher);
                        hex_cipher = removeSpaces(hex_cipher);

                        // adjusting the bool for a recheck
                        for (char i : hex_cipher) {
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

                    xorDecipher(hex_cipher, key, message);
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

        if (choice_3 == "2") { // Exiting the program
            cout << "Bye bye!";
            break;
        }
    }
}

int main() {
    string mes = "Ahmed@ 011570Sobhy MAZEN &0)&&## 011570658@5=2=", ci, final;
    morseCipher(mes, ci);
    morseDecipher(ci, final);
    cout << ci << endl << final;
}