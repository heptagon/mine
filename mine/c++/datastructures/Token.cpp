#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>
#include <cstdlib>

using namespace std;

class Token
{

	public:
		Token(string s): t(s) {}

		~Token() {};
		Token(const Token& that)
		{
			this->t=that.t;
		}

		Token& operator=(const Token& rhs)
		{
			if(this == &rhs)
				return *this;
			this->t=rhs.t;
			return *this;
		}

		friend const ostream& operator << (ostream& os,const Token& t);

		bool is_opr()
		{
			const char* c = t.c_str();
			return ( *c== '+' || *c == '-' || *c == '*' || *c == '/') ;
		}

		bool is_lparen()
		{
			return t.size() ==1 && *(to_char_arr()) == '(' ;
		}

		bool is_rparen()
		{
			return t.size() ==1 && *(to_char_arr()) == ')' ;
		}

		bool is_paren()
		{
			return is_lparen() || is_rparen() ;
		}

		bool is_number()
		{
			bool ret=true;
			const char* c = to_char_arr();
			ret =  ret &&  (*c == '-' || Token::is_digit(*c));
		
			bool dec_already=false;	
			while(++c && *c && ret )
			{
				ret = ret && ( Token::is_digit(*c) || Token::is_decimal(*c) );
				if ( *c == '.')
				{
					ret = ret && !dec_already;
					dec_already=true;
				}
			}

			ret = ret && (!(*(--c) == '-' || *(--c) == '.' )); // last digit shouldnt be these two chars
			//MAX /MIN check but we dont yet know the type of number
			return ret;
		}
	
		bool is_operand()
		{
			return is_number();
		}
	
		const char* to_char_arr()
		{
			return t.c_str();
		}


		bool precedes(const Token& other)
		{
			const char c1=this->to_char_arr()[0];
			const char c2=this->to_char_arr()[0];
		
			if ( Token::is_operator(c1) && Token::is_operator(c2))	
			{
				map<char,int> order;
				order['+']=1;
				order['-']=2;
				order['*']=3;
				order['/']=4;
			        map<char,int>::iterator it_o1=order.find(c1);
			        map<char,int>::iterator it_o2=order.find(c2);
			        return ( it_o1->second > it_o2->second );

			}else{
				//throw
			}
			
		}
				

		static bool is_digit(const char& c)
		{
				return  ( (( c - '0' ) >= 0) && (( c-'0' ) <= 9));	
		}


		static bool is_decimal(const char& c)
		{
			return c == '.';
		}

		static bool is_operator(const char& c)
		{

			return ( c== '+' || c == '-' || c == '*' || c == '/') ;
		}

		static bool is_paren(const char& c)
		{
			return  c == '(' || c == ')';
		}
	protected:

		string t;

};

const ostream& operator <<(ostream& os, Token& t)
{
	os << t.to_char_arr();
	return os;
}


class ItoR
{
	public:
		ItoR(string s):i(s) 
		{
			vt = new vector<Token*>;
		}
		~ItoR() {}
		// what should be copy ctr and = operator behavior here
		// should i expose all private members through methods so 
		// as  to be copied from "that" 
		//ItoR(const ItoR& that);
		//const ItoR& operator=(const ItoR& rhs);

		const vector<Token*>& operator() ()
		{
			const vector<Token*>& tokens=tokenize();
			for(int ii=0;ii< tokens.size();ii++)
			{
				Token *t = tokens[ii];
				if ( t->is_operand())
				{
					out(t);
				}
				else if ( t->is_opr())
				{
					while( !operators.empty() && !operators.top()->is_paren() && t->precedes(*(operators.top())))
					{
						out(operators.top());
						operators.pop();
					}
					operators.push(t);
				}else if ( t->is_rparen())
				{
					while( !operators.empty() && (!(operators.top()->is_lparen())))
					{
						out(operators.top());
						operators.pop();
					}
					operators.pop(); // pop the lparen too
				}else  // if ( t.is_lparen() || operators.empty() || !t.precedes(operators.top()) )
				{
					operators.push(t);
				}
			}
			while(!operators.empty())
			{
				out(operators.top());
				operators.pop();
			}
			return *vt;	
		}

		

		
	protected:
	
		const vector<Token*>& tokenize()
		{
			vector<Token*>  *v = new vector<Token*>;
			const char* ic = i.c_str();
			int s=0;
			int e=0;
			bool num=true;
			string st;
			while(*ic)
			{
				while((*ic && Token::is_digit(*ic) || Token::is_decimal(*ic)))
				{
					e++;ic++;
				}
				st=i.substr(s,e-s);
				if(st.size())
				{
					Token* tp = new Token(st);
					v->push_back(tp);
				}
				
				s=e;
				if(*ic && (Token::is_paren(*ic) || Token::is_operator(*ic)))
				{
					e++;ic++;
					st=i.substr(s,e-s);
					Token* tp = new Token(st);
					v->push_back(tp);
					s=e;
				}
			}
			return *v;
		}

		void out(Token* t)
		{
			vt->push_back(t);
		}
			

		string i;
		vector<Token*>* vt;
		stack<Token*> operators;
};

	
class RPNEval
{
	public:
	double operator() (const vector<Token*>& v)
	{
		stack<double> s;
		vector<Token*>::const_iterator vit = v.begin();
		while(vit != v.end())
		{
			Token* t = *vit;
			if (t->is_opr())
			{	
				double d1=s.top(); s.pop();
				double d2=s.top(); s.pop();

				const char opr = t->to_char_arr()[0];
				switch(opr)
				{
					case '+':
						s.push(d2+d1);
						break;
					case '-':
						s.push(d2-d1);
						break;
					case '*':
						s.push(d2*d1);
						break;
					case '/':
						if ( d1 == 0)
							throw;
						else
							s.push(d2/d1);
						break;
					default:
						throw;
				}			

			}else{
				s.push(atof(t->to_char_arr()));
			}
			vit++;
		}
		return s.top();
	
	}

};



int main(int argc, char** argv)
{
	cout << "enter an expression \n";
	string s ;
	cin >> s;
	ItoR itor(s);
	const vector<Token*>& vt = itor();
	vector<Token*>::const_iterator vit = vt.begin();
	while(vit != vt.end())
	{
		Token* t = *vit;
		cout << *t;
		vit++;
	}
	cout << "\n";

	RPNEval r;
	cout << r(vt) << endl;


	return 0;
}

