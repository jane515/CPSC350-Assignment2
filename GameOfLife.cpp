//Jane Yang
//2317614
//huayang@chapman.edu
//CPSC350-01
//Assignment 2
#include "GameOfLife.h"

GameOfLife::GameOfLife()
{
  m_herizontal = 0;
  m_vertical = 0;
  popDensity = 0;
}

GameOfLife::GameOfLife(int input, int input2)
{
  m_herizontal = input;
  m_vertical = input2;

}

GameOfLife::~GameOfLife()
{
  delete m_Array;
  delete m_Array2;
  delete m_Array3;

}
//return how many neighbors one cell has
int GameOfLife::returnCell(int x,int y)
{
  return m_Array[x][y];

}
//read the file
void GameOfLife::readNum(string input)
{
  std::ifstream file;
  file.open(input);
  int times = 1;
  if(file.is_open())
  {
    std::string line;
    while(std::getline(file,line))
    {
      if(times==1)
      {
        m_herizontal=stoi(line);
      }
      else if(times==2)
      {
        m_vertical=stoi(line);
        times++;
        break;
      }
      times++;
    }
    m_Array = new int *[m_herizontal];
    for(int i = 0;i<m_herizontal;i++)
    {
      m_Array[i] = new int[m_vertical];
    }
    int countLine=-1;
    while(std::getline(file,line))
    {
      if(times==3)
      {
        countLine++;

        for(int i =0;i<m_vertical;i++)
        {

          if(line[i]=='x')
          {
            m_Array[countLine][i]=1;

          }
          else if(line[i]=='X')
          {
            m_Array[countLine][i]=1;
          }
          else if(line[i]=='-')
          {
            m_Array[countLine][i]==0;
          }
        }
      }
    }
  }
  file.close();
}
//return the popDensity
double GameOfLife::getDensity()
{
  return popDensity;
}
//generate random grid
void GameOfLife::randomGrid()
{
  srand(time(NULL));
  popDensity = ((double)rand()/(double)RAND_MAX);
  m_herizontal = rand()%20+3;
  m_vertical = rand()%20+3;
  m_Array = new int *[m_herizontal];
  for(int i =0;i<m_herizontal;i++)
  {
    m_Array[i]=new int[m_vertical];
  }
  int total = m_herizontal*m_vertical;
  int numX = total*popDensity;
  while(numX!=0)
  {
    int x = rand()%m_herizontal;
    int y = rand()%m_vertical;
    if(m_Array[x][y]!=1)
    {

      m_Array[x][y]=1;
      numX--;
    }
  }
  for(int i =0;i<m_herizontal;i++)
  {
    for(int j=0;j<m_vertical;j++)
    {
      if(m_Array[i][j]!=1)
      {
        //fill in the array
        m_Array[i][j]=0;
      }
    }
  }
}
//return the grid & other variables
int** GameOfLife::getArray()
{
  return m_Array;
}
int GameOfLife::getHerizontal()
{
  return m_herizontal;
}
int GameOfLife::getVertical()
{
  return m_vertical;
}
//check if the grid is empty
bool GameOfLife::isEmpty()
{
  for(int i =0;i<m_herizontal;i++)
  {
    for(int j=0;j<m_vertical;j++)
    {
      if(m_Array[i][j]==1)
      {
        return false;
      }
    }
  }
  return true;
}
//check if the grid is full
bool GameOfLife::isFull()
{
  int count=0;
  int total = m_herizontal*m_vertical;
  for(int i =0;i<m_herizontal;i++)
  {
    for(int j=0;j<m_vertical;j++)
    {
      if(m_Array[i][j]==0)
      {
        return false;
      }
    }
  }
  return true;
}
//check the neighbor of one cell in classic mode
int GameOfLife::checkC(int h,int v)
{
  int i = h;
  int j =v;
      int count = 0;
      if(i<m_herizontal-1)
      {
        if(m_Array[i+1][j]!=0)
        {
          count++;
        }
        if(j<m_vertical-1)
        {
          if(m_Array[i+1][j+1]!=0)
          {
            count++;
          }
        }
        if(j>0)
        {
          if(m_Array[i+1][j-1]!=0)
          {
            count++;
          }
        }
      }
      if(i>0)
      {
        if(m_Array[i-1][j]!=0)
        {
          count++;
        }
        if(j<m_vertical-1)
        {
          if(m_Array[i-1][j+1]!=0)
          {
            count++;
          }
        }
        if(j>0)
        {
          if(m_Array[i-1][j-1]!=0)
          {
            count++;

          }
        }
      }
      if(j<m_vertical-1)
      {
        if(m_Array[i][j+1]!=0)
        {
          count++;
        }
      }
      if(j>0)
      {
        if(m_Array[i][j-1]!=0)
        {
          count++;
        }
      }
  return count;
}

