#include<iostream>
#include<vector>
#include<fstream>
#include<stdlib.h>
using	namespace	std;

void	print(char	board[20][80])
{
for(int	i=0;i<80;i++)
cout<<"-";
cout<<endl;
for(int	i=0;i<20;i++)
{
cout<<"|";
for(int	j=0;j<80;j++)
cout<<board[i][j];
cout<<"|"<<endl;
}
for(int	i=0;i<80;i++)
cout<<"-";
cout<<endl;
}

class	food;
class	snake
{
int	x;
int	y;
char	value;
public:
int	getx()
{
return	x;
}
int	gety()
{
return	y;
}
void	set(int	i,int	j)
{
x=i;y=j;
}
void	setval(char	ch)
{
value=ch;
}
void	movesnake(char	b[20][80])
{
b[x][y]=value;
}
friend	void	checksn	(food	&f,vector<snake>	&n);
friend	void	check(food	&f,vector<snake>	&v,int	size,int	a,int	b);
friend	int	movingsnake(char	b[20][80],char	ch,vector<snake>	&v,int	size,int	&a,int	&bo);
};

class	food
{
int	x;
int	y;
char	value;
public:
food()
{
	x=y=4;
	value='F';
}
food(int	i,int	j)
{
x=rand()%20;y=rand()%80;value='F';
}
void	set(int	i,int	j)
{
x=i;y=j;
}
int	getx()
{
return	x;
}
int	gety()
{
return	y;
}
void	move(char	b[20][80])
{
b[x][y]=value;
}
friend	void	checksn	(food	&f,vector<snake>	&n);
friend	void	check(food	&f,vector<snake>	&v,int	size,int	a,int	b);
};

void	checksn	(food	&f,vector<snake>	&v)
{
int	flag=1;
while(flag)
{
flag=1;
for(int	i=0;i<v.size();i++)
if(v[i].getx()==f.getx()	&&	v[i].gety()==f.gety())
flag=2;
if(flag==2)
{
f.set(f.getx()+2,f.gety()+2);
}
if(flag==1)
break;
}
}


int	main()
{
int	m;
char	board[20][80];
for(int	i=0;i<20;i++)
for(int	j=0;j<80;j++)
board[i][j]=' ';
vector<snake>	v(4);
food	f(1,60);
char	ch='H';
m=5;

cout<<"Do you want to resume?y/n"<<endl;
char	choice;
cin>>choice;
if(choice=='y')
{
fstream	fo("snakebackup.txt");
int	x,y,i=0;
fo>>x;
v.resize(x);
while(fo>>x)
{
fo>>y;
v[i].setval(ch);
v[i].set(x,y);
ch='#';
i++;
}
v[v.size()-1].setval('T');
for(int	i=0;i<v.size();i++)
v[i].movesnake(board);
fo.close();
}
else{
fstream	fo("snakebackup.txt");
int	x;
fo.clear();
fo.close();
for(int	i=0;i<4;i++)
{
	v[i].set(4,m);
	m++;
	v[i].setval(ch);
	ch='#';
	if(i==3)
	v[i].setval('T');
	v[i].movesnake(board);
}}
checksn(f,v);
f.move(board);
print(board);
int	operations=1;
int	a=0,b=0;
while(operations)
{
int	flag=0;
cin>>ch;
if(movingsnake(board,ch,v,v.size(),a,b))
cout<<"Error"<<endl;
check(f,v,v.size(),a,b);
for(int	i=0;i<v.size();i++)
v[i].movesnake(board);
checksn(f,v);
f.move(board);
for(int	i=2;i<v.size();i++)
if(v[0].getx()==v[i].getx()	&&	v[0].gety()==v[i].gety())
flag=1;
if(flag==1)
{
break;
}
else
{
int	x;
fstream	fo("snakebackup.txt",std::ifstream::out|std::ifstream::trunc);
fo<<v.size()<<endl;
for(int	i=0;i<v.size();i++)
{
fo<<v[i].getx()<<endl<<v[i].gety()<<endl;
}
fo.close();
}
print(board);
}
cout<<"Game Over.Better Luck Next Time!"<<endl;
return	0;
}
int	movingsnake(char	b[20][80],char	ch,vector<snake>	&v,int	size,int	&a,int	&bo)
{
a=v[v.size()-1].getx();bo=v[v.size()-1].gety();
int	m=v[0].getx(),n=v[0].gety(),flag=0;
if(ch=='u')
{
if(v[0].getx()!=0)
v[0].set(v[0].getx()-1,v[0].gety());
else
v[0].set(19,v[0].gety());
}
else	if(ch=='l')
{
if(v[0].gety()!=0)
v[0].set(v[0].getx(),v[0].gety()-1);
else
v[0].set(v[0].getx(),79);
}
else	if(ch=='r')
{
if(v[0].gety()!=79)
v[0].set(v[0].getx(),v[0].gety()+1);
else
v[0].set(v[0].getx(),0);
}
else
{if(v[0].getx()!=19)
v[0].set(v[0].getx()+1,v[0].gety());
else
v[0].set(0,v[0].gety());
}
if(v[1].getx()==v[0].getx()	&&	v[1].gety()==v[0].gety())
flag=1;
if(flag==0)
{
b[v[v.size()-1].getx()][v[v.size()-1].gety()]=' ';
for(int	i=v.size()-1;i>1;i--)
v[i].set(v[i-1].getx(),v[i-1].gety());
v[1].set(m,n);
}
else
v[0].set(m,n);
return	flag;
}
void	check(food	&f,vector<snake>	&v,int	size,int	a,int	b)
{
if(f.getx()==v[0].getx()	&&	f.gety()==v[0].gety())
{
int	m=v[size-1].getx(),n=v[size-1].gety();
v[size-1].setval('#');
f.set(f.getx()+5,f.gety()+2);
if(f.getx()>=20	||	f.getx()<=0)
f.set(0,f.gety());
v.resize(size+1);
v[v.size()-1].set(a,b);
v[v.size()-1].setval('T');
}
}
