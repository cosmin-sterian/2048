#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include "dont_open_till_Christmas.h"
#include "menuanim.h"

#define WAIT 5

typedef struct table{
      int a[4][4];
      int scor;
} table;
typedef struct undo{
      int n;
      table *u;
} undo;

int aleator(int **a)
{
    int x,y,cap=0,i=0;
    for(x=0; x<4; x++)
        for(y=0; y<4; y++)
            if(a[x][y] == 0)
                cap++;
    if(cap==0)
        return 0;
    int **liber;
    liber = malloc(cap*sizeof(int *));
    for(x=0; x<cap; x++)
    {
        liber[x] = malloc(2*sizeof(int));
    }
    i=0;
    for(x=0; x<4; x++)
    {
        for(y=0; y<4; y++)
        {
            if(a[x][y]==0)
            {
                liber[i][0]=x;
                liber[i][1]=y;
                i++;
            }
        }
    }
    int n;
    srand(time(NULL));
    n=rand()%cap;
    x=liber[n][0];
    y=liber[n][1];
    if(n%7==0)
        a[x][y]=4;
    else
        a[x][y]=2;
    for(x=0; x<cap; x++)
        free(liber[x]);
    free(liber);
    return 1;
}

void newgame(int **a)
{
      int x,y;
      for(x=0;x<4;x++)
            for(y=0;y<4;y++)
                  a[x][y]=0;
      aleator(a);
      aleator(a);
}

int stanga(int **a, int *scor, int *cleared, int *check)
{
    int x, y, k=0, i;
    *cleared=0;
    for(x=0; x<4; x++)
    {
        y=3;
        while(a[x][y]==0 && y>=0)
            y--;
        while(y>=0)
        {
            if(a[x][y]==0)
            {
                for(i=y; i<3; i++)
                {
                    a[x][i]=a[x][i+1];
                    k=1;
                }
                a[x][3]=0;
            }
            y--;
        }
    }
    for(x=0; x<4; x++)
    {
        for(y=0; y<3; y++)
        {
            if(a[x][y]==a[x][y+1] && a[x][y]!=0)
            {
                a[x][y]=a[x][y]*2;
                if(*check==0)
                  *scor+=a[x][y];
                else
                  *cleared=*cleared+1;
                for(i=y+1; i<3; i++)
                {
                    a[x][i]=a[x][i+1];
                }
                k=1;
                a[x][3]=0;
            }
        }
    }
    return k;
}

void afisare(int **a, WINDOW *fereastra)
{
    //wclear(fereastra);
    start_color();
    int x,y,i,j,k;
    getmaxyx(fereastra,i,j);
    mvwprintw(fereastra,(i-4)/2-1,(j-7*4)/2-1,"+");
    mvwprintw(fereastra,(i-4)/2-1,(j-7*4)/2-1+7*4+1,"+");
    mvwprintw(fereastra,(i-4)/2-1+5,(j-7*4)/2-1,"+");
    mvwprintw(fereastra,(i-4)/2-1+5,(j-7*4)/2-1+7*4+1,"+");
    for(x=(i-4)/2; x<(i-4)/2-1+5; x++)
    {
        mvwprintw(fereastra,x,(j-7*4)/2-1,"|");
        mvwprintw(fereastra,x,(j-7*4)/2-1+7*4+1,"|");
    }
    for(x=(j-7*4)/2; x<(j-7*4)/2+7*4; x++)
    {
        mvwprintw(fereastra,(i-4)/2-1,x,"-");
        mvwprintw(fereastra,(i-4)/2-1+5,x,"-");
    }
    init_pair(1,COLOR_WHITE,COLOR_MAGENTA);
    init_pair(2,COLOR_WHITE,COLOR_BLUE);
    init_pair(3,COLOR_BLACK,COLOR_CYAN);
    init_pair(4,COLOR_BLACK,COLOR_GREEN);
    init_pair(5,COLOR_BLACK,COLOR_YELLOW);
    init_pair(6,COLOR_WHITE,COLOR_RED);

    init_pair(7,COLOR_YELLOW,COLOR_MAGENTA);
    init_pair(8,COLOR_YELLOW,COLOR_BLUE);
    init_pair(9,COLOR_BLUE,COLOR_CYAN);
    init_pair(10,COLOR_BLUE,COLOR_GREEN);
    init_pair(11,COLOR_BLUE,COLOR_YELLOW);
    init_pair(12,COLOR_YELLOW,COLOR_RED);

    init_pair(13,COLOR_GREEN,COLOR_MAGENTA);
    init_pair(14,COLOR_GREEN,COLOR_BLUE);
    init_pair(15,COLOR_RED,COLOR_CYAN);
    init_pair(16,COLOR_RED,COLOR_GREEN);
    init_pair(17,COLOR_RED,COLOR_YELLOW);
    init_pair(18,COLOR_GREEN,COLOR_RED);

    for(x=0; x<4; x++)
    {
        for(y=0; y<4; y++)
        {
            for(k=1; k<=18; k++)
            {
                if(a[x][y]==1<<k)
                {
                    wattron(fereastra,COLOR_PAIR(k) | A_BOLD);
                    mvwprintw(fereastra,(i-4)/2+x,(j-7*4)/2+7*y,"%7d",a[x][y]);
                    wattroff(fereastra,COLOR_PAIR(k) | A_BOLD);
                    break;
                }
            }
            wrefresh(fereastra);
        }
    }
    wrefresh(fereastra);
}

