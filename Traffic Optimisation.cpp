
//Will be updated as I add functions
/* To do
1.> Function to add roads, update action list
2.>Function to add buildings, update action list
3.>Function to check if its a valid map (no buildings with no road access)
4.>Function to automate mapping (add roads, buildings until Map is filled)
5.>Function to check fitness, update best fitness
*/

#include <iostream>
#include <stdlib.h>
#include <graphics.h>
#include <windows.h>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()

using namespace std;

int Map[5][5];
char Actions[25]; //The actions list
int actCount=0;
int BestActions[25];//The best actions list at current
int BestFitness;//Best current fitness score
char Child[25];
int ComputeTraffic(int x, int y) //don't panic
{
    int traffic=1;
    if(x==0||x==5||y==0||y==5)//edge or corner tile
    {
        if(x==0&&y==0)//top left corner
        {
            for(int i=0;i<1;i++)//cover all 3 adjacent tiles
            {
                for(int j=0;j<1;j++)
                {
                    if(Map[x+i][y+j]==-1)
                    traffic++; //add traffic if there are houses adjacent
                }
            }
           return traffic;
        }

        if(x==0&&y==5)//top right corner
        {
            for(int i=-1;i<0;i++)//cover all 3 adjacent tiles
            {
                for(int j=0;j<1;j++)
                {
                    if(Map[x+i][y+j]==-1)
                    traffic++; //add traffic if there are houses adjacent
                }
            }
            return traffic;
        }

        if(x==5&&y==0)//bottom left corner
        {
            for(int i=0;i<1;i++)//cover all 3 adjacent tiles
            {
                for(int j=-1;j<0;j++)
                {
                    if(Map[x+i][y+j]==-1)
                    traffic++; //add traffic if there are houses adjacent
                }
            }
           return traffic;
        }

         if(x==5&&y==5)//bottom right corner
        {
            for(int i=-1;i<0;i++)//cover all 3 adjacent tiles
            {
                for(int j=-1;j<0;j++)
                {
                    if(Map[x+i][y+j]==-1)
                    traffic++; //add traffic if there are houses adjacent
                }
            }
            return traffic;
        }
        if(x==0)//left edge
        {
            for(int i=0;i<1;i++)//cover all 5 adjacent tiles
            {
                for(int j=-1;j<1;j++)
                {
                    if(Map[x+i][y+j]==-1)
                    traffic++; //add traffic if there are houses adjacent
                }
            }
            return traffic;
        }
        if(y=0)//top edge
        {
            for(int i=-1;i<1;i++)//cover all 5 adjacent tiles
            {
                for(int j=0;j<1;j++)
                {
                    if(Map[x+i][y+j]==-1)
                    traffic++; //add traffic if there are houses adjacent
                }
            }
          return traffic;
        }
        if(y=5)//bottom edge
        {
            for(int i=-1;i<1;i++)//cover all 3 adjacent tiles
            {
                for(int j=-1;j<0;j++)
                {
                    if(Map[x+i][y+j]==-1)
                    traffic++; //add traffic if there are houses adjacent
                }
            }
            return traffic;
        }
        if(x=5)//right edge
        {
            for(int i=-1;i<0;i++)//cover all 3 adjacent tiles
            {
                for(int j=-1;j<1;j++)
                {
                    if(Map[x+i][y+j]==-1)
                    traffic++; //add traffic if there are houses adjacent
                }
            }
           return traffic;
        }

    }
    else//not a edge or corner tile
    {
        for(int i=-1;i<1;i++)//cover all 8 adjacent tiles
        {    for(int j=-1;j<1;j++)
            {
                if(Map[x+i][y+j]==-1)
                    traffic++; //add traffic if there are houses adjacent
            }
        }
    }

    return traffic;
}

void AddRoads(int x, int y, int traffic,int Map[5][5]) //Add roads and compute traffic change in adjacent tiles
{
    if(Map[x][y]==-2)//Empty slot
    {
        Map[x][y]=traffic;
        Actions[actCount]='R';
        actCount++;

    }
}

void AddHouses(int x,int y,int Map[5][5])
{if(Map[x][y]==-2)//Empty slot
    {
        Map[x][y]=-1;
        Actions[actCount]='H';
        actCount++;

    }
}

int CheckFitness()
{
    int sum=0, ccount=0;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(!isalpha(Map[i][j]))
            {
                sum+=Map[i][j];
                ccount++;
            }
        }
    }
    int fitness=sum/ccount;
    return fitness;
}

void GenAnc()
{
    int randc,i=0,j=0;
    while(actCount<25)
    {

        randc=rand()%2;
        if(randc==0)
        {
            AddHouses(i,j,Map);
        }
        else
        {

            AddRoads(i,j,ComputeTraffic(i,j),Map);
        }
        if(j<5)
        j++;
        else
        {
            i++;
            j=0;
        }
    }
}

