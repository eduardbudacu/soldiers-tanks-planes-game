#include<iostream.h>
#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#include<fstream.h>

#include "GUI.H"
#include "BMPLOAD.CPP"
int  SOLDATI = 10,
     TANCURI = 5,
     AVIOANE = 5;

int btn[102][5], btn2[102][5], atacate[100];
int  max=100;

int jucator[10][10], calculator[10][10];

int nr_soldati = SOLDATI,
    nr_tanc    = TANCURI,
    nr_avioane = AVIOANE,

    nr_soldati_c = nr_soldati,
    nr_tanc_c    = nr_tanc,
    nr_avioane_c = nr_avioane;


char nume[50];


void search(int no)
{}


void set_matrice()  // reseteaza matricea jucatorului
{
int i,j;
for(i=1;i<=10;i++)
for(j=1;j<=10;j++)
jucator[i][j]=0;
}

void set_matrice_calc() // reseteaza matricea calculatorului
{
int i,j;
for(i=1;i<=10;i++)
for(j=1;j<=10;j++)
calculator[i][j]=0;
for(i=1;i<=100;i++)
atacate[i]=i;
}

void sterg(int x)
{
int i,aux;
for(i=x;i<=max;i++)
atacate[i]=atacate[i+1];
}


void desen_front() //deseneaza frontul
{int i,j,t=0;

 hidemouse();
 setcolor(5);
 for(i=0;i<10;i++)
  for(j=0;j<10;j++)
  {t++;
   rectangle(15+i*30,15+j*30,45+i*30,45+j*30);
   activate(15+i*30,15+j*30,45+i*30,45+j*30,t,btn,1);
   }
}

void desen_atac()   //deseneaza tabla de atac
{int i,j,t=0;

 setcolor(1);
 moveto(15,330);
 outtext("TABLA DE ATAC");
 for(i=0;i<10;i++)
  for(j=0;j<10;j++)
 {t++;
  rectangle(15+10*i,340+j*10,25+10*i,350+j*10);
  activate(15+10*i,340+j*10,25+10*i,350+j*10,t,btn2,1);
  }
 buttonon(600,0,635,15,"EXIT",1);
 activate(600,0,635,15,101,btn2,1);
 activate(600,0,635,15,101,btn,1);
}


void desen_tanc(int x,int y)  //deseneaza un tanc la coordonatele x, y

{
readdata("tanc.bmp",x,y);
desen_front();
showmouse();
}

void desen_avion(int x,int y) //deseneaza un avion la coordonatele x, y

{
readdata("avion.bmp",x,y);
desen_front();
showmouse();
}

void desen_soldat(int x,int y) //deseneaza un soldat  la coordonatele x, y
{
readdata("soldat.bmp",x,y);
desen_front();
showmouse();
}


