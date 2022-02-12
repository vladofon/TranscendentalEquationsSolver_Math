#pragma once
#include<string>
#include"List.h"
#include"ArrayList.h"

using namespace std;

class TableSchema
{
private:

   class Row
   {
   private:

      class Column
      {
      private:

         class Cell
         {
         private:
            string data;

         public:
            Cell(string data)
            {
               this->data = data;
            }

            Cell() {}

            string getData()
            {
               return data;
            }
         };

         List<Cell>* cells;
         string columnName;

      public:
         Column(string columnName)
         {
            this->cells = new ArrayList<Cell>();
            this->columnName = columnName;
         }

         Column() { this->cells = new ArrayList<Cell>(); }

         Cell createCell(string data)
         {
            Cell newCell = Cell(data);
            cells->add(newCell);

            return newCell;
         }

         Cell getCell(long index)
         {
            return cells->get(index);
         }

         string getName()
         {
            return this->columnName;
         }

         long cellsCount()
         {
            return cells->getSize();
         }
      };

      List<Column>* columns;
      string rowName;

   public:
      Row(string rowName)
      {
         this->columns = new ArrayList<Column>();
         this->rowName = rowName;
      }

      Row() { this->columns = new ArrayList<Column>(); }

      Column createColumn(string columnName)
      {
         Column newColumn = Column(columnName);
         columns->add(newColumn);

         return newColumn;
      }

      Column getColumn(long index)
      {
         return columns->get(index);
      }

      string getName()
      {
         return this->rowName;
      }

      long colsCount()
      {
         return columns->getSize();
      }
   };

   List<Row>* rows = new ArrayList<Row>();

   long maxColumnSizeByRow(long rowId)
   {
      long maxColumnSize = 0;

      for (long i = 0; i < getRow(rowId).colsCount(); i++)
      {
         long currentColumnSize = getRow(rowId).getColumn(i).cellsCount();

         if (maxColumnSize < currentColumnSize)
         {
            maxColumnSize = currentColumnSize;
         }
      }

      return maxColumnSize;
   }

public:

   void fillColumn(long rowId, long columnId, List<string>* data)
   {
      for (long i = 0; i < data->getSize(); i++)
      {
         getRow(rowId)
            .getColumn(columnId)
            .createCell(data->get(i));
      }
   }

   void rebalanceColumns(long rowId)
   {
      long maxColumnSize = maxColumnSizeByRow(rowId);

      for (long i = 0; i < getRow(rowId).colsCount(); i++)
      {
         long currentColumnSize = getRow(rowId).getColumn(i).cellsCount();

         if (maxColumnSize > currentColumnSize)
         {
            for (long cell = currentColumnSize; cell < maxColumnSize; cell++)
            {
               getRow(rowId).getColumn(i).createCell("");
            }
         }
      }
   }

   Row createRow(string rowName)
   {
      Row newRow = Row(rowName);
      rows->add(newRow);

      return newRow;
   }

   Row getRow(long index)
   {
      return rows->get(index);
   }

   long rowsCount()
   {
      return rows->getSize();
   }


};