#include<bits/stdc++.h>

using namespace std; 
  
void solve(int tc){
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0 ; i < n;i++){
        cin >> v[i];
    }
    for(int i = 0 ; i < n-1;i++){
        if(v[i+1] < v[i]){
            cout << "YES" << endl;
            return;
        }
    }
    cout << "NO" << endl;
}
  
int main()
{ 
    #ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif

    int t = 1;  
    cin >> t; 
    for(int i = 0;i < t;i++){
        solve(i);
    }
    return 0;
}    