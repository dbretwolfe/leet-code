#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* node0 = l1;
    ListNode* node1 = l2;
    ListNode dummyHead;
    ListNode* outputNode = &dummyHead;
    int carry = 0;

    while (1) {
        // Check for null nodes and do the addition.
        if ((node0 == nullptr) && (node1 == nullptr) && (carry == 0)) {
            break;
        }
        else {
            int x = node0 ? node0->val : 0;
            int y = node1 ? node1->val : 0;

            int sum = (x + y + carry);

            if (sum > 9) {
                outputNode->next = new ListNode(sum % 10);
                carry = 1;
            }
            else {
                outputNode->next = new ListNode(sum);
                carry = 0;
            }

            node0 = node0 ? node0->next : node0;
            node1 = node1 ? node1->next : node1;
            outputNode = outputNode->next;
        }
    }

    return dummyHead.next;
};

void PrintList(ListNode* list) {
    ListNode* node = list;

    cout << "Output: ";

    while (node != nullptr) {
        cout << node->val;
        node = node->next;
    };

    cout << endl;
}

int main() {
    ListNode list0[4] = {
        ListNode(9, &list0[1]),
        ListNode(9, &list0[2]),
        ListNode(9, nullptr)
    };

    ListNode list1[3] = {
        ListNode(9, &list1[1]),
        ListNode(9, &list1[2]),
        ListNode(9, nullptr)
    };

    ListNode* sum = addTwoNumbers(list0, list1);
    PrintList(sum);
}

