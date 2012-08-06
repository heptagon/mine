#include <iostream>
using namespace std;

// decl needed for friend declarations
template <typename V> class Cell;
template <typename V> ostream& operator<< ( ostream& os, const Cell<V>& c);




template <typename V>
class Cell 
{
	public:
	Cell(int rlevel, int dlevel, int type, V val);
	~Cell();
	Cell(const Cell<V>& from);
	Cell<V>& operator=(const Cell<V>& rhs);
	
	friend ostream& operator<< <>(ostream& os, const Cell<V>& c);

	private:
		int r;
		int d;
		int type;
		V   v;
};


template <typename V> Cell<V>::Cell(int rlevel, int dlevel,int type, V val):
			r(rlevel),
			d(dlevel),
			v(val)
		{}

template <typename V> Cell<V>::~Cell()
		{}

template <typename V> Cell<V>::Cell(const Cell<V>& from)
		{
			this->r=from.r;
			this->d=from.d;
			this->type=from.type;
			this->v=from.v;
		}

template <typename V> Cell<V>& Cell<V>::operator=(const Cell<V>& rhs)
		{
			if ( this == &rhs)
				return *this;

			this->r=rhs.r;
			this->d=rhs.d;
			this->type=rhs.type;
			this->v=rhs.v;
			return *this;
		}

template <typename V> ostream& operator<< (ostream& os, const Cell<V>& c)
		{
			cout << "Hello\n" << c.r << "\nend\n";
			return os;
		}
/*
int main ( int argc, char** argv)
{
	Cell<int> *c = new Cell<int>(1,2,1,3);
	Cell<int> c2(*c);
	Cell<int> c3 = *c;
	cout << *c;
	return 0;
}
*/

