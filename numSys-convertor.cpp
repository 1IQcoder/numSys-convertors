#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

short* strToNum(string &str, int strlen);
int toDec(short* numarr, int arrlen, int fsys);
string fromDec(int num, int tsys);

int main()
{
	short fsys;
    short tsys;
    int inputnumInt;
    string inputnumStr;
    string result;
    
	bool exit = false;
	
	while(!exit)
	{
        cout << endl << "0 - exit" << endl;
        cout << "\n===========================\n" << "FROM system: ";
        cin >> fsys;
        if(!fsys)
	    {
            cout << "PORGRAM FINISHED";
            break;
        }
        cout << "TO system: ";
        cin >> tsys;

        cout << "Number: ";
        if (fsys < 11) {
            cin >> inputnumInt;
            result = fromDec(inputnumInt, tsys);
        } else {
            cin >> inputnumStr;
            string& numref = inputnumStr;
            int strlen = inputnumStr.length();
            short* numarr = strToNum(numref, strlen);
            int decnum = toDec(numarr, strlen, fsys);
            result = fromDec(decnum, tsys);
        }
        reverse(result.begin(), result.end());
        cout << "RESULT: " << result << "\n===========================\n";
	}
    return 0;
}

// ascii A => int 65
// Z => 90
// 0 => 48
// 9 => 57
short* strToNum(string &str, int strlen)
{
    short* numarr = new short[strlen] {};
    for(int i = 0; i < strlen; i++)
    {
        int asciiInt = static_cast<int>(str[i]);
        if (asciiInt > 47 && asciiInt < 58) {
            // цифра
            numarr[i] = asciiInt-48;
        } else if (asciiInt > 64 && asciiInt < 91) {
            // буква
            numarr[i] = asciiInt-65+10;
        }
    }
    return numarr;
}

int toDec(short* numarr, int arrlen, int fsys)
{
    int res = 0;
    short x = 0;
    for(short i = arrlen-1; i >= 0; i--)
    {
        res += numarr[i] * pow(fsys, x);
        x++;
    }
    delete[] numarr;
    return res;
}

string fromDec(int num, int tsys)
{
    int ost = num;
    string res;
    short i = 0;

    do {
        ost = num % tsys;
        if (ost > 9) {
            // буква
            res += static_cast<char>(ost+65-10);
        } else {
            // цифра
            res += static_cast<char>(ost+48);
        }
        num /= tsys;
        i++;
    } while(num != 0);

    return res;
}