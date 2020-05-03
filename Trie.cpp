class node{
public:
   int total;
   node* next[26];

   node(){
      total=0;
      FOR(i,0,26){
         next[i]=NULL;
      }
   }
};

int n,k;

void add(string &s,int l,node* root){

   if(l==s.length()){
      root->total++;
      return;
   }

   if(root->next[s[l]-'A']==NULL){
      root->next[s[l]-'A']=new node();
   }

   add(s,l+1, root->next[s[l]-'A']);
}

int ans=0;

int traverse(node * root,int l){
   if(root==NULL)
      return 0;
//   cout<<root->total<<endl;
   int sum=0;

   FOR(i,0,26){
      sum+=traverse(root->next[i],l+1);
   }
   int temp=((sum+root->total)/k);
   ans+=(temp)*(l);
   sum= (sum+root->total)%k;

   return (sum);
}


//..................
//without pointers


class Trie{
public:
   class node{
   public:
      ve<int>next;
      int total;
      node(){
         next.assign(26,-1);
         total =0;
      }
   };
   
   ve<node>nodes;
   int nodeCount;
   ve<ve<int>>dp;
   
   Trie(int n){
      nodes.emplace_back();
      nodeCount=1;
      dp.assign(n,ve<int>(26,0));
   }
   
   void addString(string& s,int b){
      int cur =0;
      for(int i=s.length()-1;i>=0;i--){
         int c = (s[i]-'a');
         if(nodes[cur].next[c]==-1){
            nodes.emplace_back();
            nodes[cur].next[c] =nodeCount++;
         }
         cur = nodes[cur].next[c];
      }
      nodes[cur].total+=b;
   }
   
   int traverse(string& s,int ind){
      int cur =0;
      int len=0;
      for(int i=s.length()-1;i>=0;i--){
         int c = (s[i]-'a');
         cur = nodes[cur].next[c];
         dp[ind][25-len]+=nodes[cur].total;
         len++;
      }
      FOR(j,1,26)
         dp[ind][j]+=dp[ind][j-1];
   }
};

