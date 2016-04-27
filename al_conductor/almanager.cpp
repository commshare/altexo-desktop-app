#include "alconductor.h"
#include <iostream>

using namespace std;

extern "C" AlManager* create_object()
{
  return new AlManager;
}

extern "C" void destroy_object( AlManager* object )
{
  delete object;
}

AlManager::AlManager()
{
}


void AlManager::init()
{
  cout << "AlConductor::init()qwweqwe" << endl;
}
