#include <iostream>
#include <string>
#include <stack>

using namespace std;

class str_distances
{
	public:
		str_distances(string s1, string s2):s(s1),t(s2)
		{
			int r=rr();
			int c=cc();
			a=new int*[r];
			for(int ii=0;ii<r;++ii)
			{
				a[ii]=new int[c];
			}
	
			for(int ii=0;ii<r;++ii)
				for(int jj=0;jj<c;++jj)
					a[ii][jj]=0;
		};

		~str_distances()
		{
		};
		
		str_distances* initialize_array();
		str_distances* output();
		
		str_distances* min_edit_distance();
		void print_one_min_edit_string_set();
		void print_all();


		str_distances* substring_k(int k);	
		str_distances* lcs();				
		str_distances* LCS();				
		str_distances* allLCS();				

	private:
		int** a;
		string s;
		string t;	
		int rr() { return s.length()+1; };
		int cc() { return t.length()+1; };


		int min_of_3(int a, int b, int c);
		void print_all_sequences(int i,int j,stack<char> vse, stack<char> vte, int tabs);
};



//http://www-igm.univ-mlv.fr/~lecroq/seqcomp/node1.html#SECTION001
// source goes down s --> i index : so source maps to rows
// target goes across t --> j index ; so target maps to columns
// choosing source as row index and target as column index is just a convention. CAn flip it too but make sure your pointers are again properly coordinated

// we travese row major column minor: meaning all cols in a row are first travesed
// all operations are wrt to target
// substitution cost = 1. Substituting a character in target by a character from source. diagonal
// deletion cost =1 .Deleting a character from target in the final sequence. Downwards. Row increments [ source increments ] but column doesnt [ target doesnt]
// insertion cost=1. Insering a character from target in the final sequence. Rightways. Row doesnt change [ source stays ] but column does [ target changes ]
// Algorithm:
// create an array of size r+1,c+1. r= len(source). c= len(target)
// initialize first row and first column with index values. [ see code below ]
// calculate cost of a[i][j] from the element diagonally upwards, just left or just top of [i][j]
// choose the minimum cost and insert in the array.
// repeat above steps for all cells in the array. You now have a cost array.
// the rightmost lowermost element has the answer. 
// horizonal and vertical moves add cost. Diagonal moves are free. The idea is to find a path from topleft to bottomright with most diagonal moves.

str_distances* str_distances::min_edit_distance()
{
	cout << "in min edit distance \n" ;
	int r=rr();
	int c=cc();

	//initialize the array
	for(int ii=0;ii<r;++ii)
		a[ii][0]=ii;
	for(int jj=0;jj<c;++jj)
		a[0][jj]=jj;

	// find min cost to convert s to t
	int similar_subs_cost=0;
	int deletion_cost=1;
	int insertion_cost=1;
	int nonsimilar_subs_cost=1;

	for(int ii=1;ii<r;++ii)
		for(int jj=1;jj<c;++jj)
			a[ii][jj]=min_of_3(	a[ii-1][jj]+deletion_cost,
						a[ii][jj-1]+insertion_cost,
						s[ii-1]==t[jj-1] ? a[ii-1][jj-1]+similar_subs_cost : a[ii-1][jj-1]+nonsimilar_subs_cost); 


	return this;
			
}

int str_distances::min_of_3(int a, int b, int c)
{
	int min =a;
	if ( b < min )
		min=b;
	if ( c < min)
		min=c;
	return min;
}

// work backwards in the array
// multiple answers possible. We just pick up convention for path to follow.
// start from the answer cell.
// prefer to move diagonally if possible as diagonal moves are free
// other moves are upwards [ deletion of target ] OR leftwards [ insertion of target  OR iow deletion of source ]
// repeat move until reach top border or bottom border of the array
// then work stepwise back to the origin [ topleft ]
// beware of indexes and off-by-one errors. This is hairy. Array size is [len(s)+1][len(t)+1]. Last array index is len[s], len[t].
// Last Elements in source and target strings can be accessed by len(s)-1, len(t)-1. There is a difference of 1 between last array index
// and last element index in source [ target too ]


void str_distances::print_one_min_edit_string_set()
{
	int r=rr();
	int c=cc();
	int delcost=1;
	stack<char> vse;
	stack<char> vte;
	int i=r-1;
	int j=c-1;
	while ( i >0 && j > 0 )
	{
		int sub_cost= s[i-1] == t[j-1] ? 0 : 1;
		if ( a[i-1][j-1] + sub_cost == a[i][j])
		{
			vse.push(s[i-1]); i--;
			vte.push(t[j-1]); j--;	
		}
		else if ( a[i-1][j] + delcost == a[i][j])
		{
			vse.push(s[i-1]);i--;
			vte.push('-'); // j--;
		}else
		{
			vse.push('-');// i--;
			vte.push(t[j-1]);j--;
		}
	}
	
	while(i > 0 )
	{
		vse.push(s[i-1]);i--;
		vte.push('-'); // j--;
	}	
	while ( j > 0 )
	{
		vse.push('-');// i--;
		vte.push(t[j-1]);j--;
	}
	
	cout << "printing one sequence\nvse:\t";
	while ( !vse.empty())
	{
		cout << vse.top() ;
		vse.pop();
	}
	cout << "\nvte:\t";
	while( !vte.empty())
	{
		cout << vte.top() ;
		vte.pop();
	}
	cout << "\n";
}


