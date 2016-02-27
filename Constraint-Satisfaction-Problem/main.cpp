#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string>
#include <queue>
#include <stack>
#include<map>
#include<limits.h>

using namespace std;

enum class VarType { NATIONALITY, COLOR, PET, DRINK, FOOD, JOBS };


map<int, bool> nationality;
map<int, bool> color;
map<int, bool> pet;
map<int, bool> drink;
map<int, bool> food;


int iter =0;
class Variables
{
public:
    VarType type;
    int name;
    int value;
    Variables(VarType t, int n, int v)
    {
        type = t;
        name = n;
        value = v;
    }
};

int vars, vals;

string getVarName(Variables* var)
{
		if (var->type == VarType::JOBS)
        {
			switch (var->name)
			{
			case 0:
				return "ACTOR";
			case 1:
				return "BOXER";
			case 2:
				return "CHEF";
			case 3:
				return "CLERK";
			case 4:
				return "GUARD";
			case 5:
				return "NURSE";
			case 6:
				return "POLICE_OFFICER";
			case 7:
				return "TEACHER";
			}
		}

		else if (var->type == VarType::COLOR)
        {
			switch (var->name)
			{
			case 0:
				return "RED";
			case 1:
				return "GREEN";
			case 2:
				return "BLUE";
			case 3:
				return "YELLOW";
			case 4:
				return "IVORY";
			}
		}
		else if (var->type == VarType::NATIONALITY)
        {
			switch (var->name)
			{
			case 0:
				return "ENGLISH";
			case 1:
				return "SPANISH";
			case 2:
				return "NORWEIGH";
			case 3:
				return "JAPANESE";
			case 4:
				return "UKRAIN";
			}
		}
		else if (var->type == VarType::DRINK)
        {
			switch (var->name)
			{
			case 0:
				return "JUICE";
			case 1:
				return "MILK";
			case 2:
				return "COFFEE";
			case 3:
				return "TEA";
			case 4:
				return "WATER";
			}
		}
		else if (var->type == VarType::FOOD)
        {
			switch (var->name)
			{
			case 0:
				return "SNICKERS";
			case 1:
				return "SMARTIES";
			case 2:
				return "MILKYWAY";
			case 3:
				return "KITKAT";
			case 4:
				return "HERSHEY";
			}
		}
		else if (var->type == VarType::PET)
        {
			switch (var->name)
			{
			case 0:
				return "DOG";
			case 1:
				return "ZEBRA";
			case 2:
				return "HORSE";
			case 3:
				return "SNAIL";
			case 4:
				return "FOX";
			}
		}
        return "";
}

string getJobsValName(int val)
{
		switch (val)
		{
		case 0:
			return "ROBERTA";
		case 1:
			return "THELMA";
		case 2:
			return "STEVE";
		case 3:
			return "PETE";
		}
		return "";
}

string getHousesValName(int val)
{
    switch (val)
		{
		case 0:
			return "ROBERTA";
		case 1:
			return "THELMA";
		case 2:
			return "STEVE";
		case 3:
			return "PETE";
		}
		return "";
}


class jobsPuzzle
{
public:

    int actor = 0, boxer = 1, chef = 2, clerk = 3, guard = 4, nurse = 5, police_officer = 6, teacher = 7;
    int roberta = 0, thelma = 1, steve = 2, pete = 3;
    stack<Variables*> unassignedVariables;
    stack<Variables*> assignedVariables;
    //vector<Variables*> allVariables;
    //unordered_map<int, int> varToVal;
    Variables* t[8];
    jobsPuzzle()
    {
        vars = 8;
        vals = 4;
    }

    void settingProblem()
    {
        //cout << "i am in jobs puzzle" << endl;

        t[0] = new Variables(VarType::JOBS, actor, -1);

        t[1] = new Variables(VarType::JOBS, boxer, -1);

        t[2] = new Variables(VarType::JOBS, chef, -1);

        t[3] = new Variables(VarType::JOBS, clerk, -1);

        t[4] = new Variables(VarType::JOBS, guard, -1);

        t[5] = new Variables(VarType::JOBS, nurse, -1);

        t[6] = new Variables(VarType::JOBS, police_officer, -1);

        t[7] = new Variables(VarType::JOBS, teacher, -1);
        unassignedVariables.push(t[7]);
        unassignedVariables.push(t[6]);
        unassignedVariables.push(t[5]);
        unassignedVariables.push(t[4]);
        unassignedVariables.push(t[3]);
        unassignedVariables.push(t[2]);
        unassignedVariables.push(t[1]);
        unassignedVariables.push(t[0]);

    }

