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
