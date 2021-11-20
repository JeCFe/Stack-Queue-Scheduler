//Jessica Clara Fealy 2021
//Data Structures And Algorithms With Object Oriented Programming Coursework 1

#include<iostream>

//Class which define a node which to place an object in a queue or stack 
class Node
{
	//Accessiable to all Node object outside of this class 
public:
	//Constructor of a new node which sets all the relevent data for the node to be situated in the correct location later
	Node(int value, Node* nextptr = NULL, Node* prevptr = NULL, int currentpriority = 0) {
		this->value = value; //This is the processID
		next = nextptr; //Defualt set to NULL until it can be placed into the queue or stack
		prev = prevptr; //Defualt set to NULL until it can be placed into the queue or stack
		this->priority = currentpriority; //Sets the priority of the node 
	}

	int getVal(void) { return value; } //Returns the value or processID
	Node* getNext(void) { return next; } //Returns a node pointer to the node situated in front of this node
	Node* getPrev(void) { return prev; } //Returns a node pointer to the node situated behind this node
	void setVal(int value) { Node::value = value; } //Sets the current processID or value of this node
	void setPrev(Node* prevptr) { prev = prevptr; } //Sets where the node sitatuted behind this node is located
	void setNext(Node* nextptr) { next = nextptr; } //Sets where the node situated in front of this node is located 
	int getPriority(void) { return priority; } //Returns the int prioirty value 
	void setPriority(int priority) { Node::priority = priority; } //Set the prioirty of this node 

//Only accessable within this class or derived classes
private:
	Node* next; //Varible which holds a node pointer to where the next node is located 
	Node* prev; //Variable which holds a node pointer to where the previous node is located 
	int priority; //Variable which holds the int priority value 
	int value; //Variable which hold the int processID or value 
};

//Data which define a stack, a last in first out data structure 
class Stack
{
	//Accessiable to all Node object outside of this class 
public:
	//Constructor is instalise the top of the stack
	Stack() {
		top = nullptr;
	}

	//When the stack is destroy removes all items that were in the stack
	~Stack() {
		while (this->top != nullptr)
		{
			this->Pop();
		}
	}

	//Pushing is adding an item to the front of the stack
	//Take an int value as this will be the value at the top of the stack 
	void Push(int value) {
		//Creates a new node to define the new top of the stack 
		Node* tmp = new Node(value, this->top);
		this->top = tmp;
	}

	//Used to determine return the next item in the stack
	Node* NodePop() {
		Node* tmp = top->getNext();
		return tmp;
	}

	//Used to removed items from the top of the stack
	int Pop() {
		//Try catch used to determine when the stack is empty 
		try
		{
			//If the top of the stack is a nullptr this means that the stack is empty, then throwing when this happens 
			if (this->top == nullptr)
			{

				throw "Stack Empty";
			}

			//IF the stack has items remianing do the following
			//Returning the the value of the item at the top of the stack, then removing this node 
			int value = top->getVal();
			top = NodePop();
			return value;
		}
		catch (const char* msg)
		{
			//When the stack is empty and the excemption is thrown then 
			//The error message of " Stack empty " will be shown to users, and the method will return -1
			std::cout << msg << std::endl;
			return -1;
		}
	}
	//Only accessable within this class or derived classes
private:
	Node* top;//Defines the node at the top of the stack
};


//Data which define a Queue, a first in first out data structure 
class Queue
{

	//Data which define a stack, a last in first out data structure 

public:
	//This is the constructor for the Queue, which happens whenever a new Queue object is created
	Queue() {
		//When a Queue object is created Node* are initalised as nullptr which indicates an empty queue
		back = nullptr;
		front = nullptr;
	}

	//This is the deconstructor for the Queue object
	//This happens when the object is destroyed
	~Queue() {
		//This deletes all contents of the Queue until the Node* front is a nullptr
		while (front != nullptr) {
			delete NodeDequeue();
		}
	}

	//This is the way items are added onto a queue
	//Set as virtual to allow derived objects to access and override
	void Enqueue(int i, int priority = 0) {

		//Creates a new Node which is to be placed into the Queue
		//The node required 4 arguments, value, next position, previous position, and the priority 
		Node* tmp = new Node(i, back, nullptr, priority);
		//The back of the queue is set to the new node
		back = tmp;
		if (front == nullptr) //This happens where theres only one item in the queue
		{
			front = back;
		}
		else { //When theres already more than one object in the queue
			tmp = back->getNext(); //Places the new node where the back currently is
			tmp->setPrev(back); //Sets the previous position for the new node to the back position in the queue
		}
	}

