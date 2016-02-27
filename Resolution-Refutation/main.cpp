#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <map>

using namespace std;

class Clause
{
public:
	int id;
	vector<string> literalList;
	Clause *parentX, *parentY;

	Clause(int x)
	{
		id = x;
		parentX = NULL;
		parentY = NULL;
	}
};
vector<Clause*> myClauseList;

class ResPair
{
public:
	Clause *p1, *p2;
	ResPair* parent;
	ResPair(Clause* q1, Clause* q2)
	{
		p1 = q1;
		p2 = q2;
		parent = NULL;
	}
};

bool isResolvable(Clause* a1, Clause* a2)
{
	unordered_map<string, bool> map1;
	unordered_map<string, bool> map2;

	for (int i = 0; i < a1->literalList.size(); i++)
	{
		string temp1 = a1->literalList[i];
		if (temp1[0] == '-')
		{
			string temp;
			for (int j = 1; j < temp1.length(); j++)
				temp += temp1[j];
			map1[temp] = true;
		}
		else
		{
			string temp;
			for (int j = 0; j<temp1.length(); j++)
				temp += temp1[j];
			map1[temp] = false;
		}
	}
	
	for (int i = 0; i < a2->literalList.size(); i++)
	{
		string temp1 = a2->literalList[i];
		if (temp1[0] == '-')
		{
			string temp;
			for (int j = 1; j < temp1.length(); j++)
				temp += temp1[j];
			map2[temp] = true;
		}
		else
		{
			string temp;
			for (int j = 0; j<temp1.length(); j++)
				temp += temp1[j];
			map2[temp] = false;
		}
		
	}
	
	for (unordered_map<string, bool>::iterator iter1 = map1.begin(); iter1 != map1.end(); iter1++)
	{
		for (unordered_map<string, bool>::iterator iter2 = map2.begin(); iter2 != map2.end(); iter2++)
		{
			if (iter1->first == iter2->first && iter1->second != iter2->second)
			{
			/*	cout << a1->id << " and " << a2->id << " ";
				cout << iter1->first << " and " << iter2->first << " are resolvable" << endl; */
				return true;
			}
		}
	}
	//cout << "not resolvable" << endl;
	return false;
}

Clause* resolve(Clause* a1, Clause* a2, string p)
{
	if (p[0] == '-')
	{
		string t;
		for (int i = 1; i < p.length(); i++)
		{
			t += p[i];
		}
		p = t;
	}
	
	Clause* ans = new Clause(myClauseList.size());
	map<string, bool> myAns;
	int sign = 0;
	for (int i = 0; i < a1->literalList.size(); i++)
	{
		if (a1->literalList[i][0] == '-')
		{
			string t;
			for (int q = 1; q < a1->literalList[i].length(); q++)
			{
				t += a1->literalList[i][q];
			}
			if (t.compare(p) != 0)
			{
				myAns[a1->literalList[i]] = true;
			}
			else
			{
				sign = -1;
			}
		}
		else
		{
			string t = a1->literalList[i];
			if (t.compare(p) != 0)
			{
				myAns[a1->literalList[i]] = false;
			}
			else
			{
				if (sign == 0)
				sign = 1;
			}
		}
	}
	
	for (int i = 0; i < a2->literalList.size(); i++)
	{
		if (a2->literalList[i][0] == '-')
		{
			string t;
			for (int q = 1; q < a2->literalList[i].length(); q++)
			{
				t += a2->literalList[i][q];
			}
			if (t.compare(p) != 0)
			{
				myAns[a2->literalList[i]] = true;
			}
			else
			{
				if (sign == -1)
				{
					myAns[a2->literalList[i]] = true;
				}
			}
		}
		else
		{
			string t = a2->literalList[i];
			if (t.compare(p) != 0)
			{
				myAns[a2->literalList[i]] = false;
			}
			else
			{
				if (sign == 1)
				{
					myAns[a2->literalList[i]] = false;
				}
			}
		}
	}
	
	for (map<string, bool>::iterator iter = myAns.begin(); iter != myAns.end(); iter++)
	{
		//cout << "clause " << iter->first << endl;
		ans->literalList.push_back(iter->first);
	}

	return ans;
}

void printProofTree(Clause* c)
{
	cout << c->id << " : ";
	std::cout << "[";
	for (int i = 0; i < c->literalList.size(); i++)
	{
		std::cout << c->literalList[i] << " ";
	}
	std::cout << "] ";
	std::cout << " [";
	if (c->parentX == NULL) 
		cout << "Input";
	else if (c->parentX)
		cout << c->parentX->id;
	if (c->parentY == NULL && c->parentX == NULL)
		cout << "";
	else
		cout << " , " << c->parentY->id;
	std::cout << "]";
	std::cout << endl;
	if (c->parentY != NULL)
	printProofTree(c->parentY);
	if (c->parentX != NULL)
	printProofTree(c->parentX);
		
	return;
}

