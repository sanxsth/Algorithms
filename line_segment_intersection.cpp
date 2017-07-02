#include<bits/stdc++.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define lli long long
#define sf scanf
/*


		here, the line segments under consideration are only axis parallel lines
		
		we implemnt the status using the rotating segment tree
*/
lli gy1,gy2;
vector < pair<lli,lli> > ans;


struct node // node of the avl tree would be of the this structure
{
	node * lc,*rc,*par; // pointers to the left child, right child and the parent of the current node
	lli y1,y2; // stores a 2-d point as the node element
	lli val;
	lli h;
};

struct compare // custom comparator for the priority queue used in this program
 { 
   bool operator()(const pair < pair < lli,lli > , pair< pair < lli, lli >,pair < lli, lli > > > & l, const pair < pair < lli,lli > , pair< pair < lli, lli >,pair < lli, lli > > > & r) 
   {
		if( l.first.first == r.first.first)
				return l.first.second > r.first.second; // deletion 3, horizontal 2, insertion 1
		else
			return l.first.first < r.first.first;
   } 
 };
	

class bst // the bst
{
	public:
	
	node * root; // th variale storing the root node
	bst();
	
	void ins(node *,lli,lli,lli);
	void del(node *,lli);
	lli serv(node *);
	void rr(node *);
	void ll(node *);
	void rl(node *);
	void lr(node *);
	void fin(node *,lli,lli,lli);
	void inorder(node * cnode,lli x1,lli x2,lli y);
};

bst::bst()
{
	root=NULL;
}
void bst::ins(node * cnode,lli v,lli y1,lli y2)
{
	if(root==NULL)
	{
		node * tmp= new node;
		tmp->lc=NULL;
		tmp->rc=NULL;
		tmp->val=v;
		tmp->y1=y1;
		tmp->y2=y2;
		tmp->h=1;
		tmp->par=NULL;
		root=tmp;
	}
	
	else
	{
		if(v<(cnode->val))
		{
			if(cnode->lc==NULL)
			{
					
				node * tmp= new node;
				tmp->lc=NULL;
				tmp->rc=NULL;
				tmp->y1=y1;
				tmp->y2=y2;
				tmp->val=v;
				tmp->par=cnode;
				tmp->h=1;
				cnode->lc=tmp;
			}
			else
				ins(cnode->lc,v,y1,y2);
		}
		else
		{
			if(cnode->rc==NULL)
			{
				node * tmp= new node;
				tmp->lc=NULL;
				tmp->rc=NULL;
				tmp->val=v;
				tmp->y1=y1;
				tmp->y2=y2;
				tmp->par=cnode;
				tmp->h=1;
				cnode->rc=tmp;
			}
			else
				ins(cnode->rc,v,y1,y2);
		}
		lli h1=0,h2=0;
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
				
				lli nh1=0,nh2=0;
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
				
				lli nh1=0,nh2=0;
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
			cnode->h=max(h1,h2)+1;
	}
}

void bst::del(node * cnode,lli v)
{
	if( (cnode->val==v) )
	{
		if(cnode->rc!=NULL)
		{
			if( ((cnode->rc)->lc) ==NULL && ((cnode->rc)->rc)==NULL )
			{
				cnode->val=(cnode->rc)->val;
				cnode->y1=(cnode->rc)->y1;
				cnode->y2=(cnode->rc)->y2;
				delete cnode->rc;
				cnode->rc=NULL;
			}
			else
			{
				cnode->val=serv(cnode->rc);
				cnode->y1=gy1;
				cnode->y2=gy2;
			}
		}
		else	
		{
			if(cnode->lc==NULL)
			{
				node * tpar=cnode->par;
				if(tpar==NULL)
				{
					delete cnode;
					root=NULL;
				}
				else
				{
					node * tmp=cnode;
					if(tpar->lc==tmp)
						tpar->lc=NULL;
					else
						tpar->rc=NULL;
					delete cnode;
				}
				return ;
			}
			else
			{
				cnode->val=(cnode->lc)->val;
				cnode->y1=(cnode->lc)->y1;
				cnode->y2=(cnode->lc)->y2;
				delete cnode->lc;
				cnode->lc=NULL;
			}
		}
	}
	else
	{
		if((cnode->val)>v)
			del(cnode->lc,v);
		else
			del(cnode->rc,v);
	}
	
	lli h1=0,h2=0;
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
			
			lli  nh1=0,nh2=0;
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
			
			lli  nh1=0,nh2=0;
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
		cnode->h=max(h1,h2)+1;
}