void PrintMap()
{
    for(int i=0;i<5;i++)
    {
        cout<<endl;
        for(int j=0;j<5;j++)
            cout<<Map[i][j]<<" ";
    }

    cout<<endl;
}

void Cross(char A[])
{
    int randc;

    for(int i=0;i<25;i++)
    {
        randc=rand()%2;
        if(randc==0)
            Child[i]=A[i];
        else
            if(A[i]=='R')
            {
                Child[i]='H';
            }
            else
            {
                Child[i]='R';
            }
    }
}

void GenChild(char Child[],int Map[5][5])
{
    int i=0,j=0,Count=0;
    while(Count<29)
    {

        if(Child[Count]=='H')
        {
            Map[i][j]=-1;
            Count++;
        }
        else
        {

            Map[i][j]=ComputeTraffic(i,j);
            Count++;
        }
        if(j<5)
        j++;
        else
        {
            i++;
            j=0;
        }
    }
}

void displayColorMatrix(int a[5][5]){
    int x=30,y=30;
    initwindow(1000,800);
        cleardevice();
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                switch(a[i][j]){
                case -1:
                    setcolor(BLUE);
                    setfillstyle(SOLID_FILL,BLUE);
                    rectangle(x,y,x+20,y+20);
                    floodfill(x+10,y+10,BLUE);
                    //Sleep(2000);
                break;
                case 0:
                    setcolor(WHITE);
                    setfillstyle(SOLID_FILL,WHITE);
                    rectangle(x,y,x+20,y+20);
                    floodfill(x+10,y+10,WHITE);
                    //Sleep(2000);
                break;
                case 1:
                    setcolor(LIGHTCYAN);
                    setfillstyle(SOLID_FILL,LIGHTCYAN);
                    rectangle(x,y,x+20,y+20);
                    floodfill(x+10,y+10,LIGHTCYAN);
                    //Sleep(2000);
                break;
                case 2:
                    setcolor(YELLOW);
                    setfillstyle(SOLID_FILL,YELLOW);
                    rectangle(x,y,x+20,y+20);
                    floodfill(x+10,y+10,YELLOW);
                    //Sleep(2000);
                break;
                case 3:
                    setcolor(CYAN);
                    setfillstyle(SOLID_FILL,CYAN);
                    rectangle(x,y,x+20,y+20);
                    floodfill(x+10,y+10,CYAN);
                    //Sleep(2000);
                break;
                case 4:
                    setcolor(LIGHTGREEN);
                    setfillstyle(SOLID_FILL,LIGHTGREEN);
                    rectangle(x,y,x+20,y+20);
                    floodfill(x+10,y+10,LIGHTGREEN);
                    //Sleep(2000);
                break;
                case 5:
                    setcolor(GREEN);
                    setfillstyle(SOLID_FILL,GREEN);
                    rectangle(x,y,x+20,y+20);
                    floodfill(x+10,y+10,GREEN);
                    //Sleep(2000);
                break;
                case 6:
                    setcolor(LIGHTMAGENTA);
                    setfillstyle(SOLID_FILL,LIGHTMAGENTA);
                    rectangle(x,y,x+20,y+20);
                    floodfill(x+10,y+10,LIGHTMAGENTA);
                    //Sleep(2000);
                break;
                case 7:
                    setcolor(MAGENTA);
                    setfillstyle(SOLID_FILL,MAGENTA);
                    rectangle(x,y,x+20,y+20);
                    floodfill(x+10,y+10,MAGENTA);
                    //Sleep(2000);
                break;
                case 8:
                    setcolor(LIGHTRED);
                    setfillstyle(SOLID_FILL,LIGHTRED);
                    rectangle(x,y,x+20,y+20);
                    floodfill(x+10,y+10,LIGHTRED);
                    //Sleep(2000);
                break;
                case 9:
                    setcolor(RED);
                    setfillstyle(SOLID_FILL,RED);
                    rectangle(x,y,x+20,y+20);
                    floodfill(x+10,y+10,RED);
                break;
                default:
                    setcolor(DARKGRAY);
                    setfillstyle(SOLID_FILL,DARKGRAY);
                    rectangle(x,y,x+20,y+20);
                    floodfill(x+10,y+10,DARKGRAY);
                }
                x+=30;
            }
            x=30;
            y+=30;
        }
    getch();
}



int main()
{
    int Map2[5][5];
    srand(time(0));
    int fitness1,fitness2,fitness3;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
             Map[i][j]=-2;
             Map2[i][j]=-2;
        }
    }
    GenAnc();
    PrintMap();
    fitness1=CheckFitness();
    GenAnc();
    PrintMap();
    fitness2=CheckFitness();
    for(int i=0;i<25;i++)
        cout<<Actions[i]<<" ";
    cout<<endl;
    Cross(Actions);
    for(int i=0;i<25;i++)
        cout<<Child[i]<<" ";
    cout<<endl;
    GenChild(Child,Map2);

    cout<<endl;
    displayColorMatrix(Map);
    displayColorMatrix(Map2);

    return 0;
}



