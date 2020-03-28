void getsieve(bool * p, LL n){
//NloglonN for all numbers upto N
	memset(p,true,(n+1)*sizeof(bool));
	for(LL i=4;i<=n;i+=2)
		p[i]=0;
	p[2]=1;
	for(LL i=3;i<=n;i+=2){
		if(p[i]){
			for(LL j=i*i;j<=n;j+=2*i){
				p[j]=false;
			}
		}
	}
	p[1]=p[0]=0;
}


void getsegmentedsieve(bool *p,LL a,LL b){
	// p is array from a to b
	// mapped on 0 to b-a
	// create p[b-a+1]
	LL rootb=(LL)sqrt(b);
	bool *p1=new bool[rootb+1];
	getsieve(p1,rootb);
	memset(p,true,(b-a+1)*sizeof(bool));
	if(a%2==0){
		for(LL i=a;i<=b;i+=2)
			p[i-a]=0;
	}
	else{
		for(LL i=a+1;i<=b;i+=2)
			p[i-a]=0;
	}
	for(LL i=3;i<=rootb;i+=2){
		if(p1[i]){
			for(LL j=a;j<=b;++j){
				if(p[j-a]==1){
					if(j==i)
						continue;
					if(j%i==0){
						p[j-a]=0;
					}
				}
			}
		}
	}
}


bool isPrime(LL a){
	//N^.5 for one particular number
	if(a==2)
		return true;
	if(a%2==0)
		return false;
	LL root=sqrt(a);
	for(int i=3;i<=(LL)root;i+=2){
		if(a%i==0)
			return false;
	}
	return true;
}


void getprimefactors(unordered_map<LL,LL> & m,LL n){
// using getsieve function also
	while(n%2==0){
		m[2]+=1;
		n/=2;
	}
	LL root=(LL)sqrt(n+1);
	bool* primes=new bool[root+1];
	getsieve(primes,root);
	for(int i=3;i<=root;i+=2){
		if(primes[i]){
			while(n%i==0){
				m[i]+=1;
				n/=i;
			}
			if(n==1)
				break;
		}
	}
	if(n!=1){
		m[n]+=1;
	}
}

void sieveprimefactors(LL *factors,LL n){
	// factors is of size n+1
	// prime factors for all numbers 1 to n
	memset(factors,-1,(n+1)*sizeof(LL));

	factors[1]=1;

	for(LL i=2;i<=n;i+=2)
		factors[i]=2;

	for(LL i =3;i<=n;i+=2){
		if(factors[i]==-1){
			factors[i]=i;
			for(LL j=i*i;j<=n;j+=2*i){
				if(factors[j]==-1)
					factors[j]=i;
			}
		}
	}
}

void sievedivisors(vector<int>* arr,LL n){
	//divisors of all numbers from 1 to n
	// n logn 

	// arr[1].pb(1);

	for(int i=1;i<=n;++i){
		for(int j=i;j<=n;j+=i){
			arr[j].pb(i);
		}
	}
}