#include <vector>
#include <exception>
#include <string>

class Master
{
public:
    Master(std::vector<std::string> words, std::string secret) : words(words), _secret(secret)
    {
        if (secret.length() != 6)
        {
            throw std::invalid_argument("Invalid secret length!");
        }

        if (words.empty() == true)
        {
            throw std::invalid_argument("Empty word list!");
        }

        if (IsInWordList(secret) == false)
        {
            throw std::invalid_argument("Secret is not in word list!");
        }
    }

    int guess(std::string word)
    {
        if ((IsInWordList(word) == false) || (word.length() != 6))
        {
            return -1;
        }

        int correct = 0;

        if (word.compare(_secret) == 0)
        {
            return 6;
        }
        else
        {
            for (int i = 0; i < 6; i++)
            {
                correct = (word[i] == _secret[i]) ? correct + 1 : correct;
            }
        }

        return correct;
    }

    std::vector<std::string> words;

private:
    bool IsInWordList(std::string word)
    {
        for (std::string s : words)
        {
            if (s == word)
            {
                return true;
            }
        }

        return false;
    }

    const std::string _secret;
};