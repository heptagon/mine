#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main( int argc, char** argv)
{
	fstream f;
	string line;
	f.open("files.cpp",ios::in|ios::out);
	if ( f.is_open())
	{
		while(f.good())
		{
			getline(f,line);
			cout << line << endl;
		}	
	f.close();
	cout << "done printing file" << endl;
	}else{
		cerr << "cant open file";
	}
	return 0;
}
