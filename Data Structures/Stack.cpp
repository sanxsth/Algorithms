#include<bits/stdc++.h>
using namespace std;

struct StackNode 
{
	int data;
	StackNode *next;
};

class Stack
{
	private:
		StackNode *top;

	public:
		Stack()
		{
			top = NULL;
		}

		void push(int val)
		{
			StackNode *node = new StackNode;
			node->data = val;
			node->next = NULL;

			node->next = top;
			top = node;
		}

		int pop()
		{
			if (top == NULL) throw "Cannot perform pop on an emtpy stack.";

			StackNode *node = top;
			top = top->next;

			int val = node->data;
			delete node;
            return val;
		}

		int peek()
		{
			if (top == NULL) throw "Cannot peek an empty stack.";

			return top->data;
		}
};


int main()
{
	Stack* s = new Stack();
	
	/* Usage
	 *
     * s->push(4);
     * s->peek(); // returns 4
     * s->pop(); // returns 4
     * s->pop(); // throws an error sicne the stack is now empty.
     */

	return 0;
}