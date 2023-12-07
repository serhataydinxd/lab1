#include "Deque.h"
#include <stdexcept>

///------------------------------------------------------
/// Default constructor
/// 
Deque::Deque() {
	DequeNode* head = NULL;
	DequeNode* tail = NULL;
	int noOfItems = 0;
} //end-Deque

///------------------------------------------------------
/// Destructor
/// 
Deque::~Deque() {
	// Fill this in
} //end-~Deque

///------------------------------------------------------
/// Adds a new item to the front of the Deque
/// 
void Deque::AddFront(int item) {
	if (head == NULL)
		tail = head = new DequeNode(item);

	// Inserts node at the front end
	else {
		DequeNode* newNode = new DequeNode(item);
		head->prev = newNode;
		head = newNode;
	}

	// Increments count of elements by 1
	noOfItems++;
} //end-AddFront

///------------------------------------------------------
/// Adds a new item to the end of the Deque
/// 
void Deque::AddRear(int item) {
	if (tail == NULL) {
		head = tail = new DequeNode(item);
	}

	// Inserts node at the rear end
	else {
		DequeNode* newNode = new DequeNode(item);
		tail->next = newNode;
		tail = newNode;
	}

	noOfItems++;
} //end-AddRear

///------------------------------------------------------
/// Remove and return the item at the front of the Deque
/// If the Deque is empty, throw an exception
/// 
int Deque::RemoveFront() {
	if (head == NULL) {
		throw std::runtime_error("Deque is empty");
	}
	else {
		DequeNode* temp = head;
		head = head->next;
		int item = temp->item;
		delete temp;
		noOfItems--;
		return item;
	}
	return 0;
} //end-RemoveFront

///------------------------------------------------------
/// Remove and return the item at the rear of the Deque
/// If the Deque is empty, throw an exception
/// 
int Deque::RemoveRear() {
	if (tail == NULL) {
		throw std::runtime_error("Deque is empty");
	}
	else {
		DequeNode* temp = tail;
		tail = tail->prev;
		int item = temp->item;
		delete temp;
		noOfItems--;
		return item;
	}
	return 0;
} //end-RemoveRear

///------------------------------------------------------
/// Return the item at the front of the Deque (do not remove the item)
/// If the Deque is empty, throw an exception
/// 
int Deque::Front() {
	if(head == NULL)
		throw std::runtime_error("Deque is empty");
	else
		return head->item;
} //end-Front

///------------------------------------------------------
/// Return the item at the rear of the Deque (do not remove the item)
/// If the Deque is empty, throw an exception
/// 
int Deque::Rear() {
	if(tail == NULL)
		throw std::runtime_error("Deque is empty");
	else
		return tail->item;
	return 0;
} //end-Rear
