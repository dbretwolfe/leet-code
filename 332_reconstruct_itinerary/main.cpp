#include <iostream>
#include <vector>

void AddNextDestination(
    std::vector<std::string>& itenerary, 
    std::vector<std::vector<std::string>>& tickets, 
    std::vector<bool> used,
    int& usedCount)
{
    for (int i = 0; i < tickets.size(); i++) {
        if (used[i] == true){
            continue;
        }
        else if (itenerary.empty()) {
            if (tickets[i][0] == "JFK") {
                itenerary.push_back(tickets[i][0]);
                itenerary.push_back(tickets[i][1]);
                used[i] = true;
                usedCount++;
            }
        }
        else if (itenerary[itenerary.size() - 1] == tickets[i][0]) {
            itenerary.push_back(tickets[i][1]);
            used[i] = true;
            usedCount++;
        }
    }
}

std::vector<std::string> findItinerary(std::vector<std::vector<std::string>>& tickets) 
{
    std::vector<std::string> itenerary;
    std::vector<bool> used(tickets.size());
    int usedCount = 0;

    while (usedCount < tickets.size()) {
        AddNextDestination(itenerary, tickets, used, usedCount);
    }

    return itenerary;
}

int main()
{
    std::vector<std::vector<std::string>> tickets = { {"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"} };
    std::vector<std::string>& itenerary = findItinerary(tickets);

    std::cout << "Itenerary: ";
    for (auto stop : itenerary) {
        std::cout << stop << " ";
    }
    std::cout << std::endl;

}