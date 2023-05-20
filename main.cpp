#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <stack>
#include <queue>
using namespace std;
vector<int> a[30];
vector<int> aj[30];
bool visited[30];
bool direc = false;
int noV = 0;
stack<int> topo;
int parent[30];
int color[30];
void inp()
{
    fstream file;
    file.open("input.txt",ios::in);
    file >> noV;
    file >> direc;
    int b,c;
    while(!file.eof())
    {
        file >> b;file >> c;
        a[b] .push_back(c);
        if(!direc)
            a[c].push_back(b);
        aj[c].push_back(b);
    }
    memset(visited,false,sizeof(visited));
    memset(parent,-1,sizeof(parent));
    memset(color,0,sizeof(color));
}
void dfs(int v)
{
    visited[v] = true;
    // cout << v << " ";
    for (int i = 0; i < a[v].size(); i++)
    {
        if(!visited[a[v][i]]) dfs(a[v][i]);
    }
}
void dfsIter(int v)
{
    stack<int> b;
    b.push(v);
    int cur;
    bool all = false;
    while(!b.empty())
    {
        cur = b.top();
        if(!visited[cur])
        {
            cout << cur << " ";
            visited[cur] = true;
        }
        all = false;
        for (int i = 0; i < a[cur].size(); i++)
        {
            if(!visited[a[cur][i]]){
                b.push(a[cur][i]);
                all = true;
                break;
            } 
        }
        if(!all) b.pop();
    }
}
void bfs(int v)
{
    queue<int> b;
    b.push(v);
    visited[v] = true;
    int cur;
    while(!b.empty())
    {
        cur = b.front();
        b.pop();
        cout << cur << " ";
        for (int i = 0; i < a[cur].size(); i++)
        {
            if(!visited[a[cur][i]]){
                b.push(a[cur][i]);
                visited[a[cur][i]] = true;
            } 
        }
    }
}

//kiểm tra đồ thị có liên thông
bool isConnectedGraph()
{
    dfs(0);
    for (int i = 0; i < noV; i++)
    {
        if(!visited[i]) return false;
    }
    return true;
}
void topoSort()
{
    // if(HavingCycle_Direct_DFS())
    // {
    //     cout << "Co chu trinh nen khong the sap xep topo";
    //     return;
    // }
    memset(visited,false,sizeof(visited));
    stack<int> b;
    stack<int> c;
    b.push(0);
    visited[0] = true;
    bool all = true;
    int cur;
    while(!b.empty())
    {
        cur = b.top();
        visited[cur] = true;
        all = false;
        for (int i = 0; i < a[cur].size(); i++)
        {
            if(!visited[a[cur][i]]){
                b.push(a[cur][i]);
                all = true;
                break;
            } 
        }
        if(!all)
        {
            c.push(cur);
            b.pop();
        }
    }
    while(!c.empty())
    {
        cout << c.top() << " ";
        c.pop();
    }
}
void topoSort2(int v)
{
    visited[v] = true;
    for (int i = 0; i < a[v].size(); i++)
    {
        if(!visited[a[v][i]]) dfs(a[v][i]);
    }
    topo.push(v);
}

//kiem tra chu trinh
// vô hướng
bool checkCycleDFS(int v)
{
    visited[v] = true;
    for (int i = 0; i < a[v].size(); i++)
    {
        if(!visited[a[v][i]]) 
        {
            parent[a[v][i]] = v;
            if(checkCycleDFS(a[v][i]))
            {
                return true;
            }
        }
        else if(a[v][i] != parent[v]) 
        {
            return true;
        }
    }
    return false;
}
bool HavingCycle_NoDiect_DFS()
{
    for (int i = 0; i < noV; i++)
    {
        if(!visited[i])
        {
            if(checkCycleDFS(i))
            {
                return true;
            }
        }
    }
    return false;
}

bool checkCycleBFS(int v)
{
    queue<int> b;
    b.push(v);
    visited[v] = true;
    int cur;
    while(!b.empty())
    {
        cur = b.front();b.pop();
        for (int i = 0; i < a[cur].size(); i++)
        {
            if(!visited[a[cur][i]]){
                parent[a[cur][i]] = cur;
                b.push(a[cur][i]);
                visited[a[cur][i]] = true;
            }
            else if(a[cur][i] != parent[cur]){
                return true;
            }
        }
    }
    return false;
}
bool HavingCycle_NoDiect_BFS()
{
    for (int i = 0; i < noV; i++)
    {
        if(!visited[i])
        {
            if(checkCycleBFS(i))
            {
                return true;
            }
        }
    }
    return false;
}

