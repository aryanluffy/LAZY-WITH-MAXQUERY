#include <bits/stdc++.h>
#define lli long long int
#define pb push_back
#define mod2 1000000007
#pragma GCC optimize ("-O3")
#define mod 998244353
#define MAXN 1000000000
#define v32 vector<int>
#define v64 vector<lli>
#define v1024 vector <vector <int>>
#define v4096 vector <vector <lli>>
#define vt vector
#define f(x, y, z) for (lli x = y; x < z; x++)
#define fd(x, y, z) for (lli x = y; x > z; x--)
#define lb lower_bound
#define ld long double
#define m64 map<lli,lli>
#define m32 map<int,int>
#define m64it map<lli,lli>::iterator
#define m32it map<int,int>::iterator
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define ist insert
#define endl "\n"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> 
#define p_q priority_queue 
#define min_p_q priority_queue <int,vt <int>,greater <int>>
using namespace std;
using namespace __gnu_pbds; 

template <typename T> 
void DEBUG_ARR(vt<T> a,char c)
{
	f(i,0,a.size())cout<<a[i]<<c;
	cout<<"\n";
}

lli tmod(lli x,lli m=mod){return (x%m+m)%m;}//USE AT YOUR OWN RISK
lli power(lli x, lli y,lli m=mod) 
{
    lli res = 1;  
   
    while (y > 0) 
    { 
        if (y & 1) 
            res = (res*x)%m; 
        y = y>>1; 
        x = (x*x)%m;  
    }
    if(res<0)
       res+=m; 
    return res; 
}

// lli fact[2000009];
// lli ncr(lli n,lli r){
//     lli ans=fact[n];
//     if(r>n)return 0;
//     ans=(ans*power(fact[n-r],mod-2))%mod;
//     ans=(ans*power(fact[r],mod-2))%mod;
//     return ans;
// }
class LAZY //currently set to increase a given range by a value
{
   public:
   struct node{
    lli l,r,lazy=0;lli lazyval=0,sum=0;
    pair<lli,lli> maxel={-1,-MAXN};
    pair<lli,lli> minel={-1,MAXN};
   };	
   vt <node> st;v64 h;
   LAZY(v64 a)
   { 
   	  h=a;
   	  st.resize(4*h.size());
   	  cst(0,h.size()-1);
   }	
   void cst(int l,int r,int k=0)
   {
    st[k].l=l,st[k].r=r;
    if(l==r)
        { 
          st[k].sum=h[l];
          st[k].maxel={l,h[l]};
          st[k].minel={l,h[l]};    
          return;
        }
    cst(l,(l+r)/2,2*k+1);
    cst((l+r)/2+1,r,2*k+2);
    st[k].sum=st[2*k+1].sum+st[2*k+2].sum; 
    if(st[2*k+1].maxel.second>=st[2*k+2].maxel.second)st[k].maxel=st[2*k+1].maxel;
    else st[k].maxel=st[2*k+2].maxel;
    if(st[2*k+1].minel.second<=st[2*k+2].minel.second)st[k].minel=st[2*k+1].minel;
    else st[k].minel=st[2*k+2].minel;
   }
   void shift(int k)
   {
    st[k].sum+=(st[k].r-st[k].l+1)*st[k].lazyval;
    st[k].maxel.second+=st[k].lazyval;
    st[k].minel.second+=st[k].lazyval;
    if(st[k].l!=st[k].r){
      st[2*k+1].lazyval+=st[k].lazyval;
      st[2*k+2].lazyval+=st[k].lazyval;
      st[2*k+1].lazy=st[2*k+2].lazy=1;
    }
    st[k].lazyval=0;
    st[k].lazy=0;      
   }
   lli query(int l,int r,int k=0){
	if(st[k].lazy!=0)
       shift(k);
    int ll=st[k].l,rr=st[k].r,mid=(ll+rr)/2;
    if(l>rr || ll>r)return 0;
    if(ll>=l && rr<=r)
       return st[k].sum;
       return query(l,r,2*k+1)+query(l,r,2*k+2);     
   }
   pair<lli,lli> maxquery(int l,int r,int k=0)
   {
	   if(st[k].lazy!=0)
       shift(k);
     int ll=st[k].l,rr=st[k].r,mid=(ll+rr)/2;
     if(ll>r || l>rr)return {-1,-MAXN*1000000ll};
     if(ll>=l && rr<=r)
       return st[k].maxel;
       pair<lli,lli> ans=maxquery(l,r,2*k+1),ans2=maxquery(l,r,2*k+2);
       if(ans.second>=ans2.second)return ans;
       return ans2;
   }
   pair<lli,lli> minquery(int l,int r,int k=0)
   {
	   if(st[k].lazy!=0)
       shift(k);
       int ll=st[k].l,rr=st[k].r,mid=(ll+rr)/2;
       if(ll>r || l>rr)return {-1,MAXN*1000000ll};
       if(ll>=l && rr<=r) return st[k].minel;
       pair<lli,lli> ans=minquery(l,r,2*k+1),ans2=minquery(l,r,2*k+2);
       if(ans.second<=ans2.second)return ans;
       return ans2;     
   }
   void update(int l,int r,lli x,int k=0)
   {
	  if(l>r)
		return;
   int ll=st[k].l,rr=st[k].r,mid=(ll+rr)/2;
   if(ll>r || l>rr)return;
   if(ll>=l && rr<=r)
         {st[k].lazyval+=x;
          st[k].lazy=1;      
         return;}
         if(st[k].lazy!=0)
           shift(k);
        //    if(st[k].l==st[k].r) return;
      update(l,r,x,2*k+1);
      update(l,r,x,2*k+2);
      if(st[2*k+1].lazy!=0)
       shift(2*k+1);
       if(st[2*k+2].lazy!=0)
       shift(2*k+2);
    st[k].sum=st[2*k+1].sum+st[2*k+2].sum; 
    if(st[2*k+1].maxel.second>=st[2*k+2].maxel.second)st[k].maxel=st[2*k+1].maxel;
    else st[k].maxel=st[2*k+2].maxel;
    if(st[2*k+1].minel.second<=st[2*k+2].minel.second)st[k].minel=st[2*k+1].minel;
    else st[k].minel=st[2*k+2].minel;             
   }
};

int main() 
{ 
    // fact[0]=1;
    // f(i,1,2000001)fact[i]=(i*fact[i-1])%mod;
    fastio;
    int t;
    //cin>>t;	
      t=1;
	while(t--){
        
    }
    return 0; 	
}