void rotire(int **a)
{
    int x, y, **b;
    b = calloc(4,sizeof(int *));
    for(x=0; x<4; x++)
        b[x] = calloc(4,sizeof(int));
    for(x=0; x<4; x++)
    {
        for(y=0; y<4; y++)
        {
            b[x][y]=a[3-y][x];
        }
    }
    for(x=0; x<4; x++)
    {
        for(y=0; y<4; y++)
        {
            a[x][y]=b[x][y];
        }
    }
    for(x=0; x<4; x++)
        free(b[x]);
    free(b);
}

int dreapta(int **a, int *scor, int *cleared, int *check)
{
    int n;
    rotire(a);
    rotire(a);
    n=stanga(a,scor,cleared,check);
    rotire(a);
    rotire(a);
    return n;
}

int jos(int **a, int *scor, int *cleared, int *check)
{
    int n;
    rotire(a);
    n=stanga(a,scor,cleared,check);
    rotire(a);
    rotire(a);
    rotire(a);
    return n;
}

int sus(int **a, int *scor, int *cleared, int *check)
{
    int n;
    rotire(a);
    rotire(a);
    rotire(a);
    n=stanga(a,scor,cleared,check);
    rotire(a);
    return n;
}

int checkwon(int **a)
{
    int i,j;
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
            if(a[i][j]==2048)
                return 1;
    }
    return 0;
}

void printcurrenttime(WINDOW *fereastra);

int printwon(WINDOW *fereastra, int **a)
{
    int x,y,maxy,maxx;
    getmaxyx(fereastra,maxy,maxx);
    for(x=1;x<=4;x++)
    {
          mvwprintw(fereastra,(maxy-4)/2-1+x,maxx-strlen("Ati ajuns la 2048! ")-2,"!");
          mvwprintw(fereastra,(maxy-4)/2-1+x,maxx-1,"!");
   }
   for(x=maxx-strlen("Ati ajuns la 2048! ")-1;x<maxx-1;x++)
   {
         mvwprintw(fereastra,(maxy-4)/2,x,"~");
         mvwprintw(fereastra,(maxy-4)/2+3,x,"~");
   }
   mvwprintw(fereastra,(maxy-4)/2+1,maxx-strlen("Ati ajuns la 2048! ")-1,"Ati ajuns la 2048!");
   mvwprintw(fereastra,(maxy-4)/2+2,maxx-strlen("Continuati? (D/N)")-2,"Continuati? (D/N)");
   wrefresh(fereastra);
   y=wgetch(fereastra);
   while(y!='d' && y!='n')
   {
         y=wgetch(fereastra);
         printcurrenttime(fereastra);
         wrefresh(fereastra);
   }
   if(y=='d')
   {
         return 1;
   }
   else
   {
      movealltomenu(fereastra);
      return 0;
      }
}

