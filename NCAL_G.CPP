#include<graphics.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
union REGS in,out;

void hide()
{
	in.x.ax=2;
	int86(0x33,&in,&out);
}

void show()
{
	in.x.ax=1;
	int86(0x33,&in,&out);
}

void status(int *x,int *y,int *m)
{
	in.x.ax=3;
	int86(0x33,&in,&out);
	*m=out.x.bx;
	*x=out.x.cx;
	*y=out.x.dx;
}

int chack_date(long, long, long);
void cal(long ,long,long);

void creat(int d,int m,int y)
{
	int sd;
	char dt[12];
	setcolor(YELLOW);
	setbkcolor(BLUE);
	settextjustify(1,1);
	setfillstyle(SOLID_FILL,15);
	bar(10,10,500,470);
	setfillstyle(SOLID_FILL,3);
	bar(10,10,500,50);
	settextstyle(10, HORIZ_DIR, 1);
	outtextxy(225,25,"My Calender ");
	setfillstyle(SOLID_FILL,4);
	bar(450,10,500,50);
	settextstyle(0, HORIZ_DIR, 5);
	outtextxy(475,33,"X");

	setfillstyle(SOLID_FILL,6);
	bar(10,400,500,470);
	setfillstyle(SOLID_FILL,5);
	bar(250,400,500,470);
	setfillstyle(SOLID_FILL,1);
	bar(260,410,370,460);
	bar(380,410,490,460);
	settextstyle(1, HORIZ_DIR, 4);
	outtextxy(315,435,"Today");
	outtextxy(435,435,"Go-To");

	outtextxy(125,410,"Date :");
	sprintf(dt,"%d/%d/%d",d,m,y);
	outtextxy(125,440,dt);

	setcolor(BLUE);

	// for holizontal lines
	line(10,100,500,100);
	line(10,150,500,150);
	line(10,200,500,200);
	line(10,250,500,250);
	line(10,300,500,300);
	line(10,350,500,350);
	line(10,400,500,400);

	// for vertical lines
	line(80,50,80,400);
	line(150,50,150,400);
	line(220,50,220,400);
	line(290,50,290,400);
	line(360,50,360,400);
	line(430,50,430,400);

	settextstyle(1, HORIZ_DIR, 2);
	outtextxy(45,75,"Sun");
	outtextxy(115,75,"Mon");
	outtextxy(185,75,"Tue");
	outtextxy(255,75,"Wed");
	outtextxy(325,75,"Thu");
	outtextxy(395,75,"Fri");
	outtextxy(465,75,"Sat");

	cal(m,y,d);

	settextjustify(0,2);

}

void main()
{
	struct date dd;
	int gdriver = DETECT, gmode, errorcode;
	int xx,yy,mm;
	char xp[4],yp[4],mp[3];
	char ex='n';
	int ch=0;
	long day,mon,year,nd,nm,ny;

Rerun:
{
	getdate(&dd);
	day=long(dd.da_day);
	mon=long(dd.da_mon);
	year=long(dd.da_year);
	goto Start;

};
Start:

	initgraph(&gdriver, &gmode, "c:\\tc\\bgi");
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1); /* terminate with an error code */
	}


	creat(day,mon,year);

	while(1)
	{
		show();
		status(&xx,&yy,&mm);
		if(mm==1)
		{
			if(xx>=450 && xx<=500 && yy>=10 && yy<=50 )
			{
				hide();
				setcolor(RED);
				setfillstyle(SOLID_FILL,YELLOW);
				bar(10,100,500,300);
				settextstyle(1, HORIZ_DIR, 4);
				settextjustify(1,1);
				outtextxy(250,200,"Do you want to exit (Y/N)?");
				ex=getch();
				if(ex=='y' || ex=='Y')
				{
					exit(0);
				}
				cleardevice();
				day=long(dd.da_day);
				mon=long(dd.da_mon);
				year=long(dd.da_year);
				creat(day,mon,year);
			}
			if(xx>=260 && xx<=370 && yy>=410 && yy<=460 )
			{
				goto Rerun;
			}
			if(xx>=380 && xx<=490 && yy>=410 && yy<=460 )
			{
				hide();
				closegraph();
				clrscr();
				printf("Enter the Date between 01/01/1940 to 31/12/2099\n");
				printf("Enter the day of month    : ");
				scanf("%ld",&day);
				printf("Enter the Month (as MM)   : ");
				scanf("%ld",&mon);
				printf("Enter the Year ( as YYYY) : ");
				scanf("%ld",&year);
				ch=chack_date(day,mon,year);
				if(ch==1)
				{
					printf("\nNot a valid date.\n");
					printf("Press any key to go today...");
					getch();
					goto Rerun;
				}
				else
				{
					goto Start;
				}
			}

		}
	}
}

