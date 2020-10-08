//Jane Yang
//2317614
//huayang@chapman.edu
//CPSC350-01
//Assignment 2
#include "GameOfLife.h"

using namespace std;
int main(int argc,char** argv)
{
  char answer;
  int genNum = 0;
  //initialize game
  GameOfLife *game = new GameOfLife();
  int **gameArray;
  cout<<"Would you like to provide a map file? 'y' or 'n'?"<<endl;
  cin>>answer;
  //input file
  if(answer=='y'||answer=='Y')
  {
    cout<<"Please enter the file: "<<endl;
    std::string filePath;
    cin>>filePath;
    game->readNum(filePath);
  }

  //randomize the boundry
  else
  {
    game->randomGrid();
    cout<<"Grid Size: "<<game->getHerizontal()<<" "<<game->getVertical()<<endl;
    cout<<"Population Density: "<<game->getDensity()<<endl;
  }
  cout<<"What is the game mode you want to choose? 'classic','doughnut','mirror':"<<endl;
  string answerMode;
  cin>>answerMode;
  //convert answer to lower case
  std::transform(answerMode.begin(),answerMode.end(),answerMode.begin(),::tolower);
  string answerPause;
  cout<<"Would you like brief pasud, press 'enter' for next generation, or output to a file? 'pause','enter','file':"<<endl;
  cin>>answerPause;
  std::transform(answerPause.begin(),answerPause.end(),answerPause.begin(),::tolower);
  int generation =0;
  game->creat2();
  game->creat3();
  //check if the user want to hit enter
  if(answerPause.find('e')!=std::string::npos)
  {
    while(true)
    {
      cout<<"Current Generation: "<<generation<<endl;
      game->printGrid();
      if(answerMode.find('c')!=std::string::npos)
      {
        cout<<"Classic Mode"<<endl;
        game->checkCla();
        game->printA2();
      }
      //doughnut mode
      else if(answerMode.find('d')!=std::string::npos)
      {
        cout<<"Doughnut Mode"<<endl;
        game->checkDou();

      }
      //mirror mode
      else if(answerMode.find('m')!=std::string::npos)
      {
        cout<<"Mirror Mode"<<endl;
        game->checkMir();
      }
      game->copyA();

      game->rule();

      //game->printA();
      //game->printGrid();
      if(game->isEmpty())
      {
        cout<<"The final grid"<<endl;
        game->printGrid();
        cout<<"Grid is empty, Game Over"<<endl;
        break;
      }
      if(game->isFull())
      {
        cout<<"The final grid"<<endl;
        game->printGrid();
        cout<<"Grid is full, Game Over"<<endl;
        break;
      }
      if(game->stable())
      {
        cout<<"The final grid"<<endl;
        game->printGrid();
        cout<<"Grid is stable, Game Over"<<endl;
        break;
      }
      generation++;
      cout<<"Press Enter to Continue: "<<endl;
      cin.ignore();
    }
  }
  //output to a file
  if(answerPause.find('f')!=std::string::npos)
  {
    std::string answerFile;
    cout<<"Enter the file name you want to print output: "<<endl;
    cin>>answerFile;
    ofstream out;
    out.open(answerFile);
    while(true)
    {
      out<<"Generation: "<<generation<<endl;
      for(int i=0;i<game->getHerizontal();i++)
      {
        for(int j=0;j<game->getVertical();j++)
        {

          if(game->returnCell(i,j)==0)
          {
            out<<'-'<<" ";
          }
          else
          {
            out<<'x'<<" ";
          }
        }
        out<<"\n";
      }
      if(answerMode.find('c')!=std::string::npos)
      {
        out<<"Classic Mode"<<endl;
        game->checkCla();
        for(int i=0;i<game->getHerizontal();i++)
        {
          for(int j=0;j<game->getVertical();j++)
          {
            out<<game->returnCell(i,j)<<" ";
          }
          out<<"\n";
        }
      }
      //doughnut mode
      else if(answerMode.find('d')!=std::string::npos)
      {
        out<<"Doughnut Mode"<<endl;
        game->checkDou();
        //game->printGrid();
      }
      //mirror mode
      else if(answerMode.find('m')!=std::string::npos)
      {
        out<<"Mirror Mode"<<endl;
        game->checkMir();
      }
      game->copyA();
      game->rule();
      if(game->isEmpty())
      {
        out<<"The final grid"<<endl;
        for(int i=0;i<game->getHerizontal();i++)
        {
          for(int j=0;j<game->getVertical();j++)
          {

            if(game->returnCell(i,j)==0)
            {
              out<<'-'<<" ";
            }
            else
            {
              out<<'x'<<" ";
            }
          }
          out<<"\n";
        }
        out<<"Grid is empty, Game Over"<<endl;
        break;
      }
      if(game->isFull())
      {
        out<<"The final grid"<<endl;
        for(int i=0;i<game->getHerizontal();i++)
        {
          for(int j=0;j<game->getVertical();j++)
          {

            if(game->returnCell(i,j)==0)
            {
              out<<'-'<<" ";
            }
            else
            {
              out<<'x'<<" ";
            }
          }
          out<<"\n";
        }
        out<<"Grid is full, Game Over"<<endl;
        break;
      }
      if(game->stable())
      {
        out<<"The final grid"<<endl;
        for(int i=0;i<game->getHerizontal();i++)
        {
          for(int j=0;j<game->getVertical();j++)
          {

            if(game->returnCell(i,j)==0)
            {
              out<<'-'<<" ";
            }
            else
            {
              out<<'x'<<" ";
            }
          }
          out<<"\n";
        }
        out<<"Grid is stable, Game Over"<<endl;
        break;
      }
      generation++;
    }
    out.close();
    cout<<"output is on your file now!"<<endl;
  }
  //pause for x seconds
  if(answerPause.find('p')!=std::string::npos)
  {
    cout<<"how many seconds do you want to pause bwteen each generation?: "<<endl;
    string second;
    cin>>second;
    while(true)
    {
      cout<<"Current Generation: "<<generation<<endl;
      game->printGrid();
      if(answerMode.find('c')!=std::string::npos)
      {

        cout<<"Classic Mode"<<endl;
        game->checkCla();

      }
      //doughnut mode
      else if(answerMode.find('d')!=std::string::npos)
      {
        cout<<"Doughnut Mode"<<endl;
        game->checkDou();
        //game->printGrid();
      }
      //mirror mode
      else if(answerMode.find('m')!=std::string::npos)
      {
        cout<<"Mirror Mode"<<endl;
        game->checkMir();
      }
      game->copyA();

      game->rule();

      //game->printA();
      //game->printGrid();
      if(game->isEmpty())
      {
        cout<<"The final grid"<<endl;
        game->printGrid();
        cout<<"Grid is empty, Game Over"<<endl;
        break;
      }
      if(game->isFull())
      {
        cout<<"The final grid"<<endl;
        game->printGrid();
        cout<<"Grid is full, Game Over"<<endl;
        break;
      }
      if(game->stable())
      {
        cout<<"The final grid"<<endl;
        game->printGrid();
        cout<<"Grid is stable, Game Over"<<endl;
        break;
      }
      generation++;
      std::this_thread::sleep_for(std::chrono::seconds(stoi(second)));
    }
  }
  return 0;
}
