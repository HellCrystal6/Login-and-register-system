#include <iostream>
#include <string>
#include <fstream>

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif

using namespace std;

string xorEncryptDecrypt(const string& data, const string& key) {
    string result = data;
    for (size_t i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i % key.size()];
    }
    return result;
}

void mainmenu();

int choice;
bool cinfail;
int confirmation;
string username, password, password2, line;

void writetofile(const string& username) {
    ofstream writefile;
    string file = username + ".txt";
    writefile.open(file.c_str());
    writefile << xorEncryptDecrypt(password, username); // Encrypt the password using username as the key
    writefile.close();
    mainmenu();
}

void readfile() {
    ifstream file(username + ".txt");

    cout << "Enter your username: ";
    cin >> username;

    system(CLEAR_COMMAND);

    cout << "Enter your password: ";
    string pass;
    cin >> pass;

    if (file.is_open()) {
        getline(file, line);
        string decryptedPassword = xorEncryptDecrypt(line, username); // Decrypt the stored password using username as the key
        if (pass == decryptedPassword) {
            cout << "Logged In!" << endl;
        }
        file.close();
    }
}

void registerpassword() {
    cout << "Please enter the password:" << endl;
    cin >> password;
    cout << "Please re-enter your password:" << endl;
    cin >> password2;
    if (password == password2) {
        cin.clear();
        cin.ignore(10000, '\n');
        writetofile(username);
        exit(1);
    } else {
        cout << "Sorry, invalid input" << endl;
        registerpassword();
    }
}

void registerme() {
    cout << "Please enter your username: " << endl;
    getline(cin, username);
    cout << "\nUsername -  \"" << username << "\"\nConfirm? \n\n[1] Yes\n[2] No" << endl;
    cin >> confirmation;
    if (confirmation == 1) {
        registerpassword();
    } else {
        cout << "Sorry, invalid input. Please try again" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        registerme();
    }
}

void exitProgram() {
    exit(0);
}

void mainmenu() {
    cout << "Hello, Would you like to log in or register\n[1] Login\n[2] Register\n[3] Exit" << endl;
    cin >> choice;

    do {
        cinfail = cin.fail();
        cin.clear();
        cin.ignore(10000, '\n');
    } while (cinfail == true);

    switch (choice) {
        case 1:
            readfile();
            break;

        case 2:
            registerme();
            break;

        case 3:
            exitProgram();
            break;
    }
}

int main() {
    mainmenu();
    return 0;
}
