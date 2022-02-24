#pragma once
#include  "Solver.h"
#include  "Derivative.h"


class ChordSolver : public Solver
{
public:

   ChordSolver(Equation* equation) : Solver(equation)
   {
      this->derivative = new Derivative();
   }

   long double solve(int precision) override
   {
      Step* point = findRoot();



      return 0;
   }

private:
   Derivative* derivative;

   void chooseWay()
   {
      derivative->firstOrder();
   }
};