#include <fstream>
#include <iostream>
#include <string>

using namespace std;
int main ( int argc, char** argv)
{
	fstream f;
	string l;
	f.open("./files.cpp",ios::in|ios::out);
	if ( f.is_open()) {
		while(f.good()){
			getline(f,l);
			cout << l << endl;
		}
		f << "New line\n" ;	
		f.close();
	}
	else{
		cout << "cant open the file\n";
	}





return 0;
}
