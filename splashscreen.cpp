#include<stdio.h>
#include<bios.h>
#include<conio.h>
#include<ctype.h>
#include<graphics.h>
#include<string.h>
#include<stdlib.h>
#include<dos.h>
enum TYPE {
    PASSWORD,
    INT,
    FLOAT,
    TEXT,
    ALL,
};
union REGS i,o;

int buttonm,xm,ym,gd=9,gm=1,close=1,set=1,midx,midy;

//declearation function
void getmousepos(int *buttonm,int *xm, int *ym);
void restrictmouse(int x1,int y1,int x2,int y2);
void showmouse();
int initmouse();
void setmousepos(int &xpos,int &ypos);
void hidemouse();
int menu(int);

void addrecord();
void viewrecord();
void editrecord();
void searchrecord();
void deleterecord();

void login();

int doctor();
void adddoc();
void deletedoc();
void searchdoc();
void welgr();
void userl();
void notice();
void setusrl();
void changeusrl();
void removeusrl();
int dropmenu(char menu[7][20],int x1,int y1,int x2,int y2,int opt);
void button(char name[15],int x1,int y1,int x2,int y2,int c);
void clrwin(int opt);
void drawwindow(char head[30],int x1, int y1, int x2, int y2, int c);
int program();
void managetype();
int about();
void input(int x,int y,char result[50],int limit ,int tc,int bkc,int type);
void inputbox(int x,int y,int limit,int bkc);
//end declearation
int main(){
    
    _setcursortype(0);
    initgraph(&gd,&gm,"..\\bgi");
    int menu1=-1;
    midx=getmaxx()/2;
    midy=getmaxy()/2;
    clrscr();
    //welgr();
    setfillstyle(1,BLUE);
    bar(0,0,getmaxx(),getmaxy());
    setcolor(3);
    settextstyle(2,0,5);
    settextjustify(CENTER_TEXT, TOP_TEXT);
    outtextxy(midx,0,"==== Prison Management System ====");
    settextjustify(LEFT_TEXT, TOP_TEXT);
    settextstyle(0,0,0);
    clrwin(2);
    restrictmouse(10,18,getmaxx()-10,getmaxy()-10);
    setmousepos(midx,midy);
    showmouse();
    getmousepos(&buttonm,&xm,&ym);
    menu(menu1);
    while(1){
        showmouse();
        getmousepos(&buttonm,&xm,&ym);
        if(buttonm==1){
            if(xm>=10&&xm<=34&&ym>=18&&ym<=32){
                menu1=0;
            }else if(xm>=35&&xm<=94&&ym>=18&&ym<=32){
                menu1=1;
            }else if(xm>=95&&xm<=169&&ym>=18&&ym<=32){
                menu1=2;
            }else if(xm>=170&&xm<=219&&ym>=18&&ym<=32){
                menu1=3;
            }else if(xm>=220&&xm<=269&&ym>=18&&ym<=32){
                menu1=4;
            }else menu1=-1;
            clrwin(1);
            menu(menu1);
            switch(menu1){
                case 0:program();break;
                case 1:doctor();break;
                case 2:about();break;
            }
        }
    }
    getch();
    closegraph();
    return(0);
}

int program(){
    int opt=-1,j;
    char menu[2][20]={"User Login >","Quit"};
    close=1;
    dropmenu(menu,10,33,131,76,opt);
    do{
        showmouse();
        getmousepos(&buttonm,&xm,&ym);
        if(xm>=10+10&&xm<=131-10&&ym>=33+8&&ym<=76-8&&buttonm==1){
            for(j=0;j<(76-33-8)/14;j++)
                if((ym-33-8)/14==j){
                    opt=j;
                    break;
                }
            dropmenu(menu,10,33,131,76,opt);
            switch(opt){
                case 0: userl();break;
                case 1: delay(100);cleardevice();closegraph();exit(0);
            }
        }else if(xm>=10&&xm<=34&&ym>=18&&ym<=32&&buttonm==1){
            dropmenu(menu,10,33,131,76,opt);
            continue;
        }else if(buttonm==1){
            break;
        }
    }while(close);
    return 0;
}

