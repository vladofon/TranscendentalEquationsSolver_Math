#include <iostream>
#include"Solver.h"

using namespace std;

int main()
{
   Solver* solver = new Solver(1, 3, -4, -1);
   cout.precision(4);
   cout << solver->solve() << endl;
}

