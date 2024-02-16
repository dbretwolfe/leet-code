#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <list>
#include <unordered_map>
#include <algorithm>

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

// Find the minimum lexical value of the different ticket destinations.
int LexicalCompareItinerary(std::vector<std::string>& a, std::vector<std::string>& b)
{
    if ((a.empty() == true) || (a.size() != b.size())) {
        throw std::invalid_argument("Invalid inputs for lexical comparison!");
    }

    int compVal = 0;

    for (int i = 0; i < a.size(); i++) {
        compVal = a[i].compare(b[i]);
        if (compVal != 0) {
            break;
        }
    }

    return compVal;
}

std::vector<std::string>& ChooseItinerary(std::list<Itinerary>& itineraryList, int numTickets)
{
    if (itineraryList.empty() == true) {
        throw std::invalid_argument("Itinerary list is empty!");
    }
    else if (itineraryList.size() == 1) {
        return itineraryList.begin()->nodes;
    }

    auto lowestLexical = itineraryList.begin();
    auto it = itineraryList.begin();

    for (; it != itineraryList.end(); it++) {
        if (it->usedCount != numTickets) {
            continue;
        }

        if (lowestLexical->usedCount != numTickets) {
            lowestLexical = it;
        }
        else {
            int compVal = LexicalCompareItinerary(lowestLexical->nodes, it->nodes);
            lowestLexical = (compVal > 0) ? it : lowestLexical;
        }
    }

    return lowestLexical->nodes;
}

std::vector<std::string> findItinerary(std::vector<std::vector<std::string>>& tickets) 
{
    std::list<Itinerary> itineraryList = { Itinerary(tickets.size()) };

    while (1) {
        int passCount = 0;
        auto it = itineraryList.begin();

        while(it != itineraryList.end()) {
            std::vector<int> nextTickets = GetNextTickets(*it, tickets);

            // If there are no ticket matches, increment the pass count and continue.
            // If this itinerary runs out of ticket combinations before using all tickets, remove it from the list.
            if (nextTickets.empty() == true) {
                if (it->usedCount < tickets.size()) {
                    auto temp = it;
                    it++;
                    itineraryList.erase(temp);
                }
                else {
                    passCount++;
                    it++;
                }
            }
            // If there is one ticket match, add that ticket to the current itinerary.
            // If there are more than one matches, copy the current itinerary for each match and
            // add the match to the end of the copy.
            else {
                // Create any copies before modifying the current itinerary.
                for (int j = 1 ; j < nextTickets.size(); j ++) {
                    Itinerary newItinerary(*it);
                    itineraryList.push_back(newItinerary);
                    AddNextDestination(itineraryList.back(), tickets, nextTickets[j]);
                }

                // Add the first match to the current itenerary. 
                AddNextDestination(*it, tickets, nextTickets[0]);
            }
        }

        // If none of the itineraries had any remaining matches, break the loop.
        if (passCount == itineraryList.size())
        {
            break;
        }
    } 

    return ChooseItinerary(itineraryList, tickets.size());
}

int GetNextTicketRecursive(
    std::string &from, 
    std::unordered_map<std::string, std::vector<std::string>> &ticketMap, 
    std::vector<std::string> &answer, 
    int numTickets)
{
    // If the answer already contains the maximum number of stops, return 1.
    if(answer.size() == (numTickets + 1)) {
        return 1;
    }

    // Given the current "from" location, investigate each possible "to" destination.
    for(int i = 0; i < ticketMap[from].size(); i++){
        std::string to = ticketMap[from][i];

        // If this destination was already used, try the next.
        if(to == "$$$") {
            continue;
        }

        // Otherwise, mark this destination as visited.
        ticketMap[from][i] = "$$$";
        answer.push_back(to);

        // Check whether by using this ticket next we are ultimately able to use every ticket.
        if( GetNextTicketRecursive(to, ticketMap, answer, numTickets) ) return 1;
        else{
            ticketMap[from][i] = to; // backtrack
            answer.pop_back();
        }
    }

    return 0;
}

std::vector<std::string> findItinerary1(std::vector<std::vector<std::string>>& tickets) 
{
    std::unordered_map<std::string, std::vector<std::string>> ticketMap;
    std::vector<std::string> answer;
    std::string start = "JFK";

    // Add all tickets to the map.
    for(auto ticket : tickets ) {
        ticketMap[ticket[0]].push_back(ticket[1]);
    }

    // Sort tickets by "to" in lexicographical order.
    for(auto &x : ticketMap){
        std::sort(x.second.begin(), x.second.end());
    }

    answer.push_back(start);
    GetNextTicketRecursive(start, ticketMap, answer, tickets.size());
    return answer;
}

