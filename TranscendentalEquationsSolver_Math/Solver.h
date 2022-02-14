#pragma once
#include<iostream>

#include <math.h>
#include"List.h"
#include"ArrayList.h"
#include"Step.h"

using namespace std;

class Solver
{
public:

   Solver(int firstNumber, int fnPower, int secondNumber, int snPower, int thirdNumber)
   {
      this->firstNumber = firstNumber;
      this->fnPower = fnPower;
      this->snPower = snPower;
      this->secondNumber = secondNumber;
      this->thirdNumber = thirdNumber;
   }

   List<Step*>* solve()
   {
      long double index = 0;
      int currentPrecision = 0;
      List<Step*>* steps = new ArrayList<Step*>();
      List<Step*>* keySteps = new ArrayList<Step*>();

      int digitChangingCount = 0;
      int indexChangingCount = 0;

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
               index = previous->index;

               keySteps->add(previous);

               steps->remove(steps->getSize() - 1);

               currentPrecision++;

               digitChangingCount++;

               indexChangingCount = 0;

               if (digitChangingCount > 1)
               {
                  Step* emptyStep = new Step;
                  emptyStep->isEmpty = true;
                  emptyStep->precision = currentPrecision - 1;

                  keySteps->remove(keySteps->getSize() - 1);
                  keySteps->add(emptyStep);

                  digitChangingCount--;
               }



               //if (abs(current->number) > abs(previous->number))
               //{
               //   index = add(new long double[2]{ index, nextIndex(currentPrecision) * (-1) });
               //   keySteps->add(makeStep(index, currentPrecision));
               //}
               //else
               //{
               //   keySteps->add(makeStep(index, currentPrecision));
               //}

               //currentPrecision++;

               //index = add(new long double[2]{ index, nextIndex(currentPrecision) });

               //steps->add(makeStep(index, currentPrecision));
            }
            else
            {
               digitChangingCount = 0;
               indexChangingCount++;

               if (indexChangingCount > 10)
                  break;
            }
         }

         index = add(new long double[2]{ index, nextIndex(currentPrecision) });
      }

      if (keySteps->getSize() == 0)
      {
         Step* notFound = new Step;
         notFound->precision = 0;
         notFound->isEmpty = true;

         keySteps->add(notFound);
      }

      return keySteps;
   }

private:

   long double firstNumber;
   int fnPower;
   int snPower;
   long double secondNumber;
   long double thirdNumber;

   int totalPrecision = 100;
   long double one = 1;

   long double nextIndex(int stepPrecision)
   {
      return (one / pow(10, stepPrecision));
   }

   long double separateRoot(double number)
   {
      return add(new long double[3]{ firstNumber * pow(number, fnPower), secondNumber * pow(number, snPower), thirdNumber }, 3);
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