int aranjez_armata()
{

int a,nr=0;

//deseneaza dreptunghiul pentru mesaje
setcolor(6);
moveto(350,20);
outtext("MESAJE");
rectangle(350,30,550,100);

//reseteaza matricea jucatorului
set_matrice();

while(nr < SOLDATI+TANCURI+AVIOANE )
{
 showmouse();
 a = getlink(1,101,btn);  // returneaza numarul butonului apasat

 hidemouse();
 initmouse();
 showmouse();
 hidemouse();

 if(a==101)// daca se apasa X pentru iesire
   {
    buttonclick(600,0,635,15);
    delay(100);
    buttonon(600,0,635,15,"EXIT",1);

    showmouse();
    int t=confirm("VREI SA IESI?","IESIRE");
    showmouse();

    if(t==1) return 0;

     while(a==101)
      {
      showmouse();
      a=getlink(1,101,btn);

      hidemouse();
      initmouse();
      showmouse();
	       if(a==101){
		      buttonclick(600,0,635,15);
		      delay(100);
		      buttonon(600,0,635,15,"EXIT",1);
		      showmouse();
		      t=confirm("VREI SA IESI?","IESIRE");
			 }
		 if(t==1) return 0;



	       }
	   }
  hidemouse();

 // verifica daca pozitia este ocupata sau nu
 // daca in matricea jucator este 0 pozitia este libera
 if(jucator[btn[a][1]/30+1][btn[a][2]/30]!=0 && a!=101)
 {
  //scrie mesaj
  moveto(370,50);
  setcolor(10);
  outtext("POZITIE OCUPATA");

  sound(500);
  delay(500);
  nosound();

  //sterge mesaj
  moveto(370,50);
  setcolor(0);
  outtext("POZITIE OCUPATA");
  nr--;
 }

 else if(nr < SOLDATI)
       {
       desen_soldat(btn[a][0],btn[a][1]);
       jucator[btn[a][1]/30+1][btn[a][2]/30]=1;
       }
      else if(nr< SOLDATI + TANCURI)
	    {
	    desen_tanc(btn[a][0],btn[a][1]);
	    jucator[btn[a][1]/30+1][btn[a][2]/30]=2;
	    }
	   else
	    {
	    desen_avion(btn[a][0],btn[a][1]);
	    jucator[btn[a][1]/30+1][btn[a][2]/30]=3;
	    }


 nr++;
 showmouse();

 }

 moveto(370,50);
 setcolor(10);
 outtext("GATA DE LUPTA");
 moveto(370,60);
 outtext("APASA ORICE TASTA");
 getch();
 moveto(370,50);
 setcolor(0);
 outtext("GATA DE LUPTA");
 moveto(370,60);
 outtext("APASA ORICE TASTA");
return 1;

}

//aranjeaza armata calculatorului
// matricea este completata folosind functia random
void aranjez_armata_calc()
{int i,j,nr=0;
set_matrice_calc();
 randomize();
 while(nr< SOLDATI + TANCURI + AVIOANE)
 { i=random(30000)%10+1;
   j=random(30000)%10+1;
  if(calculator[i][j]!=0)nr--;
  else if(nr < SOLDATI) calculator[i][j]=1;
       else if(nr < SOLDATI + TANCURI) calculator[i][j]=2;
       else calculator[i][j]=3;
   nr++;
 }
}


int atac()
 {
 int c;
 showmouse();
 setcolor(10);
 moveto(370,50);
 outtext("ATACA ");
 c=getlink(1,101,btn2);
 setcolor(0);
 moveto(370,50);
 outtext("ATACA ");

 //se ocupa de butonul de iesire
 if(c==101){
    buttonclick(600,0,635,15);
    delay(100);
    buttonon(600,0,635,15,"EXIT",1);

	   showmouse();
	   int t=confirm("VREI SA IESI?","IESIRE");
	   showmouse();

	   if(t==1) return 0;

	       while(c==101)
		{showmouse();
		 c=getlink(1,101,btn2);

		 hidemouse();
		 initmouse();
		 showmouse();
	       if(c==101){
		       buttonclick(600,0,635,15);
		       delay(100);
		       buttonon(600,0,635,15,"EXIT",1);
		      showmouse();
		      t=confirm("VREI SA IESI?","IESIRE");
			 }
		 if(t==1) return 0;
		 

		
	       }
	   }
 hidemouse();
 initmouse();
 showmouse();
 hidemouse();


 setcolor(10);
 if(calculator[btn[c][1]/30+1][btn[c][2]/30]>0&&calculator[btn[c][1]/30+1][btn[c][2]/30]<10)
   {

    calculator[btn[c][1]/30+1][btn[c][2]/30] = calculator[btn[c][1]/30+1][btn[c][2]/30]*10;
    setcolor(4);
    moveto(370,50);
    outtext("AI NIMERIT!!");

    sound(500);
    delay(1000);
    nosound();


    setcolor(0);
    moveto(370,50);
    outtext("AI NIMERIT!!");
    setcolor(4);
    setfillstyle(1,4);
    circle(btn2[c][0]+5,btn2[c][1]+5,3);
    floodfill(btn2[c][0]+5,btn2[c][1]+5,4);

  switch(calculator[btn[c][1]/30+1][btn[c][2]/30])
  {
   case 10: nr_soldati_c--;break;
   case 20: nr_tanc_c--;break;
   case 30: nr_avioane_c--;break;
  }


   }

else{

    setcolor(4);
    moveto(370,50);
    outtext("NU AI NIMERIT!!");
    sound(400);
    delay(500);
    nosound();
    setcolor(0);
    moveto(370,50);
    outtext("NU AI NIMERIT!!");

    setcolor(10);
    line(btn2[c][0],btn2[c][1],btn2[c][2],btn2[c][3]);}
return 1;
}

