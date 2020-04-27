void updatesum(ll*lazysumtree,ll* sumtree,int s,int e,int qs,int qe,int index,int value){

   if(lazysumtree[index]!=0){
      sumtree[index]+=(e-s+1)*lazysumtree[index];
      if(s!=e){
         lazysumtree[2*index]+=lazysumtree[index];
         lazysumtree[2*index+1]+=lazysumtree[index];
      }
      lazysumtree[index]=0;
   }

   if(s>=qs && e<=qe){
      sumtree[index]+=(e-s+1)*value;
      if(s!=e){
         lazysumtree[2*index]+=value;
         lazysumtree[2*index+1]+=value;
      }
      return;
   }

   if(e<qs || s>qe)
      return ;

   int mid=(s+e)/2;
   updatesum(lazysumtree,sumtree,s,mid,qs,qe,index*2,value);
   updatesum(lazysumtree,sumtree,1+mid,e,qs,qe,index*2+1,value);

   sumtree[index]=(sumtree[index*2]+sumtree[2*index+1]);
}

ll findsum(ll*lazysumtree,ll* sumtree,int s,int e,int qs,int qe,int index){

   if(lazysumtree[index]!=0){
      sumtree[index]+=(e-s+1)*lazysumtree[index];
      if(s!=e){
         lazysumtree[2*index]+=lazysumtree[index];
         lazysumtree[2*index+1]+=lazysumtree[index];
      }
      lazysumtree[index]=0;
   }

   if(qs<=s && qe>=e)
      return sumtree[index];

   if(e<qs || s>qe)
      return 0;

   int mid=(s+e)/2;

   return (findsum(lazysumtree,sumtree,s,mid,qs,qe,index*2)+findsum(lazysumtree,sumtree,mid+1,e,qs,qe,index*2+1));

}

void buildsumtree(ll *sumtree,ll* arr,int s,int e,int index){

   if(s==e){
      sumtree[index]=arr[s];
      return;
   }
   int mid=(s+e)/2;
   buildsumtree(sumtree,arr,s,mid,index*2);
   buildsumtree(sumtree,arr,mid+1,e,index*2+1);

   sumtree[index]=(sumtree[index*2]+sumtree[index*2+1]);
}
