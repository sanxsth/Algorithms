#include<bits/stdc++.h>
using namespace std;

struct Node
{
	int data;
	Node* next;
};

class Queue
{
	private:
		Node *front, *rear;
		int size;

	public:

		Queue()
		{
			front = rear = NULL;
			size = 0;
		}

		void enqueue(int val)
		{
			Node *node = new Node;
			node->data = val;
			node->next = NULL;

			if (front == NULL) // empty queue
				front = rear = node;
			else
			{
				rear->next = node;
				rear = node;
			}
			size++;
		}

		int dequeue()
		{
			if (front == NULL) throw "cannot perform dequeue on an empty queue.";

			int val = front->data;
			if (front == rear)
			{
				delete front;
				front = rear = NULL;
			} 
			else
			{
				Node *temp = front;
				front = front->next;
				delete temp; 
			}
			size--;
			return val;
		}

		int get_size()
		{
			return size;
		}
};

int main()
{
	Queue q;

    /* usage
    * q.enqueue(1); [1]
    * q.enqueue(2); [1, 2]
	* q.enqueue(3); [1, 2, 3]
    * q.dequeue(); [2, 3]
    * q.dequeue(); [3]
    * q.get_count(); returns 1
    */
    
	return 0;
}