bool isOpposite(string a1, string a2)
{
	if (a1[0] == '-')
	{
		if (a2[0] == '-')
		{
			return false;
		}
		else
		{
			string t1;
			for (int i = 1; i < a1.length(); i++)
				t1 += a1[i];
			if (t1.compare(a2) == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		if (a2[0] == '-')
		{
			string t1;
			for (int i = 1; i < a2.length(); i++)
				t1 += a2[i];
			if (t1.compare(a1) == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
}

bool isVisited(Clause* c1)
{
	for (int i = 0; i < myClauseList.size(); i++)
	{
		Clause* chk = myClauseList[i];
		int siz = 0;
		if (chk->literalList.size() == c1->literalList.size())
		{
			for (int j = 0; j < c1->literalList.size(); j++)
			{
				for (int k = 0; k < chk->literalList.size(); k++)
				{
					if (c1->literalList[j].compare(chk->literalList[k]) == 0)
					{
						siz++;
					}
				}
			}
			if (siz == c1->literalList.size())
				return true;
		}
	} 
	return false;
}

class cmp
{
public:
	bool operator() (ResPair* r1, ResPair* r2)
	{
		int len1 = r1->p1->literalList.size() + r1->p2->literalList.size();
		int len2 = r2->p1->literalList.size() + r2->p2->literalList.size();
		if (len1 > len2) return true;
		return false;
	}
};

bool resolution(vector<Clause*> c1)
{
	int iter = 0;
	int frnt = 1;
	priority_queue<ResPair*, vector<ResPair*>, cmp> pq;

	for (int i = 0; i < c1.size(); i++)
	{
		for (int j = i + 1; j < c1.size(); j++)
		{
			if (isResolvable(c1[i], c1[j]))
			{
				ResPair* rp = new ResPair(c1[i], c1[j]);
				pq.push(rp);
				int sz = pq.size();
				frnt = max(frnt, sz);
			}
		}
	}

	while (!pq.empty())
	{
		//Clause* resolvent = new Clause(myClauseList.size());
		iter++;
		if (iter == 1000)
		{
			std::cout << "Failure!!!" << endl;
			return false;
		}
		int sz = pq.size();
		frnt = max(frnt, sz);
		ResPair *curr = pq.top();
		pq.pop();
		for (int i = 0; i < curr->p1->literalList.size(); i++)
		{
			for (int j = 0; j < curr->p2->literalList.size(); j++)
			{
				if (isOpposite(curr->p1->literalList[i], curr->p2->literalList[j]))
				{
					Clause* resolvent = resolve(curr->p1, curr->p2, curr->p1->literalList[i]);
					resolvent->parentX = curr->p1;
					resolvent->parentY = curr->p2;
					if (resolvent->literalList.empty())
					{
						std::cout << "Success!! Empty clause found." << endl;
						cout << endl;
						std::cout << "Number of iterations: " << iter << endl;
						std::cout << "Maximum queue size: " << frnt << endl;
						cout << endl;
						std::cout << "Printing the proof tree: " << endl;
						printProofTree(resolvent);
						cout << endl;
						return true;
					}

					if (!isVisited(resolvent))
					{
						myClauseList.push_back(resolvent);
						for (int i = 0; i < myClauseList.size()-1; i++)
						{
							if (isResolvable(resolvent, myClauseList[i]))
							{
								ResPair* rp = new ResPair(myClauseList[i], resolvent);
								pq.push(rp);
							}
						}
					}
				}
			}
		}
	}
	std::cout << "Failure!!!" << endl;
	return false;
}

int main()
{
	string line;
	ifstream infile("example.txt");
	int i = 0;
	while (getline(infile, line))
	{
		stringstream new_line(line);
		string buffer;
		Clause* obj = new Clause(i);
		while (new_line >> buffer)
		{
			if (buffer[0] != '#')
			{
				obj->literalList.push_back(buffer);
			}
			else
			{
				break;
			}
		}
		if (!obj->literalList.empty())
			myClauseList.push_back(obj);
		else
			i--;
		i++;
	}
	
	cout << "The existing clauses are: " << endl;
	for (int i = 0; i < myClauseList.size(); i++)
	{
	cout << endl << myClauseList[i]->id << " ";
	for (int j = 0; j < myClauseList[i]->literalList.size(); j++)
	{
	cout << myClauseList[i]->literalList[j] << " " ;
	}
	} 
	cout << endl; 
	
	bool status = resolution(myClauseList);

	return 0;
}