	//This is used for removing items from the queue
	//Virtual is used to allow derived classes to used and override the function 
	int Dequeue() {
		//This calls a function to which removed the node from the queue and returns this node
		try
		{
			Node* tmp = NodeDequeue();
			int ret = tmp->getVal(); //Gets the int value from the node which is being removed
			if (front == nullptr) //If theres only only item in the queue
			{
				back = front;
			}
			return ret; //Returns the value (process ID) of the item removed

		}
		//If an exception is thrown then the following happens
		catch (const char* msg)
		{
			//The only event which will cause this to trigger is inside  NodeDequeue in the function call
			//This event will be that the queue is empty
			std::cout << msg << std::endl;
			return -1;
		}
	}

	//Only accessiable inside this class or friend objects 
protected:

	Node* back; //This acts as the node signifying the back of the queue
	Node* front; //this acts as the node signifying the front of the queue

	//Only accessable within this class or derived classes
private:

	virtual Node* NodeDequeue() {

		//Creates a new node pointing at the front of the queue 
		Node* tmp = front;
		//If the front of the queue is a null pointer this means the queue is empty, meaning an error needs to be thrown
		if (front == nullptr)
		{
			throw "Queue Empty";
		}
		//If the queue is not empty
		if (front != nullptr)
		{
			//To remove the first item we must set the new front to the second item in the queue
			front = front->getPrev();
			if (front != nullptr)
			{
				//If front already is not nullptr set front to null pointer to remove all links with the dequeued item
				front->setNext(nullptr);
			}
		}
		//Return the node that was at the front of the queue, that is now removed
		return tmp;
	}
};


class Scheduler : public Queue
{
	//This is the constructor for the Queue, which happens whenever a new Queue object is created
public:
	//This is the constructor whenever a scheduler is created
	//This initalises the contents of the 10 numItemmsInQueue array to 0 
	//This ensure that later loop can look over all array without having null issues 
	Scheduler()
	{
		for (size_t i = 0; i < 10; i++)
		{
			numItemsInQueues[i] = 0;
		}

	}

	//This Enqueue is different to Queue class Enqueue but does the same premise 
	void Enqueue(int i, int priority = 0) {
		//This try catch if the priority is lower than 1 or higher than 10
		try
		{
			//If priority is less or equal to 0, or higher than then 10  
			if (priority > 10 || priority <= 0)
			{
				//As prioirty can only be between 1 and 10, an exception is thrown if the given priority is out of these bounds 
				throw "Priority out of bounds";
			}
			//If the priority is between bounds then the following happens 
			//The item is added to priority_queues with -1 on the prioirty to account for indexing 
			//The Enqueue used here is the Queue class Enqueue, not the Schedulers'
			priority_queues[priority - 1].Enqueue(i, priority);
			//One is added to the relevant numItemsInQueues, this lets future processes know how many items in each queue. 
			//Doing this could've been avoided by making Scheduler a friend of Queue
			numItemsInQueues[priority - 1]++;
		}
		//Used to catch the excemption caused by out of bounds issues 
		catch (const char* msg)
		{
			//Displays to the users that out of bounds excemmption has occurred
			std::cout << msg << std::endl;
		}

	}