void userl(){
    int opt=-1,j;
    char menu[1][20]={"Set/Reset"};
    dropmenu(menu,132,41,229,98,opt);
    do{
        showmouse();
        getmousepos(&buttonm,&xm,&ym);
        if(xm>=132+10&&xm<=229-10&&ym>=41+8&&ym<=98-8&&buttonm==1){
            for(j=0;j<(98-41-8)/14;j++)
                if((ym-41-8)/14==j){
                    opt=j;
                    break;
                }
            dropmenu(menu,132,41,229,98,opt);
            delay(200);
            switch(opt){
                case 0: setusrl();break;
            }
        }else if(buttonm==1){
            break;
        }
    }while(close);
    clrwin(1);
}

void setusrl(){
    char head[30]="SET USER LOGIN";
    char usr[30]="",pwd[30]="",code[30]="";
    int a=midx/2+15+textwidth("Program Code : ");
    set=1;
    clrwin(2);
    drawwindow(head, midx/2, midy/2, (getmaxx()*3)/4, (getmaxy()*3)/4,1 );
    button("Set",midx+30,midy*3/2-22,midx+90,midy*3/2-8,7);
    button("Cancel",midx-90,midy*3/2-22,midx-30,midy*3/2-8,7);
    setcolor(15);moveto(midx/2+15,midy-26);
    outtext("Program Code :");inputbox(a,midy-26,15,15);
    setcolor(15);moveto(midx/2+15,midy-7);
    outtext("Username     :");inputbox(a,midy-7,15,15);
    setcolor(15);moveto(midx/2+15,midy+12);
    outtext("Password     :");inputbox(a,midy+12,15,15);
    do{
        getmousepos(&buttonm,&xm,&ym);
        if(buttonm==1){
            if(xm>=a-2&&xm<=a+15*8+1&&ym>=midy-26-2&&ym<=midy-26+8){
                set=1;
            }
            if(xm>=a-2&&xm<=a+15*8+1&&ym>=midy-7-2&&ym<=midy-7+8){
                set=2;
            }
            if(xm>=a-2&&xm<=a+15*8+1&&ym>=midy+12-2&&ym<=midy+12+8){
                set=3;
            }
            if(xm>=midx-90&&ym>=midy*3/2-22&&xm<=midx-30&&ym<=midy*3/2-8){
                button("Cancel",midx-90,midy*3/2-22,midx-30,midy*3/2-8,3);
                delay(100);close=0;set=0;
            }
            
            if(xm>=midx+30&&ym>=midy*3/2-22&&xm<=midx+90&&ym<=midy*3/2-8&&strlen(code)>0&&strlen(usr)>0&&strlen(pwd)>0){
                button("Set",midx+30,midy*3/2-22,midx+90,midy*3/2-8,3);
                delay(100);notice();close=0;set=0;
            }
        }
        if(set==4)set=1;
        if(set==1)
            input(a,midy-26,code,15 ,0,15,INT);
        if(set==2)
            input(a,midy-7,usr,15 ,0,15,TEXT);
        if(set==3)
            input(a,midy+12,pwd,15 ,0,15,PASSWORD);
    }while(close);
}




