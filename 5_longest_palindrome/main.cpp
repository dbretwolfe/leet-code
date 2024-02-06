#include <string>
#include <cassert>
#include <iostream>

using namespace std;

size_t FindPalindromeLength(string& str, size_t& left, size_t& right) 
{
    while ((left > 0) && (right < (str.length() - 1))) 
    {
        if (str[left - 1] == str[right + 1]) 
        {
            left--;
            right++;
        }
        else {
            break;
        }
    }

    return (right - left + 1);
}

string longestPalindrome1(string s) 
{
    if ((s.length() == 0) || (s.length() == 1))
    {
        return s;
    }

    size_t left = 0;
    size_t right = 0;
    string longest = { s[0] };

    for (int i = 0; i < (s.length() - 1); i++) {
        left = i;
        right = i;
        size_t oddLen = FindPalindromeLength(s, left, right);
        longest = (oddLen > longest.length()) ? s.substr(left, oddLen) : longest;

        if (s[i] == s[i + 1])
        {
            left = i;
            right = i + 1;
            size_t evenLen = FindPalindromeLength(s, left, right);
            longest = (evenLen > longest.length()) ? s.substr(left, evenLen) : longest;
        }
    }

    return longest;
}

int main() 
{
    cout << longestPalindrome1("babad") << endl;
    cout << longestPalindrome1("cbbd") << endl;
    cout << longestPalindrome1("BBBB") << endl;
    cout << longestPalindrome1("aaaaa") << endl;
    cout << longestPalindrome1("s") << endl;
    cout << longestPalindrome1("ab") << endl;
    cout << longestPalindrome1("aaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffgggggggggghhhhhhhhhhiiiiiiiiiijjjjjjjjjjkkkkkkkkkkllllllllllmmmmmmmmmmnnnnnnnnnnooooooooooppppppppppqqqqqqqqqqrrrrrrrrrrssssssssssttttttttttuuuuuuuuuuvvvvvvvvvvwwwwwwwwwwxxxxxxxxxxyyyyyyyyyyzzzzzzzzzzyyyyyyyyyyxxxxxxxxxxwwwwwwwwwwvvvvvvvvvvuuuuuuuuuuttttttttttssssssssssrrrrrrrrrrqqqqqqqqqqppppppppppoooooooooonnnnnnnnnnmmmmmmmmmmllllllllllkkkkkkkkkkjjjjjjjjjjiiiiiiiiiihhhhhhhhhhggggggggggffffffffffeeeeeeeeeeddddddddddccccccccccbbbbbbbbbbaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffgggggggggghhhhhhhhhhiiiiiiiiiijjjjjjjjjjkkkkkkkkkkllllllllllmmmmmmmmmmnnnnnnnnnnooooooooooppppppppppqqqqqqqqqqrrrrrrrrrrssssssssssttttttttttuuuuuuuuuuvvvvvvvvvvwwwwwwwwwwxxxxxxxxxxyyyyyyyyyyzzzzzzzzzzyyyyyyyyyyxxxxxxxxxxwwwwwwwwwwvvvvvvvvvvuuuuuuuuuuttttttttttssssssssssrrrrrrrrrrqqqqqqqqqqppppppppppoooooooooonnnnnnnnnnmmmmmmmmmmllllllllllkkkkkkkkkkjjjjjjjjjjiiiiiiiiiihhhhhhhhhhggggggggggffffffffffeeeeeeeeeeddddddddddccccccccccbbbbbbbbbbaaaa") << endl;
}