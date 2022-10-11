#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// butuh buat bikin tabula recta
// https://crypto.interactive-maths.com/autokey-cipher.html
typedef std::vector<std::vector<char>> matrixC;

void menu();
void encryption(std::string, std::string, bool, matrixC);
void decryption(std::string, std::string, bool, matrixC);
matrixC generateTabulaRecta();
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
  matrixC tabula = generateTabulaRecta();
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
    encryption(message, key, autokey, tabula);
    break;
  case 2:
    decryption(message, key, autokey, tabula);
    break;
  default:
    std::cout << "Invalid operation, please try again\n";
    break;
  }
}

matrixC generateTabulaRecta() {
  matrixC tabula(26, std::vector<char>(26));
  int i, j, k = 0, n = 26;
  for (i = 0; i < n; i++) {
    k = i;
    for (j = 0; j < n; j++) {
      tabula[i][j] = 'A' + k;
      k++;
      if (k == 26)
        k = 0;
    }
  }
  return tabula;
}

void encryption(std::string message, std::string key, bool autokey,
                matrixC tabula) {
  std::cout << "\n:: Enkripsi >\n";
  std::cout << "PT\t: " << message << '\n';
  std::cout << "K\t: " << key << "\n";

  std::string hasil = "";

  int mod;
  if (autokey) {
    mod = message.size();
  } else {
    mod = key.size();
  }

  int k = 0;
  for (int i = 0; i < message.size(); i++) {
    char c = tabula[message[i] - 'A'][key[i] - 'A'];
    if (autokey) {
      key.push_back(message[k % mod]);
    } else {
      key.push_back(key[k % mod]);
    }
    hasil.push_back(c);
    k++;
  }

  std::cout << "\nEnkripsi cipher code >\n" << hasil << '\n';
}

void decryption(std::string message, std::string key, bool autokey,
                matrixC tabula) {
  std::string hasil = message;

  std::cout << "\n:: Dekripsi >\n";
  std::cout << "CT\t: " << message << '\n';
  std::cout << "K\t: " << key << "\n";

  hasil = "";

  int mod;
  if (autokey) {
    mod = message.size();
  } else {
    mod = key.size();
  }

  int k = 0;
  for (int i = 0; i < message.size(); i++) {
    for (int j = 0; j < 26; j++) {
      if (tabula[j][key[i] - 'A'] == message[i]) {
        char c = 'A' + j;
        if (autokey) {
          key.push_back(c);
        } else {
          key.push_back(key[k % mod]);
        }
        hasil.push_back(c);
        k++;
        break;
      }
    }
  }

  std::cout << "\nDekripsi plain text >\n" << hasil << '\n';
}

void refreshUi() { std::cout << "\033[2J\033[1;1H"; }