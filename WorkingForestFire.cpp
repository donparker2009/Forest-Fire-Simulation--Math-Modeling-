#include<iostream>
#include <random>
#include <cmath>
using namespace std;

const int size = 11;
string Lattice[size][size];
double p = .5;
int n = 0;
int endTime = 60;
int unburned = size * size - 1;
int started = 1;
int fire = 0;
int burned = 0;

uniform_int_distribution<> r_dist(0,RAND_MAX);
mt19937 r_entry{};

// Seed the random number generator
void my_srandom(int s)
{
r_entry.seed(s);
}

// Return a random integer between 0 and RAND_MAX
int my_random()
{
return r_dist(r_entry);
}

string S(int row, int column)
{
	return Lattice[row][column];
}

void checkBurn(int row, int column)
{
	int count = 0;
	
	double rand = (double) my_random()/ RAND_MAX;
	
	//Left
	if ((column > 0) && (S(row,column - 1) == "F") )
	{
		count++;
	}
	//Up
	if ((row > 0) && (S(row - 1,column) == "F") )
	{
		count++;
	}
	//Right
	if ((column < size - 1) && (S(row,column + 1) == "F") )
	{
		count++;
	}
	//Down
	if ((row < size - 1) && (S(row + 1,column) == "F") )
	{
		count++;
	}
	
	if (count > 0)
	{
	
		if ( rand <= (1 - pow ((1 - p),count) ) )
		{
			Lattice[row][column] = "S";
			unburned--;
			started++;
		}
		
	}
}

void updateUnburned()
{
	for (int row = 0; row < size; row++)
	{
		for (int column = 0; column < size; column++)
			{
				if (Lattice[row][column] == "U")
				{
					checkBurn(row,column);
				}
			
			}
	}

}

void updateFire()
{
	for (int row = 0; row < size; row++)
	{
		for (int column = 0; column < size; column++)
			{
				if (S(row,column) == "F")
				{
					Lattice[row][column] = "B";
					fire--;
					burned++;
				}
			}
	}
	
	
}

void updateStarted()
{
		for (int row = 0; row < size; row++)
		{
			for (int column = 0; column < size; column++)
			{
				if (S(row, column) == "S")
				{
					Lattice[row][column] = "F";
					started--;
					fire++;
				}
			}
		}
}

int main()
{
	my_srandom(44);
	
	//Initialize Lattice
	for (int row = 0; row < size; row++)
	{
		for (int column = 0; column <  size; column++)
		{
			Lattice[row][column] = "U";
		}
	}
	
	Lattice[(size)/2][(size)/2] = "S";
	
	
		cout << endl;
		cout << "time " << n << endl;
		cout << "endTime " << endTime << endl;
		cout << "p " << p << endl;
		cout << "unburned " << unburned << endl;
		cout << "started/started " << fire + started << endl;
		cout << "burned " << burned << endl;
	
	for (int row = 0; row < size; row++)
	{
		for (int column = 0; column <  size; column++)
			{
				cout << S(row, column) + " ";
			}
		cout << endl;
	}

	cout << endl;
		
	while (n < endTime && (fire + started > 0))
	{
		
		n++;

		updateStarted();
		updateUnburned();
		updateFire();
		
		cout << endl;
		cout << "time " << n << endl;
		cout << "endTime " << endTime << endl;
		cout << "p " << p << endl;
		cout << "unburned " << unburned << endl;
		cout << "fire/started " << fire + started << endl;
		cout << "burned " << burned << endl;
		
		for (int row = 0; row < size; row++)
		{
			for (int column = 0; column <  size; column++)
				{
					cout << S(row, column) + " ";
				}
			cout << endl;
		}
		

		
	}
	return 0;
}
