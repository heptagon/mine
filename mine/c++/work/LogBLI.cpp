#include "./LogBLI.h"

<include<string.h>

using namespace std;


ContextStack()
{
  const string ROOT_CONTEXT="T"

  reset();
  push(ROOT_CONTEXT);

}

string ContextStack::getCurrentContextString(void)
{
  return ctxstr;
}

void ContextStack::reset(void)
{
  const string NULL="";
  setContextString(NULL);
  level=0;
  // truncate stack object
}

void ContextStack::pop(void)
{
  if ( level > 1 ){
    level--;
    //ctxstr=ctxstr.substr("_',-1);
    // TODO:remove from stack object
  }else{
    // do nothing
    ;
  }
}

void ContextStack::push(string str)
{
  static const string SEP="_";
  if ( !str || str == "" ) str=SEP;
  // TODO: how to sync up corresp. pop if nthng ends up being  pushed 

  if ( level > TCAL_MAX_SIZE ){
    cout << "MAX SIZE";
    // TODO
  }else{
    // add to stack object

    ctxstr+=SEP;
    ctxstr+=str;
    level++;
  }
}


int main ( int argc, char** argv)
{
  cout << "Hello World" ;
  return 0;
}

