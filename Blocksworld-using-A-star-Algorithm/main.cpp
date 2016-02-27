#include <iostream>
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
#include <time.h>
#include <map>

using namespace std;

int num_of_blocks;
int num_of_stacks;

class Node
{
public:
    vector< vector<char> > block;
    Node* parent;
    float g, h,f;
    vector<vector<vector<char> > > successors()
    {
    }
     Node(int s, int b)
       {
        parent = NULL;
        g = 0.0;
        h = 0.0;
        f = 0.0;
       }

}*blocksWorld[500000];

int mycount = 1;

void problemGenerator(Node* ans, int b, int s)
{
  srand (time(NULL));
  vector<vector<char> > values;
  vector <int> element;

 for (int i=0; i<b; i++)
      element.push_back(i);

  for (int i=0; i <s-1; i++)
    {
      int ran = rand() % b ;
      vector <char> row;
      for (int j=0; j<ran ; j++)
	{
	  int pos = rand() % b;
	  row.push_back(element[pos] + 65);
	  swap(element[pos], element[b-1]);
	  b--;
	}
      values.push_back(row);
    }

  if(b > 0)
    {
      vector <char> temp;
      int num_block_temp = b;
      for (int i=0; i<num_block_temp; i++)
        {
          int pos = rand() % b;
          temp.push_back(element[pos] + 65);
	  swap(element[pos], element[b-1]);
	  b--;
        }
      values.push_back(temp);
    }
  ans->block = values;
}

/*void swap(int &a, int &b)
{
  int temp;
  temp=a;
  a=b;
  b=temp;
} */

void printState(Node* myState, int s)
{
    vector <vector <char> > ans = myState->block;
    for(int i=0; i<ans.size(); i++)
    {
        cout << i+1 << "|-";
        for(int j=0; j<ans[i].size(); j++)
            cout <<ans[i][j];
        cout << endl;
    }
}

vector<Node*> generateSuccessor(Node* start)
  {
    vector<Node*> adj_list;
    vector<vector<char> > state = start->block;

    int check;
    for (int i=0; i<state.size(); i++)
      {
        if (state[i].size() > 0)
        {
            char tmp = state[i].back();
            state[i].pop_back();
            for (int j=0; j<state.size(); j++)
            {
                check=1;
                if(i!=j)
                {
                state[j].push_back(tmp);
                Node* new_state = new Node(num_of_blocks, num_of_stacks);
                new_state->block = state;
                for(int p=0; p<mycount; p++)
	            {
           	       if(blocksWorld[p]->block == state)
                    {
                        adj_list.push_back(blocksWorld[p]);
                        check=0;
                    }
                }
                if(check==1)
                    adj_list.push_back(new_state);
                state[j].pop_back();
                }
            }
            state[i].push_back(tmp);
        }
      }
    return adj_list;
  }


float calculate_heuristic(Node* initial_state, Node* goal)
{
    float heur;
    vector< vector<char> > now = initial_state->block;
    vector< vector<char> > reqd = goal->block;

    float blocks_not_on_zero_stack = 0;

    for(int i=1; i<num_of_stacks; i++)
    {
        blocks_not_on_zero_stack += now[i].size();
    }
 //   cout << "blocks_not_on_zero_stack " << blocks_not_on_zero_stack << endl;
    float blocks_out_of_place = 0, blocks_out_of_order_on_any_stack = 0;

    blocks_out_of_place = blocks_not_on_zero_stack;
    for(int i=0; i<now[0].size(); i++)
    {
        if(now[0][i] != reqd[0][i])
        {
            blocks_out_of_place++;
            blocks_out_of_order_on_any_stack++;
        }
    }
  //  cout << "blocks_out_of_place " << blocks_out_of_place << endl;
    blocks_out_of_order_on_any_stack += blocks_not_on_zero_stack;
  //  cout << "blocks_out_of_order_on_any_stack " << blocks_out_of_order_on_any_stack << endl;
    heur = (-0.5 * blocks_not_on_zero_stack + 4.5 * blocks_out_of_place)*5 - blocks_out_of_order_on_any_stack;
   //heur = blocks_out_of_place; // simple heuristic
    return heur;
}