void input(int x,int y,char result[50],int limit ,int tc,int bkc,int type){
    char ch,text[2]="";
    int i=0,f=-1,key,j;
    close=1;
    hidemouse();
    setcolor(3);
    rectangle(x-3,y-3,x+limit*8+2,y+9);
    setfillstyle(1,bkc);
    bar(x-2,y-2,x+limit*8+1,y+8);
    showmouse();
    settextstyle(0,0,1);
    i=strlen(result);
    moveto(x,y);
    if(i>0){
        setcolor(tc);
        hidemouse();
        if(type!=0)
            outtext(result);
        else
            for(j=0;j<i;j++)
                outtext("*");
        showmouse();
    }
    if(i>0&&strstr(result,".")!=0){
        for(j=0;j<i;j++)
            if(result[j]=='.')
                break;
        f=j;
    }
    while(kbhit()){
        getch();
    }
    do{
        do{     hidemouse();
            setcolor(tc);
            line(x+i*8,y-1,x+i*8,y+7);
            showmouse();
            getmousepos(&buttonm,&xm,&ym);
            if(buttonm==1){
                if(xm<x-2||xm>x+limit*8+1||ym<y-2||ym>y+8){
                    close=0;
                    hidemouse();
                    setcolor(bkc);
                    line(x+i*8,y-1,x+i*8,y+7);
                    showmouse();
                    goto end;
                }
            }
            if(kbhit()){
                hidemouse();
                setcolor(bkc);
                line(x+i*8,y-1,x+i*8,y+7);
                showmouse();
                break;
            }else
                delay(100);
            hidemouse();
            setcolor(bkc);
            line(x+i*8,y-1,x+i*8,y+7);
            showmouse();
            getmousepos(&buttonm,&xm,&ym);
            if(buttonm==1){
                if(xm<x-2||xm>x+limit*8+1||ym<y-2||ym>y+8){
                    close=0;
                    hidemouse();
                    setcolor(bkc);
                    line(x+i*8,y-1,x+i*8,y+7);
                    showmouse();
                    goto end;
                }
            }
            if(!kbhit())
                delay(100);
        }while(bioskey(1)==0);
        key = bioskey(0);
        ch = key & 0xFF;
        hidemouse();
        if(type==3&&(isalpha(ch)||ch == ' ')&&i<limit){
            result[i++] = ch;
            text[0] = ch;
            text[1] = '\0';
            setcolor(tc);
            outtext(text);
        }
        if((type==1&&isdigit(ch)&&i<limit)||(((ch == '.'&&f==-1)||isdigit(ch))&&type==2&&i<limit)){
            if(ch=='.')
                f=i;
            result[i++] = ch;
            text[0] = ch;
            text[1] = '\0';
            setcolor(tc);
            outtext(text);
        }
        if((type==0||type==4)&&(isalpha(ch)||(ch>='!'&&ch<='@')||ch==95||ch == ' ')&&i<limit){//ch=95=_
            result[i++] = ch;
            text[0] = ch;
            text[1] = '\0';
            setcolor(tc);
            if(type==4)
                outtext(text);
            else
                outtext("*");
        }
        
        if(ch == 8 && i > 0){
            i--;
            if(i==f)
                f=-1;
            text[0] = result[i];
            text[1] = '\0';
            result[i] = '\0';
            setcolor(bkc);
            moveto(x+(i)*(textwidth(text)),y);
            if(type!=0)
                outtext(text);
            else
                outtext("*");
            moveto(x+textwidth(result),y);
        }
        if(type==0&&key==20992){//key=20992:insert key
            moveto(x,y);
            hidemouse();
            for(int j=0;j<i;j++){
                setcolor(bkc);
                outtext("*");//delete by outtext in same color to bkc;
            }
            result[i]='\0';
            moveto(x,y);
            setcolor(tc);
            outtext(result);
            showmouse();
            delay(70);
            if(!kbhit())
                delay(270);
            moveto(x,y);
            hidemouse();
            setcolor(bkc);
            outtext(result);
            moveto(x,y);
            setcolor(0);
            for(j=0;j<i;j++)
                outtext("*");
            showmouse();
        }
    end: showmouse();
    }while(close==1);
    result[i]='\0';
    close=1;
    hidemouse();
    setfillstyle(1,bkc);
    rectangle(x-3,y-3,x+limit*8+2,y+9);
    setcolor(0);
    line(x-3,y-3,x-3,y+9);
    line(x-3,y-3,x+limit*8+2,y-3);
    showmouse();
}





void managetype(){
    int opt=-1,j;
    char menu[3][20]={"Add new","Delete","All types"};
    dropmenu(menu,301,83,397,140,opt);
    do{
        getmousepos(&buttonm,&xm,&ym);
        if(xm>=301+10&&xm<=397-10&&ym>=83+8&&ym<=140-8&&buttonm==1){
            for(j=0;j<(140-83-8)/14;j++)
                if((ym-83-8)/14==j){
                    opt=j;
                    break;
                }
            dropmenu(menu,301,83,397,140,opt);
            delay(200);
            switch(opt){
                case 0: notice();break;
                case 1: notice();break;
                case 2: notice();break;
            }
        }else if(buttonm==1){
            break;
        }
    }while(close);
    clrwin(1);
}



