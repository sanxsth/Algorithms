// Self Balancing Binary Search Tree 23-4-17 1:54pm

#include<bits/stdc++.h>

using namespace std;
long ans=0,flg=0;
void test();
void test()
{
	cout<<"here"<<endl;
}


struct node // a node of thr Avl tree would have the following structure
{
	node * lc,*rc,*par; // pointers to left child, right child and parent node; NULL if they are not present
	long val; // stores the element value 
	long h; // stores the height of the longest subtree
	long st;
};

class bst // the bst would have the following structure
{
	public:
	
	node * root; // root would be stored at this location
	bst();
	
	void ins(node *,long); // used for inserting the node
	void inorder(node *,long); // used for inorder traversal
	void rr(node *);// used for rotation case 1	
	void ll(node *);// used for rotation case 2
	void rl(node *);// used for rotation, case 3
	void lr(node *);// used for rotation case 4
	long find1(node *,long); // used for query
};

bst::bst() // default constructor
{
	root=NULL;
}
long bst:: find1(node * cnode,long x)
{
	if((cnode->val)==x)
		return 1;
	else
	{
		if(cnode->lc==cnode->rc)
			return -1;
		else
		{	
			if((cnode->val)>x)
			{
				if(cnode->lc==NULL)
					return -1;
				else
					return find1(cnode->lc,x);
			}
			else
			{
				if(cnode->rc==NULL)
					return -1;
				else
					return find1(cnode->rc,x);
			}
		}
	}
}
void bst::ins(node * cnode,long v)
{
	if(root==NULL)
	{
		node * tmp= new node;
		tmp->lc=NULL;
		tmp->rc=NULL;
		tmp->val=v;
		tmp->st=1;
		tmp->h=1;
		tmp->par=NULL;
		root=tmp;
	}
	
	else
	{
		if(v<=(cnode->val))
		{
			if(cnode->lc==NULL)
			{
					
				node * tmp= new node;
				tmp->lc=NULL;
				tmp->rc=NULL;
				tmp->val=v;
				tmp->st=1;
				tmp->par=cnode;
				tmp->h=1;
				cnode->lc=tmp;
			}
			else
				ins(cnode->lc,v);
		}
		else
		{
			if(cnode->rc==NULL)
			{
				node * tmp= new node;
				tmp->lc=NULL;
				tmp->rc=NULL;
				tmp->val=v;
				tmp->st=1;
				tmp->par=cnode;
				tmp->h=1;
				cnode->rc=tmp;
			}
			else
				ins(cnode->rc,v);
		}
		long h1=0,h2=0;
		if(cnode->lc!=NULL)
			h1=(cnode->lc)->h;
		if(cnode->rc!=NULL)
			h2=(cnode->rc)->h;
		
		if(abs(h1-h2)>1) // rotation required at cnode
		{
			if(h1>h2)
			{
				// left heavy;
				node * tmp=cnode->lc;
				
				long nh1=0,nh2=0;
				if(tmp->lc!=NULL)
					nh1=(tmp->lc)->h;
				if(tmp->rc!=NULL)
					nh2=(tmp->rc)->h;
				
				if(nh1>=nh2)
					ll(cnode);
				else
					lr(cnode);
			}
			else
			{
				// right heavy
				node * tmp=cnode->rc;
				
				long nh1=0,nh2=0;
				if(tmp->lc!=NULL)
					nh1=(tmp->lc)->h;
				if(tmp->rc!=NULL)
					nh2=(tmp->rc)->h;
				
				if(nh1<=nh2)
					rr(cnode);
				else
					rl(cnode);
			}
		}
		else
		{
			cnode->h=max(h1,h2)+1;
			long c1=0,c2=0;
			if(cnode->lc!=NULL)
				c1=(cnode->lc)->st;
			if(cnode->rc!=NULL)
				c2=(cnode->rc)->st;
			cnode->st=c1+c2+1;
		}
	}
}

