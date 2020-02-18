#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;


class player
{
	int playerNum;
	char name[50];
	int shoot, dribble, pass, defense, speed;
	double per;
	char rating;
	void calculate();
public:
	void getdata();	
	void showdata() const;
	void show_tabular() const;
	int retPlayerNo() const;
}; 


void player::calculate()
{
	per=(shoot+dribble+pass+defense+speed)/5.0;
	if(per>=85)
		rating='A';
	else if(per>=80)
		rating='B';
	else if(per>=70)
		rating='C';
	else if(per>=60)
		rating='D';
	else
		rating='F';
}

void player::getdata()
{
	cout<<"\nEnter The number of player ";
	cin>>playerNum;
	cout<<"\n\nEnter The Name of player ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter The shooting score out of 100: ";
	cin>>shoot;
	cout<<"\nEnter The dribble score out of 100 : ";
	cin>>dribble;
	cout<<"\nEnter The pass score out of 100 : ";
	cin>>pass;
	cout<<"\nEnter The defense score out of 100 : ";
	cin>>defense;
	cout<<"\nEnter The speed score out of 100 : ";
	cin>>speed;
	calculate();
}

void player::showdata() const
{
	cout<<"\nNumber of player : "<<playerNum;
	cout<<"\nName of player : "<<name;
	cout<<"\nShooting ability : "<<shoot;
	cout<<"\nDribbling ability : "<<dribble;
	cout<<"\nPassing ability : "<<pass;
	cout<<"\nDefensive ability : "<<defense;
	cout<<"\nSpeed ability :"<<speed;
	cout<<"\nPercentage of player is  :"<<per;
	cout<<"\nThe rank of the player is :"<<rating;
}

void player::show_tabular() const
{
	cout<<playerNum<<setw(6)<<" "<<name<<setw(10)<<shoot<<setw(4)<<dribble<<setw(4)<<pass<<setw(4)
		<<defense<<setw(4)<<speed<<setw(8)<<per<<setw(6)<<rating<<endl;
}

int  player::retPlayerNo() const
{
	return playerNum;
}


void write_player();	
void display_all();	
void display_pl(int);
void modify_player(int);	
void delete_player(int);	
void team_result();	
void result();		
void entry_menu();	


int main()
{
	char ch;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2); 
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. RESULT MENU";
		cout<<"\n\n\t02. ENTRY/EDIT MENU";
		cout<<"\n\n\t03. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-3) ";
		cin>>ch;
		switch(ch)
		{
			case '1': result();
				break;
			case '2': entry_menu();
				break;
			case '3':
				break;
			default :cout<<"\a";
		}
    }while(ch!='3');
	return 0;
}


void write_player()
{
	player pl;
	ofstream outFile;
	outFile.open("player.dat",ios::binary|ios::app);
	pl.getdata();
	outFile.write(reinterpret_cast<char *> (&pl), sizeof(player));
	outFile.close();
    	cout<<"\n\nPlayer record Has Been Created ";
	cin.ignore();
	cin.get();
}


void display_all()
{
	player pl;
	ifstream inFile;
	inFile.open("player.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&pl), sizeof(player)))
	{
		pl.showdata();
		cout<<"\n\n====================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}


void display_pl(int n)
{
	player pl;
	ifstream inFile;
	inFile.open("player.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&pl), sizeof(player)))
	{
		if(pl.retPlayerNo()==n)
		{
	  		 pl.showdata();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nrecord not exist";
	cin.ignore();
	cin.get();
}


void modify_player(int n)
{
	bool found=false;
	player pl;
	fstream File;
	File.open("player.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof() && found==false)
	{

		File.read(reinterpret_cast<char *> (&pl), sizeof(player));
		if(pl.retPlayerNo()==n)
		{
			pl.showdata();
			cout<<"\n\nPlease Enter The New Details of Player"<<endl;
			pl.getdata();
		    	int pos=(-1)*static_cast<int>(sizeof(pl));
		    	File.seekp(pos,ios::cur);
		    	File.write(reinterpret_cast<char *> (&pl), sizeof(player));
		    	cout<<"\n\n\t Record Updated";
		    	found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
	cin.ignore();
	cin.get();
}


void delete_player(int n)
{
	player pl;
	ifstream inFile;
	inFile.open("player.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&pl), sizeof(player)))
	{
		if(pl.retPlayerNo()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&pl), sizeof(player));
		}
	}
	outFile.close();
	inFile.close();
	remove("player.dat");
	rename("Temp.dat","player.dat");
	cout<<"\n\n\tRecord Deleted ..";
	cin.ignore();
	cin.get();
}


void team_result()
{
	player pl;
	ifstream inFile;
	inFile.open("player.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tALL PLAYERS RESULT \n\n";
	cout<<"============================================================================\n";
	cout<<"Pl#    Name         Sh  Dri Pass Def Sp  %age    Rating"<<endl;
	cout<<"============================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&pl), sizeof(player)))
	{
		pl.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}


void result()
{
	char ch;
	int pno;
	system("cls");
	cout<<"\n\n\n\tRESULT MENU";
	cout<<"\n\n\n\t1. Team Result";
	cout<<"\n\n\t2. Player Rating";
	cout<<"\n\n\t3. Back to Main Menu";
	cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1' :	team_result(); break;
	case '2' :	cout<<"\n\n\tEnter Player Number : "; cin>>pno;
				display_pl(pno); break;
	case '3' :	break;
	default:	cout<<"\a";
	}
}


void entry_menu()
{
	char ch;
	int num;
	system("cls");
	cout<<"\n\n\n\tENTRY MENU";
	cout<<"\n\n\t1.CREATE PLAYER RATING";
	cout<<"\n\n\t2.DISPLAY ALL PLAYERS RATING";
	cout<<"\n\n\t3.SEARCH PLAYER RATING ";
	cout<<"\n\n\t4.MODIFY PLAYER RATING";
	cout<<"\n\n\t5.DELETE PLAYER RATING";
	cout<<"\n\n\t6.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1':	write_player(); break;
	case '2':	display_all(); break;
	case '3':	cout<<"\n\n\tPlease Enter The Player Number "; cin>>num;
			display_pl(num); break;
	case '4':	cout<<"\n\n\tPlease Enter The Player Number "; cin>>num;
			modify_player(num);break;
	case '5':	cout<<"\n\n\tPlease Enter The Player Number "; cin>>num;
			delete_player(num);break;
	case '6':	break;
	default:	cout<<"\a"; entry_menu();
	}
}
