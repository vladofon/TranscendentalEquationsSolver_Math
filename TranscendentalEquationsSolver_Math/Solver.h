#pragma once
#include <math.h>
#include"List.h"
#include"ArrayList.h"
#include"Step.h"

class Solver
{
public:

   Solver(int firstNumber, int fnPower, int secondNumber, int thirdNumber)
   {
      this->firstNumber = firstNumber;
      this->fnPower = fnPower;
      this->secondNumber = secondNumber;
      this->thirdNumber = thirdNumber;
   }

   List<Step*>* solve()
   {
      long double index = 0;
      int currentPrecision = 0;
      List<Step*>* steps = new ArrayList<Step*>();

      while (currentPrecision != totalPrecision)
      {
         steps->add(makeStep(index, currentPrecision));

         bool canCreatePair = steps->getSize() > 1;

         if (canCreatePair)
         {
            Step* current = steps->get(steps->getSize() - 1);
            Step* previous = steps->get(steps->getSize() - 2);

            if (current->sign != previous->sign)
            {
               if (abs(current->number) > abs(previous->number))
               {
                  index = add(new long double[2]{ index, nextIndex(currentPrecision) * (-1) });
               }

               currentPrecision++;

               index = add(new long double[2]{ index, nextIndex(currentPrecision) });

               steps->add(makeStep(index, currentPrecision));
            }
         }

         index = add(new long double[2]{ index, nextIndex(currentPrecision) });
      }

      return steps;
   }

private:

   long double firstNumber;
   int fnPower;
   long double secondNumber;
   long double thirdNumber;

   int totalPrecision = 4;
   long double one = 1;

   long double nextIndex(int stepPrecision)
   {
      return (one / pow(10, stepPrecision));
   }

   long double separateRoot(double number)
   {
      return add(new long double[3]{ pow(number * firstNumber, fnPower), (secondNumber * number), thirdNumber }, 3);
   }

   Step* makeStep(long double index, int stepPrecision)
   {
      Step* newStep = new Step;

      newStep->number = separateRoot(index);
      newStep->sign = (newStep->number > 0) ? true : false;
      newStep->precision = stepPrecision;
      newStep->index = index;

      return newStep;
   }

   long double add(long double input[], int length = 2)
   {
      long double sum = 0;
      long double sumOfError = 0;

      for (int i = 0; i < length; i++)
      {
         long double y = input[i] - sumOfError;
         long double t = sum + y;
         sumOfError = (t - sum) - y;

         sum = t;
      }

      return sum;
   }
};