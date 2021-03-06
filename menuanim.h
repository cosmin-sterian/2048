#define col2on wattron(fereastra,COLOR_PAIR(27))
#define col2off wattroff(fereastra,COLOR_PAIR(27))
#define col0on wattron(fereastra,COLOR_PAIR(28))
#define col0off wattroff(fereastra,COLOR_PAIR(28))
#define col4on wattron(fereastra,COLOR_PAIR(29))
#define col4off wattroff(fereastra,COLOR_PAIR(29))
#define col8on wattron(fereastra,COLOR_PAIR(30))
#define col8off wattroff(fereastra,COLOR_PAIR(30))

#define p21 ".--------------."
#define p22 "|    _____     |"
#define p23 "|   / ___ `.   |"
#define p24 "|  |_/___) |   |"
#define p25 "|   .'____.'   |"
#define p26 "|  / /____     |"
#define p27 "|  |_______|   |"
#define p28 "|              |"
#define p29 "'--------------'"

#define p01 ".--------------."
#define p02 "|     ____     |"
#define p03 "|   .'    '.   |"
#define p04 "|  |  .--.  |  |"
#define p05 "|  | |    | |  |"
#define p06 "|  |  `--'  |  |"
#define p07 "|   '.____.'   |"
#define p08 "|              |"
#define p09 "'--------------'"

#define p41 ".--------------."
#define p42 "|   _    _     |"
#define p43 "|  | |  | |    |"
#define p44 "|  | |__| |_   |"
#define p45 "|  |____   _|  |"
#define p46 "|      _| |_   |"
#define p47 "|     |_____|  |"
#define p48 "|              |"
#define p49 "'--------------'"

#define p81 ".--------------."
#define p82 "|     ____     |"
#define p83 "|   .' __ '.   |"
#define p84 "|   | (__) |   |"
#define p85 "|   .`____'.   |"
#define p86 "|  | (____) |  |"
#define p87 "|  `.______.'  |"
#define p88 "|              |"
#define p89 "'--------------'"

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

void reprintp0(WINDOW *fereastra, int i, int j)
{
      mvwprintw(fereastra,i,j,p01);
      mvwprintw(fereastra,i+1,j,p02);
      mvwprintw(fereastra,i+2,j,p03);
      mvwprintw(fereastra,i+3,j,p04);
      mvwprintw(fereastra,i+4,j,p05);
      mvwprintw(fereastra,i+5,j,p06);
      mvwprintw(fereastra,i+6,j,p07);
      mvwprintw(fereastra,i+7,j,p08);
      mvwprintw(fereastra,i+8,j,p09);
      wrefresh(fereastra);
}

void reprintp4(WINDOW *fereastra, int i, int j)
{
      mvwprintw(fereastra,i,j,p41);
      mvwprintw(fereastra,i+1,j,p42);
      mvwprintw(fereastra,i+2,j,p43);
      mvwprintw(fereastra,i+3,j,p44);
      mvwprintw(fereastra,i+4,j,p45);
      mvwprintw(fereastra,i+5,j,p46);
      mvwprintw(fereastra,i+6,j,p47);
      mvwprintw(fereastra,i+7,j,p48);
      mvwprintw(fereastra,i+8,j,p49);
      wrefresh(fereastra);
}

void reprintp8(WINDOW *fereastra, int i, int j)
{
      mvwprintw(fereastra,i,j,p81);
      mvwprintw(fereastra,i+1,j,p82);
      mvwprintw(fereastra,i+2,j,p83);
      mvwprintw(fereastra,i+3,j,p84);
      mvwprintw(fereastra,i+4,j,p85);
      mvwprintw(fereastra,i+5,j,p86);
      mvwprintw(fereastra,i+6,j,p87);
      mvwprintw(fereastra,i+7,j,p88);
      mvwprintw(fereastra,i+8,j,p89);
      wrefresh(fereastra);
}

