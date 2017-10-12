#include"stdafx.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>
using namespace std;

int to_binary (int decimal)
{
	int n = decimal, rem, a = 0, i = 0;
	while ( decimal != 0 )
	{
		rem = decimal % 2;
		decimal /= 2;
		a = a + pow (10, i)*rem;
		i++;
	}
	return a;
}

bool is_powerof2 (int x)
{
	float m = log (x) / log (2);
	if ( floor (m) == m ) return true;
	return false;
}

int count (int decimal)
{
	int  a = 0;
	while ( decimal != 0 )
	{
		if ( decimal % 10 == 1 ) a++;
		decimal /= 10;
	}
	return a;
}

class node
{
	public:
	vector<int> n;
	vector<int> diff;
	int group;
	bool included;
	node () { included = false; }
	bool operator ==(node r);
}temp;
vector<node> minterms, t_minterms, pi;
int no_minterms, column, temp_n = -1;

bool node::operator ==(node r)
{
	if (n.size() == r.n.size() )
	{
		for ( int i = 0; i < n.size(); i++ )
		{
			if ( n[i] != r.n[i] )  return false;
		}
	}
	if ( diff.size() == r.diff.size() )
	{
		for ( int i = 0; i < diff.size(); i++ )
		{
			if ( diff[i] != r.diff[i] )  return false;
		}
	}
	if ( group != r.group ) return false;
	return true;
}

bool operator ==(vector<int>x, vector<int>y)
{
	if(x.size()==y.size() )
	{
		for ( int i = 0; i < x.size(); i++ )
		{
			if ( x[i] != y[i] ) return false;
		}
		return true;
	}
	else return false;
}

bool compare (int x, int y)
{
	int rem1, rem2, count = 0;
	if ( x == y ) return false;
	while ( x != 0 || y != 0 )
	{
		rem1 = x % 10;
		rem2 = y % 10;
		x = x / 10, y = y / 10;
		if ( rem1 != rem2 ) count++;
		if ( count == 2 ) return false;
	}
	return true;
}


int main ()
{
	int t;
	cout << "Enter the number of minterms";
	cin >> no_minterms;
	for ( int i = 0; i < no_minterms; i++ )
	{
		cin >> t;
		temp.diff.push_back (t);
		temp.group = count (to_binary (t));
		minterms.push_back (temp);
		temp.diff.clear ();
		//delete(&temp);
	}
	
	for ( node temp : minterms )
	{
		for ( node r : minterms )
		{
			if ( r == temp ) continue;
			if ( r.group == temp.group + 1 )
			{
				if ( r.n.size()==0 || r.n==temp.n)
				{
					int k = 0;
					for ( int i = 0; i < r.diff.size(); i++ ) { if ( !is_powerof2 (r.diff[i] - temp.diff[i]) ) { k = 1; break; } }
					if ( k == 0 )
					{
						node t;
						for ( int i : temp.diff ) { t.diff.push_back (i); cout << i<<"  "; }
						for ( int i : r.diff ) { t.diff.push_back (i); cout << i << "  "; } cout << "\t";
						for ( int i = 0; i < r.diff.size(); i++ )
						{
							t.n.push_back (r.diff[i] - temp.diff[i]);  cout << r.diff[i] - temp.diff[i] << "  ";
						}
						sort (t.diff.begin (), t.diff.end ());
						sort (t.n.begin (), t.n.end ());
						t.group = temp.group;
						t_minterms.push_back (t);
						r.included = temp.included = true;
						cout << "\t" << t.group << "\n";



					}
				}
			}
		}
		if ( temp.included == false ) pi.push_back (temp);
	}

	
	
	_sleep (50000);
	return 0;
}

