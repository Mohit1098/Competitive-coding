class DSU{
public:
	int * par,*size;


	DSU(int n){
		par=new int[n+1];
		size=new int[n+1];

		FOR(i,0,n+1){
			par[i]=i;
			size[i]=0;
		}
	}

	int find(int a){
		int p=a,t;
		while(par[p]!=p)
			p=par[p];

		while(p!=a){
			t=par[a];
			par[a]=p;
			a=t;	
		}

		return a;
		
	}

	void union_(int a,int b){
		int u1=find(a);
		int u2=find(b);

      if(u1 == u2)
         return ;

		if(size[u1]<size[u2]){
			par[u1]=u2;
		}else{
			if(size[u2]<size[u1]){
				par[u2]=u1;
			}
			else{
				par[u1]=u2;
				size[u2]++;
			}
		}
	}
};
