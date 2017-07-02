    #include<bits/stdc++.h> 
    using namespace std; 
    #define LL long long 
    string s; 
    struct node 
    { 
        node * arr[26]; //array to maintain outgoing edges
        int len; // length of the palindrome
        node * suffix; // stores the address of the node pointed by suffix link
        int cnt; // stores the count of the corresponding palindrome
    };
    node * lnode; // stores the address of the palindrome processed last
    class ptree 
    { 
        public: 
        node * root1, * root2; // root1 = -1 size & root2 of size zero 
        ptree() 
        { 
            //initializing root1 
            node * tmp=new node; 
            for(int i=0;i<26;i++) 
                tmp->arr[i]=NULL; 
            tmp->len=-1; 
            tmp->suffix=tmp; 
            tmp->cnt=0; 
            root1=tmp; 
            //initializing root2 
            tmp=new node; 
            for(int i=0;i<26;i++) 
                tmp->arr[i]=NULL; 
            tmp->len=0; 
            tmp->suffix=root1; 
            tmp->cnt=0; 
            root2=tmp; 
        } 
        void add(int pos) 
        { 
            node * cur=lnode; 
            while(1) 
            { 
                int sz=cur->len; 
                if((s[pos]==s[(pos-sz)-1])) //add starts here 
                { 
                    node * cur2=cur; 
                    int val=s[pos]-'a'; 
                    if((cur->arr[val])!=NULL) 
                    { 
                        (cur->arr[val])->cnt++; 
                        node * allp=(cur->arr[val])->suffix; 
                        while(allp->len!=0&&allp->len!=-1) 
                        { 
                            allp->cnt+=1; 
                            allp=allp->suffix; 
                        } 
                        lnode=cur->arr[val]; 
                        return ; 
                    } 
                    else 
                    { 
                        node * tmp=new node; 
                        for(int i=0;i<26;i++) 
                            tmp->arr[i]=NULL; 
                        tmp->len=(cur->len)+2; 
                        tmp->suffix=NULL; 
                        tmp->cnt=0; 
                        if(tmp->len==1) 
                            tmp->suffix=root2; 
                        else 
                        { 
                            cur=cur->suffix; 
                            while(1) 
                            { 
                                int sz2=cur->len; 
                                if((s[pos]==s[(pos-sz2)-1])) 
                                { 
                                    tmp->suffix=cur->arr[val]; 
                                    break; 
                                } 
                                cur=cur->suffix; 
                            } 
                        } 
                        (cur2->arr[val])=tmp; 
                        lnode=tmp; 
                        node * allp=tmp->suffix; 
                        while(allp->len!=0&&allp->len!=-1) 
                        { 
                            allp->cnt+=1; 
                            allp=allp->suffix; 
                        } 
                    } 
                    break; 
                } 
                cur=cur->suffix; 
                while(1) 
                { 
                    int sz2=cur->len; 
                    if((s[pos]==s[(pos-sz2)-1])) 
                    { 
                        break; 
                    } 
                    cur=cur->suffix; 
                } 
            } 
        } 
    }; 
    LL int ans; 
    void dfs(node * cnode) 
    { 
        ans+=((cnode->cnt)+1); 
        for(int i=0;i<26;i++) 
        { 
            if(cnode->arr[i]!=NULL) 
                dfs(cnode->arr[i]); 
        } 
    } 
    int main() 
    { 
        ptree p1; 
        lnode=p1.root1; 
        cin>>s; 
        for(int i=0;i<s.size();i++) // processing string character by character
            p1.add(i); 
        dfs(p1.root1); 
        dfs(p1.root2); 
        cout<<ans-2; 
        return 0; 
    } 