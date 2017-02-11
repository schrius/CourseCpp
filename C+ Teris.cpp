#include<windows.h>
#include<iostream>
#include<ctime>
#include<conio.h>
#include<cstdlib>
using namespace std;

int speed; // block speed
/*****************************************
*Class function                          *
******************************************/

class Teris
{
private:
    int board[23][23];   //interface
    int block[7][4][4];   //block shape
    int CurrentX;     //coordinate X Y
    int CurrentY;
    int Nowblock[4][4]; 
    int formblock; //form block
    bool IO; 
    int score;//score
    int Lines; // record eliminate lines
public:
    Teris();   //constructor
    void Transform(); //form blockk
    void Printframe(); //initial
    void Coordinate(int x,int y);
    void Print(); 
    void blockPrint();

    int test(int,int); 
    void change();
    int Down(); 
    int Dropblock();
    void delblock();
    void Newblock();    
	void Nextblock();
	void random();

    bool IR(); 
    int Key(); 
    void Move(int);
    int LineFull();
    void Gamestart();
    void Tend();
};

Teris::Teris()
{

    score = 0;
    Lines = 0;
    srand(time(0));
    IO = true;
    for(int i = 0 ; i < 23 ;i++)
    {
        for(int j = 0 ; j < 23 ; j++)
        {
            if(i==0 || i==22|| j==0 || j==12 || j==22 )
             board[i][j]=1;
            else
             board[i][j]=0;
        }
    }
    
    int shapeblock[7][4][4]=
    {  {{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}}, //  I
    
	   {{0,0,0,0},{0,1,0,0},{1,1,1,0},{0,0,0,0}}, //  T
	   
       {{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}}, //  Z
       
       {{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}}, //  S
       
       {{0,1,1,0},{0,0,1,0},{0,0,1,0},{0,0,0,0}}, //  L
       
       {{0,1,1,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}}, //  J
       
       {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}}  //  O
    };
    
    for(int i = 0 ; i < 7 ; i++)
    {
        for(int i2 = 0 ; i2 < 4 ;i2++)
        {
            for(int i3 = 0 ; i3 < 4 ;i3++)
                block[i][i2][i3] = shapeblock[i][i2][i3];
        }
    }
  random();
  Transform();
}

bool Teris::IR()
{
    return IO;
}

void Teris::Transform()
{
   
    for(int i = 0 ; i < 4 ; i++)
        for(int i2=0; i2<4; i2++)
            Nowblock[i][i2]=block[formblock][i][i2];
}

//initialize
void Teris::Printframe()
{
    
       for(int i = 0 ; i < 23 ;i++)
    {
        for(int j = 0 ; j < 23 ;j++)
        {
            switch(board[i][j])
            {
            case 0:
                cout<<"  ";
                break;
            default:
                cout<<"¡ö";
            }
            
        }
        cout<<endl;
    }
    Coordinate(26,2);
    cout<<"LV£º"<<speed;
    Coordinate(26,4);
    cout<<"Score: ";
    Coordinate(26,6);
    cout<<"Next£º";
    Coordinate(26,12);
    cout<<" ¡üChange ¡ýDrop";
    Coordinate(26,14);
    cout<<" ¡û Left";
    Coordinate(26,16);
    cout<<" ¡ú Right";
    Coordinate(26,18);
    cout<<"Space to Pause";
    Coordinate(26,20);
    cout<<"Press ESC to Exit";
    Dropblock();
    random();
    Nextblock();
}

void Teris::Nextblock()
{
    for(int n = 0; n < 4; n++)
    {
        Coordinate(28,7+n);
        for(int n2 = 0 ; n2 < 4; n2++)
        {
        	if(block[formblock][n][n2]==0)
        	cout<<"  ";
        	else cout<<"¡ö";
        }
    }
}

//Coordinate position
void Teris::Coordinate(int x,int y)  
{
     COORD pos = {x,y};   
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);   
} 


void Teris::random()
{
    formblock =rand()%7;

}

//check the block if it fits
int Teris::test(int NX,int NY)   
{
    
    for(int T1 = 0 ; T1 < 4; T1++)
    {
        for(int T2 = 0 ; T2 < 4 ; T2++)
        {
		if(Nowblock[T1][T2]&&board[T1+NY][T2+(NX)/2])
        return 0;
		}
    
    }
         return 1;
}

//check next block
int Teris::Dropblock()
{
  CurrentX=10;CurrentY=1;
  if(test(CurrentX,CurrentY))
  {
   CurrentY=0;
   blockPrint();
   return 1;
  }
  return 0;
}

