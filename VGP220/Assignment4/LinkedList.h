#pragma once
#include <iostream>

template<typename T>
class LinkedList
{
	struct Node
	{
		T data;
		Node* next = nullptr;
	};


public:
	LinkedList()
		: mHead(nullptr)
	{}

	~LinkedList()
	{
		if (IsEmpty())
		{
			return;
		}

		if (mHead->next == nullptr)
		{
			delete mHead;
			mHead = nullptr;
			return;
		}

		Node* previous = mHead;
		Node* current = mHead->next;

		while (current != nullptr)
		{
			delete previous;
			previous = current;
			current = current->next;
		}

		delete previous;
		mHead = nullptr;
		previous = nullptr;
	}

	void Insert(T data)
	{
		Node* newNode = CreateNode(data);
		if (IsEmpty())
		{
			mHead = newNode;
			return;
		}

		Node* currentNode = mHead;
		while (currentNode != nullptr)
		{
			if (currentNode->next == nullptr)
			{
				currentNode->next = newNode;
				currentNode = nullptr;
				break;
			}
			currentNode = currentNode->next;
		}
	}

	void Remove(T data)
	{
		if (IsEmpty())
		{
			std::cout << "The list is empty.\n";
			return;
		}

		if (mHead->data == data)
		{
			Node* temp = mHead->next;
			delete mHead;
			mHead = temp;
			temp = nullptr;
			return;
		}

		Node* currentNode = mHead->next;

		while (currentNode->next->data != data && currentNode != nullptr)
		{
			currentNode = currentNode->next;
		}

		if (currentNode == nullptr)
		{
			std::cout << "The element is not in the list.\n";
			return;
		}
		Node* temp = currentNode->next;
		currentNode->next = temp->next;
		delete temp;
		temp = nullptr;

	}

	bool IsEmpty()
	{
		return mHead == nullptr;
	}

	//Displays all the elements of the linked list
	void DisplayList()
	{
		// TODO: 1
		Node* temp;

		temp = mHead;

		while (temp != nullptr)
		{
			std::cout << temp->data<< " " ;
			temp = temp->next;
		}
		std::cout << "\n";
	}

	//Displays all the elements of the linked list in reverse order
	void DisplayReverseList()
	{
		// TODO: 2
		int count=0;
		Node* temp;
		temp = mHead;

		while (temp != nullptr)
		{
			++count;
			temp = temp->next;
		}

		T* helper = new T[count];

		int i = 0;
		temp = mHead;

		while (temp != nullptr)
		{
			helper[i] = temp->data;
			temp = temp->next;
			++i;
		}


		for (int i = count-1; i>= 0; --i)
		{
		
			std::cout << helper[i] << " ";
		}
		std::cout<<"\n";

	
	}

	//This function allows the user to modify an existance data
	//Returns true if the conten was modified and false if it wasn't.
	bool ModifyContent(T content, T newContent)
	{
		// TODO: 3

		Node* temp;

		temp = mHead;

		while (temp != nullptr)
		{
			if (temp->data == content)
			{
				temp->data = newContent;
				return true;

			}
			temp = temp->next;
		}

		return false;
	}

	//Clear all the data from the linked list
	void ClearList()
	{
		// TODO: 4

		Node* current = mHead;
		Node* next = nullptr;

		while(current != nullptr)
		{
			next = current->next;
			delete current;
			current = next; 

		}

		mHead = nullptr;

	}

private:
	Node* mHead;

	Node* CreateNode(T data)
	{
		Node* newNode = new Node();
		newNode->data = data;
		return newNode;
	}
};
