/*...Part - 01...*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <deque>
#include <iterator>
#include <bitset>
#include <assert.h>
#include <new>
#include <sstream>
//#include <bits/stdc++.h>
using namespace std ;

/*...Part - 02...*/

typedef long long               ll ;
typedef long double             ld ;
typedef unsigned long long      ull ;
typedef pair<int,int>           pii ;
typedef pair<ll,ll>             pll ;
typedef vector<int>             vi ;
typedef vector<ll>              vll ;
typedef vector<vector<int>>     vvi ;

int Int(){int x ; scanf("%d",&x) ; return x ;}
ll Long(){ll x ; scanf("%lld",&x) ; return x ;}

/*...Part - 03...*/
/*....Debugger....*/

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {cout << endl ;}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << ' ' ;
    err(++it, args...);
}

/*...Part - 04...*/
/*...Needed to change according to problem requirements...*/

const int N          = (int)2e5 + 5 ;
const int maxN       = (int)1e6 + 6 ;
const ll  Mod        = (ll)1e9 + 7 ;
const int inf        = (int)2e9 ;
const ll  Inf        = (ll)1e18 ;

/*..........................................................*/
/*...Part - 05...*/

#define     debug(x)    cerr << #x << " = " << x << '\n' ;
#define     rep(i,b,e)  for(__typeof(e) i = (b) ; i != (e + 1) - 2 * ((b) > (e))  ; i += 1 - 2 * ((b) > (e)))
#define     Int         Int()
#define     Long        Long()
#define     all(x)      x.begin() , x.end()
#define     sz(x)       (int)x.size()
#define     ff          first
#define     ss          second
#define     pb          push_back
#define     eb          emplace_back
#define     mem(a)      memset(a , 0 ,sizeof a)
#define     memn(a)     memset(a , -1 ,sizeof a)

/*...Part - 06...*/
/*...... ! Code start from here ! ......*/

int team[N], par[N][20], low[N], in[N], ID[N], dep[N], comp[N];
int tm, cur, up[N], down[N];
vvi g ;
vector < pii > brg ;

void Set(){
	for(int i = 0 ; i < N ; ++i)
		team[i] = i ;
}

int Find(int s){
	return s == team[s] ? s : Find(team[s]) ;
}

void merge(int u, int v){
	team[Find(u)] = team[Find(v)] ;
}

void bridge(int s, int p = 0){
	low[s] = in[s] = ++tm ;
	int cnt = 0 ;
	for(int i : g[s]){
		if(i == p){
			if(cnt)low[s] = min(low[s], in[i]) ;
			else {
				cnt = 1 ;
				continue ;
			}
			
		}
		if(in[i])low[s] = min(low[s], in[i]) ;
		else{
			bridge(i, s) ;
			low[s] = min(low[s], low[i]) ;
			if(low[i] > in[s]){
				brg.pb({s, i}) ;
			}
			else{
				merge(s, i) ;
			}
		}
	}
}

void dfs(int s, int p = 0){
	par[s][0] = p ;
	dep[s] = 1 + dep[p] ;
	for(int i = 1 ; i < 17 ; ++i)
		par[s][i] = par[par[s][i - 1]][i - 1] ;
	for(int i : g[s]){
		if(i - p)dfs(i, s) ;
	}
}

int LCA(int a, int b){
	if(dep[a] < dep[b])swap(a, b) ;
	int d = dep[a] - dep[b] ;
	for(int i = 16 ; i >= 0 ; --i){
		if(d & (1 << i))a = par[a][i] ;
	}
	if(a == b)return a; 
	for(int i = 16 ; i >= 0 ; --i){
		if(par[a][i] != par[b][i])
		a = par[a][i], b = par[b][i] ;
	}
	return par[a][0] ;
}

int intersection(int a, int b, int c, int d){
	int x = LCA(a, c) ;
	x = a ^ c ^ x ;
	int y = LCA(b, d) ;
	int dist = dep[y] - dep[x] ;
	return max(0, dist) ;
}

int main(){
    int test = 1 , tc = 0 ;
    while(test--){
        int n = Int, m = Int, q = Int ;
        g.resize(n + 1) ;
        for(int i = 1 ; i <= m ; ++i){
        	int x = Int, y = Int ;
        	g[x].pb(y) ;
        	g[y].pb(x) ;
        }
        Set() ;
        bridge(1) ;
        for(int i = 1 ; i <= n ; ++i){
        	comp[i] = Find(i) ;
        }
        vi st(n + 1, 0), box ;
        for(int i = 1 ; i <= n ; ++i){
        	int x = comp[i] ;
        	if(st[x])continue ;
        	box.pb(x) ;
        	st[x] = 1 ;
        }
        sort(all(box)) ;
        n = sz(box) ;
        int cc = 0 ;
        for(int i : box){
        	ID[i] = ++cc ;
        }
        g.clear() ;
        g.resize(n + 1) ;
        for(auto i: brg){
        	int u = comp[i.ff], v = comp[i.ss] ;
        	g[ID[u]].pb(ID[v]) ;
        	g[ID[v]].pb(ID[u]) ;
        }
        dfs(1) ;
        while(q--){
        	int a = Int, b = Int, c = Int, d = Int ;
        	a = ID[comp[a]], b = ID[comp[b]], c = ID[comp[c]], d = ID[comp[d]] ;
        	int lca_ab = LCA(a, b) ;
        	int lca_cd = LCA(c, d) ;
        	int lca_abcd = LCA(lca_ab, lca_cd) ;
        	
        	int tot = dep[c] + dep[d] - 2 * dep[lca_cd] ;
        	if(lca_abcd ^ lca_cd and lca_abcd ^ lca_ab){
        		printf("%d\n",tot);
        		continue ;
        	}
        	int inter = intersection(lca_ab, a, lca_cd, c) ;
        	inter += intersection(lca_ab, a, lca_cd, d) ;
        	inter += intersection(lca_ab, b, lca_cd, c) ;
        	inter += intersection(lca_ab, b, lca_cd, d) ;
        	printf("%d\n",tot - inter);
        }
    }
    return 0 ;
}

/*...Always look at the part - 04...*/
/*...............END................*/