int checkover(int **a)
{
    int x,y,k=0;
    for(x=0; x<4; x++)
    {
        for(y=0; y<4; y++)
        {
            if(a[x][y]==0)
                k=1;
        }
    }
    for(x=0; x<4; x++)
        for(y=0; y<3; y++)
            if(a[x][y]==a[x][y+1])
                k=1;
    return k;
}

void printcurrenttime(WINDOW *fereastra)
{
      int maxx,i;
      getmaxyx(fereastra,i,maxx);
      mvwprintw(fereastra,4,(maxx-strlen("00/00/2016 - 00:00:00"))/2-2,"+");
      mvwprintw(fereastra,4,(maxx-strlen("00/00/2016 - 00:00:00"))/2+strlen("00/00/2016 - 00:00:00")+1,"+");
      mvwprintw(fereastra,7,(maxx-strlen("00/00/2016 - 00:00:00"))/2-2,"+");
      mvwprintw(fereastra,7,(maxx-strlen("00/00/2016 - 00:00:00"))/2+strlen("00/00/2016 - 00:00:00")+1,"+");
      for(i=5;i<=6;i++)
      {
            mvwprintw(fereastra,i,(maxx-strlen("00/00/2016 - 00:00:00"))/2-2,"|");
            mvwprintw(fereastra,i,(maxx-strlen("00/00/2016 - 00:00:00"))/2+strlen("00/00/2016 - 00:00:00")+1,"|");
      }
      for(i=(maxx-strlen("00/00/2016 - 00:00:00"))/2-1;i<(maxx-strlen("00/00/2016 - 00:00:00"))/2+strlen("00/00/2016 - 00:00:00")+1;i++)
      {
            mvwprintw(fereastra,4,i,"-");
            mvwprintw(fereastra,7,i,"-");
      }
      mvwprintw(fereastra,5,(maxx-strlen("DATA - ORA"))/2,"DATA - ORA");
      time_t timp;
      struct tm *timp_str;
      time(&timp);
      timp_str = localtime(&timp);
      mvwprintw(fereastra,6,(maxx-strlen("00/00/2016 - 00:00:00"))/2,"%2d/%02d/%4d - %02d:%02d:%02d",timp_str->tm_mday,timp_str->tm_mon+1,timp_str->tm_year+1900,timp_str->tm_hour,timp_str->tm_min,timp_str->tm_sec);
}

int printover(WINDOW *fereastra)
{
    int x,y,maxy,maxx;
    getmaxyx(fereastra,maxy,maxx);
    start_color();
    init_pair(21,COLOR_RED,COLOR_BLACK);
    wattron(fereastra,COLOR_PAIR(21));
    for(x=1;x<=8;x++)
    {
          mvwprintw(fereastra,(maxy-8)/2-1+x,maxx-strlen("Apasati Q pentru a")-4,"x");
          mvwprintw(fereastra,(maxy-8)/2-1+x,maxx-1,"x");
   }
   for(x=maxx-strlen("Apasati Q pentru a")-3;x<maxx-1;x++)
   {
         mvwprintw(fereastra,(maxy-8)/2,x,"x");
         mvwprintw(fereastra,(maxy-8)/2+7,x,"x");
   }
   mvwprintw(fereastra,(maxy-8)/2+1,maxx-strlen("GAME OVER!")-6,"GAME OVER!");
   mvwprintw(fereastra,(maxy-8)/2+2,maxx-strlen("Apasati Q pentru a")-2,"Apasati Q pentru a");
   mvwprintw(fereastra,(maxy-8)/2+3,maxx-strlen("reveni la")-7,"reveni la");
   mvwprintw(fereastra,(maxy-8)/2+4,maxx-strlen("meniul principal.")-2,"meniul principal,");
   mvwprintw(fereastra,(maxy-8)/2+5,maxx-strlen("sau U")-9,"sau U");
   mvwprintw(fereastra,(maxy-8)/2+6,maxx-strlen("pentru UNDO.")-5,"pentru UNDO.");
   wattroff(fereastra,COLOR_PAIR(21));
   wrefresh(fereastra);
   y=wgetch(fereastra);
   while(y!='q' && y!='u')
   {
         y=wgetch(fereastra);
         printcurrenttime(fereastra);
         wrefresh(fereastra);
   }
   return y;
}

