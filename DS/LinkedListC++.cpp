#include <iostream>

struct Node{
    int data;
    Node *next;

    // constructor
    Node(int val){
        data = val;
        next = nullptr;
    }
};

Node *insertNode(Node *head, int val){
    Node *temp = new Node(val);
    if (!head){
        return temp;
    }
    Node *curr = head;
    while(curr->next){
        curr= curr->next;
    }
    curr->next = temp;
    return head;
}

Node *deleteNode(Node *head, int val){
    // when linked list is null
    if (!head) return head;

    // when first node contain data to delete
    if (head && head->data == val){
        Node *temp = head;
        head = head->next;
        delete temp;
        return head;
    }

    Node *curr = head, *prev=NULL;
    // search for the value to ve deleted, keeping track of the previous node
    while(curr && curr->data!=val){
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        printf("Node is not available to delete\n");
        return head;
    }

    prev->next = curr->next;
    delete curr;

    return head;
}

void printLinkedList(Node *head){
    printf("Linked List data: ");
    while(head){
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void freeLinkedListMemory(Node *head){
    Node *curr = head;
    while(curr){
        Node *temp = curr->next;
        delete curr;
        curr = temp;
    }
    std::cout<<"Linked List memory is free";
}

int main(){
    Node *head= NULL;
    head = insertNode(head, 1);
    head = insertNode(head, 1);
    head = insertNode(head, 2);
    head = insertNode(head, 3);
    head = insertNode(head, 3);
    head = insertNode(head, 4);
    head = insertNode(head, 5);
    head = insertNode(head, 5);
    head = insertNode(head, 3);
    printLinkedList(head);

    head = deleteNode(head, 3);
    printLinkedList(head);

    head = deleteNode(head, 5);
    printLinkedList(head);

    head = deleteNode(head, 1);
    printLinkedList(head);

    head = deleteNode(head, 10);
    printLinkedList(head);

    freeLinkedListMemory(head);
}