    vector<int> gettingAvailValues()
    {
            vector<int> availValues;
            for(int i=0; i<vals; i++)
            {
                availValues.push_back(i);
            }
            return availValues;
    }

    bool jobConsistent()
    {
		int job_per_person[vals];
		for(int i=0; i<vals; i++)
            job_per_person[i] = 0;
        //cout << "assigned stack size " << assignedVariables.size() << endl;
        stack<Variables*> temporary = assignedVariables;
        int times1 = temporary.size();
		for(int i=0; i<times1; i++)
        {
            Variables* var1 = temporary.top();
            temporary.pop();
			job_per_person[var1->value] = 1;
			bool isMale = (var1->value == steve || var1->value == pete);
			bool isEducated = (var1->value != pete);
            int times = temporary.size();
			for (int j=0; j<times; j++)
            {
                Variables* var2 = temporary.top();
          //      cout << "stk top to be compared " << getVarName(var2) << endl;
                temporary.pop();
				if (var1->value == var2->value)
                {
					job_per_person[var1->value]++;
					if (job_per_person[var1->value] > 2)
                    {
			//			cout << "Failed: More than 2 person have job" << endl;
						return false;
					}
				}
			}

			if (var1->name == nurse && isMale == false)
            {
				//cout << "Failed: Nurse can not be Female" << endl;
				return false;
			}

			if (var1->name == actor && isMale == false)
            {
				//cout << "Failed: Actor can not be Female" << endl;;
				return false;
			}

			if (var1->name == boxer && var1->value == roberta)
            {
				//cout << "Failed: Roberta can not be boxer" << endl;;
				return false;
			}

			if ((var1->name == nurse || var1->name == teacher || var1->name == police_officer) && isEducated == false)
            {
				//cout << "Failed: Nurse Teacher and Police can not be uneducated" << endl;;
				return false;
			}

			if (var1->name == chef && var1->value != thelma)
            {
				//cout << "Failed: THELMA has to be chef" << endl;;
				return false;
			}

			if (var1->name == clerk && (var1->value == thelma || var1->value == roberta))
            {
				//cout << "Failed: THELMA/ROBERTA can not be clerk" << endl;;
				return false;
			}

			if (var1->name == police_officer && isMale == false)
            {
				//cout << "Failed: ROBERTA/THELMA is not a police office." << endl;
				return false;
			}
			cout << getVarName(var1) << " --> " << getJobsValName(var1->value) << endl;
            return true;
		}


    }

    void assigningValueToVars(Variables* var, int value)
    {
		var->value = value;
		//unassignedVariables.pop();
		//assignedVariables.push(var);
	}

	void unassigningValueToVars(Variables* var) {
		var->value = -1;
		//unassignedVariables.push(var);
		assignedVariables.pop();
	}

    void printSol()
    {
    cout << endl << "Solution:" << endl;
   // cout<<"assigned var size"<<assignedVariables.size();
    for(int i=0; i<vars; i++)
    {
        Variables* a = assignedVariables.top();
        assignedVariables.pop();
        cout << getVarName(a) << "-->" << getJobsValName(a->value) << endl;
    }

    /*for(int i=0; i<unassignedVariables.size(); i++)
    {
        Variables* a = unassignedVariables.top();
        unassignedVariables.pop();
        cout << getVarName(a) << "-->" << getValName(a->value) << endl;
    } */
    }

