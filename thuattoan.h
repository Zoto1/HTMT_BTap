#pragma once
using namespace std;

#include <string>
string Int_To_Binary(int x); // Nhap so nguyen 4 byte -> binary 32 bits
pair<string, char> Add_8bits_Binary(string a, string b);
string Sub_8bits_Binary(string a, string b);
string Convert_To_2s_Complement(string a);
string Mul_8bits_Binary(string a, string b);