#include <iostream>
#include<string>
#include<list>
#include<sstream>
#include<algorithm>
#include<iomanip>
#include<vector>
#include<bits/stdc++.h>
#include<cstdlib>
#define MAX 1300
using namespace std;

///////////////////////////////////////////////////////////////////////////////////

void add_edges(vector<int> adj[], int src, int dest)
{
    adj[src].push_back(dest);
    adj[dest].push_back(src);
}

// Breath First Search that stores predecessor of each vertex in array p and its distance from source in array d
bool Breath_First_Search(vector<int> adj[], int src, int dest,int v,
                         int pre[], int dist[])
{
    // A queue to maintain queue of vertices whose adjacency list is to be scanned as per normal DFS algorithm
    list<int> queue;

    // boolean array visited[] which stores the information whether vertex is reached at least once in the Breadth first search
    bool *visited = (bool*)malloc(sizeof(bool)*MAX);

    // Initially all vertices are unvisited

    for (int i = 0; i < MAX; i++) {
        visited[i] = false;
        dist[i] = INT8_MAX;
        pre[i] = -1;
    }

    // now source is first to be visited and distance from source to itself should be 0
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);

    // Breath First Search Algorithm
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < adj[u].size(); i++) {
            if (!visited[adj[u][i]]) {
                visited[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1;
                pre[adj[u][i]] = u;
                queue.push_back(adj[u][i]);

                if (adj[u][i] == dest)
                    return true;
            }
        }
    }

    return false;
}

// Printing the shortest distance between source vertex and destination vertex
void Shortest_Distance(vector<int> adj[], int s,
                       int dest, int v)
{
    // predecessor[i] array stores predecessor of i and distance array stores distance of i from s
    int *pre = (int*)malloc(sizeof(int)*MAX);
    int *dist = (int*)malloc(sizeof(int)*MAX);


    if (!Breath_First_Search(adj, s, dest, v, pre, dist))
    {
        std::cerr << "Error: Path does not exist between given vertexes"<<std::endl;
        for(int i=0;i<MAX;i++){
            adj[i].clear();
        }
        return;
    }

    // Vector stores the shortest path
    vector<int> path;
    int crawl = dest;
    path.push_back(crawl);
    while (pre[crawl] != -1)
    {
        path.push_back(pre[crawl]);
        crawl = pre[crawl];
    }

    // printing path from source to destination
    for (int i = path.size() - 1; i >= 0; i--){
         if(i!=0){
             cout <<path[i];
             cout<<"-";
       }else{
			 cout<<path[i];
	   }
	}
	cout<<endl;
}

//////////////////////////////////////////////////////////////////////////////////

int main(){
// Variables to store user input vertices , source and destination.
    int vertices;
    int source,dest;
    int nedges = 0, newedges;
    int num_of_edges = 0;
	vector<vector<int>> edge;
	//int **edge;
	//int *edge[MAX];
	//for(int i=0; i<MAX; i++){
	//		edge[i] = (int*)malloc(sizeof(int)*2);
	//}
	// int edge[MAX][MAX] = {};

    vector<int>adj[MAX];
    while (!cin.eof()){
        string input;
        getline(cin,input);
        char cmd;
        cmd = input[0];

        string word = "";
        if(cmd == 'V' || cmd == 'E')
        {
			cout<<input<<endl;
            for(auto x : input)
            {
                if(x == ' '){
                    word = "";

                }else{
                    word += x;
                }
            }
        }

        if(cmd == 'V')
        {
            vertices = stoi(word.substr(0));
        }
        // Function to parse integers from given set of edges
        if(cmd == 'E')
        {
            for(int i=0;i<MAX;i++){
                adj[i].clear();
            }
            string edges = word.substr(0);
            edges.erase(0,1);
            edges.pop_back();
            edges.erase(remove(edges.begin(),edges.end(),'<'),edges.end());
            edges.erase(remove(edges.begin(),edges.end(),'>'),edges.end());
            istringstream f(edges);
            string s;
            while (getline(f, s, ','))
            {
                if (stoi(s) >= vertices)
                { std::cerr<<"Error: Vertex mentioned in edge is greater than number of vertices."<<std::endl;
                    for(int i=0;i<MAX;i++){
                        adj[i].clear();
                    }
                    break;
                }
            }
            replace(edges.begin(),edges.end(),',',' ');
            edges += ' ';
            newedges = (edges.length()/4);
            int *arr = (int*)malloc(sizeof(int)*MAX);
            //edge [newedges][2];
			/*edge = (int**)malloc(newedges*sizeof(int*));
			for(int i=0; i<2; i++)
			{
					edge[i] = (int*)malloc(2*sizeof(int));
			}*/
		   	int index = 0;
            string number;

            for(auto x : edges)
            {
                if(x == ' ')
                {
                    stringstream ss(number);
                    ss>>arr[index];
                    number = "";
                    index++;

                }
                else
                {
                    number += x;

                }
            }

            index = 0;
            for(int i = 0;i<newedges;i++)
            {
				vector<int> vt;
                for (int j=0;j<2;j++){
                    //edge[i][j] = arr[index];
                    vt.push_back(arr[index]);
					index++;
                }
				edge.push_back(vt);
            }


            for(int i=0;i<newedges;i++)
            {
                for(int j=0;j<2;j++)
                {
                    nedges++;
                    num_of_edges = nedges/2;
                }
            }

        }

        if(cmd == 's')
        {
			//int *arr = (int*)malloc(sizeof(int)*MAX);
			//edge [newedges][2];
			/*int **edge = (int**)malloc(newedges*sizeof(int*));
			for(int i=0; i<2; i++)
			{
				edge[i] = (int*)malloc(2*sizeof(int));
			}*/
						   //
            istringstream stream(input);
            string token1;
            string token2;
            string token3;
            stream >> token1 >> token2 >> token3;
            source = stoi(token2);
            dest = stoi(token3);
			if(source>=vertices){
					std::cerr<<"Error: Invalid Vertices"<<std::endl;
					continue;
			}
			if(dest>=vertices){
					std::cerr<<"Error: Invalid Vertices"<<std::endl;
                     continue;

			}
			if(source == dest){
					cout<<source;
					cout<<"-";
					cout<<dest;
					cout<<endl;
					continue;
			}

            for(int i = 0; i < num_of_edges; i++)
                add_edges(adj, edge[i][0], edge[i][1]);

            Shortest_Distance(adj,source,dest,vertices);

        }


    }

    return 0;

}