void bst::rr(node * cnode)
{
	node * tpar=cnode->par;
	node * b=cnode;
	node * c=cnode->rc;
	if(tpar!=NULL)
	{
		if(tpar->rc==cnode)
			tpar->rc=c;
		else
			tpar->lc=c;
	}
	else
		root=c;
	c->par=tpar;
	b->par=c;
	b->rc=c->lc;
	if((c->lc)!=NULL)
		(c->lc)->par=b;
	c->lc=b;
	
	long h1=0,h2=0;
	if(b->lc!=NULL)
		h1=(b->lc)->h;
	if(b->rc!=NULL)
		h2=(b->rc)->h;
	b->h=max(h1,h2)+1;
	
	long c1=0,c2=0;
	if(b->lc!=NULL)
		c1=(b->lc)->st;
	if(b->rc!=NULL)
		c2=(b->rc)->st;
	b->st=c1+c2+1;
	
	h1=0,h2=0;
	if(c->lc!=NULL)
		h1=(c->lc)->h;
	if(c->rc!=NULL)
		h2=(c->rc)->h;
	c->h=max(h1,h2)+1;	
	
	c1=0,c2=0;
	if(c->lc!=NULL)
		c1=(c->lc)->st;
	if(c->rc!=NULL)
		c2=(c->rc)->st;
	c->st=c1+c2+1;
}

void bst::ll(node* cnode)
{
	node * tpar=cnode->par;
	node * b=cnode;
	node * c=cnode->lc;
	
	if(tpar!=NULL)
	{
		if(tpar->rc==cnode)
			tpar->rc=c;
		else
			tpar->lc=c;
	}
	else
		root=c;
	c->par=tpar;
	b->par=c;
	if((c->rc)!=NULL)
		(c->rc)->par=b;
	b->lc=c->rc;
	c->rc=b;
	
	long h1=0,h2=0;
	if(b->lc!=NULL)
		h1=(b->lc)->h;
	if(b->rc!=NULL)
		h2=(b->rc)->h;
	b->h=max(h1,h2)+1;
	
	long c1=0,c2=0;
	if(b->lc!=NULL)
		c1=(b->lc)->st;
	if(b->rc!=NULL)
		c2=(b->rc)->st;
	b->st=c1+c2+1;
	
	h1=0,h2=0;
	if(c->lc!=NULL)
		h1=(c->lc)->h;
	if(c->rc!=NULL)
		h2=(c->rc)->h;
	c->h=max(h1,h2)+1;
	
	c1=0,c2=0;
	if(c->lc!=NULL)
		c1=(c->lc)->st;
	if(c->rc!=NULL)
		c2=(c->rc)->st;
	c->st=c1+c2+1;
}

void bst:: rl(node * cnode)
{
	ll(cnode->rc);
	rr(cnode);
}

void bst:: lr(node * cnode)
{
	rr(cnode->lc);
	ll(cnode);
}

void bst::inorder(node * cnode,long x)
{	
	if(cnode->val!=x)
	{
		if(cnode->val>x)
			inorder(cnode->lc,x);
		else
		{
			long tmp=0;
			if(cnode->lc!=NULL)
				tmp=(cnode->lc)->st;
			ans+=(tmp+1);
			inorder(cnode->rc,x);
		}
	}
	else
	{
		ans++;
		if(cnode->lc!=NULL)
			ans+=((cnode->lc)->st);
	}
}

void sh(node * cnode);
void sh(node * cnode)
{
	if(cnode->lc!=NULL)
		sh(cnode->lc);
	int c1=-1,c2=-1;
	if(cnode->lc!=NULL)
		c1=(cnode->lc)->val;
	if(cnode->rc!=NULL)
		c2=(cnode->rc)->val;
	cout<<"node:"<<cnode->val<<" st:"<<cnode->st<<endl;
	cout<<"lc:"<<c1<<endl;
	cout<<"rc:"<<c2<<endl;
	cout<<endl;
	if(cnode->rc!=NULL)
		sh(cnode->rc);
}

int main()
{
	bst s;
	
	long q;
	scanf("%ld",&q);
	
	while(q--)
	{
		long t,val;
		scanf("%ld%ld",&t,&val);
		
		if(t==1)
			s.ins(s.root,val);
		if(t==2)
		{
			if(s.root==NULL)
				printf("Data tidak ada\n");
			else
			{
				long tmp=s.find1(s.root,val);
				if(tmp==-1)
					printf("Data tidak ada\n");
				else
				{
					ans=0;
					flg=0;
					s.inorder(s.root,val);
					printf("%ld\n",ans);
				}
			}
		}
		if(t==3)
			sh(s.root);
	}
	return 0;
}
	
	