    Variables* mrv_heuristic(jobsPuzzle* prob)
    {
        stack<Variables*> unass = unassignedVariables;
        vector<Variables*> unass_v ;
        vector<int> values(10, -1);
        while(!unass.empty())
        {
            unass_v.push_back(unass.top());
            unass.pop();
        }


        for(int i=0; i<unass_v.size(); i++)
        {
            for(int domain =0 ; domain<4; domain++)
            {
                unass_v[i]->value = domain;
                assignedVariables.push(unass_v[i]);
                if(jobConsistent())
                    values[i]++;


                assignedVariables.pop();
            }
        }


        int mini = INT_MAX, pos =0;
	//cout<<"Printing Values---------------";
        for(int i=0; i<10; i++)
        {
            if(values[i] == -1)
                values[i] = 10;

            if(mini > values[i])
            {
                mini=values[i];
                pos =i;
            }
	  // cout<<" "<<values[i];
        }
	//cout<<endl<<" "<<pos<<endl;

       stack<Variables*>  tq = unassignedVariables;
      // cout<<"Before Printing Unassigned elements"<<endl;
         while(!tq.empty())
         {
           // cout<<" "<<getVarName(tq.top());
            tq.pop();
          }


	vector<Variables*> temp;
        for(int i=0; i<pos; i++)
        {
            temp.push_back(unassignedVariables.top());
            (unassignedVariables).pop();
        }

        Variables* ans = (unassignedVariables).top();
        (unassignedVariables).pop();

        for(int j=temp.size()-1; j>=0; j--)
        {
            (unassignedVariables).push(temp[j]);
        }

	stack<Variables*>  t = unassignedVariables;

	//cout<<"I am taking out"<<getVarName(ans)<<endl;
//	cout<<"After Printing Unassigned elements"<<endl;
	while(!t.empty())
	 {
	 //  cout<<" "<<getVarName(t.top());
	   t.pop();
	 }
     return ans;
    }

    bool jobBackTrack(jobsPuzzle* prob, int useMRV)
{
    //cout << "mrv in backtrack is " << useMRV << endl;
        Variables* var;
        //cout<<"Index"<<index<<endl;
       // if(useMRV == 0)
       // {
            //cout << "inside backtrack" << endl;
            if(prob->unassignedVariables.empty())
            {
                //cout<<"I am the culprit";
               // cout<<"size of assigned"<<assignedVariables.size();
                var = NULL;
                return true;
                //cout << "reached end" << endl;
            }

            if(useMRV !=0)
                {
		  var = mrv_heuristic(prob);
	//	  cout<<"mrv "<<getVarName(var) << endl;
		}
            else
                var = prob->unassignedVariables.top();
         //   cout << "*****************" << endl;
           // cout << "variable from queue " << getVarName(var) << endl;

	   if(!useMRV)
            prob->unassignedVariables.pop();
        //}
       /* else
        {
            var = prob->gettingVarsUsingMRV();
        } */



        vector<int> availValues = prob->gettingAvailValues();
        prob->assignedVariables.push(var);

        for(int i=0; i<availValues.size(); i++)
        {
		iter++;
           // cout << "Considering value: " << getValName(availValues[i]) << endl;
           // prob->assigningValueToVars(var, availValues[i]);
            var->value = availValues[i];
            if(prob->jobConsistent())
              {
        //          cout<<"Loop 1 "<<endl;
                  if( jobBackTrack(prob, useMRV))
                    {
          //              cout<<"Loop 2"<<endl;
                    return true;
                    }
              }
            //cout << "hereee" << endl;
           // prob->unassigningValueToVars(var);
            var->value = -1;
        }
        if(var->value == -1)
        {
                        //cout << "hereee-2" << endl;
            assignedVariables.pop();
            unassignedVariables.push(var);
        }
        return false;
}
};

class housesPuzzle
{
public:

    int english = 0, spanish = 1, norweigh = 2, japanese = 3, ukrain = 4;
	int snickers = 0, smarties = 1, milkway = 2, kitkat = 3, hershey = 4;
	int juice = 0, milk = 1, coffee = 2, tea = 3, water = 4;
	int dog = 0, zebra = 1, horse = 2, snail = 3, fox = 4;
	int red = 0, green = 1, blue = 2, yellow = 3, ivory = 4;
    Variables* t[25];
    stack<Variables*> unassignedVariables;
    stack<Variables*> assignedVariables;
    vector<Variables*> allVariables;

    housesPuzzle()
    {
        vars = 25;
        vals = 5;
    }

