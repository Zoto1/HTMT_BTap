#include "thuattoan.h"
#include <algorithm> // for std::reverse
#include <charconv>
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
  string res = "";
  char carry = '0';
  for (int i = 7; i >= 0; i--) {
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
      carry = '0' ;
      res.push_back('1');
    };
  }
  reverse(res.begin(), res.end());
  return std::make_pair(res, carry);
}
string Convert_To_2s_Complement(string a) {
  // Y tuong thuat toan : đảo bits sau đó + 1 ử bit cuối
  for (int i = 0; i < 8; i++) {
    if (a[i] == '0')
      a[i] = '1';
    else if (a[i] == '1')
      a[i] = '0';
  }
  a = Add_8bits_Binary(a, "00000001").first;
  return a;
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
  char C = '0';            // C
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

  return A+b;
}