void printscoreboard(WINDOW *fereastra, int *scor)
{
    int i,maxx;
    getmaxyx(fereastra,i,maxx);
    mvwprintw(fereastra,0,(maxx-14)/2-1,"+");
    mvwprintw(fereastra,0,(maxx-14)/2-1+14,"+");
    mvwprintw(fereastra,2,(maxx-14)/2-1,"+");
    mvwprintw(fereastra,2,(maxx-14)/2-1+14,"+");
    for(i=(maxx-14)/2; i<(maxx-14)/2-1+14; i++)
    {
        mvwprintw(fereastra,0,i,"-");
        mvwprintw(fereastra,2,i,"-");
    }
    mvwprintw(fereastra,1,(maxx-14)/2-1,"|");
    mvwprintw(fereastra,1,(maxx-14)/2-1+14,"|");
    mvwprintw(fereastra,1,(maxx-14)/2,"Scor: ");
    mvwprintw(fereastra,1,(maxx-14)/2+strlen("Scor: "),"%6d",*scor);
}

void copiere(int **a, int **b)
{
      int x,y;
      for(x=0;x<4;x++)
            for(y=0;y<4;y++)
                  b[x][y]=a[x][y];
}

int doauto(int **a, int *scor, int *cleared, int *check)
{
      int x,y=0,n=0,k=0,nf=0;
      *cleared=0;
      int **b=malloc(4*sizeof(int*));
      for(x=0;x<4;x++)
      {
            b[x]=malloc(4*sizeof(int));
      }
      copiere(a,b);
      *check=1;
      n=stanga(b,scor,cleared,check);
      if(n==1)
            nf=1;
      if(*cleared>k)
      {
            k=*cleared;
            y=1;
      }
      copiere(a,b);
      n=dreapta(b,scor,cleared,check);
      if(n==1)
            nf=1;
      if(*cleared>k)
      {
            k=*cleared;
            y=2;
      }
      copiere(a,b);
      n=sus(b,scor,cleared,check);
      if(n==1)
            nf=1;
      if(*cleared>k)
      {
            k=*cleared;
            y=3;
      }
      copiere(a,b);
      n=jos(b,scor,cleared,check);
      if(n==1)
            nf=1;
      if(*cleared>k)
      {
            k=*cleared;
            y=4;
      }
      *check=0;
      switch(y)
      {
            case 1:
                  stanga(a,scor,cleared,check);
                  break;
            case 2:
                  dreapta(a,scor,cleared,check);
                  break;
            case 3:
                  sus(a,scor,cleared,check);
                  break;
            case 4:
                  jos(a,scor,cleared,check);
                  break;
            default:
                  if(nf==1)
                  {
                        copiere(a,b);
                        if(stanga(b,scor,cleared,check)==1)
                        {
                              stanga(a,scor,cleared,check);
                              break;
                        }
                        copiere(a,b);
                        if(dreapta(b,scor,cleared,check)==1)
                        {
                              dreapta(a,scor,cleared,check);
                              break;
                        }
                        copiere(a,b);
                        if(sus(b,scor,cleared,check)==1)
                        {
                              sus(a,scor,cleared,check);
                              break;
                        }
                        copiere(a,b);
                        if(jos(b,scor,cleared,check)==1)
                        {
                              jos(a,scor,cleared,check);
                              break;
                        }
                  }
                  break;
      }
      for(x=0;x<4;x++)
            free(b[x]);
      free(b);
      return nf;
}

