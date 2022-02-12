#pragma once
#include"List.h"
#include<string>

using namespace std;

class TableRecord
{
public:

   TableRecord(List<string>* tableRecord, long cellWidth, long space, long totalColsCount, bool header, bool clossingCell)
   {
      this->tableRecord = tableRecord;
      this->cellWidth = cellWidth;
      this->space = space;
      this->totalColsCount = totalColsCount;
      this->header = header;
      this->clossingCell = clossingCell;
   }

   List<string>* getTableRecord()
   {
      return tableRecord;
   }

   long getCellWidth()
   {
      return cellWidth;
   }

   long getTotalColsCount()
   {
      return totalColsCount;
   }

   long getSize()
   {
      return tableRecord->getSize();
   }

   long getSpace()
   {
      return space;
   }

   bool isHeader()
   {
      return header;
   }

   bool isClossingCell()
   {
      return clossingCell;
   }

private:

   List<string>* tableRecord;
   long cellWidth;
   long space;
   long totalColsCount;
   bool header;
   bool clossingCell;
};