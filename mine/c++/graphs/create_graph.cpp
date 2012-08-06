#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <ctime>

using namespace std;
const int BIDRECTIONAL=1;
const int INBOUND=2;
const int OUTBOUND=3;
const int UNDIRECTIONAL=0;

typedef struct Node {
	int id;
	int val;

	Node():val(0)
	{
	}

	Node(int ii):id(ii) {};
	Node(int ii,int jj): id(ii),val(jj) {};

	~Node()
	{
	}

} Node;
typedef struct Link {
	double weight;
	int direction;
	Node* n1;
	Node* n2;
	Link() {
		weight=0;
		direction=0;
		n1=n2=NULL;
	}
	Link(Node* N1, Node* N2,double w, int d):n1(N1),n2(N2),weight(w),direction(d) {};

} Link;



	
class Graph{
	public:
		Graph()
		{
			init_graph();
		}
		~Graph()
		{
		}

		void init_graph(void) 
		{
		};
		
		bool add_node(Node* n){
			nodes[n->id]=n;
		}
		bool add_link(Link* l){
			links[l->n1->id].push_back(l->n2->id);
			if ( n1->id != n2->id )
				links[l->n2->id].push_back(l->n1->id);
			
		Node* get_node(int id);
		Node* get_node_by_val(int val);
		vector<Link*> get_links_for_node(int id);
		/*	
		List<Node> walk_bf(Node& start);
		List<Node> walk_df(Node& start);
*/

	friend ostream& operator << (ostream& os, Graph g)
	{	
		os << "hello\n";
		os << endl;	
		return os;
	}
	private:
		vector<Node*> nodes;
		map<int,vector<Node*> > links;
		string name;
};

bool add_nodes(Graph* g, int max_nodes);
bool add_links(Graph* g, int max_connections);

int main(int argc, char** argv)
{
	typedef list<Graph> LG; 	
	LG *lg = new LG();
	Graph *g=new Graph();

	add_nodes(g,100);
	add_links(g,100);
	cout << *g;
	

return 0;
}

bool add_nodes(Graph *g, int max_nodes)
{

	for(int ii=0;ii<max_nodes;++ii)
	{
		int v=rand()%1000;
		Node *n=new Node(ii,v);
		g->add_node(n);
	}
	return true;
}

bool add_links(Graph *g, int max_nodes, int max_connections)
{
	for( int ii=0;ii<max_nodes;++ii)
		g->add_link(new Link(
			g->get_node(ii),
			g->get_node(rand() %100),
			rand()%1000,
			rand()%3));
	return true;

}

