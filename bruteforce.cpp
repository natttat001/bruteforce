#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>
#include <limits>
using namespace std;

typedef struct space
{
	string destination;
	int load = 0;
	int distance[5];
} p;
//this is tuple because im stupid and misread the task. it used to return a bool value along with int
tuple<int, int> loadcost(vector<p>& ship, vector<int>& position) //putting this in recursive function, each will work with a different vector. this will calc the cost for any ship vector permutation
{
	const int costperloadperkm = 25;
	int totalload = ship[position[0]].load; //load at starting position, has to declare here so loadcost calc properly
	int distanceloadcost = ship[position[0]].distance[position[1]]; //Same as above for distance
	int loadcost = totalload * distanceloadcost * costperloadperkm;
	for (int i = 1; i < position.size() - 1; i++)
	{
		totalload += ship[position[i]].load; 	//load at current position
		distanceloadcost = ship[position[i]].distance[position[i + 1]];
		loadcost += totalload * distanceloadcost * costperloadperkm;
	}
	totalload += ship[position.back()].load; //load at end position, has to put it here so i+1 doesnt go out of bound
	return make_tuple(totalload, loadcost);
}

void recur(vector<p>& ship, vector<int>& position, int& totalloadcost, int level)
{
	if (level == ship.size())
	{
		int totalload = 0;
		int totalloadcosttemp = 0;
		bool check = true;
		for (const p& ships : ship)
		{
			cout << ships.destination << ",";

		}
		tie(totalload, totalloadcosttemp) = loadcost(ship, position);
		cout << totalloadcosttemp << endl;
		if (totalloadcosttemp < totalloadcost)
		{
			totalloadcost = totalloadcosttemp;
		}
		cout << endl;
		return;
	}
	else {
		for (int i = level; i < ship.size(); i++)
		{
			swap(ship[position[i]].destination, ship[i].destination);
			swap(position[level], position[i]);
			recur(ship, position, totalloadcost, level + 1);
			swap(ship[position[i]].destination, ship[i].destination);
			swap(position[level], position[i]); //backtrack
		}
	}
}

void makeship(vector<p>& ship)
{
	string planet[5] = { "Alpha  ", "Beta   " , "Gamma  ", "Delta  ", "Epsilon" };
	int planetload[5] = { 20, 40, 70, 10, 30 };
	int distances[5][5] =
	{
		{0, 10, 15, 12, 20},
		{10, 0,	12,	25,	14},
		{15, 12, 0, 16,	28},
		{12, 25, 16, 0, 17},
		{20, 14, 28, 17, 0},
	};
	for (int i = 0; i < 5; i++)
	{
		p temp;
		temp.destination = planet[i];
		cout << temp.destination << "    ";
		temp.load = planetload[i];
		cout << temp.load << "    ";
		for (int ii = 0; ii < 5; ii++)
		{
			temp.distance[ii] = distances[i][ii];
			cout << temp.distance[ii] << "  ";
		}
		ship.push_back(temp);
		cout << endl;
	}
	ship.shrink_to_fit();
}

int main()
{
	vector<p> ship;
	makeship(ship);
	vector<int> location; //store the current location in another vector to point to distance in ship.distance[]
	int loadcost = INT_MAX;
	for (int i = 0; i < 5; i++)
	{
		location.push_back(i);
	}
	recur(ship, location, loadcost, 0);
	cout << loadcost;
}
