#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

void dfsTraversal(int currNode, vector<bool> &visited, vector<int> &dfsList, vector<int> adjList[]) {
    visited[currNode] = true;
    dfsList.push_back(currNode);
    
    for(int connectedNode : adjList[currNode]) {
        if(!visited[connectedNode]) {
            dfsTraversal(connectedNode, visited, dfsList, adjList);
        }
    }
}

vector<int> bfsTraversal(int n, vector<int> adjList[], int startNode) {
    vector<int> bfsList;
    vector<bool> visited(n, false);
    visited[startNode] = true;
    queue<int> bfsQueue;
    bfsQueue.push(startNode);
    while(!bfsQueue.empty()) {
        int frontNode = bfsQueue.front();
        bfsQueue.pop();
        bfsList.push_back(frontNode);

        for(int connectedNode : adjList[frontNode]) {
            if(!visited[connectedNode]) {
                visited[connectedNode] = true;
                bfsQueue.push(connectedNode);
            }
        }
    }
    return bfsList;
}

// Detect Cycle in Undirected Graph using BFS
bool detectCycleUsingBFS(vector<int> adjList[], int vertices) {
    // curr_node, parent_node
    queue<pair<int, int>> bfsQueue;
    vector<bool> visited(vertices, false);
    visited[0] = true;
    bfsQueue.push({0, -1});
    while(!bfsQueue.empty()) {
        pair<int,int> frontNode = bfsQueue.front();
        bfsQueue.pop();
        int currNode = frontNode.first;
        int parentNode = frontNode.second;

        for(int connectedNode : adjList[currNode]) {
            if(!visited[connectedNode]) {
                visited[connectedNode] = true;
                bfsQueue.push({connectedNode, currNode});
            } else if(visited[connectedNode] and connectedNode != parentNode) {
                return true;
            }
        }
    }
    return true;
}

// Detect cycle in Undirected Graph using DFS
bool detectCycleUsingDFS(vector<int> adjList[], int currNode, int parentNode, vector<bool> &visited) {
    for(int connectedNode : adjList[currNode]) {
        if(!visited[connectedNode]) {
            visited[connectedNode] = true;
            if(detectCycleUsingDFS(adjList, connectedNode, currNode, visited)) {
                return true;
            }
        } else if(visited[connectedNode] and parentNode != connectedNode) {
            return true;
        }
    }
    return false;
}

void islandsCountDfs(int i, int j, vector<vector<int>> &grid,
 vector<vector<bool>> &visited, vector<pair<int,int>> &islandParts, int ibase, int jbase) {
    visited[i][j] = true;
    // This is the main part of the problem
    islandParts.push_back({i - ibase, j - jbase});
    int rows = grid.size();
    int cols = grid[0].size();
    int xdirs[] = {0, +1, 0, -1};
    int ydirs[] = {+1, 0, -1, 0};
    for(int dir = 0; dir < 4; dir++) {
        int nx = i + xdirs[dir];
        int ny = j + ydirs[dir];
        if(nx >= 0 and nx < rows and ny >= 0 and ny < cols && !visited[nx][ny] and grid[nx][ny] == 1) {
            islandsCountDfs(nx, ny, grid, visited, islandParts, ibase, jbase);
        }
    }
 }

int distinctIslandsCount(vector<vector<int>> grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    set<vector<pair<int,int>>> islandsSet;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(!visited[i][j] and grid[i][j] == 1) {
                vector<pair<int,int>> islandParts;
                islandsCountDfs(i, j, grid, visited, islandParts, i, j);
                islandsSet.insert(islandParts);
            }
        }
    }
    return islandsSet.size();
}

bool isBipartiteGraph(vector<int> adjList[], int verticesCount) {
    queue<int> q;
    vector<int> vertexColor(verticesCount, -1);
    q.push(0);
    vertexColor[0] = 0;
    while(!q.empty()) {
        int frontNode = q.front();
        q.pop();
        for(int connectedNode : adjList[frontNode]) {
            if(vertexColor[connectedNode] == -1) {
                vertexColor[connectedNode] = !vertexColor[frontNode];
                q.push(connectedNode);
            } else if(vertexColor[connectedNode] == vertexColor[frontNode]) {
                return false;
            }
        }
    }
    return true;
}

