#include<bits/stdc++.h>
#define R 20
using namespace std;
map< int, pair<int,int> > res;
int getSoln(int dist[], int V,bool x)
{
   for (int i = 0; i < V; i++){
   		int a = res[i].first;
   		int b = res[i].second;
   		if(x){   
		   res[i] = make_pair(dist[i],b);
		}
   		else{
   		   	
		   res[i] = make_pair(a,dist[i]);
		}
   }
}
int minDistance(int dist[], bool sptSet[])
{
	int V = 100;
	int min = INT_MAX, min_index;
	for (int v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] <= min)
         	min = dist[v], min_index = v;
	return min_index;
}
void dijkstra(int graph[100][100], int src,bool x)
{
	int V = 100;
    int dist[100];
	bool sptSet[100];
	for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
	dist[src] = 0;
	for (int count = 0; count < V-1; count++)
	{
		int u = minDistance(dist, sptSet);
       	sptSet[u] = true;
	   	for (int v = 0; v < V; v++)
	   	if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
    }
	getSoln(dist, V, x);
		
}
float distance(int a,int b){
	return sqrt(a*a + b*b);
}
class node{
	public:
		int x,y,n;
	public:
		node(int a, int b,int c){
			x=a,y=b,n=c;
		}
		node(int c){
			n = c;
			x = rand()%100;
			y = rand()%100;
		}
		void disp(){
			cout<<"n = "<<n<<",";
		}
};
int main(){
	freopen("output.txt","w",stdout);
	srand(time(NULL));
	vector<node*> nodes;
	for(int i = 0; i < 100 ; i++){
		nodes.push_back(new node(i));
	}
	set<node*> adj[100];
	for(int i = 0; i < 100 ; i++){
		int x0 = nodes[i]->x;
		int y0 = nodes[i]->y;
		for(int j = 0; j < 100 ; j++){
			if(i==j) 
				continue;
			int x1 = nodes[j]->x;
			int y1 = nodes[j]->y;
			float dist = distance(x1-x0,y1-y0);
			if(dist < R){
				adj[i].insert(nodes[j]);
			}
		}
	}
	node *p;
	int graph[100][100];
	for(int i = 0 ; i < 100 ; i++){
		for(int j = 0 ; j < 100 ; j++){
			graph[i][j] = 0;
		}
	}
	for(int i = 0 ; i < 100 ; i++){
		for (auto it = adj[i].begin(); it != adj[i].end(); it++){
			p = *it;
			graph[i][p->n] = 1;
		}
	}
	//choosing 0th node as src
	dijkstra(graph,0,1);
	
	//creating a wormhole link 50th and 51st link
	for(int i = 0 ; i < 100 ; i++){
		swap(graph[50][i],graph[51][i]);
	}
	//After wormhole link is created
	dijkstra(graph,0,0);
	//Print
	printf("Node \t\tHop count from Source(Node 0)\t\tHop count after wormhole\t\tChanges\n");
	for (int i = 0; i < 100; i++){
		cout<<i<<"\t\t\t\t"<<res[i].first<<"\t\t\t\t\t\t\t\t"<<res[i].second<<"\t\t\t\t\t\t\t\t"<<(res[i].first!=res[i].second)<<"\n";
	}
	return 0;
}
