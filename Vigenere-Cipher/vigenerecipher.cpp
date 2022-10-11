#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

void menu();
void encryption(std::string, std::string, bool);
void decryption(std::string, std::string, bool);
std::string generateKey(std::string, std::string, bool);
void refreshUi();

int main() {
  char yesNo;

  do {
    yesNo = ' ';
    std::cout << "\n.:: Vigenere Cipher ::.\n\n";
    menu();

    while (toupper(yesNo) != 'Y' && toupper(yesNo) != 'N') {
      std::cout << "\n\nJalankan lagi (Y/N)\t> ";
      std::cin >> yesNo;
      std::cin.ignore();
      refreshUi();
    }
  } while (toupper(yesNo) == 'Y');

  return 0;
}

void menu() {
  std::string message, key;
  char flag;
  bool autokey = false;
  std::cout << "Message\t\t> ";
  getline(std::cin, message);
  std::cout << "Key\t\t> ";
  std::cin >> key;
  std::cout << "Autokey (Y/N)\t> ";
  std::cin >> flag;

  flag = toupper(flag);
  if (flag == 'Y') {
    autokey = true;
  }

  for (auto &m : message)
    m = toupper(m);
  for (auto &k : key)
    k = toupper(k);
  message.erase(std::remove(message.begin(), message.end(), ' '),
                message.end());
  key.erase(std::remove(key.begin(), key.end(), ' '), key.end());

  int op;
  std::cout << "\n";
  std::cout << "1. Enkripsi\n";
  std::cout << "2. Dekripsi\n";
  std::cout << "Pilih operasi\t> ";
  std::cin >> op;

  switch (op) {
  case 1:
    encryption(message, key, autokey);
    break;
  case 2:
    decryption(message, key, autokey);
    break;
  default:
    std::cout << "Invalid operation, please try again\n";
    break;
  }
}

std::string generateKey(std::string message, std::string key, bool autokey) {
  int mLen = message.size();

  if (autokey) {
    for (int i = 0;; i++) {
      if (mLen == i)
        i = 0;
      if (key.size() == mLen)
        break;
      key.push_back(message[i]);
    }
  } else {
    for (int i = 0;; i++) {
      if (mLen == i)
        i = 0;
      if (key.size() == mLen)
        break;
      key.push_back(key[i]);
    }
  }

  return key;
}

void encryption(std::string message, std::string key, bool autokey) {
  std::string newKey = generateKey(message, key, autokey);
  std::cout << "\n:: Enkripsi >\n";
  std::cout << "PT\t: " << message << '\n';
  std::cout << "K\t: " << newKey << "\n";

  std::string hasil = "";

  for (int i = 0; i < message.size(); i++) {
    int c = (message[i] + newKey[i]) % 26;
    hasil.push_back(char(c + 65));
  }

  std::cout << "\nEnkripsi cipher code >\n" << hasil << '\n';
}
void decryption(std::string message, std::string key, bool autokey) {
  // dekripsi autokey sekarang mentok sampe 2x panjang key...
  std::string hasil = message;
  std::string newKey;

  if (autokey) {
    for (int i = 0; i < key.size(); i++) {
      int c = (message[i] - key[i] + 26) % 26;
      hasil[i] = (char(c + 65));
    }
    newKey = generateKey(hasil, key, autokey);
  } else {
    newKey = generateKey(message, key, autokey);
  }

  std::cout << "\n:: Dekripsi >\n";
  std::cout << "CT\t: " << message << '\n';
  std::cout << "K\t: " << newKey << "\n";

  hasil = "";

  for (int i = 0; i < message.size(); i++) {
    int c = (message[i] - newKey[i] + 26) % 26;
    hasil.push_back(char(c + 65));
  }

  std::cout << "\nDekripsi plain text >\n" << hasil << '\n';
}

void refreshUi() { std::cout << "\033[2J\033[1;1H"; }