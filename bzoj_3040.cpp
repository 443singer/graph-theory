#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
#define P pair<int,long long> 
const int N = 1000003;
const int M = 10000013;
int first[N],next_[M],to[M],eg,d[M];
long long dis[N];
inline void addedge(int x,int y,int dis) {
	next_[++eg] = first[x];
	first[x] = eg;
	to[eg] = y;
	d[eg] = dis;
}
int n,m,T,rxa,rxc,rya,ryc,rp,x,y,z;
struct cmp {
	bool operator() (P a,P b) {
		return a.second>b.second;
	}
};
priority_queue<P,vector<P >,cmp>q;
bool vis[N];
void dijkstra() {
	memset(dis,0xf,sizeof(dis));
	dis[1] = 0;
	q.push(make_pair(1,0));
	while(!q.empty()) {
		int now = q.top().first; q.pop();
		if(vis[now]) continue;
		vis[now] = 1;
		for(int i = first[now] ; i ; i = next_[i]) {
			if(dis[now]+d[i] < dis[to[i]]) {
				dis[to[i]] = dis[now]+d[i];
				q.push(make_pair(to[i],dis[to[i]]));
			}
		}
	}
}

int main() {
	scanf("%d%d",&n,&m);
	scanf("%d%d%d%d%d%d",&T,&rxa,&rxc,&rya,&ryc,&rp);
	for(int i = 1 ; i <= n ; ++i) {
		x = ((long long)x*rxa+rxc)%rp;
		y = ((long long)y*rya+ryc)%rp;
		int a = min(x%n+1,y%n+1);
		int b = max(y%n+1,y%n+1);
		addedge(a,b,100000000-100*a);
	}
	for(int i = 1 ; i <= m-T ; ++i) {
		scanf("%d%d%d",&x,&y,&z);
		addedge(x,y,z);
	}
	dijkstra();
	cout << dis[n] << endl;
}