bool isGraphBipartiteUsingDFS(int currNode, vector<int> adjList[], vector<int> &vertexColor) {
    for(int connectedNode : adjList[currNode]) {
        if(vertexColor[connectedNode] == -1) {
            vertexColor[connectedNode] = !vertexColor[currNode];
            if(!isGraphBipartiteUsingDFS(connectedNode, adjList, vertexColor)) {
                return false;
            }
        } else if(vertexColor[connectedNode] == vertexColor[currNode]) {
            return false;
        }
    }
    return true;
}

  bool detectCycleInDirectedGraph(int currNode, vector<int> &visited, vector<int> &path,
    vector<int> adjList[]) {
        for(int connectedNode : adjList[currNode]) {
            if(!visited[connectedNode]) {
                visited[connectedNode] = 1;
                path[connectedNode] = 1;
                if(detectCycleInDirectedGraph(connectedNode, visited, path, adjList)) {
                    return true;
                }
            } else if(path[connectedNode] == 1) {
                return true;
            }
        }
        path[currNode] = 0;
        return false;
    }


void topoSortDFS(int currNode, vector<int> adjList[], vector<bool> &visited, stack<int> &st) {
    visited[currNode] = true;
    for(int connectedNode : adjList[currNode]) {
        if(!visited[connectedNode]) {
            topoSortDFS(connectedNode, adjList, visited, st);
        }
    }
    st.push(currNode);
}

vector<int> topologicalSort(vector<int> adjList[], int n) {
    vector<bool> visited(n, false);
    stack<int> st;
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            topoSortDFS(i, adjList, visited, st);
        }
    }
    vector<int> topoOrder;
    while(!st.empty()) {
        topoOrder.push_back(st.top());
        st.pop();
    }

    // Get Topological Order using BFS
    vector<int> inDegree(n, 0);
    for(int i = 0; i < n; i++) {
        for(int connectedNode : adjList[i]) {
            inDegree[connectedNode]++;
        }
    }

    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(inDegree[i] == 0) {
            q.push(i);
        }
    }
    vector<int> topoOrderBFSVisit;
    while(!q.empty()) {
        int frontNode = q.front();
        q.pop();
        topoOrderBFSVisit.push_back(frontNode);
        for(int connectedNode : adjList[frontNode]) {
            inDegree[connectedNode]--;
            if(inDegree[connectedNode] == 0) {
                q.push(connectedNode);
            }
        }
    }

    return topoOrderBFSVisit;
}

vector<char> alienDictionary(vector<string> dictionary, int K) {
    vector<int> adjList[K];
    for(int i = 0; i < dictionary.size() - 1; i++) {
        string currStr = dictionary[i];
        string nextStr = dictionary[i+1];
        int j = 0;
        while(j < currStr.length() and j < nextStr.length() and currStr[j] == nextStr[j]) {
            j++;
        }
        adjList[currStr[j] - 'a'].push_back(nextStr[j] - 'a');
    }
    vector<int> indegree(K, 0);
    for(int i = 0; i < K; i++) {
        for(int connectedNode : adjList[i]) {
            indegree[connectedNode]++;
        }
    }
    queue<int> q;
    for(int i = 0; i < K; i++) {
        if(indegree[i] == 0) {
            q.push(i);
        }
    }
    vector<char> alienOrder;
    while(!q.empty()) {
        int frontNode = q.front();
        q.pop();
        alienOrder.push_back(frontNode + 'a');
        for(int connectedNode : adjList[frontNode]) {
            indegree[connectedNode]--;
            if(indegree[connectedNode] == 0) {
                q.push(connectedNode);
            }
        }
    }
    return alienOrder;
}

void shortestPathTopoSort(int currNode, vector<pair<int,int>> adjList[], vector<int> &visited, stack<int> &topoOrder) {
    visited[currNode] = 1;
    for(auto it : adjList[currNode]) {
        int connectedNode = it.first;
        if(!visited[connectedNode]) {
            shortestPathTopoSort(connectedNode, adjList, visited, topoOrder);
        }
    }
    topoOrder.push(currNode);
}

