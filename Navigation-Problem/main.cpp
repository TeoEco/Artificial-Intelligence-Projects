#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <iterator>
#include <climits>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>
#include <map>
#include <string>
#include <math.h>

using namespace std;

int num_of_vertices, num_of_edges;

class Node
{
public:
    int v;
    Node* parent;
    int x,y;
    float dis;
    Node(int I, int a, int b)
    {
        v = I;
        parent = NULL;
        x = a;
        y = b;
        dis = 0.0;
    }
    vector<int> adj_list;
    void addEdge(int dest)
    {
        adj_list.push_back(dest);
    }
    vector<int> successors()
    {
        return adj_list;
    }

    vector<int> traceback(Node* initial_state, Node* goal)
    {
        vector<int> parent_list;
        parent_list.push_back(goal->v);
        while(goal != initial_state)
        {
            parent_list.push_back(goal->parent->v);
            goal = goal->parent;
        }
        return parent_list;
    }
}*g[10000];

void printParentPath(Node* initial_state, Node* goal)
{
    Node* tmp;
    vector<int> parent_list;
    parent_list = tmp->traceback(initial_state, goal);
    cout << endl;
    cout << "Solution Path:" << endl;
    for(int i=parent_list.size()-1; i>=0; i--)
    {
        //cout << "vertex " << parent_list[i] << "(" << g[parent_list[i]]->x << ", " << g[parent_list[i]]->y << ")" << endl;
        cout << g[parent_list[i]]->x << " " << g[parent_list[i]]->y << endl;
    }
    cout << endl;
    cout << "Path length = " << parent_list.size()-1 << endl;
    return;
}

Node* BFS_Search(Node* initial_state, Node* goal)
{
    int itr = 1;
    int vrt = 0;
    int frnt;
    cout << "BFS" <<endl;
    if(initial_state == goal)
        return initial_state;

    queue<Node*> frontier;
    int visited[num_of_vertices];
    for(int i=0; i<num_of_vertices; i++)
        visited[i] = 0;

    frontier.push(initial_state);
    frnt = 1;
    visited[initial_state->v]=1;

    while(!frontier.empty())
    {
        int sz = frontier.size();
        frnt = max(frnt, sz);
        Node* x = frontier.front();
        frontier.pop();
        if(x == goal)
        {
            printParentPath(initial_state, goal);
            cout << "Total Iterations = " << itr << endl;
            for(int i=0; i<num_of_vertices; i++)
                if(visited[i])
                    vrt++;
            cout << "Vertices visited = " << vrt << "/" << num_of_vertices << endl;
            cout << "Max Frontier Size = " << frnt << endl;
            return x;
        }
        else
        {
            itr++;
            vector<int> adj_list = x->successors();
            vector<int>::iterator it = adj_list.begin();
            for(vector<int>::iterator it=adj_list.begin(); it!=adj_list.end(); it++)
            {
                if(!visited[*it])
                {
                visited[*it]=1;
                frontier.push(g[*it]);
                g[*it]->parent = x;
                }
            }
        }
    }
}

Node* DFS_Search(Node* initial_state, Node* goal)
{
    int itr = 1;
    int vrt = 0;
    int frnt;
    cout << "DFS" <<endl;
    if(initial_state == goal)
        return initial_state;

    stack<Node*> frontier;
    int visited[num_of_vertices];
    for(int i=0; i<num_of_vertices; i++)
        visited[i] = 0;

    frontier.push(initial_state);
    frnt = 1;
    visited[initial_state->v]=1;

    while(!frontier.empty())
    {
        int sz = frontier.size();
        frnt = max(frnt, sz);
        Node* x = frontier.top();
        frontier.pop();
        if(x == goal)
        {
            printParentPath(initial_state, goal);
            cout << "Total Iterations = " << itr << endl;
            for(int i=0; i<num_of_vertices; i++)
                if(visited[i])
                    vrt++;
            cout << "Vertices visited = " << vrt << "/" << num_of_vertices << endl;
            cout << "Max Frontier Size = " << frnt << endl;
            return x;
        }
        else
        {
            itr++;
            vector<int> adj_list = x->successors();
            vector<int>::iterator it = adj_list.begin();
            for(vector<int>::iterator it=adj_list.begin(); it!=adj_list.end(); it++)
            {
                if(!visited[*it])
                {
                visited[*it]=1;
                frontier.push(g[*it]);
                g[*it]->parent = x;
                }
            }
        }
    }
}

class cmp
{
public:
    bool operator()(Node* n1, Node* n2)
    {
        if(n1->dis >= n2->dis) return true;
        return false;
    }
};

Node* GBFS_Search(Node* initial_state, Node* goal)
{
    int itr = 1;
    int vrt = 0;
    int frnt;
    cout << "GBFS" <<endl;
    if(initial_state == goal)
        return initial_state;

    priority_queue<Node*, vector<Node*>, cmp> frontier;
    int visited[num_of_vertices];
    for(int i=0; i<num_of_vertices; i++)
        visited[i] = 0;

    frontier.push(initial_state);
    frnt = 1;
    visited[initial_state->v]=1;

    while(!frontier.empty())
    {
        int sz = frontier.size();
        frnt = max(frnt, sz);
        Node* x = frontier.top();
        frontier.pop();
        if(x == goal)
        {
            printParentPath(initial_state, goal);
            cout << "Total Iterations = " << itr << endl;
            for(int i=0; i<num_of_vertices; i++)
                if(visited[i])
                    vrt++;
            cout << "Vertices visited = " << vrt << "/" << num_of_vertices << endl;
            cout << "Max Frontier Size = " << frnt << endl;
            return x;
        }
        else
        {
            itr++;
            vector<int> adj_list = x->successors();
            vector<int>::iterator it = adj_list.begin();
            for(vector<int>::iterator it=adj_list.begin(); it!=adj_list.end(); it++)
            {
                if(!visited[*it])
                {
                visited[*it]=1;
                float d = sqrt(pow((g[*it]->y - goal->y),2) + pow((g[*it]->x - goal->x),2));
                g[*it]->dis = d;
                frontier.push(g[*it]);
                g[*it]->parent = x;
                }
            }
        }
    }
}