//có hướng
bool checkCycleDFSdirect(int v)
{
    color[v] = 1;
    for (int i = 0; i < a[v].size(); i++)
    {
        if(color[a[v][i]] == 0){
            if(checkCycleDFSdirect(a[v][i]))
            {
                return true;
            }
        }
        else if(color[a[v][i]] == 1) return true;
    }
    color[v] = 2;
    return false;
}
bool HavingCycle_Direct_DFS()
{
    for (int i = 0; i < noV; i++)
    {
        if(!visited[i])
        {
            if(checkCycleDFSdirect(i))
            {
                return true;
            }
        }
    }
    return false;
}

//kiểm tra đồ thị 2 phía
bool bipartiteGraphBFS(int v)
{
    queue<int> b;
    b.push(v);
    color[v] = 0;//red
    int cur;
    while(!b.empty())
    {
        cur = b.front();
        b.pop();
        for (int i = 0; i < a[cur].size(); i++)
        {
            if(color[a[cur][i]] == -1)
            {
                color[a[cur][i]] = 1-color[cur];
                b.push(a[cur][i]);
            }
            else if(color[a[cur][i]] == color[cur]) return false;
        }
    }
    return true;
}

bool isBipartiteGraphBFS()
{
    memset(color,-1,sizeof(color));
    for (int i = 0; i < noV; i++)
    {
        if(color[i] == -1)
        {
            if(!bipartiteGraphBFS(i))
                return false;
        }
    }
    return true;
}
bool bipartiteGraphDFS(int v,int p)
{
    color[v] = 1-color[p];
    for (int i = 0; i < a[v].size(); i++)
    {
        if(color[a[v][i]] == -1)
        {
            if(!bipartiteGraphDFS(a[v][i],v))
            {
                return false;
            }
        }
        else if(color[v] == color[a[v][i]]) return false;
    }
    return true;
}

bool isBipartiteGraphDFS()
{
    memset(color,-1,sizeof(color));
    color[0] = 0;
    for (int i = 0; i < noV; i++)
    {
        if(color[i] == -1)
        {
            if(!bipartiteGraphDFS(i,-1))
                return false;
        }
    }
    return true;
}

//Tìm số thành phần liên thông mạnh
void dfsForKorasaju(int v)
{
    visited[v] = true;
    for (int i = 0; i < a[v].size(); i++)
    {
        if(!visited[a[v][i]]) dfsForKorasaju(a[v][i]);
    }
    topo.push(v);
}
void dfsForKorasaju1(int v)
{
    visited[v] = true;
    for (int i = 0; i < aj[v].size(); i++)
    {
        if(!visited[aj[v][i]]) dfsForKorasaju1(aj[v][i]);
    }
}
void Kosaraju()
{
    memset(visited,false,sizeof(visited));
    for (int i = 0; i < noV; i++)
    {
        if(!visited[i])
        {
            dfsForKorasaju(i);
        }
    }
    memset(visited,false,sizeof(visited));
    int cur;
    int c = 0;
    while(!topo.empty())
    {
        cur = topo.top();
        topo.pop();
        if(!visited[cur])
        {
            dfsForKorasaju1(cur);
            c++;
        }
    }
    cout << c << endl;
}
//tìm đỉnh trụ
// code trâu
int CutVertices()
{
    memset(visited,false,sizeof(visited));
    int tplt = 0;
    int no = 0;
    for (int i = 0; i < noV; i++)
    {
        if(!visited[i])
        {
            tplt++;
            dfs(i);
        }
    }
    int tplt1 = 0;
    for (int i = 0; i < noV; i++)
    {
        memset(visited,false,sizeof(visited));
        visited[i] = true;
        tplt1 = 0;
        for (int j = 0; j < noV; j++)
        {
            if(!visited[j])
            {
                tplt1++;
                dfs(j);
            }
        }
        if(tplt1 > tplt)
        {
            no++;
            cout << i << " ";
        }
    }
    return no;
}
int main()
{
    inp();
    Kosaraju();
    // dfs(0);
    return 0;
}