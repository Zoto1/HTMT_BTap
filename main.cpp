#include "thuattoan.h"

#include <iostream>
#include <string>
#include <utility>

using namespace std;

int passed = 0;
int failed = 0;

void Check(const string& testName,
           const string& actual,
           const string& expected) {
    if (actual == expected) {
        cout << "[PASS] " << testName << '\n';
        ++passed;
    } else {
        cout << "[FAIL] " << testName << '\n';
        cout << "       Expected: " << expected << '\n';
        cout << "       Actual:   " << actual << '\n';
        ++failed;
    }
}

void CheckAdd(const string& testName,
              const pair<string, char>& actual,
              const string& expectedSum,
              char expectedCarry) {
    if (actual.first == expectedSum &&
        actual.second == expectedCarry) {
        cout << "[PASS] " << testName << '\n';
        ++passed;
    } else {
        cout << "[FAIL] " << testName << '\n';
        cout << "       Expected sum:   " << expectedSum << '\n';
        cout << "       Actual sum:     " << actual.first << '\n';
        cout << "       Expected carry: " << expectedCarry << '\n';
        cout << "       Actual carry:   " << actual.second << '\n';
        ++failed;
    }
}

int main() {
    cout << "===== TEST Int_To_Binary =====\n";

    Check(
        "Int_To_Binary(0)",
        Int_To_Binary(0),
        "00000000000000000000000000000000"
    );

    Check(
        "Int_To_Binary(1)",
        Int_To_Binary(1),
        "00000000000000000000000000000001"
    );

    Check(
        "Int_To_Binary(5)",
        Int_To_Binary(5),
        "00000000000000000000000000000101"
    );

    Check(
        "Int_To_Binary(-1)",
        Int_To_Binary(-1),
        "11111111111111111111111111111111"
    );

    Check(
        "Int_To_Binary(-2)",
        Int_To_Binary(-2),
        "11111111111111111111111111111110"
    );

    cout << "\n===== TEST Add_8bits_Binary =====\n";

    CheckAdd(
        "5 + 3 = 8",
        Add_8bits_Binary("00000101", "00000011"),
        "00001000",
        '0'
    );

    CheckAdd(
        "255 + 1 = 0, carry 1",
        Add_8bits_Binary("11111111", "00000001"),
        "00000000",
        '1'
    );

    CheckAdd(
        "128 + 128 = 0, carry 1",
        Add_8bits_Binary("10000000", "10000000"),
        "00000000",
        '1'
    );

    CheckAdd(
        "170 + 85 = 255",
        Add_8bits_Binary("10101010", "01010101"),
        "11111111",
        '0'
    );

    cout << "\n===== TEST Convert_To_2s_Complement =====\n";

    Check(
        "Bu 2 cua 3",
        Convert_To_2s_Complement("00000011"),
        "11111101"
    );

    Check(
        "Bu 2 cua 1",
        Convert_To_2s_Complement("00000001"),
        "11111111"
    );

    Check(
        "Bu 2 cua 0",
        Convert_To_2s_Complement("00000000"),
        "00000000"
    );

    Check(
        "Bu 2 cua 128",
        Convert_To_2s_Complement("10000000"),
        "10000000"
    );

    cout << "\n===== TEST Sub_8bits_Binary =====\n";

    Check(
        "5 - 3 = 2",
        Sub_8bits_Binary("00000101", "00000011"),
        "00000010"
    );

    Check(
        "3 - 5 = -2",
        Sub_8bits_Binary("00000011", "00000101"),
        "11111110"
    );

    Check(
        "0 - 1 = -1",
        Sub_8bits_Binary("00000000", "00000001"),
        "11111111"
    );

    Check(
        "255 - 255 = 0",
        Sub_8bits_Binary("11111111", "11111111"),
        "00000000"
    );

    cout << "\n===== TEST Mul_8bits_Binary =====\n";

    Check(
        "5 * 3 = 15",
        Mul_8bits_Binary("00000101", "00000011"),
        "0000000000001111"
    );

    Check(
        "255 * 2 = 510",
        Mul_8bits_Binary("11111111", "00000010"),
        "0000000111111110"
    );

    Check(
        "255 * 255 = 65025",
        Mul_8bits_Binary("11111111", "11111111"),
        "1111111000000001"
    );

    Check(
        "128 * 2 = 256",
        Mul_8bits_Binary("10000000", "00000010"),
        "0000000100000000"
    );

    Check(
        "0 * 255 = 0",
        Mul_8bits_Binary("00000000", "11111111"),
        "0000000000000000"
    );

    Check(
        "1 * 255 = 255",
        Mul_8bits_Binary("00000001", "11111111"),
        "0000000011111111"
    );
    Check(
    "Divide 1 by 1",
    Div_8bits_Binary("00000001", "00000001").second,
    "00000001"
);

Check(
    "Divide 30 by 5",
    Div_8bits_Binary("00011110", "00000101").second,
    "00000110"
);

Check(
    "Divide 255 by 2",
    Div_8bits_Binary("11111111", "00000010").second,
    "01111111"
);
    cout << "\n===== KET QUA =====\n";
    cout << "Passed: " << passed << '\n';
    cout << "Failed: " << failed << '\n';

    return failed == 0 ? 0 : 1;
}