void printtimer(WINDOW *fereastra, time_t *timp)
{
      int maxy,i;
      getmaxyx(fereastra,maxy,i);
      for(i=1;i<=4;i++)
      {
            mvwprintw(fereastra,(maxy-4)/2-1+i,0,"*");
            mvwprintw(fereastra,(maxy-4)/2-1+i,strlen("Timp ramas: 00s")+2,"*");
      }
      for(i=0;i<strlen("Timp ramas: 00s")+2;i++)
      {
            mvwprintw(fereastra,(maxy-4)/2,i,"*");
            mvwprintw(fereastra,(maxy-4)/2+3,i,"*");
      }
      mvwprintw(fereastra,(maxy-4)/2+1,1,"Auto: %ds",WAIT);
      mvwprintw(fereastra,(maxy-4)/2+2,1,"Timp ramas: %2ds",WAIT-(time(NULL)-*timp));
      wrefresh(fereastra);
}

int printmenu(WINDOW *fereastra, int *resume)
{
      wclear(fereastra);
      printmenu2048(fereastra);
      int maxx, maxy, putere=1, c, i=1;
      getmaxyx(fereastra,maxy,maxx);
      int k=strlen("NEW GAME")+4;
      start_color();
      init_pair(20,COLOR_RED,COLOR_BLACK);
      for(i=(maxy-9)/2-1;i<(maxy-9)/2+8;i++)
      {
            mvwprintw(fereastra,i,(maxx-k)/2-1,"*");
            mvwprintw(fereastra,i,(maxx-k)/2-1+k,"*");
      }
      for(i=(maxx-k)/2-1;i<(maxx-k)/2+k;i++)
      {
            mvwprintw(fereastra,(maxy-9)/2-1,i,"*");
            mvwprintw(fereastra,(maxy-9)/2+7,i,"*");
      }
      wattron(fereastra, A_BOLD | A_STANDOUT);
      mvwprintw(fereastra,(maxy-9)/2+1,(maxx-k)/2+1,"NEW GAME");
      wattroff(fereastra, A_BOLD | A_STANDOUT);
      if(*resume==0)
      {
            wattron(fereastra, COLOR_PAIR(20));
            mvwprintw(fereastra,(maxy-9)/2+3,(maxx-strlen("RESUME"))/2-1,"RESUME");
            wattroff(fereastra, COLOR_PAIR(20));
      }
      else
      mvwprintw(fereastra,(maxy-9)/2+3,(maxx-strlen("RESUME"))/2-1,"RESUME");
      mvwprintw(fereastra,(maxy-9)/2+5,(maxx-strlen("QUIT"))/2-1,"QUIT");
      i=1;
      while(putere)
      {
            wrefresh(fereastra);
            c=wgetch(fereastra);
            switch(c)
            {
                  case 'w':
                  case KEY_UP:
                              if(i>1)
                                    i--;
                              if(i==2 && *resume==0)
                                    i--;
                              break;
                  case 's':
                  case KEY_DOWN:
                              if(i<3)
                                    i++;
                              if(i==2 && *resume==0)
                                    i++;
                              break;
                  case 10:
                              putere=0;
                              break;
                  default:
                        break;
            }
            switch(i)
            {
                  case 1:
                        wattron(fereastra, A_BOLD | A_STANDOUT);
                        mvwprintw(fereastra,(maxy-9)/2+1,(maxx-k)/2+1,"NEW GAME");
                        wattroff(fereastra, A_BOLD | A_STANDOUT);
                        mvwprintw(fereastra,(maxy-9)/2+5,(maxx-strlen("QUIT"))/2-1,"QUIT");
                        if(*resume==1)
                              mvwprintw(fereastra,(maxy-9)/2+3,(maxx-strlen("RESUME"))/2-1,"RESUME");
                        else
                        {
                              wattron(fereastra, COLOR_PAIR(20));
                              mvwprintw(fereastra,(maxy-9)/2+3,(maxx-strlen("RESUME"))/2-1,"RESUME");
                              wattroff(fereastra, COLOR_PAIR(20));
                        }
                        break;
                  case 2:
                        {
                              wattron(fereastra, A_BOLD | A_STANDOUT);
                              mvwprintw(fereastra,(maxy-9)/2+3,(maxx-strlen("RESUME"))/2-1,"RESUME");
                              wattroff(fereastra, A_BOLD | A_STANDOUT);
                              mvwprintw(fereastra,(maxy-9)/2+1,(maxx-k)/2+1,"NEW GAME");
                              mvwprintw(fereastra,(maxy-9)/2+5,(maxx-strlen("QUIT"))/2-1,"QUIT");
                              break;
                        }
                  case 3:
                        wattron(fereastra, A_BOLD | A_STANDOUT);
                        mvwprintw(fereastra,(maxy-9)/2+5,(maxx-strlen("QUIT"))/2-1,"QUIT");
                        wattroff(fereastra, A_BOLD | A_STANDOUT);
                        mvwprintw(fereastra,(maxy-9)/2+1,(maxx-k)/2+1,"NEW GAME");
                        if(*resume==1)
                        mvwprintw(fereastra,(maxy-9)/2+3,(maxx-strlen("RESUME"))/2-1,"RESUME");
                        else
                        {
                              wattron(fereastra, COLOR_PAIR(20));
                              mvwprintw(fereastra,(maxy-9)/2+3,(maxx-strlen("RESUME"))/2-1,"RESUME");
                              wattroff(fereastra, COLOR_PAIR(20));
                        }
                        break;
                  default:
                        break;
            }
            wrefresh(fereastra);
            if(putere==0)
            {
                  switch(i)
                  {
                        case 1:
                              moveall(fereastra);
                              usleep(1000*50);
                              return 1;
                              break;
                        case 2:
                              moveall(fereastra);
                              usleep(1000*50);
                              return 2;
                              break;
                        case 3:
                              return 3;
                              break;
                        default:
                              break;
                  }
            }
      }
      return 0;
}

