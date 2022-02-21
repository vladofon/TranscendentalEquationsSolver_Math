#pragma once
#include "Solver.h"
#include "Step.h"
#include <iostream>

using namespace std;

class TrialMethod : public Solver
{
public:

   TrialMethod(Equation* equation) : Solver(equation)
   {

   }

   void solve(int precision)
   {
      int currentPrecision = 0;
      List<Step*>* steps = new ArrayList<Step*>();

      while (currentPrecision != precision)
      {
         if (steps->getSize() == 0)
         {
            steps->add(findRoot());
         }
         else
         {
            steps->add(
               findRoot(
                  steps->get(steps->getSize() - 1)->index,
                  steps->get(steps->getSize() - 1)->precision
               )
            );
         }
      }

      cout << steps->get(steps->getSize() - 1) << endl;
   }

};