int chack_date(long d,long m,long y)
{
	int a=0;
	if(y>=1940 && y<=2099)
	{
		if(m>0 && m<13)
		{
			if(m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12)
			{
				if(d>0 && d<=31)
				{
					a=0;
				}
				else
				{
					a=1;
				}
			}
			else if(m==2)
			{
				if(y%4==0)
				{
					if(d>0 && d<=29)
					{
						a=0;
					}
					else
					{
						a=1;
					}
				}
				else
				{
					if(d>0 && d<=28)
					{
						a=0;
					}
					else
					{
						a=1;
					}
				}
			}
			else if(m==4 || m==6 || m==9 || m==11)
			{
				if(d>0 && d<=30)
				{
					a=0;
				}
				else
				{
					a=1;
				}
			}
		}
		else
		{
			a=1;
		}

	}
	else
	{
		a=1;
	}
	return a;
}

void cal(long m,long ye, long day)
{
	long l,i,x,q,p,mx,my,Fd;
	unsigned long d,n,c,t;
	char aq[5];
	if(m<=12 && m>0)
	{
		n=ye-1940;
		c=n*365;
		t=n/4;
		if(m==1)
		{
			q=0;
			p=31;
		}
		else if(m==2)
		{
			q=31;
			if(ye%4==0)
				p=29;
			else
				p=28;
		}
		else if(m==3)
		{
			q=59;
			p=31;
		}
		else if(m==4)
		{
			q=90;
			p=30;
		}
		else if(m==5)
		{
			q=120;
			p=31;
		}
		else if(m==6)
		{
			q=151;
			p=30;
		}
		else if(m==7)
		{
			q=181;
			p=31;
		}
		else if(m==8)
		{
			q=212;
			p=31;
		}
		else if(m==9)
		{
			q=243;
			p=30;
		}
		else if(m==10)
		{
			q=273;
			p=31;
		}
		else if(m==11)
		{
			q=304;
			p=30;
		}
		else
		{
			q=334;
			p=31;
		}
		if(ye%4==0 && m>2)
		{
			q=q+1;
			d=c+t+q;
		}
		else if(ye%4==0 && m<=2)
		{
			d=c+t+q;
		}
		else
		{
			d=c+t+q+1;
		}
		l=d%7;
		mx=45;
		my=125;
		if(l==6)
		{
			x=1;
			mx=45;
		}
		else if(l==0)
		{
			x=2;
			mx=115;
		}
		else if(l==1)
		{
			x=3;
			mx=185;
		}
		else if(l==2)
		{
			x=4;
			mx=255;
		}
		else if(l==3)
		{
			x=5;
			mx=325;
		}
		else if(l==4)
		{
			x=6;
			mx=395;
		}
		else if(l==5)
		{
			x=7;
			mx=465;
		}
		else
		{
			;
		}

		for(i=1;i<=p;i++)
		{
			if(x==1)
			{
				setcolor(RED);
			}
			else
			{
				setcolor(BLUE);
			}
			if(i==day)
			{
				setfillstyle(SOLID_FILL,RED);
				bar(mx-35,my-25,mx+35,my+25);
				setcolor(YELLOW);
			}
			sprintf(aq,"%ld",i);
			outtextxy(mx,my,aq);
			x++;
			mx=mx+70;
			if(x==8)
			{
				x=1;
				my=my+50;
				mx=45;
			    /*	if(my>=350)
				{
					my=125;
				} */
			}

		}
	}

}


