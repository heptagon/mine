#include "test.pb.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void read_user_data(Person* p)
{
	cout << "Name:";
	getline(cin,*p->mutable_name());
	
	cout << "Id:";
	int id;
	cin >> id;
	p->set_id(id); 
	cin.ignore(256,'\n');

	cout << "email:";
	string email;
	getline(cin,email);	
	if ( !email.empty())
		p->set_email(email);

	while(true)
	{
		cout << "Enter phone number (enter) when done";
		string num;
		getline(cin,num);
		if (num.empty())
		{
			break;
		}
		Phnum *phnum = p->add_phnum();
		phnum->set_number(num);
		cout << "Type (optional - leave blank)";
		string type;
		getline(cin,type);
		if ( !type.empty())
			phnum->set_type(type);
	}
	return;


}

void output_file(const Plist& pl)
{
	for(int ii=0;ii<pl.person_size();++ii)
	{
		const Person& p = pl.person(ii);
		cout << "Name" << p.name() <<  endl;
		cout << "id"   << p.id()   << endl;
		if ( p.has_email())
			cout << "email" << p.email() << endl;
		for(int jj=0;jj<p.phnum_size();++jj)
		{
			const Phnum& phnum = p.phnum(jj);
			cout << "Number" << phnum.number();
			cout << "type" << phnum.type();
		}
	}

}




void write_columnar(const Plist& pl)
{

	// cells is an array of list
	// iterate over the cells; each list one at at time and dump it serially on the console.

		
}


int main ( int argc, char** argv)
{
	 GOOGLE_PROTOBUF_VERIFY_VERSION;

	if ( argc != 2)
	{
		cerr << "Usage: " << argv[0] << " addresslist file name" << endl;
		return 1;
	}		
	
	Plist l;
	fstream f(argv[1],ios::in|ios::binary);
	if ( !f)
	{
		read_user_data(l.add_person());
		
	}else if ( !l.ParseFromIstream(&f))
	{
		cerr << "cant parse file \n";
		return -1;
	}

	f.close();
	fstream out(argv[1],ios::out|ios::binary|ios::trunc);
	if ( !l.SerializeToOstream(&out))
	{
		cerr << "FAiled to write to file" << endl;
		return -1;
	}
	out.close();
	cout << "outputting the file again\n";

	Plist l2;
	fstream in(argv[1],ios::in|ios::binary);
	if ( !in)
	{
		cerr << "Cant read while dumping" << endl;
		return -1;
	}
	if (! l2.ParseFromIstream(&in))
	{
		cerr << "Cant parse input file while dumping" << endl;
	}

	output_file(l2);
	in.close();	
	google::protobuf::ShutdownProtobufLibrary();

	
	return 0;
}


