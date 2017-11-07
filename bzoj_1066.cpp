#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1003;
const int M = 1000003;
const int INF = 2000000000;
int first[N],next_[M*2],to[M*2],cap[M*2],eg = 1;
inline void addedge(int x,int y,int d) {
	next_[++eg] = first[x];
	first[x] = eg;
	to[eg] = y;
	cap[eg] = d;
}
inline void add(int x,int y,int d) {
	addedge(x,y,d);
	addedge(y,x,0);
}
int cur[N];
int q[N],t,h,dep[N],S,T,n,m;
bool Bfs() {
	memset(dep,0,sizeof(dep));
	t = 1 ; h = 0;
	q[1] = S ; dep[S] = 1;
	do {
		int u = q[++h];
		for(int i = first[u] ; i ; i = next_[i]) {
			int v = to[i];
			if(!dep[v] && cap[i]) {
				dep[v] = dep[u] + 1;
				q[++t] = v;
			}
		}
	}while(h<t);
	return dep[T]!=0;
}
int dfs(int u,int flow) {
	if(u==T || !flow) return flow;
	int &i = cur[u] , ret = 0;
	if(i==-1) i = first[u];
	for( ; i ; i = next_[i]) {
		int v = to[i];
		if(dep[v]==dep[u]+1 && cap[i]) {
			int t = dfs(v,min(flow,cap[i]));
			cap[i] -= t ; flow -= t;
			cap[i^1] += t ; ret += t;
		}
		if(!flow) break;
	}
	return ret;
}
int dinic() {
	int ret = 0;
	while(Bfs()) {
		memset(cur,-1,sizeof(cur));
		ret += dfs(S,INF);
	}
	return ret;
}
char G1[23][23],G2[23][23];
int d,biao[23][23],ans,cnt;
int sqr(int x) {return x*x;}
int main() {
	scanf("%d%d%d",&n,&m,&d);
	S = 0 ; T = n*m*2+1;
	for(int i = 1 ; i <= n ; ++i) scanf(" %s",G1[i]+1);
	for(int i = 1 ; i <= n ; ++i) scanf(" %s",G2[i]+1);
	for(int i = 1 ; i <= n ; ++i)
		for(int j = 1 ; j <= m ; ++j)
			biao[i][j] = ++cnt;
	for(int i = 1 ; i <= n ; ++i)
		for(int j = 1 ; j <= m ; ++j) {
			if(G2[i][j]=='L') ans++,add(S,biao[i][j],1);
			int C = G1[i][j]-'0';
			if(!C) continue;
			int x = biao[i][j] , y = biao[i][j]+n*m;
			add(x,y,C);
			if(i<=d || j<=d || i+d>n || j+d>m) add(y,T,INF);
			else for(int k = 1 ; k <= n ; ++k)
				for(int l = 1 ; l <= m ; ++l) {
					if(i==k && j==l) continue;
					int C2 = G1[k][l] - '0';
					if(!C2) continue;
					if(sqr(i-k)+sqr(j-l) <= sqr(d))
						add(y,biao[k][l],INF);
				}
		}
	
	cout << ans - dinic() << endl;
}
