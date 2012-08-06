#include <iostream>
#include <string>
using namespace std;


class Cell
{
	public:
		Cell(int rlevel, int dlevel, int type_code, string val);
		~Cell();
		Cell(const Cell& that);
		Cell& operator=(const Cell& rhs);
		friend ostream& operator << (ostream& os, const Cell& c);
	private:
		int rl;
		int dl;
		int t;
		string v;


};

Cell::Cell(int rlevel, int dlevel, int type_code, string val)
	:rl(rlevel),
	 dl(dlevel),
	 t(type_code),
	 v(val)
	{}

Cell::~Cell()
	{}

Cell::Cell(const Cell& that)
	{
	
		this->rl=that.rl;
		this->dl=that.dl;
		this->t =that.t;
		this->v =that.v;
	}

Cell& Cell::operator= (const Cell& rhs)
	{
		if ( this == &rhs)
			return *this;

		this->rl=rhs.rl;
		this->dl=rhs.dl;
		this->t =rhs.t;
		this->v =rhs.v;
		return *this;
	}

ostream& operator<< ( ostream& os, const Cell& c)
	{
		cout << "Hello\n" << c.v << "\nEnd\n";
		return os;
	}

/*
int main(int argc, char** argv)
	{
		Cell *c = new Cell(1,3,1,"abc");
		Cell c2(*c);
		Cell c3=*c;
		cout << *c << c2 << c3 ;
		return 0;
	}
*/

