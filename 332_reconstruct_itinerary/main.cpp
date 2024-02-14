#include <iostream>
#include <vector>
#include <string>

class Itinerary
{
public:
    Itinerary(size_t numTickets) { used.resize(numTickets); }

    
    std::vector<std::string> nodes;
    std::vector<bool> used;
    int usedCount = 0;
};

// Append the destination of the next ticket to the itinerary.
void AddNextDestination(
    Itinerary& itinerary, 
    std::vector<std::vector<std::string>>& tickets,
    int nextTicket
    )
{
    if (itinerary.nodes.empty() == true) {
        itinerary.nodes.push_back(tickets[nextTicket][0]);
        itinerary.nodes.push_back(tickets[nextTicket][1]);
    }
    else {
        itinerary.nodes.push_back(tickets[nextTicket][1]);
    }

    itinerary.used[nextTicket] = true;
    itinerary.usedCount++;
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

// Find any tickets that will continue the itenerary.
std::vector<int> GetNextTickets(
    Itinerary& itinerary, 
    std::vector<std::vector<std::string>>& tickets
    )
{
    std::vector<int> nextTickets;

    for (int i = 0; i < tickets.size(); i++) {
        if (itinerary.used[i] == true){
            continue;
        }
        else if (itinerary.nodes.empty() == true) {
            if (tickets[i][0] == "JFK") {
                nextTickets.push_back(i);
            }
        }
        else if (itinerary.nodes[itinerary.nodes.size() - 1] == tickets[i][0]) {
            nextTickets.push_back(i);
        }
    }

    return nextTickets;
}

std::vector<std::string> findItinerary(std::vector<std::vector<std::string>>& tickets) 
{
    std::vector<Itinerary> itineraryList = { Itinerary(tickets.size()) };

    while (1) {
        int passCount = 0;
        for (int i = 0; i < itineraryList.size(); i++) {
            std::vector<int> nextTickets = GetNextTickets(itineraryList[i], tickets);

            // If there are no ticket matches, increment the pass count and continue.
            if (nextTickets.empty() == true) {
                passCount++;
                continue;
            }
            // If there is one ticket match, add that ticket to the current itinerary.
            // If there are more than one matches, copy the current itinerary for each match and
            // add the match to the end of the copy.
            else {
                // Create any copies before modifying the current itinerary.
                for (int j = 1 ; j < nextTickets.size(); j ++) {
                    Itinerary newItinerary(itineraryList[i]);
                    itineraryList.push_back(newItinerary);
                    AddNextDestination(itineraryList.back(), tickets, nextTickets[j]);
                }

                // Add the first match to the current itenerary. 
                AddNextDestination(itineraryList[i], tickets, nextTickets[0]);
            }
        }

        // If none of the itineraries had any remaining matches, break the loop.
        if (passCount == itineraryList.size())
        {
            break;
        }
    }   

    return std::vector<std::string>();
}

int main()
{
    std::vector<std::vector<std::string>> tickets0 = { {"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"} };
    std::vector<std::vector<std::string>> tickets1 = { {"JFK","SFO"}, {"JFK","ATL"}, {"SFO","ATL"}, {"ATL","JFK"}, {"ATL","SFO"} };
    std::vector<std::vector<std::string>> tickets2 = { {"JFK","KUL"}, {"JFK","NRT"}, {"NRT","JFK"} };
    std::vector<std::string>& itinerary = findItinerary(tickets2);

    std::cout << "itinerary: ";
    for (auto stop : itinerary) {
        std::cout << stop << " ";
    }
    std::cout << std::endl;
}