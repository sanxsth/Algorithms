    /* segtree with lazy propagation 
    */
    #include<bits/stdc++.h>
    using namespace std;
    #define LL long long
	
	
    struct tree_node // each node of the segment tree would be of the type tree_node
    {
        tree_node *left, * right; // points to left and right childs of the node
        LL int l,r; // l-> the left boundary value of the range; range -> right boundary value of the range
        LL int data;// represents the global data
        LL int flg,add_val; // flg used as a flag to mark ranges that need update before query
    };
     
    class st // the seg-tree would be of the type st
    {
        public:
        tree_node * root; // represents the root_node
        st()
        {
            root=NULL;
        }
        tree_node * build(LL int n,LL int l,LL int r); // function for building the tree
        void update(tree_node * node,LL int val,LL int l,LL int r); // function to update the tree; both point and range update can be done
        LL int search(tree_node * node,LL int l,LL int r); // used to query the tree
    };
     
    tree_node * st::build(LL int n,LL int l,LL int r)
    {
        tree_node * p=new tree_node; // declaration of a node and initializing its values
        p->left=NULL; 
        p->right=NULL;
        p->l=l;
        p->r=r;
        p->data=0;
        p->flg=0;
        p->add_val=0;
        if(n>1)
        {
            LL int mid=(r+l)/2;
            p->left=build(mid-l+1,l,mid);
            p->right=build(r-mid,mid+1,r);
        }
        return p;
    }
     
    void st::update(tree_node * node,LL int val,LL int l,LL int r) // for a node flg=1 means its global range value is not updated; else flg=0
    {
        if( (node->l==l) && (node->r==r) )
        {
            LL int no_cnt=(r-l)+1;
            node->flg=1;
            node->data=((node->data)+(val*no_cnt));
            node->add_val+=val;
        }
        else
        {
            LL int mid=(node->r+node->l)/2;
            if((node->flg)==1)
            {
                tree_node * l_node=node->left;
                tree_node * r_node=node->right;
                (l_node->flg)=1;
                l_node->data=((l_node->data)+( ( (l_node->r) - (l_node->l) +1 ) * (node->add_val) ));
                l_node->add_val=((l_node->add_val)+(node->add_val));
                r_node->flg=1;
                r_node->data=((r_node->data)+( ( (r_node->r) - (r_node->l) +1 ) * (node->add_val) ));
                r_node->add_val=((r_node->add_val) + (node->add_val) );
                node->flg=0;
                node->add_val=0;
            }
            if(r<=mid)
            {
                update(node->left,val,l,r);
            }
            else
            {
                if(l>mid)
                {
                    update(node->right,val,l,r);
                }
                else
                {
                    update(node->left,val,l,mid);
                    update(node->right,val,mid+1,r);
                }
            }
            node->data=((node->left)->data) + ((node->right)->data);
        }
    }
     
    LL int st::search(tree_node * node,LL int l,LL int r)
    {
        if(node->l==l && node->r==r)
        {
            return node->data;
        }
        else
        {
            LL int mid=(node->r+node->l)/2;
            if((node->flg)==1)
            {
                tree_node * l_node=node->left;
                tree_node * r_node=node->right;
                (l_node->flg)=1;
                l_node->data=((l_node->data)+( ( (l_node->r) - (l_node->l) +1 ) * (node->add_val) ));
                l_node->add_val=((l_node->add_val)+(node->add_val));
                r_node->flg=1;
                r_node->data=((r_node->data)+( ( (r_node->r) - (r_node->l) +1 ) * (node->add_val) ));
                r_node->add_val=((r_node->add_val) + (node->add_val) );
                node->flg=0;
                node->add_val=0;
            }
            if(r<=mid)
            {
                return search(node->left,l,r);
            }
            else
            {
                if(l>mid)
                {
                    return search(node->right,l,r);
                }
                else
                {
                    return ( search(node->left,l,mid) + search(node->right,mid+1,r) );
                }
            }
        }
    }
    int main()
    {
        LL int tc;
        scanf("%lld",&tc);
        while(tc--)
        {
            LL int n,m;
            scanf("%lld%lld",&n,&m);
            st segt;
            segt.root=segt.build(n,1,n);
            while(m--)
            {
                LL int c;
                scanf("%lld",&c);
                if(c==1)
                {
                    LL int l,r;
                    scanf("%lld%lld",&l,&r);
                    LL int ans=segt.search(segt.root,l,r);
                    printf("%lld\n",ans);
                }
                else
                {
                    LL int l,r,value;
                    scanf("%lld%lld%lld",&l,&r,&value);
                    segt.update(segt.root,value,l,r);
                }
            }
            delete segt.root;
        }
        return 0;
    } 
