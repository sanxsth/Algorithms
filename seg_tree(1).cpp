    #include<bits/stdc++.h>
    using namespace std;
	
    #define LL long long
	
    struct tree_node // each node of the segment tree would be of the type tree_node
    {
        tree_node *left, * right; // pointers to left and right childs of a the node
        LL int l,r; // l-> left boundary value of the range; r-> right boundary value of the range
        LL int data; // global data of the represented range
    };
     
    class st // a segment tree would be of the type st;
    {
        public:
        tree_node * root; // the root node of the tree
        st()
        {
            root=NULL;
        }
        tree_node * build(LL int n,LL int l,LL int r); // fucntion that builds the tree from the given range of values
        void update(tree_node * node,LL int pos,LL int val); // update function
        LL int search(tree_node * node,LL int l,LL int r); // query function
    };
     
    tree_node * st::build(LL int n,LL int l,LL int r)
    {
        tree_node * p=new tree_node; // creating the current node
        p->left=NULL;
        p->right=NULL;
        p->l=l;
        p->r=r;
        p->data=0;
        if(n>1)// creates left and right child if the range size is more than one
        {
            int mid=(r+l)/2;
            p->left=build(mid-l+1,l,mid);
            p->right=build(r-mid,mid+1,r);
        }
        return p;
    }
     
    void st::update(tree_node * node,LL int pos,LL int val)
    {
        if(node->l==node->r)
        {
            if(node->l==pos)
                node->data+=val;
        }
        else
        {
            LL int mid=(node->r+node->l)/2;
            if(pos<=mid)
            {
                update(node->left,pos,val);
            }
            else
                update(node->right,pos,val);
            node->data=((node->left)->data) + ((node->right)->data);
        }
    }
     
    LL int st::search(tree_node * node,LL int l,LL int r)
    {
        if(node->l==l && node->r==r)
            return node->data;
        else
        {
            LL int mid=(node->r+node->l)/2;
            if(r<=mid)
                return search(node->left,l,r);
            else
            {
                if(l>mid)
                    return search(node->right,l,r);
                else
                    return (search(node->left,l,mid) + search(node->right,mid+1,r) );
            }
        }
    }
    int main()
    {
        st segt; // tree declaration
        LL int n,m;
        scanf("%lld%lld",&n,&m);
        segt.root=segt.build(n,1,n);
        while(m--)
        {
            string s;
            cin>>s;
            if(s=="find")
            {
                LL int l,r;
                scanf("%lld%lld",&l,&r);
                LL int ans=segt.search(segt.root,l,r);
                printf("%lld\n",ans);
            }
            else
            {
                LL int l,r;
                scanf("%lld%lld",&l,&r);
                segt.update(segt.root,l,r);
            }
        }
        return 0;
    } 
