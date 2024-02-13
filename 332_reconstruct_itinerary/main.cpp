#include <iostream>
#include <vector>
#include <string>

void AddNextDestination(
    std::vector<std::string>& itenerary, 
    std::vector<std::vector<std::string>>& tickets,
    int ticketNum,
    std::vector<bool>& used,
    int& usedCount
    )
{
    if (itenerary.empty()) {
        itenerary.push_back(tickets[ticketNum][0]);
        itenerary.push_back(tickets[ticketNum][1]);
    }
    else {
        itenerary.push_back(tickets[ticketNum][1]);
    }

    used[ticketNum] = true;
    usedCount++;
}

// Find the minimum lexical value of the different ticket destinations.
int ChooseTicket(std::vector<std::vector<std::string>>& tickets, std::vector<int> ticketNums)
{
    int ticket = (ticketNums.empty() == true) ? -1 : ticketNums[0];

    for (int i : ticketNums) {
        int compVal = tickets[i][1].compare(tickets[ticket][1]);
        if (compVal < 0) {
            ticket = i;
        }
    }

    return ticket;
}

int GetNextTicket(
    std::vector<std::string>& itenerary, 
    std::vector<std::vector<std::string>>& tickets, 
    std::vector<bool>& used
    )
{
    std::vector<int> nextTickets;

    for (int i = 0; i < tickets.size(); i++) {
        if (used[i] == true){
            continue;
        }
        else if (itenerary.empty()) {
            if (tickets[i][0] == "JFK") {
                nextTickets.push_back(i);
            }
        }
        else if (itenerary[itenerary.size() - 1] == tickets[i][0]) {
            nextTickets.push_back(i);
        }
    }
    
    if (nextTickets.empty() == true) {
        return -1;
    }
    else if (nextTickets.size() == 1) {
        return nextTickets[0];
    }
    else {
        return ChooseTicket(tickets, nextTickets);
    }
}

std::vector<std::string> findItinerary(std::vector<std::vector<std::string>>& tickets) 
{
    std::vector<std::string> itenerary;
    std::vector<bool> used(tickets.size());
    int usedCount = 0;

    while (usedCount < tickets.size()) {
        int nextTicket = GetNextTicket(itenerary, tickets, used);
        if (nextTicket < 0)
        {
            break;
        }
        
        AddNextDestination(itenerary, tickets, nextTicket, used, usedCount);
    }

    return itenerary;
}

int main()
{
    std::vector<std::vector<std::string>> tickets0 = { {"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"} };
    std::vector<std::vector<std::string>> tickets1 = { {"JFK","SFO"}, {"JFK","ATL"}, {"SFO","ATL"}, {"ATL","JFK"}, {"ATL","SFO"} };
    std::vector<std::string>& itenerary = findItinerary(tickets1);

    std::cout << "Itenerary: ";
    for (auto stop : itenerary) {
        std::cout << stop << " ";
    }
    std::cout << std::endl;
}