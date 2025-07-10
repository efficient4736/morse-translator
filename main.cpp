#include <iostream>
#include <string>
#include <map>
#include <cctype>
using namespace std;

int main() {
    // Morsecode-Tabelle
    map<char, string> morse = {
        {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."},
        {'F', "..-."}, {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"},
        {'K', "-.-"}, {'L', ".-.."}, {'M', "--"}, {'N', "-."}, {'O', "---"},
        {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
        {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"}, {'Y', "-.--"},
        {'Z', "--.."}, {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, 
        {'3', "...--"}, {'4', "....-"}, {'5', "....."}, {'6', "-...."}, 
        {'7', "--..."}, {'8', "---.."}, {'9', "----."}
    };

    // Inverse Map für Morse zu Text
    map<string, char> morse_to_char;
    for (const auto& pair : morse) {
        morse_to_char[pair.second] = pair.first;
    }

    cout << "Morsecode-Uebersetzer\n";
    cout << "---------------------\n\n";
    cout << "1: Text zu Morse\n";
    cout << "2: Morse zu Text\n\n";
    cout << "Wahl: ";
    int choice;
    if (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "\nUngueltige Wahl! Programm wird beendet.\n";
        return 1;
    }
    cin.ignore();

    if (choice == 1) {
        // Text zu Morse
        cout << "\nText eingeben (nur Grossbuchstaben, Zahlen und Leerzeichen):\n";
        string text;
        getline(cin, text);

        // Text in Großbuchstaben umwandeln
        for (char& c : text) {
            c = toupper(c);
        }

        cout << "\nMorsecode-Ausgabe:\n\n";
        string word = "";
        bool has_invalid = false;
        for (char c : text) {
            if (c == ' ') {
                if (!word.empty()) {
                    cout << word << "\n";
                    word = "";
                }
            } else if (morse.find(c) != morse.end()) {
                word += morse[c] + " ";
            } else {
                word += "? ";
                has_invalid = true;
            }
        }
        if (!word.empty()) {
            cout << word << "\n";
        }
        if (has_invalid) {
            cout << "\nHinweis: Ungültige Zeichen wurden durch '?' ersetzt.\n";
        }
        cout << endl;
    } else {
        // Morse zu Text
        cout << "\nMorsecode eingeben (Buchstaben durch Leerzeichen, Woerter durch / trennen):\n";
        cout << "Beispiel: ... --- ... / .-   (fuer 'SOS A')\n";
        string morse_input;
        getline(cin, morse_input);

        cout << "\nText-Ausgabe:\n\n";
        string letter = "";
        bool has_invalid = false;
        for (size_t i = 0; i <= morse_input.size(); ++i) {
            char c = (i < morse_input.size()) ? morse_input[i] : ' ';
            if (c == ' ' || c == '/') {
                if (!letter.empty()) {
                    if (morse_to_char.find(letter) != morse_to_char.end()) {
                        cout << morse_to_char[letter];
                    } else {
                        cout << "?";
                        has_invalid = true;
                    }
                    letter = "";
                }
                if (c == '/') {
                    cout << " ";
                }
            } else {
                letter += c;
            }
        }
        if (has_invalid) {
            cout << "\n\nHinweis: Ungueltige Morsezeichen wurden durch '?' ersetzt.\n";
        }
        cout << endl;
    }

    return 0;
}