//fall
int Teris::Down() 
{ 
    int NewY;
    NewY = CurrentY + 1;
    if((test(CurrentX,NewY)))
    {   
        delblock(); 
        CurrentY = NewY;
		blockPrint();
        return 1; 
    } 
    Newblock();
    return 0;
}

//display block
void Teris::blockPrint()
{
  for(int bp = 0; bp < 4; bp++)
  {
   for(int bp2 = 0; bp2 < 4; bp2++)
   {
     if(Nowblock[bp][bp2])
     {
         if(CurrentY+bp>0)
         {
		 Coordinate(CurrentX+bp2*2,CurrentY+bp);
         cout<<"¡ö";
		 }
     }
   }
  }
}

//eliminate line
void Teris::delblock()
{
  
  for(int DB = 0 ; DB < 4; DB++)
  {
   for(int DB2 = 0 ; DB2 < 4 ; DB2++)
   {
     if(Nowblock[DB][DB2])
     {
         if(CurrentY+DB>0)
         {
		 Coordinate(CurrentX+DB2*2,CurrentY+DB);
         cout<<"  ";
		 }
     }
   }
  }
}

//new block
void Teris::Newblock()
{
  for(int NB = 0 ; NB < 4; NB++)
  {
   for(int NB2 = 0 ; NB2 < 4 ;NB2++)
   {
     if(Nowblock[NB][NB2])
         board[NB+CurrentY][NB2+(CurrentX)/2] = Nowblock[NB][NB2];
   }
  }
  LineFull();
  Transform();
  random();
  Nextblock();
  
  if(Dropblock()==0)
  {
  IO=false;
  }

}

//receive key 72 up, 75 left, 77 right, 80 down,  27 ESC
int Teris::Key()
{
    int k;
    if(kbhit())
    {
        k = getch();
        return k;
    }
    return 0;
}

//move left and right
void Teris::Move(int NX)
{
    int NewX;
    if(NX == 1)
    NewX = CurrentX-2;
    else NewX = CurrentX+2;

    if(test(NewX,CurrentY))
    {  
        delblock();
        CurrentX = NewX; 
		blockPrint();
     
    } 
}

//change shape
void Teris::change()
{
    int change[4][4];
    
    for(int ch = 0; ch < 4; ch++)
     for(int ch2 = 0 ; ch2 < 4; ch2++)
         change[ch][ch2] = Nowblock[ch2][3-ch];
     
    int che = 1; 
    for(int che1 = 0; che1 < 4; che1++)
    {
        for(int che2 = 0 ; che2 < 4; che2++)
            if(change[che1][che2]&&board[che1+CurrentY][che2+CurrentX/2])
            {
			che=0;
			break;
			}
            
    }
    
    if(che)
      {
        delblock();
       for(int cha = 0 ; cha < 4; cha++)
        for(int cha2 = 0 ; cha2 < 4; cha2++)
         Nowblock[cha][cha2]= change[cha][cha2];

         blockPrint();
      }
}



int Teris::LineFull()  //check lines if full
{
    int multiple = 0; //record score, times score if eliminate more than 1
    for(int MFy=1;MFy<22;MFy++) // line
    {
        int full=1;  // line full
        for(int MFx=1;MFx<12;MFx++)
            if(board[MFy][MFx]==0)
            {
			full=0;
			break;
			}

        if(full)
        {
            multiple +=1 ;
            for(int NFy = MFy; NFy > 0; NFy--)
            {
                Coordinate(2,NFy);
                for(int NFx =1 ; NFx<12;NFx++)
                {
                    if(NFy>1)
                       board[NFy][NFx]=board[NFy-1][NFx];
                    else
                        board[NFy][NFx]=0;

                  if(board[NFy][NFx])
                    cout<<"¡ö";
                  else
                    cout<<"  ";
                }
            }
        }      
    }
    if(multiple>0)
    {
    score =  score+10*multiple*multiple; // get score
    
    Coordinate(35,4);
	cout<<score;
    Lines += multiple;
    
    if(Lines>=30 && Lines % 30 ==0 && speed<11)
    {
        speed += 1;
        Coordinate(36,2);
		cout<<speed;
    }
	}
return 0;
}