void legenda(WINDOW *fereastra)
{
      int maxy,maxx;
      getmaxyx(fereastra,maxy,maxx);
      int i;
      for(i=1;i<=8;i++)
      {
            mvwprintw(fereastra,maxy-i,(maxx-strlen("W,A,S,D / sageti = mutari"))/2-1,"*");
            mvwprintw(fereastra,maxy-i,(maxx-strlen("W,A,S,D / sageti = mutari"))/2+strlen("W,A,S,D / sageti = mutari"),"*");
      }
      for(i=(maxx-strlen("W,A,S,D / sageti = mutari"))/2-1;i<(maxx-strlen("W,A,S,D / sageti = mutari"))/2+strlen("W,A,S,D / sageti = mutari");i++)
      {
            mvwprintw(fereastra,maxy-8,i,"*");
            mvwprintw(fereastra,maxy-1,i,"*");
      }
      wattron(fereastra, A_UNDERLINE);
      mvwprintw(fereastra,maxy-7,(maxx-strlen("LEGENDA"))/2-1,"LEGENDA");
      wattroff(fereastra, A_UNDERLINE);
      mvwprintw(fereastra,maxy-6,(maxx-strlen("W,A,S,D / sageti = mutari"))/2,"W,A,S,D / sageti = mutari");
      mvwprintw(fereastra,maxy-5,(maxx-strlen("U = Undo"))/2-1,"U = Undo");
      mvwprintw(fereastra,maxy-4,(maxx-strlen("F5 = Quicksave"))/2-1,"F5 = Quicksave");
      mvwprintw(fereastra,maxy-3,(maxx-strlen("F9 = Quickload"))/2-1,"F9 = Quickload");
      mvwprintw(fereastra,maxy-2,(maxx-strlen("T = CHEAT(pentru testing)"))/2,"T = CHEAT(pentru testing)");
      wrefresh(fereastra);
}

void quicksave(int **a, int *scor)
{
      FILE *mem;
      mem=fopen("save.txt", "w");
      int x, y;
      for(x=0;x<4;x++)
      {
            for(y=0;y<4;y++)
            {
                  fprintf(mem,"%d ",a[x][y]);
            }
            fprintf(mem,"\n");
      }
      fprintf(mem,"%d",*scor);
      fclose(mem);
}

