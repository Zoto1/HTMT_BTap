#include "thuattoan.h"
#include <algorithm> // for std::reverse
#include <iostream>
#include <string>

using namespace std;

// Nhap so nguyen 4 byte -> binary 32 bits
string Int_To_Binary(int x) {
  // Y tuong thuat toan : Chia cho 2 lấy dư cho đến khi x / 2 == 0
  // Edge case so am -> chuyen sang so bu 2 :
  // đảo bits sau đó + 1 ử bit cúi

  bool negative = false;
  if (x < 0) {
    negative = true;
    x = -x;
  }
  string res = "";
  for (int i = 0; i < 32; i++) {
    int32_t remider = x % 2;
    res.push_back(remider + '0');
    x = x / 2;
  }
    reverse(res.begin(), res.end());

  if (negative) {
    for (int i = 0; i < 32; i++) {
      if (res[i] == '0')
        res[i] = '1';
      else if(res[i] == '1')
        res[i] = '0';
    }
    for (int i = 31; i >= 0; --i) {
      if (res[i] == '0') {
        res[i] = '1';
        break;
      }
      res[i] == '0';
    }
  }

  return res;
}


