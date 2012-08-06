#include <iostream>
#include <string>

using namespace std;
string mult(string s1, string s2);
string mult2(string s1,string s2);

int main(int argc, char ** argv)
{
  string n1="";
  string n2="";

  cout << "Enter number 1:\n";
  cin >> n1;

  cout << "Enter number 2: \n";
  cin >> n2;

  cout << "n1 is " << n1 << " and n2 is " << n2 << "\n" ;
  cout << "length of n1 is " << n1.length() << " and of n2 is " << n2.length() << " \n" ;

  // check if all characters are numerals or decimals or (+-)sign[ in the right position]; remove whitespaces
  string res=mult2(n1, n2);
  // removve leading zeroes
  cout << n1 << " * " << n2 << " is " << res << "\n" ;
  return 0;
}



string mult2(string s1, string s2)
{
  typedef unsigned long long ullong;
  if ( s1.length() == 0 || s2.length() == 0 ) 
    return "";
  
  bool negs1=false,negs2=false;
  string s3=s1;
  string s4=s2;
  if ( s1[0] == '-' ){
    negs1=true;
    s3=s1.erase(0,1);
  }
  if ( s2[0] == '-' ){
    s4=s2.erase(0,1);
    negs2=true;
  }
  
  size_t poss1dec=s1.find('.');
  size_t poss2dec=s2.find('.');

  ullong s1digitsafterdecimal=0;
  ullong s2digitsafterdecimal=0;
  if ( poss1dec != string::npos ){
    s1digitsafterdecimal=s3.length()-poss1dec-1;
    s3 = s3.erase(poss1dec,1);
  }
  if ( poss2dec != string::npos ){
    s2digitsafterdecimal=s4.length()-poss2dec-1;
    s4 = s4.erase(poss2dec,1);
  }
  ullong totaldigafterdecimal=s1digitsafterdecimal+s2digitsafterdecimal;
  // todo check for platform compatibility and range
  
  s4 =       poss2dec != string::npos ? s4.erase(poss2dec,1) : s4;

  ullong l3=s3.length();
  ullong l4=s4.length();
  if ( l3+l4+2 < min(l3,l4))
    return "Err:Need to use Real/double and check for return types compatibility";
  

  ullong max_len=l3+l4+1;
  string result(max_len,'0');

  for ( int jj=0; jj<l4;++jj){
    string row(max_len,'0');
    ullong toskip=l4-jj-1;
    ullong rowpos=max_len-1 - toskip;
    
    int carry=0;
    for ( int ii=l3-1;ii>=0; --ii){
      int product=(int)(((char)(s3[ii])-'0')) * (int)(((char)(s4[jj])-'0'))+carry;
      row[rowpos--]=(char)((product%10)+'0');
      carry=product/10;
    }
    row[rowpos]=(char)(carry+'0');
    
    int sumcarry=0;
    for(int mm=max_len-1; mm >=0; --mm){
      int sum=(int)((char)(result[mm])-'0')+(int)((char)(row[mm])-'0')+sumcarry;
      result[mm]=(char)((char)(sum%10)+ '0');
      sumcarry=sum/10;
    }
    if( sumcarry>0)
      cout << "SumCarry > 0 ";

    //cout << row << "\n" ;
    //cout << "partial result" << result << "\n";
  }
  


  if ( totaldigafterdecimal > 0 )
    result.insert(result.length()-totaldigafterdecimal,1,'.');

  if (( negs1 && !negs2 ) || ( !negs1 && negs2))
    result.insert(0,1,'-');

  //  cout << "Final Result " << result << "\n";


  return result;


}

string mult( string  n1,  string n2)
{
  string res="";
  return res;
  /*
  if ( n1.length() == 0 || n2.length()== 0 )
    return res;

  // handle . and - sign
  bool n1neg=false;
  bool n2neg=false;

  if ( n1[0]=="-")
    n1neg=true;

  if ( n2[0] =="-")
    n2neg=true;

  int posn1dec=n1.find(".");
  int posn2dec=n2.find(".");

  string s3,s4;

  if ( n1neg )
    s3=n1.erase(0,0).erase(posn1dec,0);
  else
    s3=n1.erase(posn1dec,0);

  if ( n2neg )
    s4.erase(0,0).erase(posn2dec,0);
  else
    s4=n2.erase(posn2dec,0);

  int l3=s3.length();
  int l4=s4.length();


  long maxlen=l3+l4+2;
  string row(maxlen,"0");
  string result(maxlen,"0");
  int numzeroes=l4-1;
  long rowpos=maxlen-1;

  for ( int jj = 0 ; jj<l4;++jj){
    for(int kk=0; kk<numzeroes;kk++)
      row[rowpos--]="0";
    numzeroes--;

    int carry=0;
    for ( int ii=l3-1; ii>=0;--ii){
      int p_and_c=(((int)((char)(s3[ii])-'0'))*((int)(char(s4[kk]-'0')))+carry);
      row[rowpos--]=(char)('0'+(char)(p_and_c%10));
      carry=p_and_c/10;
    }
    row[rowpos]=(char)('0' + (char)(carry));
  }
  int carryres=0;
  int mm=max_len-1;
  for(mm=maxlen-1; mm >=0;--mm){
    int sum=((int)((char)(result[mm])-'0'))+((int)((char)(row[mm])-'0'))+carry;
    result[mm]=(char)('0' + (char)(sum%10));
    carry=sum/10;
  }
  

  return result;
  */
}
