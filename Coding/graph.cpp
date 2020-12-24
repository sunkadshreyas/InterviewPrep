#include<bits/stdc++.h>
using namespace std;

class BridgeGraph
{
	int nodes;
	map<int,list<int>> adjList;
	public:
	BridgeGraph(int nodes)
	{
		this->nodes = nodes;
	}
	void addEdge(int x, int y)
	{
		adjList[x].push_back(y);
		adjList[y].push_back(x);
	}
	void bridgeUtil(int src, bool visited[], int ancestor[], int entrytime[], int& timer, bool& flag, int parent=-1)
	{
		visited[src] = true;
		ancestor[src] = entrytime[src] = timer++;
		list<int> nbrs = adjList[src];
		for(int nbr: nbrs)
		{
			if(nbr == parent)
			{
				// i have come from this route
				continue;
			}
			if(!visited[nbr])
			{
				bridgeUtil(nbr,visited,ancestor,entrytime,timer,flag,src);
				// forward edges all bridges are forward edges
				// set the ancestor to the lowest while returning from dfs
				// for a node it will check all its nbrs and set its time to min time
				ancestor[src] = min(ancestor[src], ancestor[nbr]);
				if(entrytime[src] < ancestor[nbr])
				{
					// nbr doesn't know any other path to the src vertex
					// that's why disc[src] < ances[nbr] which will be a bridge
					cout<<src<<"->"<<nbr<<" is a bridge\n";
					flag = true;
				}
			}
			else
			{
				// is a back edge
				ancestor[src] = min(ancestor[src], entrytime[nbr]);
			}
		}
	}
	void bridgeExists()
	{
		bool visited[nodes];
		int ancestor[nodes];
		// ancestor will give time of a node which is connected to it
		int entrytime[nodes];
		// the discovered time of node
		int timer = 0;
		int src = 0;
		bool flag = false;
		for(int i=0; i<nodes; i++)
		{
			if(!visited[i])
			{
				bridgeUtil(src, visited, ancestor, entrytime, timer, flag);
			}
		}
		if(!flag)
			cout<<"no bridge\n";
	}
};

class DirectedGraph
{
	int nodes;
	map<int,list<int>> adjList;
	public:
	DirectedGraph(int nodes)
	{
		this->nodes = nodes;
	}
	void addEdge(int x, int y)
	{
		adjList[x].push_back(y);
	}
	bool cycleUtil(int src, bool visited[], bool recursionStack[])
	{
		if(visited[src] == false)
		{
			visited[src] = true;
			recursionStack[src] = true;
			list<int> nbrs = adjList[src];
			for(int nbr : nbrs)
			{
				if(!visited[nbr] && cycleUtil(nbr,visited,recursionStack))
				{
					return true;
				}
				else if(recursionStack[nbr])
					return true;
			}
		}
		recursionStack[src] = false;
		return false;
	}
	bool cycleExists()
	{
		bool visited[nodes];
		bool recursionStack[nodes];
		
		for(int i=0; i<nodes; i++)
		{
			visited[i] = false;
			recursionStack[i] = false;
		}
		
		/*
		for(int i=0; i<nodes; i++)
		{
			if(!visited[i])
			{
				if(cycleUtil(i,visited,recursionStack))
					return true;
			}
		}
		*/
		if(cycleUtil(0,visited,recursionStack))
			return true;
		
		return false;
	}
};

class GraphSearch
{
	map<int,list<int>> adjList;
	public:
	void addEdge(int x, int y)
	{
		adjList[x].push_back(y);
		adjList[y].push_back(x);
	}
	void bfsSearch(int src)
	{
		map<int,bool> visited;
		queue<int> q;
		
		q.push(src);
		visited[src] = true;
		
		while(!q.empty())
		{
			int frontNode = q.front();
			q.pop();
			cout<<frontNode<<" ";
			for(int v: adjList[frontNode])
			{
				// all neighbors of frontNode
				if(!visited[v])
				{
					visited[v] = true;
					q.push(v);
				}
			}
		}
		cout<<"\n";
	}
	void dfs_helper(int src, map<int,bool>& visited)
	{
		cout<<src<<" ";
		visited[src] = true;
		
		for(int v: adjList[src])
		{
			if(!visited[v])
			{
				dfs_helper(v,visited);
			}
		}
	}
	void dfsSearch(int src)
	{
		map<int,bool> visited;
		int parent = -1;
		
		dfs_helper(src, visited);
		cout<<"\n";
	}
};


