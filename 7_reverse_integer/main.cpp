#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

int reverse1(int x) 
{
    // Convert from 2's complement
    const int sign = (x & (1 << 31)) ? -1 : 1;
    const int absVal = abs(x);

    char intStr[11];
    sprintf(intStr, "%ld", absVal);
    int len = strlen(intStr);
    char reverseIntStr[11] = { 0 };
    
    for (int i = 0; i < len; i++)
    {
        reverseIntStr[len - i - 1] = intStr[i];
    }

    double resultFloat = atof(reverseIntStr);
    if (resultFloat > 2147483647.0)
    {
        resultFloat = 0.0;
    }
    else
    {
        resultFloat *= sign;
    }

    return static_cast<int>(resultFloat);
}

int pow10(int pow)
{
    static constexpr int lut[10] = 
    {
        1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000
    };

    if ((pow >= 0) && (pow < sizeof(lut)))
    {
        return lut[pow];
    }
    else
    {
        throw invalid_argument("Argument out of range!");
    }   
}

bool IsValidIntDigits(vector<int>& digits)
{
    static constexpr int maxReversed[] = { 2, 1, 4, 7, 4, 8, 3, 6, 4, 7 };

    if (digits.size() > 10)
    {
        return false;
    }
    else if (digits.size() < 10)
    {
        return true;
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            if (digits[i] > maxReversed[i])
            {
                return false;
            }
            else if (digits[i] < maxReversed[i])
            {
                return true;
            }
        }
    }

    return true;
}

int reverse2(int x) 
{
    // Convert from 2's complement
    const int sign = (x & (1 << 31)) ? -1 : 1;
    int absVal = abs(x);

    vector<int> digits;
    while (absVal > 0)
    {
        digits.push_back(absVal % 10);
        absVal /= 10;
    }

    if (IsValidIntDigits(digits) == false)
    {
        return 0;
    }

    int output = 0;

    for (int i = 0; i < digits.size(); i++)
    {
        int powerOf10 = digits.size() - i - 1;
        
        output += (digits[i] * pow10(powerOf10));
    }

    return (output * sign);
}

int reverse3(int x)
{
    int reverse = 0;
    const int sign = (x < 0) ? -1 : 1;
    int absVal = abs(x);

    while (absVal != 0)
    {
        int digit = absVal % 10;
        absVal /= 10;
        if ((reverse > (INT_MAX / 10)) || ((reverse == (INT_MAX / 10)) && (digit > 7)))
        {
            return 0;
        }

        reverse *= 10;
        reverse += digit;
    }

    return (reverse * sign);
}

int main()
{
    cout << reverse3(321) << endl;
    cout << reverse3(-321) << endl;
    cout << reverse3(123450) << endl;
    cout << reverse3(2147483647) << endl;
    cout << reverse3(-2147483648) << endl;
    cout << reverse3(-2147483412) << endl;
    cout << reverse3(-1563847412) << endl;
}