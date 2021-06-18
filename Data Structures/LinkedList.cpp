#include<bits/stdc++.h>
using namespace std;

struct Node
{
	int val;
	Node *next;
};

class LinkedList
{
	private:
		Node *head;
		Node *tail;
		int size;

		Node* reverse(Node *node)
		{
			if(node == NULL || node->next == NULL) return node;
			
			Node *rest = reverse(node->next);

			(node->next)->next = node; // (node->next) will be the tail of the currently reversed list 
			node->next = NULL;

			return rest;
		}

	public:
		LinkedList()
		{
			head = tail = NULL;
			size = 0;
		}

		void push_back(int val)
		{
			Node *node = new Node;
			node->val = val;
			node->next = NULL;

			if (head == NULL)
				head = tail = node;
			else
			{
				Node* cur = head;

				while (cur->next != NULL)
				{
					cur = cur->next;
				}

				cur->next = node;
				tail = node;
			}
			size++;
		}

		void pop_back()
		{
			Node *cur = head;

			if (cur == NULL) throw "Cannot perform pop on an empty linked list.";
			
			Node *prev = NULL;
			while(cur->next != NULL)
			{
				prev = cur;
				cur = cur->next;
			}

			if(prev == NULL)
			{
				delete head;
				head = tail = NULL;
			}
			else
			{
				prev->next = NULL;
				delete cur;
				tail = prev;
			}
			size--;
		}

		void print()
		{
			Node *cur = head;
			cout<<"values: ";
			while (cur != NULL)
			{
				cout<<cur->val<<" ";
				cur = cur->next;
			}
			cout<<endl;
		}

		bool insert(int val, int pos)
		{

			if (pos > size || pos < 0) return false;

			Node *node = new Node();
			node->val = val;
			node->next = NULL;

			if (head == NULL)
				head = tail = node;
			else if (pos == 0)
			{
				node->next = head;
				head = node;
			}
			else
			{
				int prev_pos = 0;
				Node *prev = head;

				while ((prev_pos + 1) != pos)
				{
					prev = prev->next;
					prev_pos++;
				}

				node->next = prev->next;
				prev->next = node;

				if (prev == tail)
					tail = node;
			}

			size++;
			return true;
		}

		bool delete_at(int pos) 
		{
			if(pos >= size) return false;

			Node *cur = head, *prev = NULL;
			int cur_pos = 0;
			while(cur_pos != pos)
			{
				prev = cur;
				cur = cur->next;
				cur_pos++;
			}

			if(prev == NULL)
				head = cur->next;
			else
				prev->next = cur->next;

			if(cur == tail)
				tail = prev;

			delete cur;
			size--;
			return true;
		}

		void reverse()
		{
			Node *rev_head = reverse(head);
			head = rev_head;
		}
	};


int main()
{

	LinkedList list;

	/* Usage
	 *
	 * list.push_back(1); [1]
	 * list.push_back(2); [1, 2]
	 * list.push_back(3); [1, 2, 3]
	 * list.pop_back(); [1, 2]
	 * list.insert(0, 0); [0, 1, 2]
	 * list.insert(3, 1); [0, 3, 1, 2]
	 * list.delete_at(1); [0, 1, 2]
	 * list.reverse(); [2, 1, 0]
	 */
	
	return 0;
}