void quickload(WINDOW *fereastra, int **a, int *scor, undo *v)
{
      FILE *mem;
      mem=fopen("save.txt", "r");
      int x,y,maxy,maxx;
      getmaxyx(fereastra,maxy,maxx);
      if(mem == NULL)
      {
            for(x=1;x<=6;x++)
            {
                  mvwprintw(fereastra,(maxy-6)/2-1+x,maxx-strlen("pentru continuare ")-2,"*");
                  mvwprintw(fereastra,(maxy-6)/2-1+x,maxx-1,"*");
            }
            for(x=maxx-strlen("pentru continuare. ")-1;x<maxx-1;x++)
            {
                  mvwprintw(fereastra,(maxy-6)/2,x,"*");
                  mvwprintw(fereastra,(maxy-6)/2+5,x,"*");
            }
            mvwprintw(fereastra,(maxy-6)/2+1,maxx-strlen("Nu a fost gasita")-2,"Nu a fost gasita");
            mvwprintw(fereastra,(maxy-6)/2+2,maxx-strlen("nicio salvare.")-4,"nicio salvare.");
            mvwprintw(fereastra,(maxy-6)/2+3,maxx-strlen("Apasati ENTER")-5,"Apasati ENTER");
            mvwprintw(fereastra,(maxy-6)/2+4,maxx-strlen("pentru continuare.")-1,"pentru continuare.");
            wrefresh(fereastra);
            while((y=wgetch(fereastra))!=10)
            {
                  printcurrenttime(fereastra);
            }
      }
      else
      {
            for(x=0;x<4;x++)
            {
                  for(y=0;y<4;y++)
                        fscanf(mem,"%d",&a[x][y]);
            }
            fscanf(mem,"%d",scor);
            fclose(mem);
            v->n = 0;
            v->u=realloc(v->u,0);
      }
}

void addundo(undo *v, int **b, int *scor)
{
      (v->n)++;
      v->u=realloc(v->u,(v->n)*sizeof(table));
      int x,y;
      for(x=0;x<4;x++)
            for(y=0;y<4;y++)
                  (v->u[v->n - 1].a[x][y])=b[x][y];
      v->u[v->n -1].scor=*scor;
}

void doundo(undo *v, int **b, int *scor)
{
      if(v->n > 0)
      {
            (v->n)--;
            int x, y;
            for(x=0;x<4;x++)
                  for(y=0;y<4;y++)
                        b[x][y]=(v->u[v->n].a[x][y]);
            *scor=v->u[v->n].scor;
            v->u=realloc(v->u,(v->n)*sizeof(table));
      }
}

