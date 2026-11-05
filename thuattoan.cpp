#include "thuattoan.h"
#include <algorithm> // for std::reverse
#include <bit>
#include <charconv>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <stdexcept> // for std::invalid_argument
#include <string>
#include <utility> // for std::pair
using namespace std;

// Nhap so nguyen 4 byte -> binary 32 bits
string Int_To_Binary(int x) {
  // Y tuong thuat toan : Chia cho 2 lấy dư cho đến khi x / 2 == 0
  // Edge case so am -> chuyen sang so bu 2 :
  // đảo bits sau đó + 1 tử bit cúi

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
      else if (res[i] == '1')
        res[i] = '0';
    }
    for (int i = 31; i >= 0; --i) {
      if (res[i] == '0') {
        res[i] = '1';
        break;
      }
      res[i] = '0';
    }
  }

  return res;
}
pair<string, char> Add_8bits_Binary(

    string a, string b) { // Tra ve 1 pair <string, char> trong đó string là kết
                          // quả cộng 2 số nhị phân 8 bit, char là bit nhớ
  // Y tuong thuat toan : Cộng bit từ phải sang trái, nếu tổng 2 bit = 1 thì
  // carry = 0, nếu tổng 2 bit = 2 thì carry = 1
  if (a.length() != b.length())
    throw invalid_argument("Hai chuoi phai co cung do dai");
  string res = "";
  char carry = '0';
  for (int i = static_cast<int>(a.length()) - 1; i >= 0; i--) {
    char bits_a = a[i];
    char bits_b = b[i];

    if (((bits_a == '0' && bits_b == '1') ||
         (bits_a == '1' && bits_b == '0')) &&
        carry == '0')
      res.push_back('1');
    else if (((bits_a == '0' && bits_b == '1') ||
              (bits_a == '1' && bits_b == '0')) &&
             carry == '1') {
      res.push_back('0');
      carry = '1';
    } else if ((bits_a == '1' && bits_b == '1') && carry == '0') {
      carry = '1';
      res.push_back('0');
    } else if ((bits_a == '1' && bits_b == '1') && carry == '1') {
      carry = '1';
      res.push_back('1');
    } else if ((bits_a == '0' && bits_b == '0') && carry == '0') {
      res.push_back('0');
    } else if ((bits_a == '0' && bits_b == '0') && carry == '1') {
      carry = '0';
      res.push_back('1');
    };
  }
  reverse(res.begin(), res.end());
  return std::make_pair(res, carry);
}
string Convert_To_2s_Complement(string a) {
  for (int i = 0; i < static_cast<int>(a.length()); ++i) {
    if (a[i] == '0')
      a[i] = '1';
    else
      a[i] = '0';
  }

  string one(a.length(), '0');
  one.back() = '1';

  return Add_8bits_Binary(a, one).first;
}
string Sub_8bits_Binary(string a, string b) {
  // Y tuong thuat toan : chuyen b sang so bu 2 sau đó cộng với a
  b = Convert_To_2s_Complement(b);
  return Add_8bits_Binary(a, b).first;
}
string Mul_8bits_Binary(string a, string b) {
  // Y tuong thuat toan : ta có [C,A,Q] trong đó C là bit nhớ
  // A là kết quả, Q là số nhân
  // Nếu bit cuối Q = 1 thì cộng M vào A với M là số bị nhân, nếu bit cuối Q = 0
  // thì không cộng Sau đó dịch phải [C,A,Q] 1 bit, lặp lại
  string A = "00000000"; // A
  char C = '0';          // C
  for (int i = 0; i < 8; i++) {
    // Xét bit cuối Q
    if (b[7] == '1') {
      auto result = Add_8bits_Binary(A, a);
      A = result.first;
      C = result.second;
    }
    // Dịch phải [C,A,Q] 1 bit

    // thêm bit 0 vào đầu A
    b.pop_back();
    b.insert(b.begin(), A.back());
    A.pop_back();
    A.insert(A.begin(), C);
    C = '0'; // reset C về 0 sau khi dịch phải
  }

  return A + b;
}
pair<string, string> Div_8bits_Binary(string a, string b) {
  // Y tuong thuat toan : ta có [ A,Q] trong đó C là bit nhớ
  // A là số dư , Q là thương
  // a: số bị chia
  // b: số chia
  // Trả về {số dư, thương}
  string A = "000000000"; // A
  string M = "0" + b;     // M
  string Q = a;           // Q
  for (int i = 0; i < 8; i++) {
    // Dich trái [C,A,Q] 1 bit
    A.erase(A.begin());
    A.push_back(Q.front());
    Q.erase(Q.begin());
    // A = A - M
    A = Sub_8bits_Binary(A, M);
    // Nếu A < 0 thì Q = 0, A = A + M
    if (A[0] == '1') {
      Q.push_back('0');
      A = Add_8bits_Binary(A, M).first;
    } else {
      Q.push_back('1');
    }
  }

  return {A.substr(1), Q};
}
//===================================Second
// part========================================
string Unsigned_To_Binary(unsigned int value) {
  if (value == 0)
    return "0";

  string result;

  while (value > 0) {
    result.push_back(static_cast<char>('0' + value % 2));

    value /= 2;
  }

  reverse(result.begin(), result.end());
  return result;
}
void Analyze_Float(float x) {
  char sign = x < 0 ? '1' : '0';

  float absoluteValue = abs(x);
  if (absoluteValue == 0.0f) {
    cout << "Sign:     " << sign << '\n';
    cout << "Exponent: 00000000\n";
    cout << "Mantissa: 00000000000000000000000\n";
    cout << "IEEE 754: " << sign << " 00000000 "
         << "00000000000000000000000\n";
    return;
  }
  int intergerpart = static_cast<int>(absoluteValue);

  float fractionalPart = absoluteValue - intergerpart;
  string binaryInteger = Unsigned_To_Binary(intergerpart);
  string binaryFraction;
  for (int i = 0; i < 150; ++i) {
    fractionalPart *= 2.0f;

    if (fractionalPart >= 1.0f) {
      binaryFraction.push_back('1');
      fractionalPart -= 1.0f;
    } else {
      binaryFraction.push_back('0');
    }
  }

  int realExponent;
  string mantissaSource;
    if (intergerpart != 0) {
        // Ví dụ: 101.1 → 1.011 × 2^2
        realExponent =
        // Lấy số K = length của binaryInteger - 1
            static_cast<int>(binaryInteger.length()) - 1;
        // Mantissa = phần sau dấu chấm của binaryInteger + binaryFraction
        mantissaSource =
            binaryInteger.substr(1) + binaryFraction;
    } else {
        // Ví dụ: 0.00101 → 1.01 × 2^-3
        size_t firstOne = binaryFraction.find('1');

        if (firstOne == string::npos) {
            cout << "Khong tim thay bit 1\n";
            return;
        }
        // số mũ thực = - (vị trí bit 1 đầu tiên + 1)
        realExponent =
            -static_cast<int>(firstOne) - 1;

        mantissaSource =
            binaryFraction.substr(firstOne + 1);
    }

}