vector<int> shortestPathInDAG(vector<pair<int,int>> adjList[], int n, int src) {
    // get the topological ordering of the nodes
    stack<int> topoOrder;
    vector<int> visited(n, false);
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            shortestPathTopoSort(i, adjList, visited, topoOrder);
        }
    }
    // remove items from the stack and decide the distance to the neighbours
    vector<int> shortestDistance(n, INT_MAX);
    shortestDistance[src] = 0;
    while(!topoOrder.empty()) {
        int currNode = topoOrder.top();
        topoOrder.pop();
        if(shortestDistance[currNode] == INT_MAX) {
            continue;
        }
        for(auto it : adjList[currNode]) {
            int connectedNode = it.first;
            int dist = it.second;
            if(shortestDistance[currNode] + dist < shortestDistance[connectedNode]) {
                shortestDistance[connectedNode] = shortestDistance[currNode] + dist;
            }
        }
    }
    return shortestDistance;
}

struct wordLadderQueue {
    string currWord;
    int currLevel;
    vector<string> transformWords;
};

vector<vector<string>> WordLadder2(string beginWord, string endWord, vector<string> wordList) {
    set<string> wordsSet;
    for(string s : wordList) {
        wordsSet.insert(s);
    }
    wordsSet.erase(beginWord);
    queue<wordLadderQueue> q;
    q.push({beginWord, 0, {}});
    vector<vector<string>> ans;
    while(!q.empty()) {
        wordLadderQueue qfront = q.front();
        q.pop();
        string currWord = qfront.currWord;
        int currLevel = qfront.currLevel;
        vector<string> currListWords = qfront.transformWords;
        if(currWord == endWord) {
            ans.push_back(currListWords);
        }
        for(int i = 0; i < currWord.length(); i++) {
            for(char ch = 'a'; ch <= 'z'; ch++) {
                string newWord = currWord;
                newWord[i] = ch;
                if(wordsSet.find(newWord) != wordsSet.end()) {
                    currListWords.push_back(newWord);
                    q.push({newWord, currLevel + 1, currListWords});
                    wordsSet.erase(newWord);
                }
            }
        }
    }
    return ans;
}

vector<int> dijkstraAlgorithm(vector<pair<int,int>> adjList[], int n, int srcNode, int dstNode) {
    vector<int> dist(n, INT_MAX);
    dist[srcNode] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> minHeap;
    minHeap.push({0, srcNode});
    vector<int> srcArr(n, 0);
    while(!minHeap.empty()) {
       pair<int,int> topElement = minHeap.top();
       minHeap.pop();

       int currDist = topElement.first;
       int currNode = topElement.second;

       for(auto connectedNeighbour : adjList[currNode]) {
        int neighbourNode = connectedNeighbour.first;
        int distToNeighbour = connectedNeighbour.second;

        if(dist[neighbourNode] > currDist + distToNeighbour) {
            dist[neighbourNode] = currDist + distToNeighbour;
            srcArr[neighbourNode] = currNode;
            minHeap.push({dist[neighbourNode], neighbourNode});
        }

       }
    }

    int traverseNode = dstNode;
    while(traverseNode != srcNode) {
        cout << traverseNode << " <- ";
        traverseNode = srcArr[traverseNode];
    }
    cout << srcNode << "\n";

    return dist;
}

int minimumEffort(vector<vector<int>> grid) {
   int rows = grid.size();
   int cols = grid[0].size();
   
   priority_queue<pair<int, pii>, vector<pair<int, pii>>, greater<pair<int, pii>>> minHeap;
   
   vector<vector<int>> ans(rows, vector<int>(cols, INT_MAX));
   ans[0][0] = 0;

   minHeap.push({0, {0, 0}});

    vector<int> xdirs = {-1, 0, 1, 0};
    vector<int> ydirs = {0, 1, 0, -1};

   while(!minHeap.empty()) {
        pair<int,pii> topElement = minHeap.top();
        minHeap.pop();

        int currDiff = topElement.first;
        int currX = topElement.second.first;
        int currY = topElement.second.second;

        for(int dir = 0; dir < 4; dir++) {
            int newX = currX + xdirs[dir];
            int newY = currY + ydirs[dir];

            if(newX >= 0 and newX < rows and newY >= 0 and newY < cols) {
                int newDiff = abs(grid[newX][newY] - grid[currX][currY]);
                int finalDiff = max(newDiff, currDiff);

                if(ans[newX][newY] > finalDiff) {
                    minHeap.push({finalDiff, {newX, newY}});
                    ans[newX][newY] = finalDiff;
                }
            }
        } 
   }

   return ans[rows - 1][cols - 1];
}

