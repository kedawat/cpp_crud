#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;

    Node (int val){
        data = val;
        next = nullptr;
    }
};


class LinkedList{
    private:
        Node *head;

    public:
        LinkedList(): head(nullptr) {}
        ~LinkedList();

        void insertNode(int val);
        void deleteNode(int val);
        void printLinkedList();
};

LinkedList::~LinkedList(){
    Node *curr = head;
    while(curr){
        Node *temp = curr->next;
        delete curr;
        curr = temp;
    }
    cout<<"Linked List destructor"<<endl;
}

void LinkedList::insertNode(int val){
    Node *temp = new Node(val);
    if (!head){
        head = temp;
        return;
    }
    Node *curr = head;
    while(curr->next){
        curr= curr->next;
    }
    curr->next = temp;
}

void LinkedList::deleteNode(int val){
    // when linked list is null
    if (!head){
        cout<<"Linked list is empty, can't delete";
        return;
    }

    // when first node contain data to delete
    if (head && head->data == val){
        Node *temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node *curr = head, *prev=NULL;
    // search for the value to ve deleted, keeping track of the previous node
    while(curr && curr->data!=val){
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        printf("Node is not available to delete\n");
        return;
    }

    prev->next = curr->next;
    delete curr;
}

void LinkedList::printLinkedList(){
    cout<<"Linked List data: ";
    Node *curr = head;
    while(curr){
        cout<< curr->data<<" ";
        curr = curr->next;
    }
    printf("\n");
}

int main(){
    LinkedList list;
    list.insertNode(1);
    list.insertNode(1);
    list.insertNode(2);
    list.insertNode(3);
    list.insertNode(3);
    list.insertNode(4);
    list.insertNode(5);
    list.insertNode(5);
    
    list.printLinkedList();

    list.deleteNode(3);
    list.printLinkedList();

    list.deleteNode(5);
    list.printLinkedList();

    list.deleteNode(1);
    list.printLinkedList();
}
