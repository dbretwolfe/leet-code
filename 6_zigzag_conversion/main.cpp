#include <iostream>

using namespace std;

string GetSpaceString(size_t len)
{
    string temp;
    for (int i = 0; i < len; i ++)
    {
        temp.push_back(' ');
    }

    return temp;
}

string convert1(string s, int numRows) 
{
    size_t stringIndex = 0;
    
    size_t lettersPerZigZag = max(((2 * numRows) - 2), 1);
    size_t charsPerZig = max(lettersPerZigZag, (size_t)2);
    size_t numZigs = s.length() / lettersPerZigZag;
    string spaceString = GetSpaceString(numRows);

    string output;

    for (int row = 0; row < numRows; row++)
    {
        for (int zigZag = 0; zigZag <= numZigs; zigZag++)
        {
            string temp = GetSpaceString(charsPerZig);
            
            // Print the first character in the row.
            stringIndex = (lettersPerZigZag * zigZag) + row;
            if (stringIndex < s.length())
            {
                temp[0] = s[stringIndex];
            }
            
            // If this is a middle row, print the additional character.
            if ((row != 0) && (row != numRows - 1))
            {
                stringIndex = ((zigZag + 1) * lettersPerZigZag) - row;
                if (stringIndex < s.length())
                {
                    size_t column = 2 * (numRows - (row + 1));
                    temp[column] = s[stringIndex];
                }
            }

            output += temp;
        }
        output += '\n';
    }

    return output;
}

string convert2(string s, int numRows) 
{
    size_t stringIndex = 0;
    
    size_t lettersPerZigZag = max(((2 * numRows) - 2), 1);
    size_t numZigs = s.length() / lettersPerZigZag;

    string output;

    for (int row = 0; row < numRows; row++)
    {
        for (int zigZag = 0; zigZag <= numZigs; zigZag++)
        {
            // Print the first character in the row.
            stringIndex = (lettersPerZigZag * zigZag) + row;
            if (stringIndex < s.length())
            {
                output += s[stringIndex];
            }
            
            // If this is a middle row, print the additional character.
            if ((row != 0) && (row != numRows - 1))
            {
                stringIndex = ((zigZag + 1) * lettersPerZigZag) - row;
                if (stringIndex < s.length())
                {
                    output += s[stringIndex];
                }
            }
        }
    }

    return output;
}

int main()
{
    cout << convert2("PAYPALISHIRING", 1) << endl;
    cout << convert2("PAYPALISHIRING", 2) << endl;
    cout << convert2("PAYPALISHIRING", 3) << endl;
    cout << convert2("PAYPALISHIRING", 4) << endl;
    cout << convert2("A", 1) << endl;
    cout << convert2("A", 4) << endl;
}