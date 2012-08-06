#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cstring>


//http://www-igm.univ-mlv.fr/~lecroq/seqcomp/index.html

using namespace std;
int lcs(char* a, char* b);

int print_local_similar(char* s, char* t);
int min_of_3(int a, int b, int c);
int min_edit_distance(char* a, char* b);
int** get_2d_arr(int r, int c);
void printarr(int** a, int r, int c);
int max_of_4(int a, int b, int c, int d);

int main(int argc, char** argv)
{


  char s[]="GUMBO";
  char t[]="GAMBOL";
  int d = min_edit_distance(s,t);
  cout << "min edit distance d is " << d << endl;
/*
  int lcs_len=lcs(s,t);
  cout << "lcs length is " << lcs_len << endl;
  int ret = print_local_similar(s,t);
*/

}


//http://www.merriampark.com/ld.htm

int min_edit_distance(char* s, char* t)
{

	int ls=strlen(s);
	int lt=strlen(t);
	int cost=0;
	// target length = num of rows but does it matter?
	int** marr = get_2d_arr(lt+1,ls+1);
	printarr(marr,lt+1,ls+1);
	
	// initialize	0th row and col
	for(int ii=0;ii<lt+1;++ii)
	{
		marr[ii][0]=ii;
	}

	for ( int jj=0;jj<ls+1;++jj)
	{
		marr[0][jj] = jj;
	}

	for(int jj=1;jj<ls+1;++jj)
	{	
		for(int ii=1;ii<lt+1;++ii)
		{
			if(s[jj-1] == t[ii-1])
			{
				cost=0;
			}else
			{
				cost=1;
			}
			marr[ii][jj] = min_of_3(marr[ii][jj-1]+1,marr[ii-1][jj]+1,marr[ii-1][jj-1]+cost);	
			//printarr(marr,lt+1,ls+1);
			//cout <<  "updated marr["<<ii<<"]["<<jj<<"]\n";
			//sleep(1);
		}
		
	}

			printarr(marr,lt+1,ls+1);
	// printing one aligment
	{
		int subcost=1;
		int delcost=1;
		int inscost=1;
		char* sa= new char[ls+lt+1];
		char* ta= new char[ls+lt+1];
		for ( int ii=0;ii<ls+lt;++ii)
		{
			sa[ii]='~';
			ta[ii]='~';
		}
		sa[ls+lt+1]='\0';
		ta[ls+lt+1]='\0';

		int j=ls;
		int i=lt;
		int ii=0;
		while( i > 0 && j > 0)
		{
			if ( marr[i][j] == marr[i-1][j-1])
			{
				sa[ii]=s[j-1];
				ta[ii]=t[i-1];
				i--;
				j--;
			}
			else if( marr[i][j]  == marr[i-1][j] + delcost)
			{
				sa[ii]=s[j-1];
				ta[ii]='-';
				j--;
			}else
			{
				sa[ii]='-';
				ta[ii]=t[i-1];
				i--;
			}
			ii++;
		}
		while( j > 0)
		{
			sa[ii]=s[j-1];
			ta[ii]='-';
			j--;
			ii++;
		}
		while( i > 0)
		{
			sa[ii]='-';
			ta[ii]=t[i-1];
			i--;
			ii++;
		}

		cout << "sa" << sa << "\n";
		cout << "ta" << ta << "\n";		

	}


	return marr[lt][ls];
}


int lcs(char* s, char* t)
{


	int ls=strlen(s);
	int lt=strlen(t);
	int cost=0;
	// target length = num of rows but does it matter?
	int** marr = get_2d_arr(lt+1,ls+1);
	printarr(marr,lt+1,ls+1);


	// initialize	0th row and col
	for(int ii=0;ii<lt+1;++ii)
	{
		marr[ii][0]=0;
	}

	for ( int jj=0;jj<ls+1;++jj)
	{
		marr[0][jj] = 0;
	}

	for(int jj=1;jj<ls+1;++jj)
	{
		for(int ii=1;ii<lt+1;++ii)
		{
			if(s[jj-1] == t[ii-1])
			{
				marr[ii][jj]=marr[ii-1][jj-1]+1;
			}else{
				marr[ii][jj]=max(marr[ii-1][jj],marr[ii][jj-1]);
			}
		}
	}
	printarr(marr,lt+1,ls+1);
	return marr[lt][ls];

}
//http://www-igm.univ-mlv.fr/~lecroq/seqcomp/node2.html
int print_local_similar(char* s, char* t)
{
	int ls=strlen(s);
	int lt=strlen(t);
	// target length = num of rows but does it matter?
	int** marr = get_2d_arr(lt+1,ls+1);
	printarr(marr,lt+1,ls+1);


	// initialize	0th row and col
	for(int ii=0;ii<lt+1;++ii)
	{
		marr[ii][0]=0;
	}

	for ( int jj=0;jj<ls+1;++jj)
	{
		marr[0][jj] = 0;
	}
	int subcost=-3;
	int delcost=-1;
	int inscost=-1;
	int realsubcost=subcost;	
	int maxval=0;
	int maxi=0;
	int maxj=0;
	
	for(int jj=1;jj<ls+1;++jj)
	{
		for(int ii=1;ii<lt+1;++ii)
		{
			if(s[jj-1] == t[ii-1])
			{
				realsubcost=1;
			}else
			{
				realsubcost=subcost;
			}
			marr[ii][jj]=max_of_4(0,marr[ii-1][jj-1]+realsubcost,marr[ii-1][jj]+delcost,marr[ii][jj-1]+inscost);
			if(marr[ii][jj] > maxval)
			{
				maxval=marr[ii][jj];
				maxi=ii;
				maxj=jj;
			}
		}
	}
	printarr(marr,lt+1,ls+1);
	cout << "max optimal sequence length is " << maxval << "ending at ["<< maxi << "][" << maxj << "]\n";
	return maxval;

}

int max_of_4(int a, int b, int c, int d)
{
	int max1= a > b ? a : b;
	int max2= c > d ? c : d;
	int maxval = max1 > max2 ? max1 : max2;
	return maxval;
}

int min_of_3(int a, int b, int c)
{

	int min = a < b ? a : b;
	min = c < min ? c : min;
	return min;
}

int**  get_2d_arr(int r, int c)
{

	int** marr = new int*[r];
	for (int ii=0;ii<r;++ii)
	{
		marr[ii]=new int[c];
	}
	

	for (int ii=0;ii<r;++ii)
	{
		for (int jj =0; jj<c;++jj)
		{
			marr[ii][jj] = 0;
		}
	}
	return marr;
}

void printarr(int** marr,int r, int c)
{
	cout << "\f";
	cout<<  "array is ["<<r<<"]["<<c<<"]\n";
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
		if( ii >= 10)
			cout << "[" << ii << "] " ;
		else
			cout << "[" << ii << "]  " ;
			
		for (int jj =0; jj<c;++jj)
		{
			if ( jj == 10)
			{
				cout << " ";
			}

			if ( marr[ii][jj] >=10)
				cout << "\b" << marr[ii][jj] << "    ";
			else
				cout << marr[ii][jj] << "    ";

		}
		cout << endl;
	}
}