//check the neighbor of one cell in doughnut mode
int GameOfLife::checkD(int x, int y)
{
  int i =x;
  int j =y;
  int count = 0;
  int nRow = m_herizontal-1;
  int nCol = m_vertical-1;
  //if the first row, check the last row
  if(i=0)
  {
    if(m_Array[nRow][j]!=0)
    {
      count++;
    }
    //corner 0,nCol
    if(j=nCol)
    {
      if(m_Array[nRow][0]!=0)
      {
        count++;
      }
    }
    else
    {
      if(m_Array[nRow][j+1]!=0)
      {
        count++;
      }
    }

    //corner 0,0
    if(j=0)
    {
      if(m_Array[nRow][nCol]!=0)
      {
        count++;
      }
    }
    else
    {
      if(m_Array[nRow][j-1]!=0)
      {
        count++;
      }
    }
  }
  if(i=nRow)
  {
    if(m_Array[0][j]!=0)
    {
      count++;
    }
    //corner nRow,0
    if(j=0)
    {
      if(m_Array[0][nCol]!=0)
      {
        count++;
      }
    }
    else
    {
      if(m_Array[0][j-1]!=0)
      {
        count++;
      }
    }
    //corner nrow,ncol
    if(j=nCol)
    {
      if(m_Array[0][0]!=0)
      {
        count++;
      }
    }
    else
    {
      if(m_Array[0][j+1]!=0)
      {
        count++;
      }
    }
  }
  //first column, check the last coloumn
  if(j=0)
  {
    //left
    if(m_Array[i][nCol]!=0)
    {
      count++;
    }
    if(i!=nRow)
    {
      if(m_Array[i+1][nCol]!=0)
      {
        count++;
      }
    }
    if(i!=0)
    {
      if(m_Array[i-1][nCol]!=0)
      {
        count++;
      }
    }
  }
  //last coloumn, check first coloumn
  if(j=nCol)
  {
    if(m_Array[i][0]!=0)
    {
      count++;
    }
    if(i!=nRow)
    {
      if(m_Array[i+1][0]!=0)
      {
        count++;
      }
    }
    if(i!=0)
    {
      if(m_Array[i-1][0]!=0)
      {
        count++;
      }
    }
  }
  if(i<nRow)
  {
    if(m_Array[i+1][j]!=0)
    {
      count++;
    }
    if(j<nCol-1)
    {
      if(m_Array[i+1][j+1]!=0)
      {
        count++;
      }
    }
    if(j>0)
    {
      if(m_Array[i+1][j-1]!=0)
      {
        count++;
      }
    }
  }
  if(i>0)
  {
    if(m_Array[i-1][j]!=0)
    {
      count++;
    }
    if(j<nCol-1)
    {
      if(m_Array[i-1][j+1]!=0)
      {
        count++;
      }
    }
    //not the first column, check left-down
    if(j>0)
    {
      if(m_Array[i-1][j-1]!=0)
      {
        count++;

      }
    }
  }
  //not the last column, check right
  if(j<nCol-1)
  {
    if(m_Array[i][j+1]!=0)
    {
      count++;
    }
  }
  //not the first column, check left
  if(j>0)
  {
    if(m_Array[i][j-1]!=0)
    {
      count++;
    }
  }
  return count;
}
//check the neighbor of one cell in mirror mode
int GameOfLife::checkM(int x, int y)
{
  int i =x;
  int j =y;
  int count = 0;
  int nRow = m_herizontal-1;
  int nCol = m_vertical-1;
  //top row
  if(i=0)
  {
    if(m_Array[i][j]!=0)
    {
      count++;
    }
    if(j=0)
    {
      if(m_Array[0][0]!=0)
      {
        count+=3;
      }
    }
    else if(j=nCol)
    {
      if(m_Array[0][nCol]!=0)
      {
        count+=3;
      }
    }
  }
  //last row
  if(i=nRow)
  {
    if(m_Array[nRow][j]!=0)
    {
      count++;
    }
    if(j=0)
    {
      if(m_Array[nRow][0]!=0)
      {
        count+=3;
      }
    }
    else if(j=nCol)
    {
      if(m_Array[nRow][nCol]!=0)
      {
        count+=3;
      }
    }
  }
  if(j=0)
  {
    if(m_Array[i][j]!=0)
    {
      count++;
    }
  }
  else if(j=nCol)
  {
    if(m_Array[i][j]!=0)
    {
      count++;
    }
  }
  if(i<nRow-1)
  {
    if(m_Array[i+1][j]!=0)
    {
      count++;
    }
    if(j<nCol-1)
    {
      if(m_Array[i+1][j+1]!=0)
      {
        count++;
      }
    }
    if(j>0)
    {
      if(m_Array[i+1][j-1]!=0)
      {
        count++;
      }
    }
  }
  if(i>0)
  {
    if(m_Array[i-1][j]!=0)
    {
      count++;
    }
    if(j<nCol-1)
    {
      if(m_Array[i-1][j+1]!=0)
      {
        count++;
      }
    }
    if(j>0)
    {
      if(m_Array[i-1][j-1]!=0)
      {
        count++;

      }
    }
  }
  if(j<nCol-1)
  {
    if(m_Array[i][j+1]!=0)
    {
      count++;
    }
  }
  if(j>0)
  {
    if(m_Array[i][j-1]!=0)
    {
      count++;
    }
  }
  return count;
}

