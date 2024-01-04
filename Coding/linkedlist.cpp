#include<bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node* next;
};

void InsertInFrontLinkedList(Node* &headNode, int data) {
	Node* newNode = new Node();
	newNode->data = data;
	newNode->next = headNode;
	headNode = newNode;
}

void InsertInBackLinkedList(Node* &headNode, int value) {
	Node* newNode = new Node();
	newNode->data = value;
	newNode->next = NULL;
	if(headNode == NULL) {
		headNode = newNode;
		return;
	}
	Node* tempNode = headNode;
	while (tempNode->next != NULL) {
		tempNode = tempNode->next;
	}
	tempNode->next = newNode;
}

void PrintLinkedList(Node* headNode) {
    while(headNode != NULL) {
        cout << headNode->data << " ";
        headNode = headNode->next;
    }
    cout << "\n";
}

void InsertAtNthPos(Node* &headNode, int value, int n) {
	Node* newNode = new Node();
	newNode->data = value;
	newNode->next = NULL;
	Node* tempNode = headNode;
	Node* prevPtr = NULL;
	int i = 0;
	for(i = 0; i < n; i++) {
		if(tempNode != NULL) {
			prevPtr = tempNode;
			tempNode = tempNode->next;
		} else {
			break;
		}
	}
	if(i < n) {
		cout << "Invalid input n : " << n << "\n";
		return;
	}
	if(prevPtr == NULL) {
		newNode->next = headNode;
		headNode = newNode;
		return;
	}
	prevPtr->next = newNode;
	newNode->next = tempNode;
}

void reverseLinkedList(Node* &headNode) {
	Node* curr = headNode;
	Node* nxt = curr;
	Node* prev = NULL;
	while(curr != NULL) {
		nxt = curr->next;
		curr->next = prev;
		prev = curr;
		curr = nxt;
	}
	headNode = prev;
}

void recursiveReverseLinkedList(Node* &headNode, Node* n) {
	if(n->next == NULL) {
		headNode = n;
		return;
	}
	recursiveReverseLinkedList(headNode, n->next);
	Node* m = n->next;
	m->next = n;
	n->next = NULL;
}

int main() {
    Node* headNode = NULL;
	InsertInBackLinkedList(headNode, 1);
    PrintLinkedList(headNode);
    InsertInBackLinkedList(headNode, 2);
    PrintLinkedList(headNode);
    InsertInBackLinkedList(headNode, 3);
    PrintLinkedList(headNode);
	InsertInFrontLinkedList(headNode, 4);
	PrintLinkedList(headNode);
	InsertInFrontLinkedList(headNode, 5);
	PrintLinkedList(headNode);
	InsertInFrontLinkedList(headNode, 6);
	PrintLinkedList(headNode);
	InsertAtNthPos(headNode, 100, 10);
	PrintLinkedList(headNode);
	reverseLinkedList(headNode);
	PrintLinkedList(headNode);
	InsertInFrontLinkedList(headNode, 7);
	PrintLinkedList(headNode);
	reverseLinkedList(headNode);
	PrintLinkedList(headNode);
	recursiveReverseLinkedList(headNode, headNode);
	PrintLinkedList(headNode);
	InsertInFrontLinkedList(headNode, 8);
	PrintLinkedList(headNode);
	recursiveReverseLinkedList(headNode, headNode);
	PrintLinkedList(headNode);
    return 0;
}