void Teris::Tend()
{
	char again;
    Coordinate(0,0);
int over[23][30]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1,0,1,1,1,1,1,0,1,0,0,0,0,0,1},
    {1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,1,0,0,1,1,1,0,0,1,0,1,1,1,1,1},
    {1,0,1,1,1,1,1,1,1,0,1,1,1,1,0,1,0,1,0,0,0,1,0,1,0,1,1,1,1,1},
    {1,0,1,1,1,0,0,0,1,0,1,1,1,1,0,1,0,1,1,0,1,1,0,1,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,0,1,0,0,0,0,0,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1},
    {1,1,0,1,1,1,0,1,1,0,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1},
    {1,1,1,0,0,0,1,1,1,0,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,0,0,0,1,1,1,0,1,1,1,1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,1},
    {1,1,0,1,1,1,0,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
    {1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
    {1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,1},
    {1,0,1,1,1,1,1,0,1,1,0,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1},
    {1,1,0,1,1,1,0,1,1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
    {1,1,1,0,0,0,1,1,1,1,1,1,0,1,1,1,1,0,0,0,0,0,1,0,1,1,1,1,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};
	HANDLE SCon;
	SCon=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(SCon,12);
	for(int e1 = 0; e1 < 23; e1++)
	{
   	 for(int e2 = 0; e2 < 30; e2++)
 	   {
        if(over[e1][e2]==1)
            cout<<"¡ö";
        else
            cout<<"  ";
	    }
    cout<<"\n";
	}
	cout<<"Do You Want to Play Again?  Y/N";
	cin>>again;
	if(toupper(again)=='Y')
	return;
	else 
	exit(0);
}

void Teris::Gamestart()
{
	int Keyin;
	char quit;
    Printframe(); //initialize windows
    Coordinate(2,1);
    
    int finish = clock();
    int start=0;

    do
    {
     if(IR()==false)
         break;

     if((finish-start)>(550-50*speed)) 
     { 
      Down();     
      start = finish; 
     }
      finish = clock();
      
    Keyin = Key();
      if(Keyin)
      {
          switch(Keyin)
          {
          case 72:
             change();
			 break;
          case 75:
             Move(1);
			 break;
          case 77:
             Move(2);
			 break;
          case 80:
              Down();
			  break;
          case 27:
          	Coordinate(2,23);
          	cout<<"Do You Want To Exit ?  Y/N";
              cin>>quit;
              if(toupper(quit)=='Y')
              {
			  system("cls");
			  exit(0);
			  }
			  else 
			  {
			  Coordinate(2,23);
			  cout<<"\t\t\t\t\t\t\t\t\t\t";
              break;
          	  }
		  case 32:
              {
               Coordinate(2,23);
               system("pause");
               break;
              }
          }
      }
    }while(toupper(quit)!='Y');
    Tend();
}

/*****************************************
*main function                           *
******************************************/


int main()
{
	HANDLE hCon;
	hCon=GetStdHandle(STD_OUTPUT_HANDLE);
	
	int choice;
	Teris *Tris = 0;
	
	do
	{
	SetConsoleTextAttribute(hCon,3);
    cout<<"\n\n\n\t¨X¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨[\n";
    cout<<"\t¨U\t\4\4\4\4\4\4\4 \4\4\4\4\4\4 \4\4\4\4\4\4\4 \4\4\4\4\4\4    ¡ö  \4      \4\t¨U\n"
    	<<"\t¨U\t   \4    \4         \4    \4     \4   \4\4    \4  \4   \t¨U\n"
    	<<"\t¨U\t   \4    \4\4\4\4\4\4    \4    \4\4\4\4\4\4    \4\4     \4\4    \t¨U\n"
		<<"\t¨U\t   \4    \4         \4    \4     \4   \4\4    \4  \4   \t¨U\n"
		<<"\t¨U\t   \4    \4\4\4\4\4\4    \4    \4      \4  \4\4  \4      \4 \t¨U \n"
		<<"\t¨^¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨a\n"
        <<"\n\t\t\t\6 1. Play Game  \6\n"
		<<"\n\t\t\t\5 2. Quit       \5\n\n\t\t\t\1 ";
	cin>>choice;
	
	switch(choice)
	{
		case 1: {
		cout<<"\n\t\t\2  Please Enter Game Level 1-10 \n\t\t   The Higher Value the Faster speed\n\t\t\6  ";
		cin>>speed;
		while(speed>10||speed<1)
		{
			cin.clear();
			cout<<"\t\tInvalid Speed\n";
			main();
		}
		Tris = new Teris;
		system("cls");
		SetConsoleTextAttribute(hCon,8);
		Tris->Gamestart();
		break;
	}
		case 2:{exit(0);
			break;
		}
		default : cout<<"\n\t\nInvalid choice.\n";
		main();
		break;
	}
    system("cls");
    delete Tris;
    Tris = 0;
    }while(choice!=2);

return 0;
}