    void settingProblem()
	{
		t[0] = new Variables(VarType::NATIONALITY, english, -1);
        t[1] = new Variables(VarType::NATIONALITY, spanish, -1);
        t[2] = new Variables(VarType::NATIONALITY, norweigh, -1);
        t[3] = new Variables(VarType::NATIONALITY, ukrain, -1);
        t[4] = new Variables(VarType::NATIONALITY, japanese, -1);
        t[5] = new Variables(VarType::COLOR, green, -1);
        t[6] = new Variables(VarType::COLOR, blue, -1);
        t[7] = new Variables(VarType::COLOR, yellow, -1);
        t[8] = new Variables(VarType::COLOR, ivory, -1);
        t[9] = new Variables(VarType::COLOR, red, -1);
        t[10] = new Variables(VarType::DRINK, juice, -1);
        t[11] = new Variables(VarType::DRINK, coffee, -1);
        t[12] = new Variables(VarType::DRINK, milk, -1);
        t[13] = new Variables(VarType::DRINK, tea, -1);
        t[14] = new Variables(VarType::DRINK, water, -1);
        t[15] = new Variables(VarType::FOOD, snickers, -1);
        t[16] = new Variables(VarType::FOOD, smarties, -1);
        t[17] = new Variables(VarType::FOOD, milkway, -1);
        t[18] = new Variables(VarType::FOOD, kitkat, -1);
        t[19] = new Variables(VarType::FOOD, hershey, -1);
        t[20] = new Variables(VarType::PET, dog, -1);
        t[21] = new Variables(VarType::PET, horse, -1);
        t[22] = new Variables(VarType::PET, zebra, -1);
        t[23] = new Variables(VarType::PET, snail, -1);
        t[24] = new Variables(VarType::PET, fox, -1);
        unassignedVariables.push(t[24]);        allVariables.push_back(t[0]);
        unassignedVariables.push(t[23]);        allVariables.push_back(t[1]);
        unassignedVariables.push(t[22]);        allVariables.push_back(t[2]);
        unassignedVariables.push(t[21]);        allVariables.push_back(t[3]);
        unassignedVariables.push(t[20]);        allVariables.push_back(t[4]);
        unassignedVariables.push(t[19]);        allVariables.push_back(t[5]);
        unassignedVariables.push(t[18]);        allVariables.push_back(t[6]);
        unassignedVariables.push(t[17]);        allVariables.push_back(t[7]);
        unassignedVariables.push(t[16]);        allVariables.push_back(t[8]);
        unassignedVariables.push(t[15]);        allVariables.push_back(t[9]);
        unassignedVariables.push(t[14]);        allVariables.push_back(t[10]);
        unassignedVariables.push(t[13]);        allVariables.push_back(t[11]);
        unassignedVariables.push(t[12]);        allVariables.push_back(t[12]);
        unassignedVariables.push(t[11]);        allVariables.push_back(t[13]);
        unassignedVariables.push(t[10]);        allVariables.push_back(t[14]);
        unassignedVariables.push(t[9]);         allVariables.push_back(t[15]);
        unassignedVariables.push(t[8]);         allVariables.push_back(t[16]);
        unassignedVariables.push(t[7]);         allVariables.push_back(t[17]);
        unassignedVariables.push(t[6]);         allVariables.push_back(t[18]);
        unassignedVariables.push(t[5]);         allVariables.push_back(t[19]);
        unassignedVariables.push(t[4]);         allVariables.push_back(t[20]);
        unassignedVariables.push(t[3]);         allVariables.push_back(t[21]);
        unassignedVariables.push(t[2]);         allVariables.push_back(t[22]);
        unassignedVariables.push(t[1]);         allVariables.push_back(t[23]);
        unassignedVariables.push(t[0]);         allVariables.push_back(t[24]);
	}

    vector<int> gettingAvailValues()
    {
            vector<int> availValues;
            for(int i=0; i<vals; i++)
            {
                availValues.push_back(i);
            }
            return availValues;
    }

    int getVariableValue(VarType type, int name)
    {
		for (auto variable : allVariables)
        {
			if (variable->type == type && variable->name == name)
				return variable->value;
		}
		return -1;
	}

