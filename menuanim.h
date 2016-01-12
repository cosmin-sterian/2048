#define col2on wattron(fereastra,COLOR_PAIR(27))
#define col2off wattroff(fereastra,COLOR_PAIR(27))

#define p21 ".--------------."
#define p22 "|    _____     |"
#define p23 "|   / ___ `.   |"
#define p24 "|  |_/___) |   |"
#define p25 "|   .'____.'   |"
#define p26 "|  / /____     |"
#define p27 "|  |_______|   |"
#define p28 "|              |"
#define p29 "'--------------'"

void reprintp2(WINDOW *fereastra, int i, int j)
{
      mvwprintw(fereastra,i,j,p21);
      mvwprintw(fereastra,i+1,j,p22);
      mvwprintw(fereastra,i+2,j,p23);
      mvwprintw(fereastra,i+3,j,p24);
      mvwprintw(fereastra,i+4,j,p25);
      mvwprintw(fereastra,i+5,j,p26);
      mvwprintw(fereastra,i+6,j,p27);
      mvwprintw(fereastra,i+7,j,p28);
      mvwprintw(fereastra,i+8,j,p29);
      wrefresh(fereastra);
}

void movep2(WINDOW *fereastra, int i, int j)
{
      int x,y;
      for(x=i;x>=0;x--)
      {
            wclear(fereastra);
            reprintp2(fereastra,x,j);
            usleep(1000*200);
      }
      for(y=j;y>=0;y--)
      {
            wclear(fereastra);
            reprintp2(fereastra,0,y);
            usleep(1000*50);
      }
}

void moveall(WINDOW *fereastra)
{
      int maxy,maxx;
      getmaxyx(fereastra,maxy,maxx);
      col2on;
      movep2(fereastra,(maxy-18)/2-2,(maxx-45)/2-1);
      col2off;
}

void printcorners(WINDOW *fereastra)
{
      col2on;
      reprintp2(fereastra,0,0);
      col2off;
}

void printmenu2048(WINDOW *fereastra)
{
      int maxy,maxx;
      getmaxyx(fereastra,maxy,maxx);
      start_color();
      init_pair(27,COLOR_WHITE,COLOR_BLUE);
      init_pair(28,COLOR_WHITE,COLOR_RED);
      init_pair(29,COLOR_WHITE,COLOR_GREEN);
      init_pair(30,COLOR_WHITE,COLOR_YELLOW);
      int i;
      wattron(fereastra,COLOR_PAIR(27));
      //for(i=(maxy-18)/2-1;i<(maxy-18)/2+17;i++)
      //{
            reprintp2(fereastra,(maxy-18)/2-2,(maxx-45)/2-1);
            //sleep(1);
      //}
      wattroff(fereastra,COLOR_PAIR(27));
}