void str_distances::print_all()
{
	cout << "printing all sequences\n";
	stack<char> vse;
	stack<char> vte;
	print_all_sequences( rr() -1, cc() -1,vse,vte,0);
}


// same as print one sequence .but we recurse at every possible branch instead of picking one path and never backtracking.
// note for implementation: stacks are passed copy by value. :( so that pushes and pops in the recursion change dont effect backtracking.
// dont forget to pop the stacks while within the same function call instance but between different conditionals
 
void  str_distances::print_all_sequences(int i,int j,stack<char> vse, stack<char> vte, int tabs)
{
	for( int ii=0;ii<tabs;++ii)
		cout << "  ";
	
	cout << "ni:nj:nv:ntabs\t" << i << ":" << j << ":" << a[i][j] << ":" << tabs << "\n";
	int delcost=1;
	int inscost=1;

	if(i>0)
	{
		if ( j>0)
		{
			int sub_cost= s[i-1] == t[j-1] ? 0 : 1;
			if ( a[i][j]==a[i-1][j-1]+sub_cost)
			{
				vse.push(s[i-1]);
				vte.push(t[j-1]);
				for( int ii=0;ii<tabs;++ii)
				cout << "  ";
				cout << "oi:oj:ov:otabs\t" << i << ":" << j << ":" << a[i][j] << ":" << tabs << "S-->\n";
				print_all_sequences(i-1,j-1,vse,vte,tabs+1);
				vse.pop();
				vte.pop();
			}
			if(  a[i][j] ==a[i-1][j] +delcost)
			{
				vse.push(s[i-1]);
				vte.push('-');
				for( int ii=0;ii<tabs;++ii)
				cout << "  ";
				cout << "oi:oj:ov:otabs\t" << i << ":" << j << ":" << a[i][j] << ":" << tabs << "D-->\n";
				print_all_sequences(i-1,j,vse,vte,tabs+1);
				vse.pop();
				vte.pop();
			}
			if ( a[i][j] == a[i][j-1]+inscost )
			{
				vse.push('-');
				vte.push(t[j-1]);
				for( int ii=0;ii<tabs;++ii)
				cout << "  ";
				cout << "oi:oj:ov:otabs\t" << i << ":" << j << ":" << a[i][j] << ":" << tabs << "I-->\n";
				print_all_sequences(i,j-1,vse,vte,tabs+1);
				vse.pop();
				vte.pop();
			}
			
		}else{
			vse.push(s[i-1]);
			vte.push('-');
			for( int ii=0;ii<tabs;++ii)
			cout << "  ";
			cout << "oi:oj:ov:otabs\t" << i << ":" << j << ":" << a[i][j] << ":" << tabs << "Y-->\n";
			print_all_sequences(i-1,0,vse,vte,tabs+1);
			vse.pop();
			vte.pop();
		}
	}else{
		if ( j > 0 )
		{
			vse.push('-');
			vte.push(t[j-1]);
			for( int ii=0;ii<tabs;++ii)
			cout << "  ";
			cout << "oi:oj:ov:otabs\t" << i << ":" << j << ":" << a[i][j] << ":" << tabs << "X-->\n";
			print_all_sequences(0,j-1,vse,vte,tabs+1);
			vse.pop();
			vte.pop();
		}else{
			cout << "*******\n";
			cout << "PRINT\n";
			cout << "vse:\t";
			while ( !vse.empty())
			{
				cout << vse.top() ;
				vse.pop();
			}
			cout << "\n";
			cout << "vte:\t";
			while( !vte.empty())
			{
				cout << vte.top() ;
				vte.pop();
			}
			cout << "\n*******\n";
			cout << "\n\n";
		}
	}
}

str_distances* str_distances::substring_k(int k)
{
	int r=rr();
	int c=cc();

	for(int jj=0;jj<c;++jj)
		a[0][jj]=0;
	for(int ii=0;ii<r;++ii)
		a[ii][0]=ii;

	for(int ii=1;ii<r;++ii)
	{
		for(int jj=1; jj<c;++jj)
		{
			int p=0;
			if( s[ii-1]!=t[jj-1])
				p=1;
			a[ii][jj]=min_of_3(a[ii-1][jj-1]+p,
					   a[ii-1][jj]+1,
					   a[ii][jj-1]+1);
		}		
	}
	for(int jj=0;jj<c;++jj)
	{
		if(a[r-1][jj] <= k )
			cout << "This is the endpoint of another substring in target with a min edit distance <= " << k << " wrt x : " << jj << endl;
	}
	return this;	
}

