# include <bits/stdc++.h>
using namespace std;
# define ll long long int
# define loop(i,b) for(int i=0;i<b;i++)

void printVec(vector< vector<ll> > v){
    loop(i, v.size()){
        loop(j, v[i].size()){
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}

void recur(vector< vector<ll> > & v, ll i, ll j,ll num){
    static ll pointer = 0;
    if(num<=0){return;}
    if(num==2){
        
        ll x = ++pointer;
        for(ll k=0;k<num;k++){
            for(ll m=0;m<num;m++){    
                if(v[i+k][m+j]==0ll) 
                v[i+k][m+j]=x; 
            }  
        }
        return ;   
    }
    ll rowpos=0,colpos=0;
    for(ll k=0;k<num;k++){
        for(ll m=0;m<num;m++){
            if(v[k+i][m+j]!=0ll)
                rowpos=k,colpos=m;
        }
    }
    
    if(rowpos< i+num/2){
        ll c3;
        if(colpos<j+ num/2){c3=  j+(num/2);}
        else if(colpos>= j+num/2){c3=  j+(num/2)-1;}
        ++pointer;
        v[i+(num/2)][(j+num/2)-1]=pointer; 
        v[i+num/2][j+num/2]=pointer;
        v[i+(num/2)-1][c3]=pointer;
    }
    
    else if(rowpos>=i+num/2){
        ll n4;
        if(colpos<j+num/2){n4= j+num/2;}
        else if(colpos>=j+num/2){n4= (j+num/2)-1;}
        ++pointer;
        v[(i+num/2)-1][(j+num/2)]=pointer; 
        v[i+num/2][n4]=pointer;
        v[i+(num/2)-1][(j+num/2)-1]=pointer;
    }
    recur(v,i,j+num/2,num/2);
    recur(v,i+num/2,j,num/2);
    recur(v,i+num/2,j+num/2,num/2);
    recur(v,i,j,num/2);
    return ;
    
}
 
int main(){
    ll n,a,b ;
    cin>>n>>a>>b;
    vector< vector<ll> > vec(n);
    for(ll i=0;i<n;i++){
        for(ll j=0;j<n;j++){
            if(i == a-1 && j== b-1){
                vec[i].push_back(-1);
            }
            else vec[i].push_back(0);
        }
    }
    recur(vec,0,0,n);
    printVec(vec);
}