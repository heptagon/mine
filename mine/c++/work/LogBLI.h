#ifndef LOGBLI_H
#define LOGBLI_H

#include <iostream>

using namespace std;

int TCAL_MAX_SIZE=20;
int TCAL_MAX_LENGTH=200;

public class ContextStack {

 public:
  static ContextStack&  getInstance(void){
    static ContextStack ctx = ContextStack();
    return ctx;
  }

  ~ContextStack() {}

  string getCurrentContextString();
  string pop(void);
  int push(string str);
  
 private:
  ContextStack();
  ContextStack & operator = ( const ContextStack& contextStack);
  ContextStack ( const ContextStack contextStack);

  void setContextString(string String);
  void reset(void);
  
  static const int TCAL_MAX_SIZE;
  static const int TCAL_MAX_LENGTH;
  string ctxstr;
  int level;

};

#endif
