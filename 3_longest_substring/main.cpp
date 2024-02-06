#include <string>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <iostream>

using namespace std;

int lengthOfLongestSubstring1(string s) {
    int longestLength = 0;
    string longestSubstring;

    int startIndex = 0;
    int searchIndex = 0;

    bitset<128> charList = 0;
    int length = 0;

    while (searchIndex < s.length())
    {
        if (charList[s[searchIndex]] != 1) {
            charList[s[searchIndex]] = 1;
            searchIndex++;
        }
        else {
            charList = 0;
            length = (searchIndex - startIndex);
            if (length > longestLength)
            {
                longestLength = length;
                longestSubstring = s.substr(startIndex, length);
            }

            startIndex++;
            searchIndex = startIndex;
        }
    }

    // Handle the case where end of string was reached without finding a duplicate character.
    if (startIndex != searchIndex) {
        length = (searchIndex - startIndex);
        if (length > longestLength)
        {
            longestLength = length;
            longestSubstring = s.substr(startIndex, length);
        }
    }

    cout << longestSubstring;

    return longestLength;
}

int lengthOfLongestSubstring2(string s) {
    unordered_map<char, int> charMap;

    int left = 0;
    int right = 0;
    int longestLength = 0;

    for (right = 0; right < s.length(); right++) {
        while (charMap.find(s[right]) != charMap.end()) {
            charMap.erase(s[left]);
            left++; 
        }
        
        charMap[s[right]] = 0;

        longestLength = max(longestLength, (right - left + 1));
    }

    return longestLength;
}

int lengthOfLongestSubstring3(string s) {
        // Initialize an unordered set to keep track of unique characters in the current substring.
        unordered_set<char> map;
        int mSize = 0;  // Initialize a variable to store the length of the longest substring without repeating characters.
        int i = 0, j = 0;

        // Iterate through the string using pointers 'i' and 'j'.
        while (j < s.size()) {
            // While the character at 'j' is already in the set,
            while (map.find(s[j]) != map.end()) {
                // Remove the character at 'i' from the set and move 'i' to the right.
                map.erase(s[i]);
                ++i;
            }
            // Update 'mSize' with the maximum length of the current substring ('j - i + 1').
            mSize = max(mSize, j - i + 1);
            // Add the character at 'j' to the set.
            map.insert(s[j]);
            ++j;
        }

        // Return the final length of the longest substring without repeating characters.
        return mSize;
    }

int main()
{
    cout << lengthOfLongestSubstring2("anviaj") << endl;
    cout << lengthOfLongestSubstring2("bbbbb") << endl;
    cout << lengthOfLongestSubstring2("bbbbabcde") << endl;
    cout << lengthOfLongestSubstring2("abcabcbb") << endl;
    cout << lengthOfLongestSubstring2("pwwkew") << endl;
}