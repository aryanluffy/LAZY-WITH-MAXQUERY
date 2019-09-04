#include <bits/stdc++.h>
#define lli long long int
#define pb push_back
#define mod 1000000007
#pragma GCC optimize ("-O2")
#define mod2 998244353
#define MAXN 1000000000
#define v32 vector<int>
#define v64 vector<lli>
#define v1024 vector <vector <int>>
#define v4096 vector <vector <lli>>
#define vt vector
#define f(x, y, z) for (int x = y; x < z; x++)
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
#define p_q priority_queue 
#define min_p_q priority_queue <int,vt <int>,greater <int>>
using namespace std;
using namespace __gnu_pbds; 

class LAZY //currently set to set a given range by a value
{
   public:
   struct node
   {
    lli l,r,lazy=0;lli lazyval=0,sum=0,maxel=0, maxval=-MAXN;
   };	
   vt <node> st;v64 h;
   LAZY(v64 a)
   { 
   	  h=a;
   	  st.resize(4*h.size());
   	  cst(0,h.size()-1);
   }	
   int intersectiontype1(int l,int r,int ll,int rr)
   { 
      	if(r<ll || rr<l)
        return 0;
        return 1;
   }
   void cst(int l,int r,int k=0)
   {
    st[k].l=l,st[k].r=r;
    if(l==r)
        { 
          st[k].sum=h[l];
          st[k].maxel=l;
          st[k].maxval=h[l];   
          return;
        }
    cst(l,(l+r)/2,2*k+1);
    cst((l+r)/2+1,r,2*k+2);
    st[k].sum=st[2*k+1].sum+st[2*k+2].sum; 
    st[k].maxval=max(st[2*k+1].maxval,st[2*k+2].maxval);
    if(st[2*k+1].maxval>=st[2*k+2].maxval)
    st[k].maxel=st[2*k+1].maxel;
    else st[k].maxel=st[2*k+2].maxel;   
   }
   void shift(int k)
   {
    st[k].sum+=(st[k].r-st[k].l+1)*st[k].lazyval;
    st[k].maxval+=st[k].lazyval;
    if(st[k].l!=st[k].r){
      st[2*k+1].lazyval+=st[k].lazyval;
      st[2*k+2].lazyval+=st[k].lazyval;
      st[2*k+1].lazy=st[2*k+2].lazy=1;
    }
    st[k].lazyval=0;
    st[k].lazy=0;      
   }
   lli query(int l,int r,int k=0)
   {
	if(st[k].lazy!=0)
       shift(k);
   int ll=st[k].l,rr=st[k].r,mid=(ll+rr)/2;
   if(ll>=l && rr<=r)
       return st[k].sum;
       lli ans=0;   
       if(intersectiontype1(ll,mid,l,r)==1)
          ans=query(l,r,2*k+1);
       if(intersectiontype1(1+mid,rr,l,r)==1)
          ans+=query(l,r,2*k+2);
          return ans;     
   }
   pair<lli,lli> maxquery(int l,int r,int k=0)
   {
	   if(st[k].lazy!=0)
       shift(k);
     int ll=st[k].l,rr=st[k].r,mid=(ll+rr)/2;
     if(ll>=l && rr<=r)
       return {st[k].maxel,st[k].maxval};
       pair<lli,lli> ans={-1,-MAXN*1000000ll};   
       if(intersectiontype1(ll,mid,l,r)==1)
          ans=maxquery(l,r,2*k+1);
       if(intersectiontype1(1+mid,rr,l,r)==1)
        { 
          pair <lli,lli> temp=maxquery(l,r,2*k+2);
          if(ans.second<temp.second) ans.first=temp.first,ans.second=temp.second;
        }
          return ans;     
   }
   void update(int l,int r,lli x,int k=0)
   {
	  if(l>r)
		return;
   int ll=st[k].l,rr=st[k].r,mid=(ll+rr)/2;
   if(ll>=l && rr<=r)
         {st[k].lazyval+=x;
          st[k].lazy=1;      
         return;}
         if(st[k].lazy!=0)
           shift(k);
           if(st[k].l==st[k].r) return;
   if(intersectiontype1(ll,mid,l,r)==1)
      update(l,r,x,2*k+1);
   if(intersectiontype1(mid+1,rr,l,r)==1)
      update(l,r,x,2*k+2);
      if(st[2*k+1].lazy!=0)
       shift(2*k+1);
       if(st[2*k+2].lazy!=0)
       shift(2*k+2);
    st[k].sum=st[2*k+1].sum+st[2*k+2].sum; 
    st[k].maxval=max(st[2*k+1].maxval,st[2*k+2].maxval);
    if(st[2*k+1].maxval>=st[2*k+2].maxval)
    st[k].maxel=st[2*k+1].maxel;
    else st[k].maxel=st[2*k+2].maxel;          
   }
};

lli arr[1000][1000];
int main() 
{ 
  fastio;
  

  return 0; 	
}
