#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>

using namespace std;

char choice;
int itr = 0;

class Clause
{
public:
	
	int id;
	vector<string> literals;
	
	Clause(int id)
	{
		this->id = id;
	}

};
vector<Clause*> clauses;
vector<string> symbols;
map<string, bool> model;

bool isSame(string a, string b)
{
	string tmp;
	if (a[0] == '-')
	{
		for (int i = 1; i < a.size(); i++)
			tmp += a[i];
		a = tmp;
	}
	if (a.compare(b) == 0)
		return true;
	else
		return false;
}

bool unitTrue(string& cr, vector<string>& cls, map<string, bool>& mp)
{
	map<string, bool>::iterator it;
	if (cr[0] != '-')
		it = mp.find(cr);
	else
	{
		string t;
		for (int i = 1; i < cr.size(); i++)
		{
			t += cr[i];
		}
		it = mp.find(t);
	}
	if (it != mp.end())
		return false;
	int cnt = 0;
	for (int i = 0; i < cls.size(); i++)
	{
		if (cls[i].compare(cr) != 0)
		{
			string t = cls[i];
			if (t[0] == '-')
			{
				string tp;
				for (int a = 1; a < t.size(); a++)
					tp += t[a];
				t = tp;
			}
			if (mp.find(t) != mp.end())
				cnt++;
		}
	}
	if (cnt != cls.size() - 1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool pureTrue(string& cr, vector<Clause*>& cls, map<string, bool>& mp)
{
	int sign = 0;
	for (int i = 0; i < cls.size(); i++)
	{
		for (int j = 0; j < cls[i]->literals.size(); j++)
		{
			if (isSame(cls[i]->literals[j], cr))
			{
				if (cls[i]->literals[j][0] == '-')
				{
					if (sign == 0 || sign == -1)
						sign = -1;
					else
						return false;
				}
				else
				{
					if (sign == 0 || sign == 1)
						sign = 1;
					else
						return false;
				}
			}
		}
	}
	return true;
}

bool findPolarity(string c, vector<Clause*> a)
{
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 0; j < a[i]->literals.size(); j++)
		{
			string now = a[i]->literals[j];
			if (now[0] == '-')
			{
				string t;
				for (int k = 1; k < now.size(); k++)
					t += now[k];
				now = t;
				if (isSame(now, c))
				{
					return false;
				}
			}
			else
			{
				if (isSame(now, c))
				{
					return true;
				}
			}
		}
	}
}

vector<Clause*> findUnassignedClauses(vector<Clause*> c, map<string, bool> m)
{
	vector<Clause*> ans;
	for (int i = 0; i < c.size(); i++)
	{
		bool str_status = false;
		for (int j = 0; j < c[i]->literals.size(); j++)
		{
			string t = c[i]->literals[j];
			if (t[0] == '-')
			{
				string tmp;
				for (int k = 1; k < t.size(); k++)
				{
					tmp += t[k];
				}
				t = tmp;
			}
			map<string, bool>::iterator it;
			it = m.find(t);
			if (it != m.end())
			{
				str_status = str_status || true;
			}
		}
		if (str_status != true)
		{
			ans.push_back(c[i]);
		} 
	}
	return ans;
}

vector<Clause*> findUnassignedClausesForUnit(vector<Clause*> c, map<string, bool> m)
{
	vector<Clause*> ans;
	for (int i = 0; i < c.size(); i++)
	{
		bool str_status = false;
		for (int j = 0; j < c[i]->literals.size(); j++)
		{
			string t = c[i]->literals[j];
			map<string, bool>::iterator it;
			if (t[0] == '-')
			{
				string tmp;
				for (int k = 1; k < t.size(); k++)
				{
					tmp += t[k];
				}
				it = m.find(tmp);
				if (it != m.end())
				{
					if (it->second == true)
						str_status = str_status || false;
					else
						str_status = str_status || true;
				}
				else
					str_status = str_status;
			}
			else
			{
				it = m.find(t);
				if (it != m.end())
				{
					if (it->second == true)
						str_status = str_status || true;
					else
						str_status = str_status || false;
				}
				else
					str_status = str_status;
			}
		}
		
		if (str_status != true)
		{
			ans.push_back(c[i]);
		}
	}
	return ans;
}