int main() {
    // int n, m, isDirected;
    // cin >> n >> m >> isDirected;
    // vector<int> adjList[n];
    // for(int edge = 0; edge < m; edge++) {
    //     int u, v;
    //     cin >> u >> v;
    //     adjList[u].push_back(v);
    //     if(isDirected == 1) {
    //         continue;
    //     }
    //     adjList[v].push_back(u);
    // }
    
    // vector<int> bfsList = bfsTraversal(n, adjList, 0);
    // cout << "BFS Traversal Order : ";
    // for(int node : bfsList) {
    //     cout << node << " ";
    // } 
    // cout << "\n";

    // cout << "DFS Traversal Order : ";
    // vector<bool> dfsVisited(n, false);
    // vector<int> dfsList;
    // dfsTraversal(0, dfsVisited, dfsList, adjList);
    // for(int node : dfsList) {
    //     cout << node << " ";
    // }
    // cout << "\n";

    // vector<bool> cycleDFSVisited(n, false);
    // bool correctAnswer = true;
    // bool isCyclePresentUsingBFS = detectCycleUsingBFS(adjList, n);
    // cycleDFSVisited[0] = true;
    // bool isCyclePresentUsingDFS = detectCycleUsingDFS(adjList, 0, -1, cycleDFSVisited);
    // if(isCyclePresentUsingBFS == isCyclePresentUsingDFS == correctAnswer) {
    //     cout << "Correct Answer \n";
    // } else {
    //     cout << "Incorrect Answer \n";
    // }

    // vector<vector<int>> grid = {
    //     {1, 0, 1, 1, 1},
    //     {1, 0, 0, 0, 0},
    //     {0, 0, 0, 1, 1},
    //     {1, 1, 0, 1, 1}
    // };
    // cout << "Distinct Islands Count = " << distinctIslandsCount(grid) << "\n";

    // bool isGraphBipartite = true;
    // vector<int> vertexColors(n, -1);
    // vertexColors[0] = 0;
    // bool isGraphBipartiteDFS = isGraphBipartiteUsingDFS(0, adjList, vertexColors);
    // bool isGraphBipartiteUsingBFS = isBipartiteGraph(adjList, n);
    // if(isGraphBipartiteDFS == isGraphBipartite and isGraphBipartiteUsingBFS == isGraphBipartite) {
    //     cout << "Correct answer \n";
    // } else {
    //     cout << "Incorrect answer \n";
    // }

    // cout << "Topological Sort = ";
    // vector<int> topoOrder = topologicalSort(adjList, n);
    // for(int i : topoOrder) {
    //     cout << i << " ";
    // }
    // cout << "\n";

    // int m, n;
    // cin >> m >> n;
    // vector<pair<int,int>> adjList[m];
    // for(int i = 0; i < n; i++) {
    //     int u, v, w;
    //     cin >> u >> v >> w;
    //     adjList[u].push_back({v, w});
    // }
    // int srcVertex;
    // cout << "Enter the source vertex : ";
    // cin >> srcVertex;
    // vector<int> shortestDistance = shortestPathInDAG(adjList, m, srcVertex);
    // for(int i = 0; i < m; i++) {
    //     cout << shortestDistance[i] << " ";
    // }
    // cout << "\n";

    // int nodes, edges;
    // cin >> nodes >> edges;
    // vector<pair<int,int>> adjList[nodes];
    // for(int edge = 1; edge <= edges; edge++) {
    //     int u, v, w;
    //     cin >> u >> v >> w;
    //     adjList[u].push_back({v, w});
    //     adjList[v].push_back({u, w});
    // }
    // int srcNode, dstNode;
    // cin >> srcNode >> dstNode;
    // vector<int> res = dijkstraAlgorithm(adjList, nodes, srcNode, dstNode);
    // for(int r : res) {
    //     cout << r << " ";
    // }
    // cout << "\n";

    vector<vector<int>> grid = {
        {1, 2, 2},
        {3, 8, 2},
        {5, 3, 5}
    };
    cout << "Minimum effort = " << minimumEffort(grid) << "\n";

    return 0;
}