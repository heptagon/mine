#include <iostream>
#include <string>
using namespace std;

class HowEasy
{
	public:
	HowEasy(){cc=0;};
	~HowEasy() {};
	int pointVal(string s)
	{
		int lw=0;
		int wc=0;
		while( cc < s.length())
		{
			string t=scan_token(s);
			if 	( is_word(t))
			{
				int lcw=wl(t);
				if ( lcw > 0)
				{
					lw+=lcw;
					wc++;
				}
			}else{
				cc = reach_begin_of_next_token(s);
				if (cc >= s.length() )
				{
					break;
				}

			}
		}				
		if ( !wc) return 0;
		int al=lw/wc;
		if ( al == 3)
			return 250;
		if ( al ==4 || al == 5)
			return 500;
		if ( al >= 6 )
			return 1000;
		else 
			return 0;
	} //method
	
	protected:
	string scan_token(string s)
	{
		//cc has been set to begin of next token
		cc=reach_begin_of_next_token(s);
		string t=string("");
		while ( cc < s.length())
		{
			if ( s[cc] != ' ')
			{
				t.push_back(s[cc]);
			}else{
				break;
			}
			cc++;
		}
		//t.push_back('\0');
		return t;
	}
	
	int reach_begin_of_next_token(string s)
	{
			if ( cc ==0 && s[cc] != ' ')
				return cc;
				
			while( cc < s.length() && s[cc]  == ' ')
				cc++;
				
			return cc;
	}
	
	int wl(string s)
	{
		if(s.length() == 0 )
			return 0;
		if ( s[s.length()-1] == '.')
			return s.length() -1;
			
		return s.length();
	}
	
	bool is_word(string t)
	{
		for(int ii=0;ii<t.length();++ii)
		{
			if(t[ii] >'0' && t[ii] <'9')
				return false;
			
			if( t[ii] =='.' && ii < t.length()-1)
				return false;	
		}
		return true;
	}
	
	private:
		int cc; // current char posn
} ;// class

int main( int argc, char** argv)
{
	char s[50];
	cin.getline(s,50);
	HowEasy he;
	cout << " avg length is " << he.pointVal(s) << "\n";
}



	