void movep2(WINDOW *fereastra, int i2, int j2, int i0, int j0, int i4, int j4, int i8, int j8)
{
	int x2,y2=j2, y0=j0;
      int maxy,maxx;
      getmaxyx(fereastra,maxy,maxx);
      x2=i2;
      int x4=x2+10,y4=y2,y8=j0+1;
      while(1)
      {
            if(x2<0 && x4>maxy-9 && y0>maxx-16 && y2<0 && y4<0 && y8 > maxx-16)
                  break;
            wclear(fereastra);
            col2on;
            reprintp2(fereastra,x2,y2);
            col2off;
            col0on;
            reprintp0(fereastra,x2,y0);
            col0off;
            col4on;
            reprintp4(fereastra,x4,y4);
            col4off;
            col8on;
            reprintp8(fereastra,x4,y8);
            col8off;
            x2--;
            x4++;
            y0++;
            y2--;
            y4--;
            y8++;
            if(x2<0 && !(x4>maxy-9 && y0>maxx-16 && y2<0 && y4<0 && y8 > maxx-16))
                  x2++;
            if(x4>maxy-9 && !(x2<0 && y0>maxx-16 && y2<0 && y4<0 && y8 > maxx-16))
                  x4--;
            if(y0>maxx-16 && !(x2<0 && x4>maxy-9 && y2<0 && y4<0 && y8 > maxx-16))
                  y0--;
            if(y2<0 && !(x2<0 && x4>maxy-9 && y0>maxx-16 && y4<0 && y8 > maxx-16))
                  y2++;
            if(y4<0 && !(x2<0 && x4>maxy-9 && y0>maxx-16 && y2<0 && y8 > maxx-16))
                  y4++;
            if(y8>maxx-16 && !(x2<0 && x4>maxy-9 && y0>maxx-16 && y2<0 && y4<0))
                  y8--;
            usleep(1000*50);
      }
}

void movep2reverse(WINDOW *fereastra, int i2, int j2, int i0, int j0, int i4, int j4, int i8, int j8)
{
      int maxy,maxx;
      getmaxyx(fereastra,maxy,maxx);
	int x2,y2=0, y0=maxx-16;
      x2=0;
      int x4=maxy-9,y4=0,y8=maxx-16;
      while(1)
      {
            if(x2>i2 && x4<i4 && y0<j0 && y2>j2 && y4>j4 && y8<j8)
                  break;
            wclear(fereastra);
            col2on;
            reprintp2(fereastra,x2,y2);
            col2off;
            col0on;
            reprintp0(fereastra,x2,y0);
            col0off;
            col4on;
            reprintp4(fereastra,x4,y4);
            col4off;
            col8on;
            reprintp8(fereastra,x4,y8);
            col8off;
            x2++;
            x4--;
            y0--;
            y2++;
            y4++;
            y8--;
            if(x2>i2 && !(x4<i4 && y0<j0 && y2>j2 && y4>j4 && y8<j8))
                  x2--;
            if(x4<i4 && !(x2>i2 && y0<j0 && y2>j2 && y4>j4 && y8<j8))
                  x4++;
            if(y0<j0 && !(x2>i2 && x4<i4 && y2>j2 && y4>j4 && y8<j8))
                  y0++;
            if(y2>j2 && !(x2>i2 && x4<i4 && y0<j0 && y4>j4 && y8<j8))
                  y2--;
            if(y4>j4 && !(x2>i2 && x4<i4 && y0<j0 && y2>j2 && y8<j8))
                  y4--;
            if(y8<j8 && !(x2>i2 && x4<i4 && y0<j0 && y2>j2 && y4>j4))
                  y8++;
            usleep(1000*50);
      }
}


void moveall(WINDOW *fereastra)
{
      int maxy,maxx;
      getmaxyx(fereastra,maxy,maxx);
      movep2(fereastra,(maxy-18)/2-2,(maxx-45)/2-1,(maxy-18)/2-2,(maxx-45)/2+30,(maxy-18)/2-2+10,(maxx-45)/2-1,(maxy-18)/2-2+10,(maxx-45)/2+30);
}