bool findUnitPolarity(string c)
{
	if (c[0] == '-')
		return false;
	else
		return true;
}

pair<string, bool> findUnitCaluse(vector<Clause*>& c, map<string, bool>& mp)
{
bool polarity;
pair<string, bool> ans;

vector<Clause*> c_new = findUnassignedClausesForUnit(c, mp);

if (c_new.size() == 0)
return ans;

for (int i = 0; i < c_new.size(); i++)
{
	for (int j = 0; j < c_new[i]->literals.size(); j++)
	{
		string curr = c_new[i]->literals[j];
		if (unitTrue(curr, c_new[i]->literals, mp))
		{
			polarity = findUnitPolarity(curr);
			if (curr[0] == '-')
			{
				string a;
				for (int k = 1; k < curr.size(); k++)
					a += curr[k];
				curr = a;
			}
			ans = make_pair(curr, polarity);
			return ans;
		}
	}
}

return ans;

}

pair<string, bool> findPureClause(vector<Clause*>& c, vector<string>& pr, map<string, bool>& mp)
{
	bool polarity;
	pair<string, bool> ans;
	if (pr.size() == 0)
	{
		return ans;
	}
	vector<Clause*> c_new = findUnassignedClauses(c, mp);
	if (c_new.size() == 0)
		return ans;
;
	for (int i = 0; i < pr.size(); i++)
	{
		string curr = pr[i];
		if (pureTrue(curr, c_new, mp))
		{
			polarity = findPolarity(curr, c_new);
			if (polarity == true || polarity == false)
			{
				ans = make_pair(curr, polarity);
				return ans;
			}
		}
	}
	return ans;
}

bool findOpp(bool v)
{
	if (v == true)
		return false;
	else
		return true;
}

bool findVal(string t, map<string, bool> m)
{
	if (t[0] == '-')
	{
		string tp;
		for (int j = 1; j < t.size(); j++)
		{
			tp += t[j];
		}
		if (m.find(tp) == m.end())
			return true;
		bool tpval = m.find(tp)->second;
		tpval = findOpp(tpval);
		return tpval;
	}
	else
	{
		if (m.find(t) == m.end())
			return true;
		bool tval = m.find(t)->second;
		return tval;
	}
}

bool chkSatis(Clause* c, map<string, bool> m)
{
	for (int i = 0; i < c->literals.size(); i++)
	{
		string tmp = c->literals[i];
		bool v = findVal(tmp, m);
		if (v == true)
		{
			return true;
		}
	}
	return false;
}

bool chkClauses(vector<Clause*> c, map<string, bool> mp)
{
	for (int i = 0; i < c.size(); i++)
	{
		if (!chkSatis(c[i], mp))
		{
			return false;
		}
	}
	return true;
}