int main()
{
    std::vector<std::vector<std::string>> tickets0 = { {"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"} };
    std::vector<std::vector<std::string>> tickets1 = { {"JFK","SFO"}, {"JFK","ATL"}, {"SFO","ATL"}, {"ATL","JFK"}, {"ATL","SFO"} };
    std::vector<std::vector<std::string>> tickets2 = { {"JFK","KUL"}, {"JFK","NRT"}, {"NRT","JFK"} };
    std::vector<std::vector<std::string>> tickets3 = { {"EZE","TIA"},{"EZE","HBA"},{"AXA","TIA"},{"JFK","AXA"},{"ANU","JFK"},{"ADL","ANU"},{"TIA","AUA"},{"ANU","AUA"},{"ADL","EZE"},{"ADL","EZE"},{"EZE","ADL"},{"AXA","EZE"},{"AUA","AXA"},{"JFK","AXA"},{"AXA","AUA"},{"AUA","ADL"},{"ANU","EZE"},{"TIA","ADL"},{"EZE","ANU"},{"AUA","ANU"} };
    std::vector<std::vector<std::string>> tickets4 = { {"AXA","EZE"},{"EZE","AUA"},{"ADL","JFK"},{"ADL","TIA"},{"AUA","AXA"},{"EZE","TIA"},{"EZE","TIA"},{"AXA","EZE"},{"EZE","ADL"},{"ANU","EZE"},{"TIA","EZE"},{"JFK","ADL"},{"AUA","JFK"},{"JFK","EZE"},{"EZE","ANU"},{"ADL","AUA"},{"ANU","AXA"},{"AXA","ADL"},{"AUA","JFK"},{"EZE","ADL"},{"ANU","TIA"},{"AUA","JFK"},{"TIA","JFK"},{"EZE","AUA"},{"AXA","EZE"},{"AUA","ANU"},{"ADL","AXA"},{"EZE","ADL"},{"AUA","ANU"},{"AXA","EZE"},{"TIA","AUA"},{"AXA","EZE"},{"AUA","SYD"},{"ADL","JFK"},{"EZE","AUA"},{"ADL","ANU"},{"AUA","TIA"},{"ADL","EZE"},{"TIA","JFK"},{"AXA","ANU"},{"JFK","AXA"},{"JFK","ADL"},{"ADL","EZE"},{"AXA","TIA"},{"JFK","AUA"},{"ADL","EZE"},{"JFK","ADL"},{"ADL","AXA"},{"TIA","AUA"},{"AXA","JFK"},{"ADL","AUA"},{"TIA","JFK"},{"JFK","ADL"},{"JFK","ADL"},{"ANU","AXA"},{"TIA","AXA"},{"EZE","JFK"},{"EZE","AXA"},{"ADL","TIA"},{"JFK","AUA"},{"TIA","EZE"},{"EZE","ADL"},{"JFK","ANU"},{"TIA","AUA"},{"EZE","ADL"},{"ADL","JFK"},{"ANU","AXA"},{"AUA","AXA"},{"ANU","EZE"},{"ADL","AXA"},{"ANU","AXA"},{"TIA","ADL"},{"JFK","ADL"},{"JFK","TIA"},{"AUA","ADL"},{"AUA","TIA"},{"TIA","JFK"},{"EZE","JFK"},{"AUA","ADL"},{"ADL","AUA"},{"EZE","ANU"},{"ADL","ANU"},{"AUA","AXA"},{"AXA","TIA"},{"AXA","TIA"},{"ADL","AXA"},{"EZE","AXA"},{"AXA","JFK"},{"JFK","AUA"},{"ANU","ADL"},{"AXA","TIA"},{"ANU","AUA"},{"JFK","EZE"},{"AXA","ADL"},{"TIA","EZE"},{"JFK","AXA"},{"AXA","ADL"},{"EZE","AUA"},{"AXA","ANU"},{"ADL","EZE"},{"AUA","EZE"}};
    std::vector<std::string>& itinerary = findItinerary1(tickets1);

    std::cout << "itinerary: ";
    for (auto stop : itinerary) {
        std::cout << stop << " ";
    }
    std::cout << std::endl;
}