void movealltomenu(WINDOW *fereastra)
{
      int maxy,maxx;
      getmaxyx(fereastra,maxy,maxx);
      movep2reverse(fereastra,(maxy-18)/2-2,(maxx-45)/2-1,(maxy-18)/2-2,(maxx-45)/2+30,(maxy-18)/2-2+10,(maxx-45)/2-1,(maxy-18)/2-2+10,(maxx-45)/2+30);
}

void printcorners(WINDOW *fereastra)
{
      int maxy,maxx;
      getmaxyx(fereastra,maxy,maxx);
      col2on;
      reprintp2(fereastra,0,0);
      col2off;
      col0on;
      reprintp0(fereastra,0,maxx-16);
      col0off;
      col4on;
      reprintp4(fereastra,maxy-9,0);
      col4off;
      col8on;
      reprintp8(fereastra,maxy-9,maxx-16);
      col8off;
}

void printmenu2048(WINDOW *fereastra)
{
      int maxy,maxx;
      getmaxyx(fereastra,maxy,maxx);
      start_color();
      init_pair(27,COLOR_BLACK,COLOR_BLUE);
      init_pair(28,COLOR_BLACK,COLOR_RED);
      init_pair(29,COLOR_BLACK,COLOR_GREEN);
      init_pair(30,COLOR_BLACK,COLOR_YELLOW);

      col2on;
      reprintp2(fereastra,(maxy-18)/2-2,(maxx-45)/2-1);
      col2off;
      col0on;
      reprintp0(fereastra,(maxy-18)/2-2,(maxx-45)/2+30);
      col0off;
      col4on;
      reprintp4(fereastra,(maxy-18)/2-2+10,(maxx-45)/2-1);
      col4off;
      col8on;
      reprintp8(fereastra,(maxy-18)/2-2+10,(maxx-45)/2+30);
      col8off;
}

int checkempty(int *v, int *dim)
{
      int i;
      for(i=0;i<*dim;i++)
      {
            if(v[i]==0)
                  return 0;
      }
      return 1;
}

void afterexit(WINDOW *fereastra)
{
      int maxy,maxx;
      getmaxyx(fereastra,maxy,maxx);
      init_pair(31,COLOR_BLACK,COLOR_BLUE);
      srand(time(NULL));
      int i,j,r;
      int *v=calloc(maxy,sizeof(int));
      int *dim=calloc(1,sizeof(int));
      *dim=maxy;
      while(checkempty(v,dim)!=1)
      {
            r=rand()%(*dim);
            while(v[r]==1)
                  r=rand()%(*dim);
            v[r]=1;
            if(r==maxy/2)
            {
                  for(j=0;j<(maxx-strlen(" CYA ! "))/2;j++)
                  {
                        wattron(fereastra,COLOR_PAIR(31));
                        mvwprintw(fereastra,r,j," ");
                        wattroff(fereastra,COLOR_PAIR(31));
                  }
                  mvwprintw(fereastra,r,j," CYA ! ");
                  for(j=j+strlen(" CYA ! ");j<maxx;j++)
                  {
                        wattron(fereastra,COLOR_PAIR(31));
                        mvwprintw(fereastra,r,j," ");
                        wattroff(fereastra,COLOR_PAIR(31));
                  }
            }
            else
            {
                  for(j=0;j<maxx;j++)
                  {
                        wattron(fereastra,COLOR_PAIR(31));
                        mvwprintw(fereastra,r,j," ");
                        wattroff(fereastra,COLOR_PAIR(31));
                        wrefresh(fereastra);
                  }
            }
            wrefresh(fereastra);
            usleep(1000*70);
      }
      curs_set(TRUE);
      for(i=maxy-1;i>=0;i--)
      {
            for(j=maxx-1;j>=0;j--)
            {
                  wmove(fereastra,i,j);
                  mvwprintw(fereastra,i,j," ");
                  wrefresh(fereastra);
                  usleep(1000);
            }
      }

      free(v);
      free(dim);
}
