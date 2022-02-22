#pragma once
#include"Step.h"
#include"List.h"
#include"ArrayList.h"
#include<math.h>

class EquationMember
{
public:
   EquationMember(int multiplier, int power, bool isVariable)
   {
      this->multiplier = multiplier;
      this->power = power;
      this->isVariable = isVariable;
   }

   EquationMember() {}

   int multiplier;
   int power;
   bool isVariable;

   long double represent(long double value)
   {
      if (isVariable)
      {
         return multiplier * pow(value, power);
      }
      else
      {
         return pow(multiplier, power);
      }
   }
};

class Equation
{
public:

   Equation(List<EquationMember>* equation)
   {
      this->equation = equation;
   }

   EquationMember get(int index)
   {
      return equation->get(index);
   }

   long size()
   {
      return equation->getSize();
   }

private:

   List<EquationMember>* equation;
};

class Solver
{
public:
   Solver(Equation* equation)
   {
      this->equation = equation;
   }
protected:

   Step* findRoot(long double startPoint = 0, int precision = 0)
   {
      List<Step*>* steps = new ArrayList<Step*>();
      List<Step*>* keySteps = new ArrayList<Step*>();

      int digitChangingCount = 0;
      int indexChangingCount = 0;
      int currentPrecision = precision;

      bool isPrecisionReached = (precision == 0) ? currentPrecision == precision + 1 : currentPrecision == precision + 2;

      while (keySteps->getSize() != precision + 1 && !isPrecisionReached)
      {
         steps->add(makeStep(startPoint, currentPrecision));

         bool canCreatePair = steps->getSize() > 1;

         if (canCreatePair)
         {
            Step* current = steps->get(steps->getSize() - 1);
            Step* previous = steps->get(steps->getSize() - 2);

            if (current->sign != previous->sign)
            {
               startPoint = previous->index;

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
            }
            else
            {
               digitChangingCount = 0;
               indexChangingCount++;

               if (indexChangingCount > 10)
                  break;
            }
         }

         startPoint = add(new long double[2]{ startPoint, nextIndex(currentPrecision) });
      }

      if (keySteps->getSize() == 0)
      {
         Step* notFound = new Step;
         notFound->precision = 0;
         notFound->isEmpty = true;

         keySteps->add(notFound);
      }

      return keySteps->get(keySteps->getSize() - 1);
   }

private:
   Equation* equation;

   long double nextIndex(int stepPrecision)
   {
      return (1 / pow(10, stepPrecision));
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

   long double separateRoot(long double number)
   {
      long membersCount = equation->size();
      long double* members = new long double[membersCount];

      for (long i = 0; i < membersCount; i++)
      {
         members[i] = equation->get(i).represent(number);
      }

      return add(members, membersCount);
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