//print the grid
void GameOfLife::printGrid()
{
  cout<<"The Grid: "<<endl;
  for(int i =0;i<m_herizontal;i++)
  {
    for(int j =0;j<m_vertical;j++)
    {
      if(m_Array[i][j]==0)
      {
        cout<<'-'<<" ";
      }
      else
      {
        cout<<'x'<<" ";
      }
    }
    cout<<"\n";
  }
}
//create array3 to store the previous grid
void GameOfLife::creat3()
{
  m_Array3 = new int *[m_herizontal];
  for(int i = 0;i<m_herizontal;i++)
  {
    m_Array3[i] = new int[m_vertical];
  }
}
//create array2 to store the number of neighors of each cell
void GameOfLife::creat2()
{
  m_Array2 = new int *[m_herizontal];
  for(int i = 0;i<m_herizontal;i++)
  {
    m_Array2[i] = new int[m_vertical];
  }
}
//print the number if neighors each cell has
void GameOfLife::printA()
{
  cout<<"Count: "<<endl;
  for(int i =0;i<m_herizontal;i++)
  {
    for(int j =0;j<m_vertical;j++)
    {
      cout<<m_Array2[i][j]<<" ";
    }
    cout<<"\n";
  }
}
//print the last grid
void GameOfLife::printB()
{
  cout<<"Last: "<<endl;
  for(int i =0;i<m_herizontal;i++)
  {
    for(int j =0;j<m_vertical;j++)
    {
      cout<<m_Array3[i][j]<<" ";
    }
    cout<<"\n";
  }
}
//copy the grid and store as the last grid
void GameOfLife::copyA()
{

  for(int i =0;i<m_herizontal;i++)
  {
    for(int j=0;j<m_vertical;j++)
    {
      m_Array3[i][j]=m_Array[i][j];
    }
  }
}
//check if the previous grid is the same as current grid
bool GameOfLife::stable()
{
  for(int i =0;i<m_herizontal;i++)
  {
    for(int j=0;j<m_vertical;j++)
    {
      if(m_Array3[i][j]!=m_Array[i][j])
      return false;
    }
  }
  return true;
}
//rule of the game
void GameOfLife::rule()
{
  for(int i=0;i<m_herizontal;i++)
  {
    for(int j=0;j<m_vertical;j++)
    {
      //1 or 0 neighbor die
      if(m_Array2[i][j]==0)
      {
        m_Array[i][j]=0;
      }
      else if(m_Array2[i][j]==1)
      {
        m_Array[i][j]=0;
      }
      //2 neighbors, stay the same
      else if(m_Array2[i][j]==2)
      {
        continue;
      }
      else if(m_Array2[i][j]==3)
      {
        m_Array[i][j]=1;
      }
      else
      {
        m_Array[i][j]=0;
      }
    }
  }
}
//print the array that stores the number of neighbors of each cell
void GameOfLife::printA2()
{
  for(int i=0;i<m_herizontal;i++)
  {
    for(int j=0;j<m_vertical;j++)
    {
      cout<<m_Array2[i][j]<<" ";
    }
    cout<<"\n";
  }
}
//check the whole grid with the classic mode
void GameOfLife::checkCla()
{
  m_Array2 = new int *[m_herizontal];
  for(int i = 0;i<m_herizontal;i++)
  {
    m_Array2[i] = new int[m_vertical];
  }
  for(int i=0;i<m_herizontal;i++)
  {
    for(int j=0;j<m_vertical;j++)
    {
      int count = 0;
      if(i<m_herizontal-1)
      {
        if(m_Array[i+1][j]!=0)
        {
          count++;
        }
        if(j<m_vertical-1)
        {
          if(m_Array[i+1][j+1]!=0)
          {
            count++;
          }
        }
        if(j>0)
        {
          if(m_Array[i+1][j-1]!=0)
          {
            count++;
          }
        }
      }
      if(i>0)
      {
        if(m_Array[i-1][j]!=0)
        {
          count++;
        }
        if(j<m_vertical-1)
        {
          if(m_Array[i-1][j+1]!=0)
          {
            count++;
          }
        }
        if(j>0)
        {
          if(m_Array[i-1][j-1]!=0)
          {
            count++;

          }
        }
      }
      if(j<m_vertical-1)
      {
        if(m_Array[i][j+1]!=0)
        {
          count++;
        }
      }
      if(j>0)
      {
        if(m_Array[i][j-1]!=0)
        {
          count++;
        }
      }
      m_Array2[i][j]=count;
    }
  }
}
//check the whole grid with the doughnut mode
void GameOfLife::checkDou()
{
  m_Array2 = new int *[m_herizontal];
  for(int i = 0;i<m_herizontal;i++)
  {
    m_Array2[i] = new int[m_vertical];
  }
  int nRow = m_herizontal-1;
  int nCol = m_vertical-1;
  for(int i=0;i<m_herizontal;i++)
  {
    for(int j=0;j<m_vertical;j++)
    {
      int count = 0;
      //if the first row, check the last row
      if(i==0)
      {
        if(m_Array[nRow][j]!=0)
        {
          count++;
        }
        //corner 0,nCol
        if(j==nCol)
        {
          if(m_Array[nRow][0]!=0)
          {
            count++;
          }
        }
        else
        {
          if(m_Array[nRow][j+1]!=0)
          {
            count++;
          }
        }

        //corner 0,0
        if(j==0)
        {
          if(m_Array[nRow][nCol]!=0)
          {
            count++;
          }
        }
        else
        {
          if(m_Array[nRow][j-1]!=0)
          {
            count++;
          }
        }
      }
      if(i==nRow)
      {
        if(m_Array[0][j]!=0)
        {
          count++;
        }
        //corner nRow,0
        if(j==0)
        {
          if(m_Array[0][nCol]!=0)
          {
            count++;
          }
        }
        else
        {
          if(m_Array[0][j-1]!=0)
          {
            count++;
          }
        }
        //corner nrow,ncol
        if(j==nCol)
        {
          if(m_Array[0][0]!=0)
          {
            count++;
          }
        }
        else
        {
          if(m_Array[0][j+1]!=0)
          {
            count++;
          }
        }
      }
      //first column, check the last coloumn
      if(j==0)
      {
        //left
        if(m_Array[i][nCol]!=0)
        {
          count++;
        }
        if(i!=nRow)
        {
          if(m_Array[i+1][nCol]!=0)
          {
            count++;
          }
        }
        if(i!=0)
        {
          if(m_Array[i-1][nCol]!=0)
          {
            count++;
          }
        }
      }
      //last coloumn, check first coloumn
      if(j==nCol)
      {
        if(m_Array[i][0]!=0)
        {
          count++;
        }
        if(i!=nRow)
        {
          if(m_Array[i+1][0]!=0)
          {
            count++;
          }
        }
        if(i!=0)
        {
          if(m_Array[i-1][0]!=0)
          {
            count++;
          }
        }
      }
      if(i<nRow)
      {
        if(m_Array[i+1][j]!=0)
        {
          count++;
        }
        if(j<nCol)
        {
          if(m_Array[i+1][j+1]!=0)
          {
            count++;
          }
        }
        if(j>0)
        {
          if(m_Array[i+1][j-1]!=0)
          {
            count++;
          }
        }
      }
      if(i>0)
      {
        if(m_Array[i-1][j]!=0)
        {
          count++;
        }
        if(j<nCol)
        {
          if(m_Array[i-1][j+1]!=0)
          {
            count++;
          }
        }
        //not the first column, check left-down
        if(j>0)
        {
          if(m_Array[i-1][j-1]!=0)
          {
            count++;

          }
        }
      }
      //not the last column, check right
      if(j<nCol)
      {
        if(m_Array[i][j+1]!=0)
        {
          count++;
        }
      }
      //not the first column, check left
      if(j>0)
      {
        if(m_Array[i][j-1]!=0)
        {
          count++;
        }
      }
      //cout<<count<<" ..";
      m_Array2[i][j]=count;
    }
    //cout<<"\n";
  }
}
//check the whole grid with the mirror mode
void GameOfLife::checkMir()
{
  m_Array2 = new int *[m_herizontal];
  for(int i = 0;i<m_herizontal;i++)
  {
    m_Array2[i] = new int[m_vertical];
  }

  for(int i=0;i<m_herizontal;i++)
  {
    for(int j=0;j<m_vertical;j++)
    {
      int count = 0;
      int nRow = m_herizontal-1;
      int nCol = m_vertical-1;
      //top row
      if(i==0)
      {
        if(m_Array[i][j]!=0)
        {
          count++;
        }
        if(j==0)
        {
          if(m_Array[0][0]!=0)
          {
            //-
            count++;
          }
        }
        else if(j==nCol)
        {
          if(m_Array[0][nCol]!=0)
          {
            count++;
          }
        }
        if(j!=nCol)
        {
          if(m_Array[i][j+1]!=0)
          {
            count++;
          }
        }
        if(j!=0)
        {
          if(m_Array[i][j-1]!=0)
          {
            count++;
          }
        }
      }
      //last row
      if(i==nRow)
      {
        if(m_Array[nRow][j]!=0)
        {
          count++;
        }
        if(j==0)
        {
          if(m_Array[nRow][0]!=0)
          {
            count++;
          }
        }
        else if(j==nCol)
        {
          if(m_Array[nRow][nCol]!=0)
          {
            count++;
          }
        }
        //not the last column
        if(j!=nCol)
        {

          if(m_Array[i][j+1]!=0)
          {
            count++;
          }
        }
        if(i!=0)
        {
          if(m_Array[i][j-1]!=0)
          {

            count++;
          }
        }
      }
      //first column
      if(j==0)
      {
        if(m_Array[i][j]!=0)
        {
          count++;
        }
        if(i!=0)
        {
          if(m_Array[i-1][j]!=0)
          {
            count++;
          }
        }
        if(i!=nRow)
        {
          if(m_Array[i+1][j]!=0)
          {
            count++;
          }
        }
      }

      //last column
      if(j==nCol)
      {
        //cout<<m_Array[i-1][j]<<endl;
        if(m_Array[i][j]!=0)
        {

          count++;
        }
        if(i!=0)
        {
          if(m_Array[i-1][j]!=0)
          {

            count++;
          }
        }

        if(i!=nRow)
        {
          if(m_Array[i+1][j]!=0)
          {

            count++;
          }
        }
      }
      if(i<nRow)
      {
        if(m_Array[i+1][j]!=0)
        {

          count++;
        }
        if(j<nCol)
        {
          if(m_Array[i+1][j+1]!=0)
          {
            count++;
          }
        }
        if(j>0)
        {
          if(m_Array[i+1][j-1]!=0)
          {
            count++;
          }
        }
      }
      if(i>0)
      {
        if(m_Array[i-1][j]!=0)
        {
          count++;
        }
        if(j<nCol)
        {
          if(m_Array[i-1][j+1]!=0)
          {
            count++;
          }
        }
        if(j>0)
        {
          if(m_Array[i-1][j-1]!=0)
          {
            count++;

          }
        }
      }
      if(j<nCol)
      {
        if(m_Array[i][j+1]!=0)
        {
          count++;
        }
      }
      if(j>0)
      {
        if(m_Array[i][j-1]!=0)
        {
          count++;
        }
      }
      m_Array2[i][j]=count;
    }
  }
}
