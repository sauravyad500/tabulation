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
	bool grouped;
	bool included;
	node () { grouped = false; included = false; }
	bool operator ==(node r);
}temp;
vector<node> minterms, t_minterms, pi, final;
int no_minterms, column, temp_n = -1;

bool node::operator ==(node r)
{
	if ( n.size () == r.n.size () )
	{
		for ( int i = 0; i < n.size (); i++ )
		{
			if ( n[i] != r.n[i] )  return false;
		}
	}
	else return false;
	if ( diff.size () == r.diff.size () )
	{
		for ( int i = 0; i < diff.size (); i++ )
		{
			if ( diff[i] != r.diff[i] )  return false;
		}
	}
	else return false;
	if ( group != r.group ) return false;
	return true;
}


template <typename tl>
bool if_notpresent (tl t, vector<tl> pr)
{
	for ( tl f : pr )
	{
		if ( f == t ) return false;
	}

	return true;
}

bool is_aset (vector<int> x, vector<int>y)
{
	int c1 = 0, c2 = 0,count=0;
	for ( int j = 0; j < x.size (); j++ )
	{
		c1 = 0;
		for ( int k = 0; k < y.size (); k++ )
		{
			if ( x[j] == y[k] ) { c1++; break; }
		}
		if ( c1 != 0 )c2++;
	}
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
	int t,groups;
	cout << "Enter the number of minterms";
	cin >> no_minterms;
	for ( int i = 0; i < no_minterms; i++ )
	{
		cin >> t;
		temp.diff.push_back (t);
		temp.group = count (to_binary (t));
		minterms.push_back (temp);
		temp.diff.clear ();
	}

	do
	{
		groups = 0;
		for ( int k = 0; k < minterms.size (); k++ )
		{
			for ( int j = 0; j < minterms.size (); j++ )
			{
				if ( minterms[j] == minterms[k] ) continue;
				if ( minterms[j].group == minterms[k].group + 1 )
				{
					if ( minterms[j].n.size () == 0 || minterms[j].n == minterms[k].n )
					{
						int p = 0;
						for ( int i = 0; i < minterms[j].diff.size (); i++ ) { if ( !is_powerof2 (minterms[j].diff[i] - minterms[k].diff[i]) ) { p = 1; break; } }
						if ( p == 0 )
						{
							node t;
							for ( int i : minterms[k].diff ) { t.diff.push_back (i);/* cout << i << "  ";*/ }
							for ( int i : minterms[j].diff ) { t.diff.push_back (i);/* cout << i << "  ";*/ } //cout << "\t";
							for ( int i = 0; i < minterms[j].diff.size (); i++ )
							{
								t.n.push_back (minterms[j].diff[i] - minterms[k].diff[i]); // cout << minterms[j].diff[i] - minterms[k].diff[i] << "  ";
							}
							for ( int i : minterms[k].n ) t.n.push_back (i);
							sort (t.diff.begin (), t.diff.end ());
							sort (t.n.begin (), t.n.end ());
							auto last = unique (t.n.begin (), t.n.end ());
							t.n.erase (last, t.n.end ());
							t.group = minterms[k].group;
							t_minterms.push_back (t);
							groups++;
							minterms[k].grouped = minterms[j].grouped = true;




						}
					}
				}
			}
			cout << "diff : ";
			for ( int i : minterms[k].diff ) cout << i << "\t"; cout << "n : ";
			for ( int i : minterms[k].n ) cout << i << "\t"; cout << "group : ";
			cout << minterms[k].group;
			if ( !minterms[k].grouped && if_notpresent(minterms[k],pi)) { pi.push_back (minterms[k]); cout << "\tungrouped\n"; } else cout << "\tgrouped\n";
		} cout << "\n\n\n\n";
		minterms.clear ();
		copy (t_minterms.begin (), t_minterms.end (), back_inserter (minterms));
		t_minterms.clear ();

	} while ( groups != 0 );
	//remove duplicates

	cout << "\n\n\n\n\t size" << pi.size () << "\n";
	for ( node temp : pi )
	{
		for ( int i : temp.diff ) cout << i << "\t"; cout << "\t n \t";
		for ( int i : temp.n ) cout << i << "\t"; cout << "\tgroup\t";
		cout << temp.group << "\t";
		cout << "\n";
	}cout << "\n\n\n";

	for ( int a=0;a<pi.size();a++ )
	{
		for ( int i = 0; i < pi[a].diff.size (); i++ )
		{
			int c = 0;
			for ( int k = 0; k < pi.size (); k++ )
			{
				for ( int j = 0; j < pi[k].diff.size (); j++ )
				{
					if ( pi[a] == pi[k] && i == j ) continue;
					if ( pi[k].diff[j] == pi[a].diff[i] ) c++;

				}
			}
			if ( c == 0 ){ pi[a].included = true; break; }
		}
	}

	cout << "\n\n\n\n\t size" << pi.size () << "\n";
	for ( node temp : pi )
	{
		if ( temp.included )
		{
			for ( int i : temp.diff ) cout << i << "\t"; cout << "\t n \t";
			for ( int i : temp.n ) cout << i << "\t"; cout << "\tgroup\t";
			cout << temp.group << "\t";
			cout << "\n";
		}
	}cout << "\n\n\n";

	vector<int> h;
	for ( int i = 0; i < pi.size (); i++ )
	{
		if (! pi[i].included )
		{
			for ( int j = 0; j < pi[i].diff.size (); j++ )
			{
				int c= 0;
				for ( node temp : pi )
				{
					if ( temp.included )
					{
						for ( int g : temp.diff ) { if ( pi[i].diff[j] == g ) c++; }
					}
				}
				if ( c == 0 && if_notpresent (pi[i].diff[j], h) ) h.push_back (pi[i].diff[j]);
				
			}
		}
	}
	cout << "\n\n\n";
	int no_notincluded;
	for ( node temp : pi ) { if ( !temp.included )no_notincluded++; }

	for ( int i : h ) cout << "\t" << i;

	_sleep (150000);
	return 0;
}