int prisoner(){
    char menu[5][20]={"Add","Update","Delete    >","Search    >","View"};
    int opt=-1,j;
    close=1;
    dropmenu(menu,35,33,150,118,opt);
    do{
        showmouse();
        getmousepos(&buttonm,&xm,&ym);
        if(xm>=35+10&&xm<=150-10&&ym>=33+8&&ym<=118-8&&buttonm==1){
            for(j=0;j<(118-33-8)/14;j++)
                if((ym-33-8)/14==j){
                    opt=j;
                    break;
                }
            dropmenu(menu,35,33,150,118,opt);
            switch(opt){
                case 0:adddoc();break;
                case 1:notice();break;
                case 2:deletedoc();break;
                case 3:searchdoc();break;
                case 4:notice();break;
            }
        }else if(xm>=35&&xm<=94&&ym>=18&&ym<=32&&buttonm==1){
            dropmenu(menu,35,33,150,118,opt);
            continue;
        }else if(buttonm==1){
            break;
        }
    }while(close);
    clrwin(1);
    return 1;
}




void adddoc(){
    char head[30]="SET USER LOGIN";
    char usr[30]="",pwd[30]="",code[30]="";
    int a=midx/8+15+textwidth("Program Code : ");
    set=1;
    clrwin(2);
    drawwindow(head, midx/8, midy/4+16, (getmaxx()*15)/16, (getmaxy()*7)/8+16,1 );
    button("Set",midx+30,midy*3/2-22,midx+90,midy*3/2-8,7);
    button("Cancel",midx-90,midy*3/2-22,midx-30,midy*3/2-8,7);
    setcolor(15);moveto(a-textwidth("Program Code : "),midy-26);
    outtext("Program Code :");inputbox(a,midy-26,15,15);
    setcolor(15);moveto(a-textwidth("Program Code : "),midy-7);
    outtext("Username     :");inputbox(a,midy-7,15,15);
    setcolor(15);moveto(a-textwidth("Program Code : "),midy+12);
    outtext("Password     :");inputbox(a,midy+12,15,15);
    do{
        getmousepos(&buttonm,&xm,&ym);
        if(buttonm==1){
            if(xm>=a-2&&xm<=a+15*8+1&&ym>=midy-26-2&&ym<=midy-26+8){
                set=1;
            }
            if(xm>=a-2&&xm<=a+15*8+1&&ym>=midy-7-2&&ym<=midy-7+8){
                set=2;
            }
            if(xm>=a-2&&xm<=a+15*8+1&&ym>=midy+12-2&&ym<=midy+12+8){
                set=3;
            }
            if(xm>=midx-90&&ym>=midy*3/2-22&&xm<=midx-30&&ym<=midy*3/2-8){
                button("Cancel",midx-90,midy*3/2-22,midx-30,midy*3/2-8,3);
                delay(100);close=0;set=0;
            }
            
            if(xm>=midx+30&&ym>=midy*3/2-22&&xm<=midx+90&&ym<=midy*3/2-8&&strlen(code)>0&&strlen(usr)>0&&strlen(pwd)>0){
                button("Set",midx+30,midy*3/2-22,midx+90,midy*3/2-8,3);
                delay(100);close=0;set=0;
            }
        }
        if(set==4)set=1;
        if(set==1)
            //inputdat(a,midy-26,day,mon,year ,0,15);
            input(a,midy-26,code,15 ,0,15,INT);
        if(set==2)
            input(a,midy-7,usr,15 ,0,15,TEXT);
        if(set==3)
            input(a,midy+12,pwd,15 ,0,15,PASSWORD);
    }while(close);
}




void deletedoc(){
    int opt=-1,j;
    char menu[3][20]={"By ID","By Name"};
    dropmenu(menu,151,69,237,112,opt);
    do{
        getmousepos(&buttonm,&xm,&ym);
        if(xm>=151+10&&xm<=237-10&&ym>=69+8&&ym<=112-8&&buttonm==1){
            for(j=0;j<(112-69-8)/14;j++)
                if((ym-69-8)/14==j){
                    opt=j;
                    break;
                }
            dropmenu(menu,151,69,237,112,opt);
            delay(200);
            switch(opt){
                case 0: notice();break;
                case 1: notice();break;
            }
        }else if(buttonm==1){
            break;
        }
    }while(close);
    clrwin(1);
}



