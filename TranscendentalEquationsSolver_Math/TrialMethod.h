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
            currentPrecision++;
         }
         else
         {
            steps->add(
               findRoot(
                  steps->get(steps->getSize() - 1)->index,
                  currentPrecision
               )
            );
            currentPrecision++;
         }
      }

      cout << steps->get(steps->getSize() - 1)->index << endl;
   }

};