    bool housesConsistent()
    {

        int job_per_person[vals];
		for(int i=0; i<vals; i++)
            job_per_person[i] = 0;
        //cout << "assigned stack size " << assignedVariables.size() << endl;
        stack<Variables*> temporary = assignedVariables;
        int times1 = temporary.size();
		for(int i=0; i<times1; i++)
        {
            Variables* var1 = temporary.top();

/*
	    if(var1->type == VarType::NATIONALITY && var1->name == english && var1->value != 2)
		return false;
*/

/*

	    if(var1->type == VarType::COLOR && var1->name == green && var1->value != 4)
		return false;


	    if(var1->type == VarType::PET && var1->name == dog && var1->value != 3)
                return false;
*/


            if (var1->type == VarType::NATIONALITY && var1->name == english && getVariableValue(VarType::COLOR, red) != -1 && var1->value != getVariableValue(VarType::COLOR, red))
            {
	//			cout << "Failed 1" << endl;
				return false;
			}
  if (var1->type == VarType::COLOR && var1->name == red && getVariableValue(VarType::NATIONALITY, english) != -1 && var1->value != getVariableValue(VarType::NATIONALITY, english))
            {
          //                      cout << "Failed 1" << endl;
                                return false;
                        }

			if (var1->type == VarType::NATIONALITY && var1->name == spanish && getVariableValue(VarType::PET, dog) != -1 && var1->value != getVariableValue(VarType::PET, dog))
            {
		//		cout << "Failed 2" << endl;
				return false;
			}

                        if (var1->type == VarType::PET && var1->name == dog && getVariableValue(VarType::NATIONALITY, spanish) != -1 && var1->value != getVariableValue(VarType::NATIONALITY, spanish))
            {
                  //              cout << "Failed 2" << endl;
                                return false;
                        }

			if (var1->type == VarType::NATIONALITY && var1->name == norweigh && var1->value != 0)
            {
		//		cout << "Failed 3" << endl;
				return false;
			}


			if (var1->type == VarType::COLOR && var1->name == green && getVariableValue(VarType::COLOR, ivory) != -1 && var1->value != (getVariableValue( VarType::COLOR, ivory))+1)
            {
		//		cout << "Failed_4" << endl;
				return false;
			}



                        if (var1->type == VarType::COLOR && var1->name == ivory && getVariableValue(VarType::COLOR, green) != -1 && var1->value != (getVariableValue( VarType::COLOR, green))-1)
            {
                  //              cout << "Failed 4" << endl;
                                return false;
                        }


			if (var1->type == VarType::FOOD && var1->name == hershey && getVariableValue(VarType::PET, fox) != -1 && (getVariableValue(VarType::PET, fox) + 1) != var1->value)
            {
		//		cout << "Failed 5" << endl;
				return false;
			}

		   if (var1->type == VarType::PET && var1->name == fox && getVariableValue(VarType::FOOD, hershey) != -1 && (getVariableValue(VarType::FOOD, hershey) - 1) != var1->value)
            {
                  //              cout << "Failed 5" << endl;
                                return false;
                        }

			if (var1->type == VarType::COLOR && var1->name == yellow && getVariableValue(VarType::FOOD, kitkat) != -1 && getVariableValue(VarType::FOOD, kitkat) != var1->value)
            {
		//		cout << "Failed 6" << endl;
				return false;
			}


		      if (var1->type == VarType::FOOD && var1->name == kitkat && getVariableValue(VarType::COLOR, yellow) != -1 && getVariableValue(VarType::COLOR, yellow) != var1->value)
            {
                  //              cout << "Failed 6" << endl;
                                return false;
                        }


			if (var1->type == VarType::COLOR && var1->name == blue && var1->value != 1)
            {
		//		cout  << "Failed 7" << endl;
				return false;
			}

			if (var1->type == VarType::FOOD && var1->name == smarties && getVariableValue(VarType::PET, snail) != -1 && getVariableValue(VarType::PET, snail) != var1->value)
            {
		//		cout << "Failed 8" << endl;
				return false;
			}


	      if (var1->type == VarType::PET && var1->name == snail && getVariableValue(VarType::FOOD, smarties) != -1 && getVariableValue(VarType::FOOD, smarties) != var1->value)
            {
                  //              cout << "Failed 8" << endl;
                                return false;
                        }


			if (var1->type == VarType::FOOD && var1->name == snickers && getVariableValue(VarType::DRINK, juice) != -1 && getVariableValue(VarType::DRINK, juice) != var1->value)
            {
		//		cout << "Failed 9" << endl;
				return false;
			}

/*
                        if (var1->type == VarType::DRINK && var1->name == juice && getVariableValue(VarType::FOOD, snickers) != -1 && getVariableValue(VarType::FOOD, snickers) != var1->value)
            {
                                cout << "Failed 9" << endl;
                                return false;
                        }

*/
			if (var1->type == VarType::NATIONALITY && var1->name == ukrain && getVariableValue(VarType::DRINK, tea) != -1 && getVariableValue(VarType::DRINK, tea) != var1->value)
            {
		//		cout << "Failed 10" << endl;
				return false;
			}

			if (var1->type == VarType::NATIONALITY && var1->name == japanese && getVariableValue(VarType::FOOD, milkway) != -1 && getVariableValue(VarType::FOOD, milkway) != var1->value)
            {
		//		cout << "Failed 11" << endl;
				return false;
			}


		   if (var1->type == VarType::FOOD && var1->name == milkway && getVariableValue(VarType::NATIONALITY, japanese) != -1 && getVariableValue(VarType::NATIONALITY, japanese) != var1->value)
            {
                  //              cout << "Failed 11" << endl;
                                return false;
                        }



			if (var1->type == VarType::FOOD && var1->name == kitkat && getVariableValue(VarType::PET, horse) != -1 && ((getVariableValue(VarType::PET, horse) - 1) != var1->value))
            {
		//		cout << "Failed_12" << endl;
				return false;
			}




		     if (var1->type == VarType::PET && var1->name == horse && getVariableValue(VarType::FOOD, kitkat) != -1 && (((getVariableValue(VarType::FOOD, kitkat) + 1) != var1->value )))
            {
                  //              cout << "Failed 12" << endl;
                                return false;
                        }


			if (var1->type == VarType::DRINK && var1->name == coffee && getVariableValue(VarType::COLOR, green) != -1 && getVariableValue(VarType::COLOR, green) != var1->value)
            {
		//		cout << "Failed 13" << endl;
				return false;
			}


		 if (var1->type == VarType::COLOR && var1->name == green && getVariableValue(VarType::DRINK, coffee) != -1 && getVariableValue(VarType::DRINK, coffee) != var1->value)
            		{
                //                cout << "Failed 13" << endl;
                                return false;
                        }



			if (var1->type == VarType::DRINK && var1->name == milk && var1->value != 2)
            {
		//		cout << "Failed 14" << endl;
				return false;
			}

			if (var1->type == VarType::DRINK && var1->name == tea && getVariableValue(VarType::NATIONALITY, ukrain) != -1 && getVariableValue(VarType::NATIONALITY, ukrain) != var1->value)
            {
		//		cout << "Failed 15" << endl;
				return false;
			}
     //   cout << "var " << getVarName(var1) << " value " << var1->value << endl;
        }
    return true;
    }

