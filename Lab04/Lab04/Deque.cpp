#include "Deque.h"
#include <iostream>

using namespace std;

///------------------------------------------------------
/// Default constructor
/// 
Deque::Deque() { // Constructor
	DequeNode* head = NULL;
	DequeNode* tail = NULL;
	noOfItems = 0;
} //end-Deque

///------------------------------------------------------
/// Destructor
/// 
Deque::~Deque() { // Destructor, empties out the Deque
	while (head != NULL) {
		DequeNode* tempNode = head;
		head = head->next;
		delete tempNode;
	}
} //end-~Deque

///------------------------------------------------------
/// Adds a new item to the front of the Deque
/// 
void Deque::AddFront(int item) {
	// Create a new node
	DequeNode* newNode = new DequeNode(item);
	// Set the new node's next pointer to the current head
	newNode->next = head;
	// Set the new node's prev pointer to NULL
	newNode->prev = NULL;
	// If head is present then set the current head's prev pointer to the new node
	if (head != NULL) {
		head->prev = newNode;
	}
	// Set the new head
	head = newNode;
	// If tail is not present then set the tail to the new node
	if (tail == NULL) {
		tail = newNode;
	}
	// Increment the number of items
	noOfItems++;
} //end-AddFront

///------------------------------------------------------
/// Adds a new item to the end of the Deque
/// 
void Deque::AddRear(int item) {
	// Create a new node
	DequeNode* newNode = new DequeNode(item);
	// Set the new node's prev pointer to the current tail
	newNode->prev = tail;
	// Set the new node's next pointer to NULL
	newNode->next = NULL;
	// If tail is present then set the current tail's next pointer to the new node
	if (tail != NULL) {
		tail->next = newNode;
	}
	// Set the new tail
	tail = newNode;
	// If head is not present then set the head to the new node
	if (head == NULL) {
		head = newNode;
	}
	// Increment the number of items
	noOfItems++;
} //end-AddRear

///------------------------------------------------------
/// Remove and return the item at the front of the Deque
/// If the Deque is empty, throw an exception
/// 
int Deque::RemoveFront() {
	// Create a variable to store the front value
	int front = 0;
	// If the deque is empty then throw an exception
	if (head == NULL) {
		throw exception("No Element in List");
	}
	else {
		// Set a temp node to the head, set the front value to the head's item, set the head to the next node
		front = head->item;
		DequeNode* tempNode = head;
		head = head->next;
		// If the deque is now empty then set the tail to NULL as well
		if (head == NULL) {
			tail = NULL;
		}
		// Else set the head's prev pointer to NULL
		else {
			head->prev = NULL;
		}
		//delete the temp node, and decrement the number of items
		delete tempNode;
		noOfItems--;
	}
	return front;
} //end-RemoveFront

///------------------------------------------------------
/// Remove and return the item at the rear of the Deque
/// If the Deque is empty, throw an exception
/// 
int Deque::RemoveRear() {
	// Create a variable to store the rear value
	int rear = 0;
	// If the deque is empty then throw an exception
	if (tail == NULL) {
		throw exception("No Element in List");
	}
	else {
		// Set a temp node to the tail, set the rear value to the tail's item, set the tail to the prev node
		rear = tail->item;
		DequeNode* tempNode = tail;
		tail = tail->prev;
		// If the deque is now empty then set the head to NULL as well
		if (tail == NULL) {
			head = NULL;
		}
		// Else set the tail's next pointer to NULL
		else {
			tail->next = NULL;
		}
		//delete the temp node, and decrement the number of items
		delete tempNode;
		noOfItems--;
	}
	return rear;
} //end-RemoveRear

///------------------------------------------------------
/// Return the item at the front of the Deque (do not remove the item)
/// If the Deque is empty, throw an exception
/// 
int Deque::Front() {
	// Create a variable to store the front value
	int front = 0;
	// If the deque is empty then throw an exception
	if (head == NULL) {
		throw exception("No Element in List");
	}
	// Else set the front value to the head's item and return it
	else {
		front = head->item;
	}
	return front;
} //end-Front

///------------------------------------------------------
/// Return the item at the rear of the Deque (do not remove the item)
/// If the Deque is empty, throw an exception
/// 
int Deque::Rear() {
	// Create a variable to store the rear value
	int rear = 0;
	// If the deque is empty then throw an exception
	if (head == NULL) {
		throw exception("No Element in List");
	}
	// Else set the rear value to the tail's item and return it
	else {
		rear = tail->item;
	}
	return rear;
} //end-Rear
