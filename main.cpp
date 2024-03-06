#include <iostream>
#include <string>

using namespace std;

int main() {
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
            } else if (choice_2 == "2") {
                cout << "1 and 2";
            } else {
                cout << "1 and 3";
            }
        } if (choice_1 == "2") {
            if (choice_2 == "1") {
                cout << "2 and 1";
            } else if (choice_2 == "2") {
                cout << "2 and 2";
            } else {
                cout << "2 and 3";
            }
        }
    }