lli bst::serv(node * cnode)
{
	if(cnode->lc==NULL && cnode->rc==NULL)
	{
		lli tval=cnode->val;
		gy1=cnode->y1;
		gy2=cnode->y2;
		node * tmp=cnode->par;
		delete tmp->lc;
		tmp->lc=NULL;
		return tval;
	}
	else
	{
		if(cnode->lc==NULL)
		{
			lli tval=cnode->val;
			gy1=cnode->y1;
			gy2=cnode->y2;
			cnode->val=(cnode->rc)->val;
			delete cnode->rc;
			cnode->rc=NULL;
			cnode->h=1;
			return tval;
		}
		else
		{
			lli tval=serv(cnode->lc);
			lli h1=0,h2=0;
			if(cnode->rc!=NULL)
				h2=(cnode->rc)->h;
			if(cnode->lc!=NULL)
				h1=(cnode->lc)->h;
			if(abs(h1-h2)>1) // rotation required at cnode
			{
				if(h1>h2)
				{
					// left heavy;
					node * tmp=cnode->lc;
					
					lli nh1=0,nh2=0;
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
					
					lli nh1=0,nh2=0;
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
				cnode->h=max(h1,h2)+1;
			return tval;
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
	
	h1=0,h2=0;
	if(c->lc!=NULL)
		h1=(c->lc)->h;
	if(c->rc!=NULL)
		h2=(c->rc)->h;
	c->h=max(h1,h2)+1;	

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
		
	h1=0,h2=0;
	if(c->lc!=NULL)
		h1=(c->lc)->h;
	if(c->rc!=NULL)
		h2=(c->rc)->h;
	c->h=max(h1,h2)+1;
	
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


void bst::inorder(node * cnode,lli x1,lli x2,lli y)
{	
	if(cnode->lc!=NULL)
		inorder(cnode->lc,x1,x2,y);
	if((cnode->val) >= x1 && cnode->val <=x2)
	{
		if( (cnode->val) == x1 || cnode->val ==x2 )
		{
			if(cnode->y1!=y && cnode->y2!=y)
				ans.pb(mp(cnode->val,y));
		}
		else
			ans.pb(mp(cnode->val,y));
	}
	if(cnode->rc!=NULL)
		inorder(cnode->rc,x1,x2,y);
}

void bst::fin(node * cnode,lli x1,lli x2,lli y)
{
	if(cnode->val <= x1 || cnode->val >= x2)
	{
		if(cnode->val <= x1)
		{
			if(cnode->rc!=NULL)
				fin(cnode->rc,x1,x2,y);
		}
		else
		{
			if(cnode->lc!=NULL)
				fin(cnode->lc,x1,x2,y);
		}
	}
	else
	{
		ans.pb(mp(cnode->val,y));
		if(cnode->rc!=NULL)
			fin(cnode->rc,x1,x2,y);
		if(cnode->lc!=NULL)
				fin(cnode->lc,x1,x2,y);
	}
}
	
	


int main()
{
	bst s;
	int n;
	cin>>n;
	// priority queue used to fetch the points by the decreasing y co-ordinate
	priority_queue < pair < pair < lli,lli > , pair< pair < lli, lli >,pair < lli, lli > > >   ,vector< pair < pair < lli,lli > , pair< pair < lli, lli >,pair < lli, lli > > > >,compare >   q;
	
	while(n--)
	{
		lli x1,x2,y1,y2;
		sf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
		if(x1==x2)// vertical
		{
			if(y2>y1)
			{
				lli tmp=y2;
				y2=y1;
				y1=tmp;
			}
			q.push(mp(mp(y1,1),mp(mp(x1,x2),mp(y1,y2))));
			q.push(mp(mp(y2,3),mp(mp(x1,x2),mp(y1,y2))));
		}
		else
		{
			if(x2<x1)
			{
				lli tmp=x2;
				x2=x1;
				x1=tmp;
			}
			q.push(mp(mp(y1,2),mp(mp(x1,x2),mp(y1,y2))));
		}
	}
	
	while(!q.empty())
	{
		int typ=q.top().first.second;
		lli x1=q.top().second.first.first;
		lli x2=q.top().second.first.second;
		lli y2=q.top().second.second.second;
		lli y1=q.top().second.second.first;
		lli y=q.top().first.first;
		q.pop();
		if(typ==3)
			s.del(s.root,x1);
		if(typ==2 && s.root!=NULL)
			s.inorder(s.root,x1,x2,y);
		if(typ==1)
			s.ins(s.root,x1,y1,y2);
	}
	sort(ans.begin(),ans.end());
	for(long i=0;i<ans.size();i++)
		cout<<ans[i].first<<" "<<ans[i].second<<endl;
	return 0;
}
		
		
		
		