int main()
{
    int **a,n=0,x,putere=1,t=0,i,k;
    int *scor = malloc(1*sizeof(int));
    *scor=0;
    int *cleared = malloc(sizeof(int));
    *cleared = 0;
    int *check=malloc(1*sizeof(int));
    *check = 0;

    time_t *timp = malloc(1*sizeof(clock_t));
    *timp = time(NULL);

    int *resume = malloc(sizeof(int));
    *resume = 0; // 0=unavailable, 1=available

    undo *v = malloc(sizeof(undo));
    v->u=malloc(0);
    v->n=0;

    a = calloc(4,sizeof(int *));
    for(x=0; x<4; x++)
        a[x] = calloc(4,sizeof(int));
    int c;
    initscr();
    noecho();
    curs_set(FALSE);

    int maxx=4,maxy=4;
    getmaxyx(stdscr,maxy,maxx);
    WINDOW *fereastra = newwin(maxy,maxx,0,0);
    keypad(fereastra,TRUE);
    switch(printmenu(fereastra,resume))
    {
          case 1:
                  goto new_game;
                  break;
            case 2:
                  goto resume_game;
                  break;
            case 3:
                  goto quit_game;
                  break;
            default:
                  break;
   }
    wrefresh(fereastra);

new_game:
//-------------------------------------START GAME-----------------------------------
    newgame(a);
    v->u=realloc(v->u,0);
    v->n=0;
    *scor=0;
    *resume=1;
    t=0;
    n=0;
    putere=1;
    *check=0;
    *cleared=0;
    resume_game:
    *timp=time(NULL);
    wtimeout(fereastra,500);
    afisare(a,fereastra);
    printscoreboard(fereastra,scor);
    printtimer(fereastra,timp);
    printcurrenttime(fereastra);
    printcorners(fereastra);
    legenda(fereastra);
    wrefresh(fereastra);
    while(putere)
    {
         c=0;
        *cleared=0;
        *check=0;
        n=0;
        if((c=wgetch(fereastra))==ERR && (time(NULL)-*timp)>=WAIT)
        {
             addundo(v,a,scor);
             n=doauto(a,scor,cleared,check);
             wclear(fereastra);
             *timp=time(NULL);

      }
        switch(c)
        {
        case 'a':
        case KEY_LEFT:
            addundo(v,a,scor);
            n=stanga(a,scor,cleared,check);
            wclear(fereastra);
            *timp = time(NULL);
            break;
        case 'd':
        case KEY_RIGHT:
            addundo(v,a,scor);
            n=dreapta(a,scor,cleared,check);
            wclear(fereastra);
            *timp = time(NULL);
            break;
        case 'w':
        case KEY_UP:
            addundo(v,a,scor);
            n=sus(a,scor,cleared,check);
            wclear(fereastra);
            *timp = time(NULL);
            break;
        case 's':
        case KEY_DOWN:
            addundo(v,a,scor);
            n=jos(a,scor,cleared,check);
            wclear(fereastra);
            *timp = time(NULL);
            break;
      case KEY_F(5):
            quicksave(a,scor);
            *timp = time(NULL);
            break;
      case KEY_F(9):
            quickload(fereastra,a,scor,v);
            wclear(fereastra);
            *timp = time(NULL);
            break;
        case 'q':
            movealltomenu(fereastra);
            switch(printmenu(fereastra,resume))
            {
                  case 1:
                          goto new_game;
                          break;
                    case 2:
                          goto resume_game;
                          break;
                    case 3:
                          goto quit_game;
                          break;
                    default:
                          break;
           }
            break;
        case 't':
            *timp=time(NULL);
            wclear(fereastra);
            a[0][3]=1024;
            a[0][2]=1024;
            break;
        case 'u':
                  doundo(v,a,scor);
                  wclear(fereastra);
                  *timp = time(NULL);
                break;
        default:
            break;
        }
        if(n==1)
        {
            aleator(a);
        }
        afisare(a,fereastra);
        printscoreboard(fereastra,scor);
        printtimer(fereastra,timp);
        printcurrenttime(fereastra);
        printcorners(fereastra);
        legenda(fereastra);
        wrefresh(fereastra);
        if(t==0)
        {
            t=checkwon(a);
        }
        if(t==1)
        {
             printbeforewin(fereastra);
             afisare(a,fereastra);
             printscoreboard(fereastra,scor);
             printcurrenttime(fereastra);
             printcorners(fereastra);
             legenda(fereastra);
             *timp=time(NULL);
             printtimer(fereastra,timp);
             wrefresh(fereastra);
             usleep(1000*100);
            putere=printwon(fereastra, a);
            t=2;
        }
        k=0;
        for(i=1; i<=4; i++)
        {
            if(checkover(a)==0)
                k++;
            rotire(a);
        }
        if(k==4)
        {
            switch(printover(fereastra))
            {
                  case 'q':
                  movealltomenu(fereastra);
                        putere=0;
                        break;
                  case 'u':
                        *timp=time(NULL);
                        doundo(v,a,scor);
                        break;
                  default:
                        break;
            }
      }
      if(putere==0)
      {
            putere=1;
            switch(printmenu(fereastra,resume))
            {
                  case 1:
                          goto new_game;
                          break;
                    case 2:
                          goto resume_game;
                          break;
                    case 3:
                          goto quit_game;
                          break;
                    default:
                          break;
           }
     }
    }
    quit_game:
    afterexit(fereastra);
    wclear(fereastra);
    delwin(fereastra);
    endwin();
    for(x=0; x<4; x++)
        free(a[x]);
    free(a);
    free(v->u);
    free(v);
    free(scor);
    free(check);
    free(timp);
    free(cleared);
    free(resume);
    return 0;
}