//ataca calculatorul
void AI_ATAC()
{int c,poz;

poz = random(30000)%max+1;
c = atacate[poz];
sterg(poz);
max--;




 if(jucator[btn[c][1]/30+1][btn[c][2]/30]>0 &&jucator[btn[c][1]/30+1][btn[c][2]/30]<10 )
  {
    jucator[btn[c][1]/30+1][btn[c][2]/30]=jucator[btn[c][1]/30+1][btn[c][2]/30]*10;

    setcolor(10);
    line(btn[c][0],btn[c][1],btn[c][2],btn[c][3]);
 //mesaj
    setcolor(4);
    moveto(370,50);
    outtext("AI FOST NIMERIT");

    sound(500);
    delay(1000);
    nosound();

    setcolor(0);
    moveto(370,50);
    outtext("AI FOST NIMERIT!!");
 switch(jucator[btn[c][1]/30+1][btn[c][2]/30])
  {
   case 10: nr_soldati--;break;
   case 20: nr_tanc--;break;
   case 30: nr_avioane--;break;
  }

  }

 else {
      setcolor(4);
      moveto(370,50);
      outtext("CALCULATORUL A RATAT");

      sound(500);
      delay(500);
      nosound();

      setcolor(0);
      moveto(370,50);
      outtext("CALCULATORUL A RATAT");

      setcolor(4);
      circle(btn[c][0]+15,btn[c][1]+15,10);
      setfillstyle(1,4);
      floodfill(btn[c][0]+15,btn[c][1]+15,4);
      }

}

int final_joc()
{

char aux[10];
setcolor(1);
line(280,50,280,400);
rectangle(50,50,520,400);
setcolor(4);
moveto(340 ,120);
outtext("JUCATOR:");


itoa(SOLDATI-nr_soldati,aux,10);
moveto(370,150);
outtext(aux);

if(SOLDATI-nr_soldati!=1)
{
 moveto(370,160);
 outtext("OAMENI PIERDUTI");
}
else
{
 moveto(370,160);
 outtext("OM PIERDUT");
}

moveto(370,180);
itoa(TANCURI-nr_tanc,aux,10);
outtext(aux);
if(TANCURI-nr_tanc!=1)
{
 moveto(370,190);
 outtext("TANCURI PIERDUTE");
}
else
{
moveto(370,190);
outtext("TANC PIERDUT");
}

moveto(370,210);
itoa(AVIOANE-nr_avioane,aux,10);
outtext(aux);
if(5-nr_avioane!=1)
{
moveto(370,230);
outtext("AVIOANE PIERDUTE");
}
else
{
moveto(370,230);
outtext("AVION PIERDUT");
}

moveto(100,120);
outtext("CALCULATOR:");

itoa(SOLDATI-nr_soldati_c,aux,10);
moveto(70,150);
outtext(aux);
if(15-nr_soldati_c!=1)
{
moveto(70,160);
outtext("OAMENI PIERDUTI");
}
else
{
moveto(70,160);
outtext("OM PIERDUT");
}
moveto(70,180);
itoa(TANCURI-nr_tanc_c,aux,10);
outtext(aux);
if(5-nr_tanc_c!=1)
{
moveto(70,190);
outtext("TANCURI PIERDUTE");
}
else
{
moveto(70,190);
outtext("TANC PIERDUT");
}
moveto(70,210);
itoa(AVIOANE-nr_avioane_c,aux,10);
outtext(aux);
if(5-nr_avioane_c!=1)
{
moveto(70,230);
outtext("AVIOANE PIERDUTE");
}
else
{
moveto(70,230);
outtext("AVION PIERDUT");
}
activate(600,0,635,15,101,btn2,1);
activate(600,0,635,15,101,btn,1);
buttonon(600,0,635,15,"EXIT",1);
 hidemouse();
 initmouse();
 showmouse();
 

int a;
a = getlink(1,101,btn);  // returneaza numarul butonului apasat

 hidemouse();
 initmouse();
 showmouse();


 if(a==101)// daca se apasa X pentru iesire
   {
    buttonclick(600,0,635,15);
    delay(100);
    buttonon(600,0,635,15,"EXIT",1);

    showmouse();
    int t=confirm("VREI SA IESI?","IESIRE");
    showmouse();

    if(t==1) return 0;

     while(a==101)
      {
      showmouse();
      a=getlink(1,101,btn);

      hidemouse();
      initmouse();
      showmouse();
	       if(a==101){
		      buttonclick(600,0,635,15);
		      delay(100);
		      buttonon(600,0,635,15,"EXIT",1);
		      showmouse();
		      t=confirm("VREI SA IESI?","IESIRE");
			 }
		 if(t==1) return 0;



	       }
	   }
  hidemouse();
return 1;
}

