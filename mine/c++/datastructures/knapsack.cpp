#include <iostream>
#include <string>
using namespace std;

void f(int,string);
int main(int argc, char** argv)
{
	int n=0;
	cin >> n;
	string s="";

	f(n,s);

}	

void f(int n,string s)
{
	if ( n <0)
	{
	//	cout << s  << " is not a valid combination\n";
		return;
	}
	if ( n == 0)
	{
		cout <<s <<  " is a Valid combination\n";
		return;
	}
	f(n-6,s+"6,");
	f(n-2,s+"2,");
	f(n-1,s+"1,");
}