	//This is used to dequeue objects from a queue, this operates differently to the Dequeue, found in Queue
	int Dequeue() {
		try
		{
			//The bool is used to determine whether there are any items in the queues to know whether an excemption is to be thrown 
			bool areItems = false;
			//Int holder of what queue is currently to be drawn from 
			int selectedQueue;
			//next functions as the pscudo random seed to generate a random sequence 
			static int next = 3251;
			//Uses next to generate a randon number between 1 - 10000
			next = ((next * next) / 100) % 10000;

			//This number have been normalised from a 4 digit random number to a random number between 1 - 100
			int prob = next % (100 + 1 - 0) + 0;


			//This sections determines which queue is to be used based on their weighted probability, the queue selected is then defined 

			//2% probability of priority queue 1 being selected 
			if (prob <= 2)
			{
				selectedQueue = 0;
			}
			//3% probability of priority queue level 2 being selected
			if (prob > 2 && prob <= 4)
			{
				selectedQueue = 1;
			}
			//4% chance for prioirty 3 to be selected
			if (prob > 4 && prob <= 7)
			{
				selectedQueue = 2;
			}
			//5% chance for the priority 4 to be selected
			if (prob > 7 && prob <= 11)
			{
				selectedQueue = 3;
			}
			//7% chance for priority 5 to be selected
			if (prob > 11 && prob <= 18)
			{
				selectedQueue = 4;
			}
			//11% chance for the priority 6 queue to be selected
			if (prob > 18 && prob <= 28)
			{
				selectedQueue = 5;
			}
			//12% chance for the priority 7 queue to be selected
			if (prob > 28 && prob <= 39)
			{
				selectedQueue = 6;
			}
			//12% chance for the priority 8 queue to be selected
			if (prob > 39 && prob <= 50)
			{
				selectedQueue = 7;
			}
			//Priority 9 has a 26% chance of being selected
			if (prob > 50 && prob <= 65)
			{
				selectedQueue = 8;
			}
			//The highest priority has a 35% chance of being selected 
			if (prob > 65 && prob <= 100)
			{
				selectedQueue = 9;
			}
			//This for loop is used to determine if any of the arrays contain any data before an attempt to dequeue is preformed
			for (size_t i = 0; i < 10; i++)
			{
				if (numItemsInQueues[i] > 0)
				{
					//As long as at least 1 array contains data then the code after this for loop is able to run
					areItems = true;
				}
			}
			//If none of the queues contain data then a char excemption is thrown to inform the user that theres no more data in any queue
			if (!areItems)
			{
				throw "No items in any priority queue";
			}
			//This for loop is used to pull data from the randomly selected queue
			//If the queue selected contains no data then the nect highest priority queue is selected 
			for (size_t i = selectedQueue; i < 10; i++)
			{
				//If the current queue contains any data 
				if (numItemsInQueues[i] > 0)
				{
					//Removes 1 from the relevent numItemInQueue array which is used to detmine how many items in each queue
					numItemsInQueues[i]--;
					//Returns the value removed from the queue using the parents Dequeue method 
					return priority_queues[i].Dequeue();
				}
			}
			//If the selected queue is empty, and all higher priority queues are empty then a for loop is used to test if theres any data from
			//the nexct lower priortiy, this continues until data is found which can be dequeued
			for (size_t i = selectedQueue; i >= 0; i--)
			{
				//If the current queue contains any data 
				if (numItemsInQueues[i] > 0)
				{
					//Removes 1 from the relevent numItemInQueue array which is used to detmine how many items in each queue
					numItemsInQueues[i]--;
					//Returns the value removed from the queue using the parents Dequeue method 
					return priority_queues[i].Dequeue();
				}
			}
		}
		//If a char error is thrown in the previous Try block then the following happens 
		//The only exception which can be thrown is that all queues are empty 
		catch (const char* msg)
		{
			std::cout << msg << " " << std::endl;
			return -1;
		}

	}

	//This virtual function is not used
	//But was and can be used for a basic priority FIFO queue
	virtual Node* NodeDequeue() {
		try
		{
			//Creates a new node pointing at the front of the queue 
			Node* tmp = front;
			//If the front of the queue is a null pointer this means the queue is empty, then if true throw an error
			if (front == nullptr)
			{
				throw "Queue Empty";
			}
			//If the queue is not empty
			if (front != nullptr)
			{
				//To remove the first item we must set the new front to the second item in the queue
				front = front->getPrev();
				if (front != nullptr)
				{
					//If front already is not nullptr set front to null pointer to remove all links with the dequeued item
					front->setNext(nullptr);
				}
			}
			//Return the node that was at the front of the queue, that is now removed
			return tmp;
		}
		catch (const char* msg)
		{
			//Displays the error message that the queue is empty
			std::cout << msg << std::endl;
		}

	}

	//Only accessable within this class or derived classes
private:
	//Hold an array of 10 for 10 priority queues
	Queue priority_queues[10];
	//Hold an array of 10 for the 10 pirority queues
	//Used to determine if an array contains any data 
	//Preferably would make Scheduler a friend of Queue, but this is an alternative solution 
	int numItemsInQueues[10];
};