void searchdoc(){
    int opt=-1,j;
    char menu[4][20]={"By ID","By Last Name","By First Name","By Specialty"};
    dropmenu(menu,151,83,285,154,opt);
    do{
        getmousepos(&buttonm,&xm,&ym);
        if(xm>=151+10&&xm<=285-10&&ym>=83+8&&ym<=154-8&&buttonm==1){
            for(j=0;j<(154-83-8)/14;j++)
                if((ym-83-8)/14==j){
                    opt=j;
                    break;
                }
            dropmenu(menu,151,83,285,154,opt);
            delay(200);
            switch(opt){
                case 0: notice();break;
                case 1: notice();break;
                case 2: notice();break;
                case 3: notice();break;
            }
        }else if(buttonm==1){
            break;
        }
    }while(close);
    clrwin(1);
}















int menu(int select){
    char ch, menu[3][20]={"\360","Prisoner","About"};
    char date[11];
    struct date da;
    hidemouse();
    setfillstyle(1,3);
    setcolor(15);
    line(9,17,631,17);
    line(9,17,9,32);
    setcolor(0);
    line(631,18,631,32);
    bar(10,18,630,32);
    getdate(&da);
    setcolor(0);
    outtextxy(20,21,menu[0]);
    outtextxy(40,21,menu[1]);
    outtextxy(105,21,menu[2]);
    showmouse();
    switch(select){
        case 0: hidemouse();
            setfillstyle(9,9);
            setcolor(0);
            line(10,18,34,18);
            line(10,18,10,31);
            setcolor(15);
            line(35,18,35,32);
            line(10,32,35,32);
            bar(11,19,34,31);
            outtextxy(20,21,menu[0]);
            break;
        case 1: hidemouse();
            setfillstyle(9,9);
            setcolor(0);
            line(35,18,35,31);
            line(35,18,95,18);
            setcolor(15);
            line(95,18,95,32);
            line(35,32,95,32);
            bar(36,19,94,31);
            outtextxy(40,21,menu[1]);
            break;
        case 2: hidemouse();
            setfillstyle(9,9);
            setcolor(0);
            line(95,18,169,18);
            line(95,18,95,32);
            setcolor(15);
            line(170,18,170,31);
            line(95,32,170,32);
            bar(96,19,169,31);
            outtextxy(105,21,menu[2]);
            break;
            
            
    }
    sprintf(date,"%02d/%02d/%d",da.da_day,da.da_mon,da.da_year);
    setcolor(0);
    outtextxy(550,21,date);
    showmouse();
    return select;
}



