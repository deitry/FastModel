#ifndef FM_FIELD_H
#define FM_FIELD_H

/**
Заголовочный файл модуля, который будет описывать структуру данных полей -
функций от двух и более переменных, заданных на равномерной сетке.
Пока для простоты выделим 2-мерные и 3-мерные поля, потом, в случае чего, обобщим.

Field3 можно реализовать как подкласс Field2 - ??
*/

class FMField2
{
protected:
   double X0, Y0; // начальные значения для X, Y
   double dX, dY; // шаг сетки по X, Y
   int maxX, maxY;// сколько значений

   double** F;

   double def;

public:
   FMField2();
   ~FMField2();
   double get(double X, double Y);

   void init(double X0, double dX, int maxX,
             double Y0, double dY, int MaxY,
             double defval);

   //void allocF();

   void set(double*** F1) {this->F = *F1;} // ??
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Для простоты - функция от трёх переменных на основе Field2, без наследования
class FMField3
{
protected:
   double X0, Y0, Z0; // начальные значения для X, Y
   double dX, dY, dZ; // шаг сетки по X, Y
   int maxX, maxY, maxZ;// сколько значений

   double def;  // значение по умолчанию - сейчас не используется

   double*** F;   // коренное отличие от Field2 - массив теперь трёхмерен

public:
   FMField3();
   ~FMField3() {delete F;}
   double get(double X, double Y, double Z);

   void init(double X0, double dX, int maxX,
             double Y0, double dY, int maxY,
             double Z0, double dZ, int maxZ,
             double defval);


   void setF(double*** F1) {this->F = F1;} // ??
};

double** CreateMatrix(int maxX, int maxY);
FMField2* ReadField2FromFile(char* FileName);


#endif