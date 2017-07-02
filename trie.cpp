// following is an implementation of trie 
// Code written to solve the problem https://www.codechef.com/problems/WSITES01 on codechef.com


#include<bits/stdc++.h>
using namespace std;

#define ll long long 
#define mp make_pair
#define pb push_back
#define sf scanf
#define pf printf

int flg=1; // flg == 0 if the answer does n't exist;
string s; // used to fetch the input string; declared global as the trie function works on it directly instead of passing it as a paremeter
char ch;

struct node // each node of the trie would be of this type
{
	long cb,cnb,b,nb;
	node* arr[26]; // each node would have atmost 26 edges; each for each character of the latin letters from 'a' to 'b';
};

vector <string > ans;
long cnt=0;

class trie
{
	public:
	node * root; // root node of the trie
	trie()
	{root=NULL;}
	
	void ins(node *); // used to build the trie from the given set of string
	void trav(node *,string); // used to traverse the string
	void chek(node *); // perform the check function
};

void trie::chek(node *cnode)
{
	if(cnode!=NULL)
	{
		if(cnode->b>0 && cnode->cnb>0)
			flg=0;
	}
	if(flg)
	{
		for(int i=0;i<26;i++)
		{
			if(cnode->arr[i]!=NULL)
				chek(cnode->arr[i]);
		}
	}
}
void trie:: ins(node * cnode)
{
	if(cnt!=s.size())
	{
		if(root==NULL)
		{
			root = new node;
			root->b=0;
			root->cb=0;
			root->nb=0;
			root->cnb=0;
			for(int i=0;i<26;i++)
				root->arr[i]=NULL;
			cnode=root;
		}
		int pos=s[cnt]-'a';
		if(cnode->arr[pos]==NULL)
		{
			cnode->arr[pos]= new node;
			cnode->arr[pos]->b=0;
			cnode->arr[pos]->nb=0;
			cnode->arr[pos]->cb=0;
			cnode->arr[pos]->cnb=0;
			for(int i=0;i<26;i++)
				(cnode->arr[pos])->arr[i]=NULL;
		}
		cnt++;
		ins(cnode->arr[pos]);
		if(ch=='-')
			cnode->cb++;
		else
			cnode->cnb++;
	}
	else
	{
		if(ch=='-')
			cnode->b++;
		else
			cnode->nb++;
	}
	
}

void trie::trav(node * cnode,string s)
{
	if(cnode->nb==0 && cnode!=root && cnode->cnb==0)
		ans.pb(s);
	else
	{
		for(int i=0;i<26;i++)
		{
			string tmp=s;
			tmp.pb('a'+i);
			if(cnode->arr[i]!=NULL)
				trav(cnode->arr[i],tmp);
		}
	}
}

int main()
{
	long n;
	cin>>n;
	
	trie t;
	for(long i=0;i<n;i++)
	{
		cin>>ch>>s;
		cnt=0;
		t.ins(t.root); // inserts each string as they come by...
	}
	string tmp="";
	t.chek(t.root);
	if(flg)
	{
		t.trav(t.root,tmp);
		cout<<ans.size()<<endl;
		//sort(ans.begin(),ans.end());
		for(long i=0;i<ans.size();i++)
			cout<<ans[i]<<endl;
	}
	else
		cout<<-1<<endl;
	return 0;
}