void welgr()
{
    /* COLORS (text mode)
     ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ≥Back-≥Fore-
     Constant     ≥Value≥grnd?≥grnd?
     ÕÕÕÕÕÕÕÕÕÕÕÕÕÕÿÕÕÕÕÕÿÕÕÕÕÕÿÕÕÕÕÕ
     BLACK        ≥  0  ≥ Yes ≥ Yes
     BLUE         ≥  1  ≥ Yes ≥ Yes
     GREEN        ≥  2  ≥ Yes ≥ Yes
     CYAN         ≥  3  ≥ Yes ≥ Yes
     RED          ≥  4  ≥ Yes ≥ Yes
     MAGENTA      ≥  5  ≥ Yes ≥ Yes
     BROWN        ≥  6  ≥ Yes ≥ Yes
     LIGHTGRAY    ≥  7  ≥ Yes ≥ Yes
     DARKGRAY     ≥  8  ≥ No  ≥ Yes
     LIGHTBLUE    ≥  9  ≥ No  ≥ Yes
     LIGHTGREEN   ≥ 10  ≥ No  ≥ Yes
     LIGHTCYAN    ≥ 11  ≥ No  ≥ Yes
     LIGHTRED     ≥ 12  ≥ No  ≥ Yes
     LIGHTMAGENTA ≥ 13  ≥ No  ≥ Yes
     YELLOW       ≥ 14  ≥ No  ≥ Yes
     WHITE        ≥ 15  ≥ No  ≥ Yes
     ƒƒƒƒƒƒƒƒƒƒƒƒƒƒ≈ƒƒƒƒƒ≈ƒƒƒƒƒ≈ƒƒƒƒƒƒ
     BLINK        ≥128  ≥ No  ≥
     
     */
    clrscr();
    int i, a=(getmaxx()-textwidth("<<<               >>>"))/2;
    setfillstyle(1, BLUE);
    bar(0,0,getmaxx(),getmaxy());
    setcolor(11);
    //textcolor(11);
    //textbackground(BLUE);
    
    settextstyle(0, 0, 7);
    outtextxy((getmaxx()-textwidth("Prison"))/2,50,"Prison");
    outtextxy((getmaxx()-textwidth("Management"))/2,150,"Management");
    outtextxy((getmaxx()-textwidth("System"))/2,250,"System");
    setfillstyle(1,15);
    //left vertical bars
    bar(50,20,60,110);
    bar(30,20,40,110);
    bar(70,20,80,110);
    bar(90,20, 100,110);
    //left horizontal bars
    bar(20,50, 110, 40);
    bar(20,70, 110, 60);
    bar(20,90, 110, 80);
    
    bar(getmaxx()-90,20,getmaxx()-100,110);
    bar(getmaxx()-50,20,getmaxx()-60,110);
    bar(getmaxx()-30,20,getmaxx()-40,110);
    bar(getmaxx()-70,20,getmaxx()-80,110);
    
    bar(getmaxx()-20,40,getmaxx()-110,50);
    bar(getmaxx()-20,60,getmaxx()-110,70);
    bar(getmaxx()-20,80,getmaxx()-110,90);
    
    setcolor(9);
    do{
        settextstyle(0, 0, 1);
        setcolor(BLUE);
        outtextxy(a,getmaxy()-15,"<<<               >>>");
        setcolor(4);
        outtextxy(a,getmaxy()-15,"    PRESS ANY KEY    ");
        delay(250);if(kbhit()){getch();break;}
        setcolor(BLUE);
        outtextxy(a,getmaxy()-15,"<<<               >>>");
        setcolor(4);
        outtextxy(a,getmaxy()-15,"  < PRESS ANY KEY >  ");
        delay(250);if(kbhit()){getch();break;}
        setcolor(BLUE);
        outtextxy(a,getmaxy()-15,"<<<               >>>");
        setcolor(4);
        outtextxy(a,getmaxy()-15," << PRESS ANY KEY >> ");
        delay(250);if(kbhit()){getch();break;}
        setcolor(BLUE);
        outtextxy(a,getmaxy()-15,"<<<               >>>");
        setcolor(4);
        outtextxy(a,getmaxy()-15,"<<< PRESS ANY KEY >>>");
        delay(250);if(kbhit()){getch();break;}
    }while(1);
    setcolor(0);
    for(i=0;i<getmaxy()/4;i++){
        delay(20);
        //colliding splashscreen
        rectangle(midy-i,midy-i,getmaxx()+i-midy,midy+i);
        rectangle(i,i,getmaxx()-i,getmaxy()-i);
    }
}



void clrwin(int opt){
    if(opt==2)
        menu(-1);
    hidemouse();
    setcolor(0);
    line(9,33,631,33);
    line(9,34,9,340);
    setcolor(15);
    line(631,34,631,339);
    line(10,340,631,340);
    setfillstyle(1,11);
    bar(10,34,630,339);
    showmouse();
}



int about(){
    char str[3][35]={"Project : Prison Management System","Created by : Gunesh Shanbhag"};
    close=1;
    drawwindow("About me", midx/2, midy/2, (getmaxx()*3)/4, (getmaxy()*3)/4,1 );
    settextstyle(0,0,1);
    setcolor(15);
    for(int i=0;i<2;i++)
        outtextxy(midx/2+15,midy-50+(i*20),str[i]);
    outtextxy(midx/2+15,midy-10,"Detail : In this project I have ");
    outtextxy(midx/2+15,midy+10,"         coded in C and Graphics to");
    outtextxy(midx/2+15,midy+30,"         make the project look better.");
    button("OK",midx-30,midy*3/2-22,midx+30,midy*3/2-8,7);
    
    do{
        getmousepos(&buttonm,&xm,&ym);
        if(buttonm==1){
            if(xm>=midx-30&&ym>=midy*3/2-22&&xm<=midx+30&&ym<=midy*3/2-8){
                button("OK",midx-30,midy*3/2-22,midx+30,midy*3/2-8,3);
                delay(100);close=0;;
            }
        }
    }while(close);
    return 4;
}



