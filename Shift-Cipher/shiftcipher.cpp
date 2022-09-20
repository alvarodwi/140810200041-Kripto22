#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

void menu();
void encryption(std::string, int);
void decryption(std::string, int);
void refreshUi();

int main() {
  char yesNo;

  do {
    yesNo = ' ';
    std::cout << "\n.:: Shift Cipher ::.\n\n";
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
  std::string message;
  int key;
  std::cout << "Message\t> ";
  getline(std::cin, message);
  std::cout << "Key\t> ";
  std::cin >> key;
  key = key % 26;

  int op;
  std::cout << "\n";
  std::cout << "1. Enkripsi\n";
  std::cout << "2. Dekripsi\n";
  std::cout << "Pilih operasi\t> ";
  std::cin >> op;

  switch (op) {
  case 1:
    encryption(message, key);
    break;
  case 2:
    decryption(message, key);
    break;
  default:
    std::cout << "Invalid operation, please try again\n";
    break;
  }
}

void encryption(std::string message, int key) {
  // std::cout << "\n:: Enkripsi >\n";
  // std::cout << "message\t: " << message << '\n';
  // std::cout << "key\t: " << key << "\n\n";

  std::string hasil = "";

  for (int i = 0; i < message.length(); i++) {
    // deteksi spasi
    if (message[i] == ' ') {
      hasil += ' ';
      continue;
    }
    // huruf kapital
    if (isupper(message[i]))
      hasil += char(int(message[i] + key - 65) % 26 + 65);
    // huruf non kapital
    else
      hasil += char(int(message[i] + key - 97) % 26 + 97);
  }

  std::cout << "\nEnkripsi cipher code >\n" << hasil << '\n';
}
void decryption(std::string message, int key) {
  // std::cout << "\n:: Dekripsi >\n";
  // std::cout << "message\t: " << message << '\n';
  // std::cout << "key\t: " << key << "\n\n";

  std::string hasil = "";

  for (int i = 0; i < message.length(); i++) {
    // deteksi spasi
    if (message[i] == ' ') {
      hasil += ' ';
      continue;
    }

    // huruf kapital
    if (isupper(message[i]))
      hasil += char(int(message[i] + (26 - key) - 65) % 26 + 65);
    // huruf non kapital
    else
      hasil += char(int(message[i] + (26 - key) - 97) % 26 + 97);
  }

  std::cout << "\nDekripsi plain text >\n" << hasil << '\n';
}

void refreshUi() { std::cout << "\033[2J\033[1;1H"; }