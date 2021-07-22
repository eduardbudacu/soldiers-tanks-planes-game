#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<math.h>
#include<alloc.h>
#include<bios.h>
#include<string.h>
#include<dir.h>
#include<ctype.h>
#include<process.h>
#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<fstream.h>
#include<io.h>
#include<fcntl.h>
ifstream fp;

int p[16]={BLACK,RED,GREEN,BROWN,BLUE,MAGENTA,BROWN,DARKGRAY,LIGHTGRAY,LIGHTRED,LIGHTGREEN,YELLOW,LIGHTBLUE,BLUE,LIGHTCYAN,WHITE};
void loadbmp(char *name,int offset, int w, int h,int x,int y);

void readdata(char *name,int x,int y)
{

	fp.open(name);
	if (!fp) {
		fp.close();
		setcolor(RED);
		cout<<"Error Opening file "<<name<<"\nMake sure all the required Files are in the same directory and they are not in use.\t";cout<<"\n\t\tPress enter to exit.";
		getche();
		exit(1);
		}
	int data1;
	long data2;
	int type;
	fp.read((char*)&type,sizeof(type));
	fp.read((char*)&data2,sizeof(data2));
	fp.read((char*)&data2,sizeof(data2));
	fp.read((char*)&data2,sizeof(data2));
	int offset=data2;
	fp.read((char*)&data2,sizeof(data2));
	fp.read((char*)&data2,sizeof(data2));
	int w=data2;
	fp.read((char*)&data2,sizeof(data2));
	int h=data2;
	fp.read((char*)&data1,sizeof(data1));
	fp.read((char*)&data1,sizeof(data1));

	fp.read((char*)&data2,sizeof(data2));
	fp.read((char*)&data2,sizeof(data2));
	fp.read((char*)&data2,sizeof(data2));
	fp.read((char*)&data2,sizeof(data2));
	fp.read((char*)&data2,sizeof(data2));
	fp.read((char*)&data2,sizeof(data2));

	loadbmp(name,offset,w,h,x,y);
	fp.close();
}

void loadbmp(char *name,int offset, int w, int h,int x,int y) {
	char data3;
	fp.seekg(offset);
	int a=w;
	if(w%8!=0)
	a=(w+8)-(w%8);
	int  count=0,row=h;
	long pos;

	while(row>0 && count<a)
	{
		while(!fp.eof())
		{
			fp.read(&data3 , sizeof(data3));

		     if(p[(data3 & 0x0f)]!=0)putpixel(count+x , row+y ,p[(data3 & 0x0f)]);
			count++;

		     if(p[(data3 & 0x0f)]!=0)putpixel(count+x , row+y ,p[(data3 & 0x0f)]);
			count++;


			if(count>=a)
			{
				count=0;
				row-=1;
			}
		}

		fp.tellg();
		fp.close();
		fp.open(name);
		count++;
		if(count==a)
			count=0;
		count++;
		if(count==a)
			count=0;

		fp.seekg(pos+2);
	}
// return 0;
}