bool satisfiability(vector<Clause*> cl, vector<string> p, map<string, bool> &m)
{
	if (p.empty())
	{	
		if (chkClauses(cl, m))
		{
			std::cout << endl;
			std::cout << "*****Solution******" << endl;
			std::cout << "After DPLL: " << endl;
			std::cout << "Number of nodes searched: " << itr << endl;

			for (map<string, bool>::iterator iter = m.begin(); iter != m.end(); iter++)
			{
				std::cout << iter->first << " ";
				if (iter->second == true)
					std::cout << "true" << endl;
				else
					std::cout << "false" << endl;
			}
			std::cout << "True propositions: " << endl;
			for (map<string, bool>::iterator iter = m.begin(); iter != m.end(); iter++)
			{
				if (iter->second == true)
					std::cout << iter->first << " ";
			}
			if (choice == 'y')
			{
				std::cout << endl << "The team agents are:" << endl;
				for (map<string, bool>::iterator iter = m.begin(); iter != m.end(); iter++)
				{
					if (iter->second == true)
					{
						string fin = iter->first;
						if (fin.compare("a") == 0 || fin.compare("b") == 0 || fin.compare("c") == 0 || fin.compare("d") == 0 || fin.compare("e") == 0 || fin.compare("f") == 0 || fin.compare("g") == 0 || fin.compare("h") == 0)
							std::cout << iter->first << " ";
					}
				}
			}
			cout << endl;
			return true;
		}
		else
			return false;
	}
	
	pair<string, bool> pure = findPureClause(cl, p, m);
	if (!pure.first.empty())
	{
		std::cout << "pure symbol: " << pure.first << " with value " << pure.second << endl;
		for (int i = 0; i < p.size(); i++)
		{
			if (p[i].compare(pure.first) == 0)
			{
				p.erase(p.begin() + i);
			}
		}
		m[pure.first] = pure.second;
		itr++;
		return satisfiability(cl, p, m);
	}
	
	
	pair<string, bool> unit = findUnitCaluse(cl, m);
	if (!unit.first.empty())
	{
		std::cout << "unit symbol: " << unit.first << " with value " << unit.second << endl;
		for (int i = 0; i < p.size(); i++)
		{
			if (p[i].compare(unit.first) == 0)
			{
				p.erase(p.begin() + i);
			}
		}
		
		m[unit.first] = unit.second;
		itr++;
		if (satisfiability(cl, p, m))
			return true;
		else
		{
			map<string, bool>::iterator it;
			it = m.find(unit.first);
			m.erase(it);
			p.push_back(unit.first);
			std::sort(p.begin(), p.end());
			return false;
		}

	}
	
	string curr = p.front();
	std::cout << "current string " << curr << " ";
	p.erase(p.begin());
	m[curr] = true;
	std::cout << "value " << m[curr] << endl;
	itr++;
	vector<Clause*> cl_now = findUnassignedClausesForUnit(cl, m);
	if (chkClauses(cl_now, m))
	{
		
		if (satisfiability(cl_now, p, m))
			return true;

	}
	m[curr] = false;
	cl_now = findUnassignedClausesForUnit(cl, m);
	std::cout << "current string " << curr << " ";
	std::cout << "value " << m[curr] << endl;
	itr++;
	if (chkClauses(cl_now, m))
	{
		//itr++;
		if (satisfiability(cl_now, p, m))
			return true;
	}
			
	std::cout << "backtracking...... " << endl;
	map<string, bool>::iterator it;
	it = m.find(curr);
	m.erase(it); 
	p.push_back(curr);
	std::sort(p.begin(), p.end());
	return false;
}

int main()
{
	string filename;
	std::cout << "Enter the file name." << endl;
	cin >> filename;
	
	std::cout << "Is this the multi-agent Knowledge base? (y/n)" << endl;
	cin >> choice;
	int num_jobs;
	string jb;
	vector<string> jobs;
	if (choice == 'y')
	{


		std::cout << "Enter the number of jobs." << endl;
		cin >> num_jobs; 
		std::cout << "Enter the jobs" << endl;
		for (int i = 0; i < num_jobs; i++)
		{
			cin >> jb;
			jobs.push_back(jb);
		}
	}
	
	string line;
	ifstream infile(filename+".txt");
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
				obj->literals.push_back(buffer);
				string tmp;
				if (buffer[0] == '-')
				{
					for (int j = 1; j < buffer.size(); j++)
					{
						tmp += buffer[j];
					}
				}
				else
				{
					tmp = buffer;
				}
				int cnt = 0;
				for (int j = 0; j < symbols.size(); j++)
				{
					if (symbols[j].compare(tmp) != 0)
						cnt++;
				}
				if (cnt == symbols.size())
				{
					symbols.push_back(tmp);
				}
			}
			else
			{
				break;
			}
		}
		if (!obj->literals.empty())
			clauses.push_back(obj);
		else
			i--;
		i++;
	}
	
	

	std::cout << "The existing clauses are: " << endl;
	for (int i = 0; i < clauses.size(); i++)
	{
		std::cout << endl << clauses[i]->id << ": ";
		for (int j = 0; j < clauses[i]->literals.size(); j++)
		{
			std::cout << clauses[i]->literals[j] << " ";
		}
	}
	std::cout << endl;
	
	if (!jobs.empty())
	{
		for (int i = 0; i < jobs.size(); i++)
		{

			Clause* obj = new Clause(clauses.size());
			obj->literals.push_back(jobs[i]);
			clauses.push_back(obj);
		}
	}
	

	std::sort(symbols.begin(), symbols.end());
	std::cout << endl;
	std::cout << "The list of symbols is: " << endl;
	for (int i = 0; i < symbols.size(); i++)
		std::cout << symbols[i] << " ";
	std::cout << endl;
	std::cout << endl;
	itr++;
	satisfiability(clauses, symbols, model);

	return 0;
}