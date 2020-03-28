void updatemin(int*lazymintree,int* mintree,int s,int e,int qs,int qe,int index,int value){

	if(lazymintree[index]!=0){
		mintree[index]+=lazymintree[index];
		if(s!=e){
			lazymintree[2*index]+=lazymintree[index];
			lazymintree[2*index+1]+=lazymintree[index];
		}
		lazymintree[index]=0;
	}

	if(s>=qs && e<=qe){
		mintree[index]+=value;
		if(s!=e){
			lazymintree[2*index]+=value;
			lazymintree[2*index+1]+=value;
		}
		return;
	}

	if(e<qs || s>qe)
		return;

	int mid=(s+e)/2;
	updatemin(lazymintree,mintree,s,mid,qs,qe,index*2,value);
	updatemin(lazymintree,mintree,1+mid,e,qs,qe,index*2+1,value);
	mintree[index]=min(mintree[index*2],mintree[2*index+1]);
}

int findmin(int*lazymintree,int* mintree,int s,int e,int qs,int qe,int index){
	// cout<<s<<" "<<e<<" "<<lazymintree[index]<<endl;
	if(lazymintree[index]!=0){
		mintree[index]+=lazymintree[index];
		if(s!=e){
			lazymintree[2*index]+=lazymintree[index];
			lazymintree[2*index+1]+=lazymintree[index];
		}
		lazymintree[index]=0;
	}

	if(qs<=s && qe>=e)
		return mintree[index];

	if(e<qs || s>qe)
		return INT_MAX;

	int mid=(s+e)/2;

	return min(findmin(lazymintree,mintree,s,mid,qs,qe,index*2),findmin(lazymintree,mintree,mid+1,e,qs,qe,index*2+1));

}

void buildmintree(int *mintree,int* arr,int s,int e,int index){

	if(s==e){
		mintree[index]=arr[s];
		return;
	}
	int mid=(s+e)/2;
	buildmintree(mintree,arr,s,mid,index*2);
	buildmintree(mintree,arr,mid+1,e,index*2+1);

	mintree[index]=min(mintree[index*2],mintree[index*2+1]);
	return;
}
