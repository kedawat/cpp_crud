#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *next;
};

struct Node * newNode(int value){
    struct Node *temp = (struct Node *) malloc(sizeof (struct Node));
    temp->data = value;
    temp->next = NULL;
    return temp;
}

struct Node *insertNode(struct Node *head, int val){
    struct Node *temp = newNode(val);
    if (!head){
        return temp;
    }
    struct Node *curr = head;
    while(curr->next){
        curr= curr->next;
    }
    curr->next = temp;
    return head;
}

struct Node *deleteNode(struct Node *head, int val){
    // when linked list is null
    if (!head) return head;

    // when first node contain data to delete
    if (head && head->data == val){
        struct Node *temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    struct Node *curr = head, *prev=NULL;
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
    free(curr);

    return head;
}

void printLinkedList(struct Node *head){
    printf("Linked List data: ");
    while(head){
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main(){
    struct Node *head= NULL;
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
}