str_distances* str_distances::lcs()
{
	int r=rr();
	int c=cc();

	for(int ii=0;ii<r;++ii)
		a[ii][0]=0;
	for(int jj=0;jj<c;++jj)
		a[0][jj]=0;
	
	int delcost=0;
	int inscost=0;
	int subcost=0;
	for(int ii=1;ii<r;++ii)
	{
		for(int jj=1;jj<c;++jj)
		{
			if(s[ii-1] == t[jj-1])
				a[ii][jj]=a[ii-1][jj-1]+1;
			else
				a[ii][jj]=max( a[ii-1][jj] , a[ii][jj-1] );
		}
	}
	cout << "lcs is " << a[r-1][c-1];

	return this;
}

str_distances* str_distances::LCS()
{
	int r=rr();
	int c=cc();
	int ii=r-1;
	int jj=c-1;
	stack<char> s_lcs;
	while(ii>0 && jj > 0)
	{
		if (( a[ii][jj] == a[ii-1][jj-1]+1) && ( s[ii-1] == t[jj-1]))
		{
			s_lcs.push(s[ii-1]);
			ii--;jj--;
		}
		else if ( a[ii-1][jj] > a[ii][jj-1])
		{
			ii--;
		}else{
			jj--;
		}
	}
	cout << "printing one Lcs\n";
	while(!s_lcs.empty())
	{
		cout << s_lcs.top() ;
		s_lcs.pop();
	}
	cout << "\n";
	return this;
}

str_distances* str_distances::allLCS()
{
	int r=rr();
	int c=cc();
	int lcsv=a[r-1][c-1];
	int i=r-1;
	int j=c-1;
	for(int i=r-1;i>0;--i)
	{
		for( int j=c-1;j>0;--j)
		{
			if(a[i][j] != lcsv)
				continue;

			int ii=i;
			int jj=j;
			stack<char> s_lcs;
			while(ii>0 && jj > 0)
			{
				if (( a[ii][jj] == a[ii-1][jj-1]+1) && ( s[ii-1] == t[jj-1]))
				{
					s_lcs.push(s[ii-1]);
					ii--;jj--;
				}
				else if ( a[ii-1][jj] > a[ii][jj-1])
				{
					ii--;
				}else{
					jj--;
				}
			}
			cout << "printing a Lcs\n";
			while(!s_lcs.empty())
			{
				cout << s_lcs.top() ;
				s_lcs.pop();
			}
			cout << "\n";
		}
	}
	return this;
}

str_distances* str_distances::initialize_array()
{
	for(int ii=0;ii<rr();++ii)
		for(int jj=0;jj<cc(); ++jj)
			a[ii][jj]=0;

	return this;
};

str_distances* str_distances::output()
{
	int r=rr();
	int c=cc();

        //cout << "\f";
        cout<<  "array is ["<<r<<"]["<<c<<"]\n";

        cout << "    ";
        cout << "     ";
	cout << "[-]  ";	
        for ( int jj=0;jj <c-1; ++jj)
        {
                if(jj>=10)
                        cout << "["<< t[jj] << "]  " ;
                else

                        cout << "["<< t[jj] << "]  " ;
        }
        cout << "\n";

        cout << "     ";
        cout << "    ";
        for ( int jj=0;jj <c; ++jj)
        {
                if(jj>=10)
                        cout << "["<< jj << "] " ;
                else

                        cout << "["<< jj << "]  " ;
        }
        cout << "\n";


        for (int ii=0;ii<r;++ii)
        {
                if ( ii == 0 )
                        cout << "[-]  " ;
		else if( ii >= 10)
                        cout << "[" << s[ii-1] << "] " ;
                else
                        cout << "[" << s[ii-1] << "]  " ;

                if( ii >= 10)
                        cout << "[" << ii << "]  " ;
                else
                        cout << "[" << ii << "]  " ;

                for (int jj =0; jj<c;++jj)
                {
                        if ( jj == 10)
                        {
                                cout << " ";
                        }

                        if ( a[ii][jj] >=10)
                                cout << "\b" << a[ii][jj] << "    ";
                        else
                                cout << a[ii][jj] << "    ";

                }
                cout << endl;
        }


	return this;
}





int main(int argc, char** argv)
{
	//string s="GAMBO";
	//string t="GUMBOL";
	//string s="abcdef";
	//string t="defabc";
	string s="YWCQPGK";
	string t="LAWYQQKPGKA";
	str_distances sd(s,t);

	sd.initialize_array()->output()->min_edit_distance()->output();
	sd.print_one_min_edit_string_set();
	sd.print_all();	

	sd.initialize_array()->output()->substring_k(2)->output();
	sd.initialize_array()->output()->lcs()->output()->LCS()->allLCS();
		
	return 0;
}












