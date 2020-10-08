//Jane Yang
//2317614
//huayang@chapman.edu
//CPSC350-01
//Assignment 2
#include <iostream>
#include <sstream>
#include<fstream>
#include<string>
#include<cmath>
#include<algorithm>
#include<time.h>
#include<ctime>
#include<thread>
#include<chrono>
using namespace std;

class GameOfLife{

public:
  GameOfLife();
  GameOfLife(int x, int y);
  ~GameOfLife();

  //void readInFile(string path);
  void readNum(string input);
  void randomGrid();
  void rule();
  void checkCla();
  void checkDou();
  void checkMir();
  int** getArray();
  int getHerizontal();
  int getVertical();
  int checkC(int h,int v);
  int checkD(int x, int y);
  int checkM(int x, int y);
  void printGrid();
  bool isEmpty();
  bool isFull();
  bool stable();
  void copyA();
  void printA();
  void printB();
  void creat2();
  void creat3();
  void printA2();
  int returnCell(int x,int y);
  double getDensity();


  int **m_Array;
  int **m_Array2;
  int **m_Array3;
  int m_herizontal;
  int m_vertical;
  double popDensity;
  private:

};