int main()
{
    ifstream inFile;
    inFile.open("ATMgraph.txt");
    std::string line;
    vector<string> v;
    int var = 1;
    map<string, int> mp;

    getline(inFile, line);
    char * dup = strdup(line.c_str());
    char * token = strtok(dup, " :\t");
    while(token != NULL){
        v.push_back(string(token));
        token = strtok(NULL, " ");
    }
    free(dup);
    num_of_vertices = atoi(v[1].c_str());

    while(var <= num_of_vertices)
    {
        getline(inFile, line);
        dup = strdup(line.c_str());
        token = strtok(dup, " :\t");
        char* x = strtok(NULL, " ");
        char* y = strtok(NULL, " ");
        int xi = atoi(x);
        int yi = atoi(y);
        string temp, temp1, temp2;
        ostringstream convert, convert1;
        convert << xi;
        temp1 = convert.str();
        convert1 << yi;
        temp2 = convert1.str();
        temp = temp1 + temp2;
        mp[temp] = atoi(token);
        g[var-1] = new Node((atoi(token)), (atoi(x)), (atoi(y)));
        free(dup);
        var ++;
    }

    getline(inFile, line);
    dup = strdup(line.c_str());
    token = strtok(dup, " :\t");
    while(token != NULL){
        v.push_back(string(token));
        token = strtok(NULL, " ");
    }
    free(dup);
    num_of_edges = atoi(v[3].c_str());

    var = 0;
    while(var < num_of_edges)
    {
        getline(inFile, line);
        dup = strdup(line.c_str());
        token = strtok(dup, " :\t");
        char* v1 = strtok(NULL, " ");
        char* v2 = strtok(NULL, " ");
        g[(atoi(v1))]->addEdge((atoi(v2)));
        g[(atoi(v2))]->addEdge((atoi(v1)));
        free(dup);
        var ++;
    }

    while(1)
    {
        int ch;
        cout << endl;
        cout << "Enter option for Search:" << endl;
        cout << "1 Breadth-First Search" << endl;
        cout << "2 Depth-First Search" << endl;
        cout << "3 Greedy Best-First Search" << endl;
        cout << "4 Exit" << endl;
        cin >> ch;
        int x1, y1, x2, y2;

        switch(ch)
        {
            case 1:
                {
                    cout << endl;
                    cout << "Enter source co-ordinates" << endl;
                    cin >> x1 >> y1;
                    cout << "Enter destination co-ordinates" << endl;
                    cin >> x2 >> y2;
                    cout << endl;
                    string temp, temp1, temp2;
                    ostringstream convert, convert1, convert2, convert3;
                    convert << x1;
                    temp1 = convert.str();
                    convert1 << y1;
                    temp2 = convert1.str();
                    temp = temp1 + temp2;
                    int v1 = mp.find(temp)->second;
                    convert2 << x2;
                    temp1 = convert2.str();
                    convert3 << y2;
                    temp2 = convert3.str();
                    temp = temp1 + temp2;
                    int v2 = mp.find(temp)->second;
                    BFS_Search(g[v1], g[v2]);
                    break;
                }
            case 2:
                {
                    cout << endl;
                    cout << "Enter source co-ordinates" << endl;
                    cin >> x1 >> y1;
                    cout << "Enter destination co-ordinates" << endl;
                    cin >> x2 >> y2;
                    cout << endl;
                    string temp, temp1, temp2;
                    ostringstream convert, convert1, convert2, convert3;
                    convert << x1;
                    temp1 = convert.str();
                    convert1 << y1;
                    temp2 = convert1.str();
                    temp = temp1 + temp2;
                    int v1 = mp.find(temp)->second;
                    convert2 << x2;
                    temp1 = convert2.str();
                    convert3 << y2;
                    temp2 = convert3.str();
                    temp = temp1 + temp2;
                    int v2 = mp.find(temp)->second;
                    DFS_Search(g[v1], g[v2]);
                    break;
                }
            case 3:
                {
                    cout << endl;
                    cout << "Enter source co-ordinates" << endl;
                    cin >> x1 >> y1;
                    cout << "Enter destination co-ordinates" << endl;
                    cin >> x2 >> y2;
                    cout << endl;
                    float dist = sqrt(pow((y2-y1),2) + pow((x2-x1),2));
                    cout << "GBFS dis " << dist << endl;
                    string temp, temp1, temp2;
                    ostringstream convert, convert1, convert2, convert3;
                    convert << x1;
                    temp1 = convert.str();
                    convert1 << y1;
                    temp2 = convert1.str();
                    temp = temp1 + temp2;
                    int v1 = mp.find(temp)->second;
                    g[v1]->dis = 0.0;
                    convert2 << x2;
                    temp1 = convert2.str();
                    convert3 << y2;
                    temp2 = convert3.str();
                    temp = temp1 + temp2;
                    int v2 = mp.find(temp)->second;
                    g[v2]->dis = dist;
                    GBFS_Search(g[v1], g[v2]);
                    break;
                }

            case 4:
                exit(1);
            default:
                cout << "Enter valid option" << endl;
        }
    }

    return 0;
}
