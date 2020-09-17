//segtree with lazy propagation 

#include<bits/stdc++.h>
using namespace std;
#define ll long long

struct Node
{
    Node *l_child, * r_child;
    ll l, r; // lmts
    ll data;
    ll flg, add_val; // flg used mark ranges that need updation before query
};
 
class SegTree
{
    public:
    Node * root;
    SegTree()
    {
        root=NULL;
    }
    Node * build(ll l,ll r);
    void update(Node * node, ll val, ll l, ll r);
    ll search(Node * node, ll l, ll r);
};
 
Node * SegTree::build(ll l, ll r)
{
    Node * p = new Node;
    p->l_child = NULL; 
    p->r_child = NULL;
    p->l = l;
    p->r = r;
    p->data = 0;
    p->flg = 0;
    p->add_val = 0;
    if((r-l))
    {
        ll mid = (r+l)/2;
        p->l_child = build(l, mid);
        p->r_child = build(mid+1, r);
    }
    return p;
}
 
void SegTree::update(Node * node, ll val, ll l, ll r)
{
    if( (node->l == l) && (node->r == r) )
    {
        ll no_cnt = (r-l)+1;
        node->flg = 1;
        node->data = ((node->data) + (val*no_cnt));
        node->add_val += val;
    }
    else
    {
        ll mid = (node->r + node->l)/2;
        if((node->flg) == 1)
        {
            Node * l_node = node->l_child;
            Node * r_node = node->r_child;

            (l_node->flg) = 1;
            l_node->data = ((l_node->data)+( ( (l_node->r) - (l_node->l) +1 ) * (node->add_val) ));
            l_node->add_val = ((l_node->add_val)+(node->add_val));

            r_node->flg = 1;
            r_node->data = ((r_node->data)+( ( (r_node->r) - (r_node->l) +1 ) * (node->add_val) ));
            r_node->add_val = ((r_node->add_val) + (node->add_val) );

            node->flg = 0;
            node->add_val = 0;
        }
        if(r<=mid)
            update(node->l_child, val, l, r);
        else
        {
            if(l>mid)
                update(node->r_child, val, l, r);
            else
            {
                update(node->l_child, val, l, mid);
                update(node->r_child, val, mid+1, r);
            }
        }
        node->data = ((node->l_child)->data) + ((node->r_child)->data);
    }
}
 
ll SegTree::search(Node * node, ll l, ll r)
{
    if(node->l==l && node->r==r) return node->data;

    ll mid = (node->r + node->l)/2;
    if((node->flg)==1)
    {
        Node * l_node = node->l_child;
        Node * r_node = node->r_child;

        (l_node->flg) = 1;
        l_node->data = ((l_node->data)+( ( (l_node->r) - (l_node->l) +1 ) * (node->add_val) ));
        l_node->add_val = ((l_node->add_val)+(node->add_val));

        r_node->flg = 1;
        r_node->data = ((r_node->data)+( ( (r_node->r) - (r_node->l) +1 ) * (node->add_val) ));
        r_node->add_val = ((r_node->add_val) + (node->add_val) );

        node->flg = 0;
        node->add_val = 0;
    }
    if(r<=mid) return search(node->l_child, l, r);

    if(l>mid)  return search(node->r_child, l, r);
    
    return ( search(node->l_child, l, mid) + search(node->r_child, mid+1, r) );
}

int main()
{
    ll tc;
    scanf("%lld",&tc);
    while(tc--)
    {
        ll n,m;
        scanf("%lld%lld", &n, &m);
        SegTree segt;
        segt.root = segt.build(1, n);
        while(m--)
        {
            ll c;
            scanf("%lld", &c);
            if(c==1)
            {
                ll l,r;
                scanf("%lld%lld", &l, &r);
                ll ans = segt.search(segt.root, l, r);
                printf("%lld\n", ans);
            }
            else
            {
                ll l,r,value;
                scanf("%lld%lld%lld", &l, &r, &value);
                segt.update(segt.root, value, l, r);
            }
        }
        delete segt.root;
    }
    return 0;
} 
