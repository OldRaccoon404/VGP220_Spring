#pragma once
#pragma once

//TODO: 5 - Implement a Queue class from scratch
//Remember that your queue should follow the FIFO standard (First In First Out)

template<typename T>
class Queue
{
public:
	Queue(size_t queueSize)
	{
		mCapacity = queueSize;
		mData = new T[mCapacity];
		mCurrentSize = 0;
		front = 0;
		rear = - 1;
	}

	~Queue()
	{
		delete[] mData;
		mData = nullptr;
		
	}
	//Inserts the data in the queue.
	void Enqueue(T data)
	{
		if (mCurrentSize < mCapacity)
		{
			rear = (rear + 1) % mCapacity;
			mData[rear] = data;
			++mCurrentSize;
		}
		else
		{
			std::cout << "\nOverflow!\n";
		}
	}

	//Removes an element from the queue and returns this element in the output parameter
	//Also it returns true if the object was removed and false if the Queue is empty
	bool Daqueue(T& output)
	{
		if (!isEmpty())
		{
			output = mData[front];
			front = (front + 1) % mCapacity;
			--mCurrentSize;

			return true;
		}
		else
		{
			std::cout << "Queue is empty \n";
			return false;

		}
	}

	//Returns true if queue is empty, false otherwise
	bool isEmpty()
	{
		if (mCurrentSize == 0)
		{
			return true;
		}
		return false;
	}

	//Display all the elements in the queue:
	//Example, lets suppose you inserted 1, 2, 3, 4, 5
	//Display should print: "front->1, 2, 3, 4, 5<-rear"
	void DisplayQueue()
	{
		std::cout << "\n\nfront->";

		for (int i = front; i <= rear; i++)
		{
			if (i != rear)
			{
				std::cout << mData[i] << ", ";
			}
			else
			{
				std::cout << mData[i];
			}
		}


		std::cout << "<-rear\n\n";

	}

private:
	int front;
	int rear;
	int mCurrentSize;
	int mCapacity;
	T* mData;
};