void updatemax(int*lazymaxtree,int* maxtree,int s,int e,int qs,int qe,int index,int value){

	if(lazymaxtree[index]!=0){
		maxtree[index]+=lazymaxtree[index];
		if(s!=e){
			lazymaxtree[2*index]+=lazymaxtree[index];
			lazymaxtree[2*index+1]+=lazymaxtree[index];
		}
		lazymaxtree[index]=0;
	}

	if(s>=qs && e<=qe){
		maxtree[index]+=value;
		if(s!=e){
			lazymaxtree[2*index]+=value;
			lazymaxtree[2*index+1]+=value;
		}
		return;
	}

	if(e<qs || s>qe)
		return;



	int mid=(s+e)/2;
	updatemax(lazymaxtree,maxtree,s,mid,qs,qe,index*2,value);
	updatemax(lazymaxtree,maxtree,1+mid,e,qs,qe,index*2+1,value);

	maxtree[index]=max(maxtree[index*2],maxtree[2*index+1]);
}

int findmax(int*lazymaxtree,int* maxtree,int s,int e,int qs,int qe,int index){

	if(lazymaxtree[index]!=0){
		maxtree[index]+=lazymaxtree[index];
		if(s!=e){
			lazymaxtree[2*index]+=lazymaxtree[index];
			lazymaxtree[2*index+1]+=lazymaxtree[index];
		}
		lazymaxtree[index]=0;
	}

	if(qs<=s && qe>=e)
		return maxtree[index];

	if(e<qs || s>qe)
		return -INT_MAX;

	int mid=(s+e)/2;

	return max(findmax(lazymaxtree,maxtree,s,mid,qs,qe,index*2),findmax(lazymaxtree,maxtree,mid+1,e,qs,qe,index*2+1));

}

void buildmaxtree(int *maxtree,int* arr,int s,int e,int index){

	if(s==e){
		maxtree[index]=arr[s];
		return;
	}
	int mid=(s+e)/2;
	buildmaxtree(maxtree,arr,s,mid,index*2);
	buildmaxtree(maxtree,arr,mid+1,e,index*2+1);

	maxtree[index]=max(maxtree[index*2],maxtree[index*2+1]);
	return;
}