void printPath(Node* initial_state, Node* final_state)
{
    vector<Node*> temp;
    temp.push_back(final_state);
    while(final_state->block != initial_state->block)
    {
        temp.push_back(final_state->parent);
        final_state = final_state->parent;
    }
    for(int i=temp.size()-1; i>=0; i--)
    {
        cout << endl;
        cout << "f=g+h=" << temp[i]->f << endl;
        printState(temp[i], num_of_stacks);
        cout << endl;
    }

    cout << "Depth: " << temp.size()-1 << endl;
    cout << endl;
}

bool isGoal(Node *currState,  Node* goalState)
{
  vector<vector<char> > a = currState->block;
  vector<vector<char> > b = goalState->block;
  if (a.size() != b.size())
    return false;
  for (int p=0; p<a.size(); p++)
    {
      if(a[p].size() != b[p].size())
        return false;
      else
        {
          for (int q=0; q<a[p].size() ; q++)
            if(a[p][q] != b[p][q])
              return false;
        }
    }
  return true;
}

bool isVisited(Node* state)
{
    for(int i=0; i<mycount; i++)
    {
        if(isGoal(blocksWorld[i], state))
        {
            return true;
        }
    }
    return false;
}

class cmp
{
public:
    bool operator()(Node* n1, Node* n2)
    {
        if(n1->f >= n2->f) return true;
        return false;
    }
};

Node* A_Star(Node* initial_state, Node* final_state)
{
    int itr = 1;
    int frnt;
    if(initial_state->block == final_state->block)
        return initial_state;

    priority_queue<Node*, vector<Node*>, cmp> frontier;

    vector< vector<char> > visited;

    initial_state->g = 0;
    initial_state->parent = NULL;
    initial_state->h = calculate_heuristic(initial_state, final_state);
    initial_state->f = initial_state->g + initial_state->h;
    frontier.push(initial_state);
    frnt = 1;

    while(!frontier.empty())
    {
        int sz = frontier.size();
        frnt = max(frnt, sz);
        Node* x = frontier.top();
        frontier.pop();

        if(isGoal(x, final_state))
        {

            cout << "Total Iterations = " << itr << endl;
            cout << "Maximum queue size = " << frnt << endl;
            cout << endl;
            cout << "Solution Path: " << endl;
            printPath(initial_state, x);
            cout << endl;
            cout << "Final State: " << endl;
            printState(x, num_of_stacks);
            cout << endl;
            cout << "Success!!!" << endl;
            cout << "******************************" << endl;
            return x;
        }
        else
        {
            if(itr == 1000)
            {
                cout << "Failed to reach the goal state." << endl;
                cout << "Final State after 1000 goal tests: " << endl;

                printState(x, num_of_stacks);
                cout << endl;
                return 0;
            }
            itr++;
          //  cout << "itr " << itr << endl;
            vector<Node*> new_list = generateSuccessor(x);
            for(int i = 0; i<new_list.size(); i++)
            {
                if(!isVisited(new_list[i]))
                {
                    new_list[i]->g = x->g + 1;
                    new_list[i]->parent = x;
                    new_list[i]->h = calculate_heuristic(new_list[i], final_state);
                    new_list[i]->f = new_list[i]->g + new_list[i]->h;
                    blocksWorld[mycount++] = new_list[i];
                    frontier.push(new_list[i]);
                }
                else
                {
                     if(new_list[i]->g > x->g + 1)
                        {
                            new_list[i]->parent = x;
                            new_list[i]->g = x->g +1;
                            new_list[i]->h =  calculate_heuristic(new_list[i], final_state);
                            new_list[i]->f = x->g + 1 + new_list[i]->h;
                               // Heapify
                            vector<Node*> temp;
                            while(!frontier.empty())
                               {
                                    temp.push_back(frontier.top());
                                    frontier.pop();

                               }
                               for(int b=0; b<temp.size(); b++)
                               {
                                   frontier.push(temp[b]);
                               }
                           }
                }
            }
        }
    }

}

