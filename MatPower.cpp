#define MX
#define MOD

void multiply(int ans[MX][MX],int a[MX][MX], int b[MX][MX]){
    for (int i = 0; i < MX; i++){ 
        for (int j = 0; j < MX; j++){ 
            ans[i][j] = 0; 
            for (int k = 0; k < MX; k++) {              
              	ans[i][j] += a[i][k]*b[k][j]; 
        		ans[i][j]%=(MOD-1);
        	}
        } 
    } 
} 
  
void mat_power(int ans[MX][MX],int mat[MX][MX],int n){
	if(n==1){
		FOR(i,0,MX){
			FOR(j,0,MX){
				ans[i][j]=mat[i][j];
			}
		}
		return ;
	}
	int temp1[MX][MX],temp2[MX][MX];
	mat_power(temp1,mat,n>>1);
	
	if(n&1)
		multiply(temp2,temp1,mat);
	else
		mat_power(temp2,temp1,1);

	multiply(ans,temp1,temp2);
	
}