void arata_fronturi()
{
 desen_front();
 int i,j;
for(i=1;i<=10;i++)
for(j=1;j<=10;j++)
 {
 if(jucator[i][j]==1||jucator[i][j]==10)
       if(jucator[i][j]==1)desen_soldat(j*30-15,(i-1)*30+15);
       else {desen_soldat(j*30-15,(i-1)*30+15);
	     setcolor(10);
	     line(j*30-15,(i-1)*30+15,j*30+15,(i-1)*30+45);}
 if(jucator[i][j]==2||jucator[i][j]==20)
       if(jucator[i][j]==2)desen_tanc(j*30-15,(i-1)*30+15);
       else {desen_tanc(j*30-15,(i-1)*30+15);
	     setcolor(10);
	     line(j*30-15,(i-1)*30+15,j*30+15,(i-1)*30+45);}
 if(jucator[i][j]==3||jucator[i][j]==30)
       if(jucator[i][j]==3)desen_avion(j*30-15,(i-1)*30+15);
       else {desen_avion(j*30-15,(i-1)*30+15);
	     setcolor(10);
	     line(j*30-15,(i-1)*30+15,j*30+15,(i-1)*30+45);}
 }

 getch();
 cleardevice();
 setcolor(0);
 moveto(100,0);
 outtext("FRONTUL TAU");
 desen_front();

for(i=1;i<=10;i++)
for(j=1;j<=10;j++)
 {
 if(calculator[i][j]==1||calculator[i][j]==10)
       if(calculator[i][j]==1)desen_soldat(j*30-15,(i-1)*30+15);
       else {desen_soldat(j*30-15,(i-1)*30+15);
	     setcolor(10);
	     line(j*30-15,(i-1)*30+15,j*30+15,(i-1)*30+45);}
 if(calculator[i][j]==2||calculator[i][j]==20)
       if(calculator[i][j]==2)desen_tanc(j*30-15,(i-1)*30+15);
       else {desen_tanc(j*30-15,(i-1)*30+15);
	     setcolor(10);
	     line(j*30-15,(i-1)*30+15,j*30+15,(i-1)*30+45);}
 if(calculator[i][j]==3||calculator[i][j]==30)
       if(calculator[i][j]==3)desen_avion(j*30-15,(i-1)*30+15);
       else {desen_avion(j*30-15,(i-1)*30+15);
	     setcolor(10);
	     line(j*30-15,(i-1)*30+15,j*30+15,(i-1)*30+45);}
 }

}


