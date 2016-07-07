#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<math.h>
#include<dos.h>

void create();
void edgeconnect(int x1,int y1,int x2,int y2);  // DDA LINE ALGORITHAM

adj[10][10],n; //'adj' is a 2D matrix, which detects adjacency matrix

struct graph
{
	int number,color,x,y;
};
struct graph ver[10];

void main()
{
	int gd=DETECT,gm;
	int i,j,k,c,col[10],m,x,p,q,chrom=0;
	int count=0;
	char cr[16][30]={"BLACK","BLUE","GREEN","CYAN","RED","MAGENTA","BROWN","LIGHTGRAY","DARKGRAY","LIGHTBLUE","LIGHTGREEN","LIGHTCYAN","LIGHTRED","LIGHTMAGENTA","YELLOW","WHITE"};
	char key;
	/*p,q are used for FLAGS.

		i,j,k are used for the loops.

		col[x] holds colors that are assigned to the -
		- previous connected nodes of that particular node.

		 m holds the maximum value of col[x], i.e, the maximum value of -
		- the color that has been used previously in its connected nodes.

		c is used to determine whether a node is isolated or not.

		chrom holds the chromatic number of the graph   */

	initgraph(&gd,&gm,"C:\\Turboc3\\BGI");
	clrscr();
	create(); //Calling  create() function.

	//This loop will draw the nodes concurrently.
	for(i=1;i<=n;i++)
	{
		setcolor(BLACK);
		circle(ver[i].x,ver[i].y,15);
		delay(800);
	}

	delay(500);

	//This loop will draw the edges.
	for(k=2;k<=n;k++)
		for(j=1;j<=k-1;j++)
			if(adj[k][j]==1)
				edgeconnect(ver[j].x,ver[j].y,ver[k].x,ver[k].y);//calling edgeconnect() function.

	delay(1000);
	clrscr();

	printf("The Graph with colors.");
	//1st node will always hold color 1.
	ver[1].color=1;
	setcolor(BLACK);
	setfillstyle(SOLID_FILL,1);
	circle(ver[1].x,ver[1].y,15);
	floodfill(ver[1].x+1,ver[1].y+1,BLACK);
	delay(800);

	/* The following procedure will determine the colors of the rest of the nodes.*/
	for(i=2;i<=n;i++)
	{
		c=0,x=0,col[x]=0,q=0;
		for(j=1;j<=i-1;j++)
		{
			if(adj[i][j]==1)
			{
				col[x]=ver[j].color; /* The color of previous connected vertices of this vertex will store in this array */
				x++;
				c++;  // If there is any connected vertex then c will increase
			}
		}

		if(c>0)  // If the vertex is not isolated
		{
			m=0;
			for(k=0;k<x;k++) // Loop to store the max value of the col[x] array
			{
				if(col[k]>m)
					m=col[k]; /* max value of the colour which has already
					 been assigned previously to the adjacent nodes,
					 will be assigned to m.*/
			}

			for(j=m-1;j>=1;j--)
			{
				p=0;      /*'p' flag is used to determine whether a color has been
					      already assigned in adjacent nodes of a particular node*/
				for(k=0;k<x;k++)
				{
					if(col[k]==j)
					{
						p++;   //If the no. of color match then it will break
						break;
					}
				}
				if(p==0)  //'p' is 0 if any color has not been used in adjacent nodes
				{
					m=j;    // So we put that color in that particular node
					q++;    // And we increment the 'q' flag to indicate this
					break;
				}
			}

			if(q==0)
				m=m+1; /*If there is no color that has not been assigned in adjacent
					nodes then q=0 and we put the next color in that particular node */
			setcolor(BLACK);
			setfillstyle(SOLID_FILL,m);
			circle(ver[i].x,ver[i].y,15);
			floodfill(ver[i].x+1,ver[i].y+1,BLACK);
			delay(800);
			ver[i].color=m;
		}

		if(c==0)   //If the vertex is Isolated then it assigns color 1 always
		{
			setcolor(BLACK);
			setfillstyle(SOLID_FILL,1);
			circle(ver[i].x,ver[i].y,15);
			floodfill(ver[i].x+1,ver[i].y+1,BLACK);
			delay(800);
			ver[i].color=1;
		}
	}

	//The following loop connects the edges
	for(i=2;i<=n;i++)
	{
		for(j=1;j<=i-1;j++)
		{
			if(adj[i][j]==1)
				line(ver[i].x,ver[i].y,ver[j].x,ver[j].y);
		}
	}


	delay(2000);
	clrscr();
	for(i=1;i<=n;i++)
	{
		if(ver[i].color>chrom)
			chrom=ver[i].color;
		printf("\n vertex = %d, color = %d",ver[i].number,ver[i].color);
	}
	printf("\nThe Chromatic no. of this graph is: %d",chrom);
	printf("\nBeta Number of this graph: \n");
	for(j=1;j<=chrom;j++)
	{
		count=0;       //count the color use number of time
		for(i=1;i<=n;i++)
		{
			if(ver[i].color==j)
			{
				count++;
			}
		}
		printf("%s=%d\n",cr[j],count);
	}
	getch();
	closegraph();
}

//Graph create
void create()
{
	int i,j,maxedge,origin,dest;
	printf("Enter the number of nodes of the graph: ");
	scanf("%d",&n);
	if(n==0)
	{
		printf("\nNumber of node is 0");
		getch();
		exit(0);
	}
	maxedge=(n*(n-1))/2;
	for(i=1;i<=n;i++)
	{
		ver[i].number=i;
		printf("Enter the x axis and y axis of circle %d : ",i);
		scanf("%d %d",&ver[i].x,&ver[i].y);
	}
	printf("\nSo the maximum number of edges should be : %d\n\n",maxedge);
	for(i=1;i<=maxedge;i++)
	{
		printf("Enter edge %d ( put 0 0 to quit ) : ",i);
		scanf("%d %d",&origin,&dest);

		if((origin==0) && (dest==0))
			break;
		if(origin>n || dest>n || origin<=0 || dest<=0)
		{
			printf("Invalid edge!\n");
			i--;
		}
		else
		{
			adj[origin][dest]=1;
			adj[dest][origin]=1;
		}
	}
	clrscr();
}

// DDA LINE ALGORITHAM
void edgeconnect(int x1,int y1,int x2,int y2)
{
	float x,y,xinc,yinc,dx,dy;
	int k,step;

	dx=x2-x1;
	dy=y2-y1;
	if(abs(dx)>abs(dy))
		step=abs(dx);
	else
		step=abs(dy);
	xinc=dx/step;
	yinc=dy/step;
	x=x1;
	y=y1;
	putpixel(x,y,0);
	for(k=1;k<=step;k++)
	{
		x=x+xinc;
		y=y+yinc;
		putpixel(x,y,0);
		delay(20);
	}
}