void button(char name[15],int x1,int y1,int x2 ,int y2,int c){
    setfillstyle(1,c);
    setcolor(15);
    hidemouse();
    line(x1,y1,x2,y1);
    line(x1,y1,x1,y2);
    setcolor(0);
    line(x2,y1,x2,y2);
    line(x1,y2,x2,y2);
    bar(x1+1,y1+1,x2-1,y2-1);
    outtextxy((x2+x1-textwidth(name))/2,(y2+y1-textheight(name))/2,name);
    showmouse();
}



void drawwindow(char head[30],int x1, int y1, int x2, int y2, int c){
    hidemouse();
    setfillstyle(1,7);
    bar(x1,y1-14,x2,y1-2);
    setfillstyle(1,c);
    bar(x1,y1,x2,y2);
    setcolor(15);
    line(x1-1,y1-15,x2+1,y1-15);
    line(x1-1,y1-15,x1-1,y2+1);
    setcolor(0);
    line(x2+1,y1-14,x2+1,y2+1);
    line(x1-1,y2+1,x2+1,y2+1);
    line(x1,y1-1,x2,y1-1);
    setcolor(15);
    rectangle(x1+5,y1+5,x2-5,y2-5);
    setcolor(0);
    settextstyle(0,0,1);
    outtextxy((x2+x1-textwidth(head))/2,y1-12,head);
    showmouse();
    
}




int dropmenu(char menu[7][20],int x1,int y1,int x2,int y2,int opt){
    int i;
    char ch;
    setfillstyle(1,14);
    setcolor(15);
    hidemouse();
    line(x1,y1,x2,y1);
    line(x1,y1,x1,y2);
    setcolor(0);
    line(x2,y1,x2,y2);
    line(x1,y2,x2,y2);
    bar(x1+1,y1+1,x2-1,y2-1);
    rectangle(x1+5,y1+5,x2-5,y2-5);
    for(i=0;i<(y2-y1-15)/14;i++){
        if(i==opt){
            setcolor(15);
            setfillstyle(1,3);
            bar(x1+10,y1+8+(i*14),x2-10,y1+20+(i*14));
            outtextxy(x1+15,y1+10+(i*14),menu[i]);
        }else{
            setcolor(0);
            outtextxy(x1+15,y1+10+(i*14),menu[i]);
        }
    }
    showmouse();
    delay(100);
    return opt;
}


//mouse function
int initmouse(){
    i.x.ax=0;//for  initialising mouse.
    int86(0x33,&i,&o);
    return (o.x.ax);
}

void showmouse(){
    i.x.ax=1; // for displaying mouse pointer.
    int86(0x33,&i,&o);
}
void hidemouse(){
    i.x.ax=2;
    int86(0x33,&i,&o);
}

void setmousepos(int &xpos,int &ypos){
    i.x.ax=4;
    i.x.cx=xpos;
    i.x.dx=ypos;
    int86(0x33,&i,&o);
}

void restrictmouse(int x1,int y1,int x2,int y2){
    i.x.ax=7;     //to define the upper left boundry of mouse.
    i.x.cx=x1;
    i.x.dx=x2;
    int86(0x33,&i,&o);
    i.x.ax=8;   //to define the bottom right boundry of mouse.
    i.x.cx=y1;
    i.x.dx=y2;
    int86(0x33,&i,&o);
}
void getmousepos(int *buttonm,int *x, int *y){
    i.x.ax=3; //to move mouse.
    int86(0x33,&i,&o);
    *buttonm=o.x.bx;
    *x=o.x.cx;
    *y=o.x.dx;
}
//end mouse function



void inputbox(int x,int y,int limit,int bkc){
    hidemouse();
    setfillstyle(1,bkc);
    bar(x-2,y-2,x+limit*8+2,y+8);
    setcolor(0);
    line(x-3,y-3,x-3,y+9);
    line(x-3,y-3,x+limit*8+2,y-3);
    showmouse();
}