int citeste_fisier_setari()
{
fstream f("setari.in", ios::in);
int citit;
f>>citit;
SOLDATI = citit;
f>>citit;
TANCURI = citit;
f>>citit;
AVIOANE = citit;
if(SOLDATI == 0 || TANCURI == 0 || AVIOANE == 0)
 {
 SOLDATI = 10;
 TANCURI = 5;
 AVIOANE = 5;
 }

nr_soldati = SOLDATI;
nr_tanc    = TANCURI;
nr_avioane = AVIOANE;

nr_soldati_c = nr_soldati;
nr_tanc_c    = nr_tanc;
nr_avioane_c = nr_avioane;
f.close();
return 1;
}

int scrie_fisier_setari(int sol, int tanc, int avion)
{
fstream f("setari.in", ios::out);

f<<sol;
f<<"#soldati\n";
f<<tanc;
f<<"#tancuri\n";
f<<avion;
f<<"#avioane\n";

f.close();
}
int joc(int tip)
{

 setcolor(5);
 moveto(100,0);
 outtext("FRONTUL TAU");
 desen_front();
 desen_atac();
 showmouse();

int c,distrus=0;

if(aranjez_armata() == 0) return 0;
aranjez_armata_calc();

c=0;

 while( c < tip && distrus == 0)
 {
  if(atac()==0)return 0;
  setcolor(10);
  moveto(370,50);
  outtext("CALCULATORUL ATACA");
  delay(500);
  setcolor(0);
  moveto(370,50);
  outtext("CALCULATORUL ATACA");
  AI_ATAC();
  if(nr_soldati==0&&nr_tanc==0&&nr_avioane==0)distrus=1;
  if(nr_soldati_c==0&&nr_tanc_c==0&&nr_avioane_c==0)distrus=1;
  c++;
 }


  getch();
 cleardevice();
 arata_fronturi();

  getch();
 cleardevice();
 final_joc();



return 1;
}
main()
{
initaddons();
char *list[]={"JOC NOU","SETARI","IESIRE"};
char *list2[]={"PANA LA MOARTE","ALEGE NUMARUL DE FOCURI", "RENUNTA"};
int ch,ch2;
int nr_focuri = 0;




while(ch != 3)
{

citeste_fisier_setari();

cleardevice();
hidemouse();
setcolor(2);
rectangle(0,0,630,470);
setfillstyle(1,2);
floodfill(5,5,2);

setcolor(1);
moveto(250,120);
showmouse();
outtext("MENIU");
ch = activemenu(200,150,list,3,30);


 switch(ch)
 { case 1:{delay(100);
	   ch2 = activemenu(200,170,list2,3,30);
	    switch(ch2)
	     {
	      case 1:{
		      cleardevice();
		      initmouse();
		      joc(105);
		      }break;
	      case 2:{
		      hidemouse();
		      while(nr_focuri == 0)

		      {
		      clrscr();
		      cleardevice();

		      cout<<"TREBUIE SA INTRODUCI UN NUMAR MAI MARE DE 0!"<<endl;
		      cout<<"NUMAR FOCURI:"; cin>>nr_focuri;

		      }
		      clrscr();
		      cleardevice();
		      cout<<"AI ALES "<<nr_focuri<<" FOCURI!"<<endl;
		      cout<<"apasa orice tasta pentru a juca...";
		      getch();
		      cleardevice();
		      initmouse();

		      joc(nr_focuri);
		      }break;
	      case 3:{
	             }break;
	     }
	  }break;
  case 2 : {
	   cleardevice();
	   int sol, tanc, avion;
	   cout<<"INTODUCETI NUMARUL DE SOLDATI, TANCURI si AVIOANE!"<<endl;
	   cout<<"NR SOLDATI:"; cin>>sol;
	   cout<<"NR TANCURI:"; cin>>tanc;
	   cout<<"NR AVIOANE:"; cin>>avion;
	   scrie_fisier_setari(sol, tanc, avion);
	   cleardevice();
	   cout<<"DATELE AU FOST SALVATE!"<<endl<<"apasa orice tasta pentru a continua...";
	   getch();
	   }break;

 }

}
exit(1);


return 0;
}