    void assigningValueToVars(Variables* var, int value)
    {
		var->value = value;
		//unassignedVariables.pop();
		//assignedVariables.push(var);
	}

	void unassigningValueToVars(Variables* var)
	{
		var->value = -1;
		//unassignedVariables.push(var);
		assignedVariables.pop();
	}

    void printSol()
    {
    cout << endl << "Solution:" << endl;
   // cout<<"assigned var size"<<allVariables.size();
    for(int i=0; i<vars; i++)
    {
        Variables* a = allVariables[i];
        //assignedVariables.pop();
        cout << getVarName(a) << "-->" << a->value << endl;
    }
    }

    bool value_exist(map<int, bool> &mymap , int value , Variables *var)
    {

                if(mymap.find(value) == mymap.end())
                {
                    mymap[value] = true;
                    return false;
                }
           return true;
    }

    void unvalue_exist(map<int, bool> &mymap , int value , Variables *var)
    {
                    auto it = mymap.find(value);
                    mymap.erase(it);
    }


    Variables* mrv_heur_house(housesPuzzle* prob)
    {

        stack<Variables*> unass ;
	unass =  unassignedVariables;

	vector<Variables*> allvariablecopy ;
        for(int i=0; i<allVariables.size(); i++)
	{
		Variables* temp = allVariables[i];
		allvariablecopy.push_back(temp);
	}
//	cout<<endl;

        vector<Variables*> unass_v ;
        vector<int> values(26, -1);
        while(!unass.empty())
        {
            unass_v.push_back(unass.top());
            unass.pop();
        }

       stack<Variables*>  tp = unassignedVariables;
  /*      cout<<"Before Before Printing Unassigned elements"<<endl;
           while(!tp.empty())
           {
              cout<<" "<<getVarName(tp.top())<<" "<<(tp.top())->value;
              tp.pop();
            }

*/

        for(int i=0; i<unass_v.size(); i++)
        {
	   // assignedVariables.push(unass_v[i]);
            for(int domain =0 ; domain<5; domain++)
            {
                unass_v[i]->value = domain;
	//	cout<<"Processing"<<getVarName(unass_v[i])<<" Value"<<domain<<endl;
                assignedVariables.push(unass_v[i]);

                if(map_check(unass_v[i]))
		{
			assignedVariables.pop();
			unass_v[i]->value = -1;
		      continue;
		}
	//	cout<<"Hurray"<<endl;

		   Variables *var = unass_v[i];
		   int pos;
           	for(int k=0; k<allVariables.size(); k++)
             	{
                	 if(var->type == allVariables[k]->type && var->name == allVariables[k]->name)
                     		{
					allVariables[k]->value = var->value;
		       			 pos=k;
					 break;
		     		}
             	}

                if(housesConsistent())
                    values[i]++;

                assignedVariables.pop();
                map_uncheck(unass_v[i]);
		allVariables[pos]->value= -1;
		unass_v[i]->value = -1;
            }
	//assignedVariables.pop();

	  //unass_v[i]->value =  -1;
        }



        int mini = INT_MAX, pos =0;
	//cout<<"Printing Values---------------";
        for(int i=0; i<=25; i++)
        {
            if(values[i] == -1)
                values[i] = 26;

            if(mini > values[i])
            {
                mini=values[i];
                pos =i;
            }

        }

       stack<Variables*>  tq = unassignedVariables;


	vector<Variables*> temp;
        for(int i=0; i<pos; i++)
        {
            temp.push_back(unassignedVariables.top());
            (unassignedVariables).pop();
        }

        Variables* ans = (unassignedVariables).top();
        (unassignedVariables).pop();

        for(int j=temp.size()-1; j>=0; j--)
        {
            (unassignedVariables).push(temp[j]);
        }

	stack<Variables*>  t = unassignedVariables;

	for(int i=0; i<allvariablecopy.size(); i++)
	{
		//cout<<allvariablecopy[i]->value<<" ";
		allVariables[i] = allvariablecopy[i];
	}

     return ans;
    }

bool map_check(Variables *var)
{

	 for(int k=0; k<allVariables.size(); k++)
            {
                if(var->type == allVariables[k]->type && var->name == allVariables[k]->name)
                    allVariables[k]->value = var->value;
            }

                if (var->type == VarType::NATIONALITY &&value_exist(nationality, var->value, var))
                return true;
             if (var->type == VarType::FOOD && value_exist(food, var->value, var))
                  return true;

            if (var->type == VarType::DRINK && value_exist(drink, var->value, var))
              return true;

            if (var->type == VarType::COLOR && value_exist(color, var->value, var))
              return true;

            if (var->type == VarType::PET && value_exist(pet, var->value, var))
              return true;


            return false;
}

void map_uncheck(Variables* var)
{

             if (var->type == VarType::NATIONALITY)
                unvalue_exist(nationality, var->value, var);

            if (var->type == VarType::FOOD)
                unvalue_exist(food, var->value, var);

            if (var->type == VarType::DRINK)
                unvalue_exist(drink, var->value, var);

            if (var->type == VarType::COLOR)
                unvalue_exist(color, var->value, var);

            if (var->type == VarType::PET)
                unvalue_exist(pet, var->value, var);
}

