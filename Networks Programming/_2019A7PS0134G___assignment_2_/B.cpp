# include <bits/stdc++.h>
using namespace std;
# define ll long long int
# define loop(a,b) for(int i=0;i<b;i++)
# define map<long long int,long long int> m1
ll point=0;
 
void check(vector<vector<ll>> & vec, pair<ll,ll> p1, pair<ll,ll> p2, pair<ll,ll> p3){
    ll k =point;
    k++;
    point=k;
    vec[p1.first][p1.second]=k; vec[p2.first][p2.second]=k;vec[p3.first][p3.second]=k;
        
}
void helper(vector<vector<ll>> & vec, ll i, ll j,ll n){
    
    if(n<0 || n>vec.size())return ;
    
    if(n==2){
        
        ll p =point;
        p++;
        point=p;
        for(ll k=0;k<n;k++){
              for(ll m=0;m<n;m++){    if(vec[i+k][m+j]==0ll) vec[i+k][m+j]=p; }
              
        }
        
        return ;    
    }
    ll rowpos=0,colpos=0;
    for(ll k=i;k<i+n;k++){
            for(ll m=j;m<j+n;m++){
                   if(vec[k][m]!=0ll)
                    rowpos=k,colpos=m;
            }
    }
    
    if(rowpos< i+n/2){
         if(colpos<j+ n/2){
                ll n1= i+(n/2);
                ll n2= (j+n/2)-1;
                pair<ll,ll> p1= {n1,n2};
                ll n3= i+n/2;
                ll n4= j+n/2;
                pair<ll,ll> p2= {n3,n4};
                ll n5=  i+(n/2)-1;
                ll n6=  j+(n/2);
                pair<ll,ll> p3= {n5,n6};
                check(vec,p1,p2,p3) ;
                
         }
         else if(colpos>= j+n/2){
                ll n1= i+n/2;
                ll n2= (j+n/2)-1;
                pair<ll,ll> p1= {n1,n2};
                ll n3= i+n/2;
                ll n4= j+n/2;
                pair<ll,ll> p2= {n3,n4};
                ll n5=  i+(n/2)-1;
                ll n6=  j+(n/2)-1;
                pair<ll,ll> p3= {n5,n6};
                check(vec,p1,p2,p3) ;
         }
    }
    
    else if(rowpos>=i+n/2){
         
         if(colpos<j+n/2){
                ll n1= (i+n/2)-1;
                ll n2= (j+n/2);
                pair<ll,ll> p1= {n1,n2};
                ll n3= i+n/2;
                ll n4= j+n/2;
                pair<ll,ll> p2= {n3,n4};
                ll n5=  i+(n/2)-1;
                ll n6=  (j+n/2)-1;
                pair<ll,ll> p3= {n5,n6};
                check(vec,p1,p2,p3) ;
         }
         
         else if(colpos>=j+n/2){
                ll n1= (i+n/2)-1;
                ll n2= (j+n/2);
                pair<ll,ll> p1= {n1,n2};
                ll n3= i+n/2;
                ll n4= (j+n/2)-1;
                pair<ll,ll> p2= {n3,n4};
                ll n5=  i+(n/2)-1;
                ll n6=  (j+n/2)-1;
                pair<ll,ll> p3= {n5,n6};
                check(vec,p1,p2,p3) ;
         }
    }
    
    
    helper(vec,i,j+n/2,n/2);
    helper(vec,i+n/2,j,n/2);
    helper(vec,i+n/2,j+n/2,n/2);
    helper(vec,i,j,n/2);
    
    return ;
    
}
 
 
void solve(){
    ll n,a,b ;
    cin>>n>>a>>b;
    vector<vector<ll>> vec(n);
    for(ll i=0;i<n;i++){
        for(ll j=0;j<n;j++){
            if(i == a-1 && j== b-1){
                vec[i].push_back(-1);
            }
            else vec[i].push_back(0);
        }
    }
    
    helper(vec,0,0,n);
    
    for(auto x:vec){
        for(auto y:x)cout<<y<<" ";
        cout<<endl;
    }
    
}
int main(){
    ll t;
    //cin>>t;
    t=1;
    while(t--){
        solve();
        cout<<endl;
    }
}