#include <iostream>

// Struct for individual Nodes
struct Node {
    int data;
    Node* next;

    // Constructor
    Node(int val) {
        data = val;
        next = nullptr;
    }
};

class CircularLinkedList{
    private:
        Node *head;
    
    public:
        CircularLinkedList();
        ~CircularLinkedList();
        
        void insertNode(int val);
        void deleteNode(int key);
        void printList();
};

CircularLinkedList::CircularLinkedList(){
    head = nullptr;
}

CircularLinkedList::~CircularLinkedList(){
    if (!head) return;

    Node *curr = head->next;
    while(curr != head){
        Node *nextNode  = curr->next;
        delete curr;
        curr = nextNode;
    }
    delete head;
    head = nullptr;
    std::cout<<"CircularLinkedList Destructor"<<std::endl;
}

void CircularLinkedList::insertNode(int val){
    Node *temp = new Node(val);
    if (!head) {
        head = temp;
        temp->next = head;
        return;
    }

    Node *curr = head;
    while(curr->next != head){
        curr = curr->next;
    }

    curr->next = temp;
    temp->next = head;
}

void CircularLinkedList::deleteNode(int key){
    if (!head){
        std::cout<<"Linked list is empty, can't delete"<<std::endl;
        return;
    }

    Node *curr=head, *prev=nullptr;
    if (curr->data == key){
        if (head->next == head){
            curr = head;
            head = nullptr;
            delete curr;
        }
        else{
            Node *last = head;
            while (last->next != head){
                last = last->next;
            }

            head = curr->next;
            last->next = curr->next;
            delete curr;
        }
    }
    else{
        while(curr->next!= head  && curr->data!=key){
            prev= curr;
            curr = curr->next;
        }

        if (curr->data == key){
            prev->next = curr->next;
            delete curr;
        }
        else{
            std::cout<<"key:"<<key<<"is not present in this list, can't delete"<<std::endl;
        }
    }
}

void CircularLinkedList::printList(){
    Node *curr=head;
    std::cout<<"Circular linked list data:";
    if (!head){
        std::cout<<"List is empty"<<std::endl;
        return;
    }

    while(curr->next != head){
        std::cout<<curr->data<<" ";
        curr = curr->next;
    }
    std::cout<<curr->data<<std::endl;
}


int main() {
    CircularLinkedList list;

    std::cout << "--- 1. Testing Insertion ---\n";
    list.insertNode(10);
    list.insertNode(20);
    list.insertNode(30);
    list.insertNode(40);
    list.printList();

    std::cout << "\n--- 2. Deleting Middle Node (20) ---\n";
    list.deleteNode(20);
    list.printList();

    std::cout << "\n--- 3. Deleting Head Node (10) ---\n";
    list.deleteNode(10);
    list.printList();

    return 0;
}