#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

// Password strength check
bool isStrongPassword(const string& password) {
    if (password.length() < 8)
        return false;

    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;

    for (int i = 0; i < password.length(); i++) {
        char ch = password[i];
        if (isupper(ch)) hasUpper = true;
        else if (islower(ch)) hasLower = true;
        else if (isdigit(ch)) hasDigit = true;
        else hasSpecial = true;
    }

    return hasUpper && hasLower && hasDigit && hasSpecial;
}

// Register user
void registerUser() {
    string username, password;

    cout << "\n--- User Registration ---\n";
    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    if (!isStrongPassword(password)) {
        cout << "? Weak password! Registration denied.\n";
        cout << "Password must contain uppercase, lowercase, digit, special character and be 8+ chars.\n";
        return;
    }

    ofstream file("users.txt", ios::app);
    file << username << " " << password << endl;
    file.close();

    cout << "? Registration successful!\n";
}

// Login user
bool loginUser() {
    string username, password, u, p;
    cout << "\n--- User Login ---\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream file("users.txt");
    while (file >> u >> p) {
        if (u == username && p == password) {
            cout << "? Login successful!\n";
            file.close();
            return true;
        }
    }

    file.close();
    cout << "? Invalid username or password!\n";
    return false;
}

// Vigenere Encryption
string encryptVigenere(string text, string key) {
    string result = "";
    int keyIndex = 0;
    for (int i = 0; i < text.length(); i++) {
        char ch = text[i];
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            char base = isupper(ch) ? 'A' : 'a';
            char k = tolower(key[keyIndex % key.length()]) - 'a';
            result += (char)((ch - base + k) % 26 + base);
            keyIndex++;
        } else {
            result += ch;
        }
    }
    return result;
}

// Vigenere Decryption
string decryptVigenere(string text, string key) {
    string result = "";
    int keyIndex = 0;
    for (int i = 0; i < text.length(); i++) {
        char ch = text[i];
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            char base = isupper(ch) ? 'A' : 'a';
            char k = tolower(key[keyIndex % key.length()]) - 'a';
            result += (char)((ch - base - k + 26) % 26 + base);
            keyIndex++;
        } else {
            result += ch;
        }
    }
    return result;
}

// File Encryption
void encryptFile() {
    string text, key;
    cin.ignore(); // Clear input buffer
    cout << "Enter text to encrypt: ";
    getline(cin, text);
    cout << "Enter encryption key: ";
    cin >> key;

    string encrypted = encryptVigenere(text, key);

    ofstream file("encrypted.txt");
    file << encrypted;
    file.close();

    cout << "?? File encrypted and saved as encrypted.txt\n";
}

// File Decryption
void decryptFile() {
    string key, encryptedText = "", line;
    cout << "Enter decryption key: ";
    cin >> key;

    ifstream file("encrypted.txt");
    if (!file) {
        cout << "? No encrypted file found!\n";
        return;
    }

    while (getline(file, line)) {
        encryptedText += line;
    }
    file.close();

    string decrypted = decryptVigenere(encryptedText, key);
    cout << "?? Decrypted text: " << decrypted << endl;
}

// Main Menu
int main() {
    int choice;
    bool loggedIn = false;

    do {
        cout << "\n==== Information Security System ====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Encrypt File (Login required)\n";
        cout << "4. Decrypt File (Login required)\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loggedIn = loginUser();
                break;
            case 3:
                if (loggedIn)
                    encryptFile();
                else
                    cout << "?? Please login first!\n";
                break;
            case 4:
                if (loggedIn)
                    decryptFile();
                else
                    cout << "?? Please login first!\n";
                break;
            case 5:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}