    bool housesBackTrack(housesPuzzle* prob, int useMRV)
{
    //cout << "mrv in backtrack is " << useMRV << endl;
        Variables* var;
        //cout<<"Index"<<index<<endl;
       // if(useMRV == 0)
       // {
            //cout << "inside backtrack" << endl;
            if(prob->unassignedVariables.empty())
            {
                //cout<<"I am the culprit";
               // cout<<"size of assigned"<<assignedVariables.size();
                var = NULL;
                return true;
                //cout << "reached end" << endl;
            }
            if(useMRV)
              {
	       // cout<<"MRV value  "<<getVarName(var)<<endl;
		var = mrv_heur_house(prob);

	      }
            else
            	var = prob->unassignedVariables.top();

            //cout << "variable from stack " << getVarName(var) << endl;

            if(!useMRV)
                prob->unassignedVariables.pop();
        //}
       /* else
        {
            var = prob->gettingVarsUsingMRV();
        } */
        vector<int> availValues = prob->gettingAvailValues();
        prob->assignedVariables.push(var);

        for(int i=0; i<availValues.size(); i++)
        {
	  iter++;
           // cout<<"I--->"<<i<<endl;
          //  cout << "Considering value: " << getVarName(availValues[i]) << endl;
           // prob->assigningValueToVars(var, availValues[i]);
            var->value = availValues[i];

           // cout << "var " << getVarName(var) << " value " << var->value << endl;

            if(map_check(var))
		{
		//  cout<<"I passed values  of "<<i<<" in "<<getVarName(var)<<endl;
                  continue;
		}

		//cout<<"Checking for values "<<i<<endl;

	  for(int k=0; k<allVariables.size(); k++)
            {
                if(var->type == allVariables[k]->type && var->name == allVariables[k]->name)
                   {
		//	cout<<"Setting dangerous <<"<<var->value<<" To"<<getVarName(var)<<endl;
			 allVariables[k]->value = var->value;
		   }
            }

            if(prob->housesConsistent())
              {
        //          cout<<"Loop 1 "<<endl;

		  // cout << "var " << getVarName(var) << " value " << var->value << endl;
                  if( housesBackTrack(prob, useMRV))
                    {
          //              cout<<"Loop 2"<<endl;
                    return true;
                    }
              }


            //cout << "hereee" << endl;
           // prob->unassigningValueToVars(var);

            map_uncheck(var);

           // var->value = -1;

        }
        var->value=-1;
        if(var->value == -1)
        {
          //  cout << "Assigning Varibale poped out" << getVarName(var) << " value " << var->value << endl;
                        //cout << "hereee-2" << endl;
            assignedVariables.pop();
         //   cout << "UNAssigning Varibale pushing in" << getVarName(var) << " value " << var->value << endl;
            unassignedVariables.push(var);
            for(int k=0; k<allVariables.size(); k++)
            {
                if(var->type == allVariables[k]->type && var->name == allVariables[k]->name)
                    allVariables[k]->value = var->value;
            }

        }
        return false;
}

};


int main()
{
    int probNum, mrv;
    cout << "Enter 1 for 'Jobs' Puzzle or 2 for 'Houses' Puzzle. " << endl;
    cin >> probNum;
   cout << "Enter MRV " << endl;
    cin >> mrv;
    if(probNum == 1)
    {
        jobsPuzzle* jb1 = new jobsPuzzle();
        jb1->settingProblem();
        bool bt = jb1->jobBackTrack(jb1, mrv);
        if(bt)
        {
            //cout << "Solution" << endl;
            jb1->printSol();
        }
        else
        {
            cout << "No solution." << endl;
        }
    }
    else if(probNum == 2)
    {
        housesPuzzle* hp1 = new housesPuzzle();
        hp1->settingProblem();

        bool ht;
        if(mrv == 0)
            ht = hp1->housesBackTrack(hp1, 1);
        if(mrv == 1)
            ht = hp1->housesBackTrack(hp1, 0);
        if(ht)
        {
           // cout << "Solution" << endl;
            hp1->printSol();
        }
        else
        {
            cout << "No solution" << endl;
        }
    }
    cout<<endl << "Iterations "<<iter<<endl;
    return 0;
}
