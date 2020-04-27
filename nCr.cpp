
const int factN =2e5+1;
int fact[factN],modI[factN];

int nCr(int n,int r){
   if(r>n)
      return 0;

   return (fact[n]*((modI[r]*modI[n-r])%MOD))%MOD;
}