class WeightedGraph
{
	unordered_map<string, list<pair<string,int>>> adjList;
	// src -> [ (dst,weight), (dst,weight) ]
	public:
	void addEdge(string src, string dst, int weight)
	{
		adjList[src].push_back(make_pair(dst,weight));
		// if the edge is directed remove the below line
		adjList[dst].push_back(make_pair(src,weight));
	}
	void printList()
	{
		for(auto p: adjList)
		{
			string src = p.first;
			list<pair<string,int>> dst = p.second;
			cout<<src<<" => ";
			for(auto pr: dst)
			{
				cout<<"("<<pr.first<<" "<<pr.second<<") ";
			}
			cout<<"\n";
		}
	}
};


class Graph
{
	int nodes;
	list<int>* adjList; // or else list<int> adjList[100];
	public:
		Graph(int nodes)
		{
			this->nodes = nodes;
			adjList = new list<int>[nodes];
		}
		void addEdge(int v1, int v2)
		{
			adjList[v1].push_back(v2);
			adjList[v2].push_back(v1);
		}
		void printList()
		{
			for(int i=0; i<nodes; i++)
			{
				cout<<i<<" => "; 
				for(int v: adjList[i])
				{
					cout<<v<<" "; 
				}
				cout<<"\n";
			}
		}
		bool cycleHelper(int node, bool* visited, int parent)
		{
			visited[node] = true;
			for(int nbr: adjList[node])
			{
				if(!visited[nbr])
				{
					bool isCycle = cycleHelper(nbr,visited,node);
					if(isCycle)
						return true;
				}
				else if(nbr!=parent)
				{
					// if i have already visited that node
					// and it is not that route i came from
					// means i have edge between current node and nbr resulting in cycle
					return true;
				}
			}
			return false;
		}
		bool cycleExists(int node)
		{
			bool visited[nodes];
			memset(visited, false, sizeof(visited));
			return cycleHelper(node,visited,-1);
		}
		bool cycleBFSUtil(bool visited[], int src)
		{
			int parent[nodes];
			memset(parent, -1, sizeof(parent));
			queue<int> q;
			q.push(src);
			visited[src] = true;
			while(!q.empty())
			{
				int node = q.front();
				q.pop();
				for(int nbr: adjList[node])
				{
					if(!visited[nbr])
					{
						visited[nbr] = true;
						q.push(nbr);
						parent[nbr] = node;
					}
					else if(parent[nbr] != node)
					{
						// there exits another edge
						return true;
					}
				}
			}
			return false;
		}
		bool cycleUsingBFS(int node)
		{
			bool visited[nodes];
			return cycleBFSUtil(visited, node);
		}
};

int main(void)
{
	//Undirected Simple Graph implementation with list
	Graph g(4);
	g.addEdge(0,1);
	g.addEdge(0,2);
	g.addEdge(1,2);
	g.addEdge(2,3);
	g.printList();
	bool isCyclePresent = g.cycleExists(0);
	if(isCyclePresent)
		cout<<"Cycle is Present\n";
	else
		cout<<"Cycle is Not Present\n";
	bool isBFSCyclePresent = g.cycleUsingBFS(0);
	if(isBFSCyclePresent)
		cout<<"Cycle using BFS is present\n";
	else
		cout<<"Cycle using BFS is not present\n";
	
	/*
	Weighted Graph implementation with unordered_map
	WeightedGraph g;
	g.addEdge("A","B",20);
	g.addEdge("A","D",50);
	g.addEdge("A","C",10);
	g.addEdge("B","D",30);
	g.addEdge("C","D",40);
	g.printList();
	*/
	
	/*
	BFS and DFS Traversal of Graphs
	GraphSearch g;
	g.addEdge(0,1);
	g.addEdge(1,2);
	g.addEdge(2,3);
	g.addEdge(3,0);
	g.addEdge(3,4);
	g.addEdge(4,5);
	cout<<"BFS Traversal is : ";
	g.bfsSearch(0);
	cout<<"DFS Traversal is : ";
	g.dfsSearch(0);
	*/
	
	/*
	//Program to check cycle exists in a directed graph using DFS
	DirectedGraph dg(4);
	dg.addEdge(0,1);
	dg.addEdge(1,2);
	dg.addEdge(0,2);
	dg.addEdge(2,0);
	dg.addEdge(2,3);
	dg.addEdge(1,3);
	bool isCycleInDirectedGraph = dg.cycleExists();
	if(isCycleInDirectedGraph)
		cout<<"Cycle exists in directed graph\n";
	else
		cout<<"No Cycle Exists\n";
	*/
	
	/*
	//Program to check if a bridge exists in graph
	BridgeGraph bg(4);
	bg.addEdge(0,1);
	bg.addEdge(1,2);
	bg.addEdge(2,3);
	//bg.addEdge(0,3);
	bg.addEdge(1,3);
	bg.bridgeExists();
	*/
	return 0;
}