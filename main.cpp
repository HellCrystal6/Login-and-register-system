#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

using namespace std;

string xorEncryptDecrypt(const string& data, const string& key) {
  string result = data;
  for (string::size_type i = 0; i < data.size(); ++i) {
    result[i] = data[i] ^ key[i % key.size()];
  }
  return result;
}

void mainMenu();

int choice;
bool cinFail;
int confirmation;
string username, line;

void writeToFile(const string& username, const string& password) {
  ofstream writeFile(username + ".txt");
  writeFile << xorEncryptDecrypt(
      password,
      username);  // Encrypt the password using the username as the key
  writeFile.close();
  mainMenu();
}

void readFile() {
  ifstream file(username + ".txt");

  cout << "Enter your username: ";
  cin >> username;

  system(CLEAR_COMMAND);

  cout << "Enter your password: ";
  string pass;
  cin >> pass;

  if (file.is_open()) {
    getline(file, line);
    string decryptedPassword = xorEncryptDecrypt(
        line,
        username);  // Decrypt the stored password using the username as the key
    if (pass == decryptedPassword) {
      cout << "Logged In!" << endl;
    } else {
      cout << "Wrong password." << endl;
    }
    file.close();
  }
}

void registerPassword() {
  string password, password2;
  cout << "Please enter the password:" << endl;
  cin >> password;
  cout << "Please re-enter your password:" << endl;
  cin >> password2;
  if (password == password2) {
    cin.clear();
    cin.ignore(10000, '\n');
    writeToFile(username, password);
    exit(1);
  } else {
    cout << "Sorry, the passwords do not match." << endl;
  }
}

void registerUser() {
  cin.ignore();
  while (true) {
    cout << "Please enter your username: " << endl;
    getline(cin, username);
    cout << "\nUsername -  \"" << username << "\"\nConfirm? \n\n[1] Yes\n[2] No"
         << endl;
    cin >> confirmation;
    if (confirmation == 1) {
      registerPassword();
      break;
    } else {
      cout << "Sorry, invalid input. Please try again." << endl;
      cin.clear();
      cin.ignore(10000, '\n');
    }
  }
}

void exitProgram() { exit(0); }

void mainMenu() {
  cout << "Hello! Would you like to log in or register?\n[1] Login\n[2] "
          "Register\n[3] Exit"
       << endl;
  cin >> choice;

  while (cin.fail()) {
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Invalid input. Please try again: ";
    cin >> choice;
  }

  switch (choice) {
    case 1:
      readFile();
      break;

    case 2:
      registerUser();
      break;

    case 3:
      exitProgram();
      break;

    default:
      cout << "Invalid input. Please try again." << endl;
      mainMenu();
      break;
  }
}

int main() {
  mainMenu();
  return 0;
}