int main()
{
            cout << endl;
            cout << "Enter number of Blocks and Stacks respectively" << endl;
            cin >> num_of_blocks >> num_of_stacks;
            blocksWorld[0] = new Node(num_of_stacks, num_of_blocks);

            // sample test cases

            //(5, 3)
           /* vector<vector<char> > block;
            vector<char> temp1;
            temp1.push_back('D');
            block.push_back(temp1);
            vector<char> temp2;
            temp2.push_back('C');
            temp2.push_back('A');
            block.push_back(temp2);
            vector<char> temp3;
            temp3.push_back('B');
            temp3.push_back('E');
            block.push_back(temp3);
            blocksWorld[0]->block = block; */

            //(20, 8)
            /*
            vector<vector<char> > block;
            vector<char> temp1;
            temp1.push_back('G');
            temp1.push_back('I');
            block.push_back(temp1);
            vector<char> temp2;
            temp2.push_back('A');
            temp2.push_back('H');
            temp2.push_back('J');
            block.push_back(temp2);
            vector<char> temp3;
            temp3.push_back('B');
            temp3.push_back('M');
            block.push_back(temp3);
            vector<char> temp4;
            block.push_back(temp4);
            vector<char> temp5;
            temp5.push_back('D');
            temp5.push_back('N');
            temp5.push_back('P');
            block.push_back(temp5);
            vector<char> temp6;
            temp6.push_back('F');
            temp6.push_back('R');
            block.push_back(temp6);
            vector<char> temp7;
            temp7.push_back('E');
            temp7.push_back('K');
            temp7.push_back('T');
            block.push_back(temp7);
            vector<char> temp8;
            temp8.push_back('C');
            temp8.push_back('L');
            temp8.push_back('O');
            temp8.push_back('Q');
            temp8.push_back('S');
            block.push_back(temp8);
            blocksWorld[0]->block = block; */


            //(5, 3)
            /*
            vector<vector<char> > block;
            vector<char> temp1;
            temp1.push_back('B');
            block.push_back(temp1);
            vector<char> temp2;
            temp2.push_back('C');
            temp2.push_back('E');
            block.push_back(temp2);
            vector<char> temp3;
            temp3.push_back('A');
            temp3.push_back('D');
            block.push_back(temp3);
            blocksWorld[0]->block = block;
            */

            //(10, 5)
            /*
            vector<vector<char> > block;
            vector<char> temp1;
            temp1.push_back('D');
            block.push_back(temp1);
            vector<char> temp2;
            temp2.push_back('E');
            temp2.push_back('F');
            temp2.push_back('I');
            temp2.push_back('J');
            block.push_back(temp2);
            vector<char> temp3;
            temp3.push_back('B');
            temp3.push_back('G');
            block.push_back(temp3);
            vector<char> temp4;
            temp4.push_back('C');
            temp4.push_back('H');
            block.push_back(temp4);
            vector<char> temp5;
            temp5.push_back('A');
            block.push_back(temp5);
            blocksWorld[0]->block = block; */


            //(8, 4)

            /*vector<vector<char> > block;
            vector<char> temp1;
            temp1.push_back('C');
            temp1.push_back('G');
            temp1.push_back('H');
            block.push_back(temp1);
            vector<char> temp2;
            temp2.push_back('B');
            temp2.push_back('A');
            block.push_back(temp2);
            vector<char> temp3;
            temp3.push_back('E');
            temp3.push_back('D');
            block.push_back(temp3);
            vector<char> temp4;
            temp4.push_back('F');
            block.push_back(temp4);
            blocksWorld[0]->block = block; */

            problemGenerator(blocksWorld[0], num_of_blocks, num_of_stacks);

            cout << endl;
            cout << "Initial State: " << endl;
            printState(blocksWorld[0], num_of_stacks);
            cout << endl;

            Node* goal = new Node(num_of_stacks, num_of_blocks);
            vector<vector<char> > goal_vector;
            vector<char> temp;
            for(int i=0; i<num_of_blocks; i++)
            {
                temp.push_back(i+65);
            }
            goal_vector.push_back(temp);
            for(int j=1;j<num_of_stacks;j++)
            {
            vector<char> temp;
	        goal_vector.push_back(temp);
            }
            goal->block = goal_vector;
            cout<<"Goal State"<<endl;
            printState(goal, num_of_stacks);
            cout << endl;
            //calculate_heuristic(blocksWorld[0], goal);

            A_Star(blocksWorld[0], goal);
            cout << "Process completed." << endl;
            cout << endl;

            return 0;
}
