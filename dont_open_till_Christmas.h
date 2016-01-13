#define r1 "@@@@@@@@@@@@@@@@@@@@@@@@@   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@0  @@@@@@@@@@@@"
#define r2 "@@@@@@@@@@@@@@@@@@@@@@0 @00   0@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@0  000 0@@@@@@@@@@"
#define r3 "@@@@@@@@@@@@@@@@@@@@@@  @000  0@@@@@@@ WOW @@@@@@@@@@@@@@@@@   00000 0@@@@@@@@@@"
#define r4 "@@@@@@@@@@@@@@@@@@@@@@  @00000   @@@@@@@@@@@@@@@@@@@@@0@@0   00000000  @@@@@@@@@"
#define r5 "@@@@@@@@@@@@@@@@@@@@@0  @00000000   @@@@@@@@@@@@@@@@@@0  00000000000@0 @@@@@@@@@"
#define r6 "@ SUCH SCORE @@@@@@@@ 00@   00000           @@@@@@@@   000@@00000000@0 @@@@@@@@@"
#define r7 "@@@@@@@@@@@@@@@@@@@@@    0000000000000000000        0000000000000000@  @@ DOGE @"
#define r8 "@@@@@@@@@@@@@@@@@@@0   0 00000000000000000000  00      00000@@0  000@  @@@ IS @@"
#define r9 "@@@@@@@@@@@@@@      00000000000000000000000000000000   000000     00@  @ AMAZED"
#define r10 "@@@@@@@@@@@0   00000@000000000000000000000000000000000            00 00@@@@@@@@@"
#define r11 "@@@@@@@@@   000000000000000000000000000000000000000000000      00@00 0@@@@@@@@@@"
#define r12 "@@@@@@@0 00000000@@@@@@@@00000000000000000000000000000000000   @@000000 @@@@@@@@"
#define r13 "@@@@@@@0 00000000        00000000000000000000000000000000000000  000000 0@@@@@@@"
#define r14 "@@@@@@  000000@@ 000     00000000000@@      @@@000000000000000000   0000 0@@@@@@"
#define r15 "@@@@@@  @00000@@       0000000000000  000      000000000000000000   000@ 0@@@@@@"
#define r16 "@@@@@  000000000000 0 00000000000000 00        000000000000000000000   @00 @@@@@"
#define r17 "@@@@@  00000000000000000000000000000 @0     00000000000000000000000000     @@@@@"
#define r18 "@@@0 0 00  0@@      @@00000000000000000 0   00000000@@@@@@@@@@@000000000   @@@@@"
#define r19 "@@@0 @000000           00000000000000000000000000000@000000000@0000000000  @@@@@"
#define r20 "@@@0 @   @  00   000    @@@@00   000000000@000000@@@ MUCH 2048 @@0000000000 @@@@"
#define r21 "@@@0 @0  @              @   000  0000000000000000@@@@@@@@@@@@@@@@00000000@@ @@@@"

void reprint(WINDOW *fereastra, int i, int j)
{
      mvwprintw(fereastra,i,j,r1);
      mvwprintw(fereastra,i+1,j,r2);
      mvwprintw(fereastra,i+2,j,r3);
      mvwprintw(fereastra,i+3,j,r4);
      mvwprintw(fereastra,i+4,j,r5);
      mvwprintw(fereastra,i+5,j,r6);
      mvwprintw(fereastra,i+6,j,r7);
      mvwprintw(fereastra,i+7,j,r8);
      mvwprintw(fereastra,i+8,j,r9);
      mvwprintw(fereastra,i+9,j,r10);
      mvwprintw(fereastra,i+10,j,r11);
      mvwprintw(fereastra,i+11,j,r12);
      mvwprintw(fereastra,i+12,j,r13);
      mvwprintw(fereastra,i+13,j,r14);
      mvwprintw(fereastra,i+14,j,r15);
      mvwprintw(fereastra,i+15,j,r16);
      mvwprintw(fereastra,i+16,j,r17);
      mvwprintw(fereastra,i+17,j,r18);
      mvwprintw(fereastra,i+18,j,r19);
      mvwprintw(fereastra,i+19,j,r20);
      mvwprintw(fereastra,i+20,j,r21);
      wrefresh(fereastra);
}

void printbeforewin(WINDOW *fereastra)
{
      int maxy,i,j=1;
      getmaxyx(fereastra,maxy,i);
      start_color();
      init_pair(25,COLOR_GREEN,COLOR_BLACK);
      init_pair(26,COLOR_RED,COLOR_BLACK);
      wattron(fereastra, COLOR_PAIR(25) | A_BOLD);
      for(i=maxy-1;i>0;i--)
      {
            wmove(fereastra,i,0);
            wclrtobot(fereastra);
            reprint(fereastra,i,0);
            wmove(fereastra,i+21,0);
            wclrtobot(fereastra);
            wrefresh(fereastra);
            usleep(1000*200);
      }
      wclear(fereastra);
      reprint(fereastra, 1, 0);
      wattroff(fereastra, COLOR_PAIR(25) | A_BOLD);
      while(1)
      {
            wattron(fereastra, COLOR_PAIR(25+(j%2)) | A_BOLD);
            reprint(fereastra, 1, 0);
            wattroff(fereastra, COLOR_PAIR(25+(j%2)) | A_BOLD);
            usleep(1000*200);
            if(j==12)
                  break;
            j++;
      }
      wattron(fereastra, COLOR_PAIR(25) | A_BOLD);
      for(i=1;i>=-21;i--)
      {
            wmove(fereastra,i,0);
            wclrtobot(fereastra);
            reprint(fereastra,i,0);
            wmove(fereastra,i+21,0);
            wclrtobot(fereastra);
            wrefresh(fereastra);
            usleep(1000*100);
      }
      wattroff(fereastra, COLOR_PAIR(25) | A_BOLD);
}
