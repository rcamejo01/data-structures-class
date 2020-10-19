/******************************************

Problem: Keep track of expenses (out/in)

What info needed for an expense:
Amount - double
Purpose - string
Date (MM/DD/YY) - struct (month, day, year - int)
*Time (hh:min) - struct (hour, min - int)

Day of Expenses - Array of Expense - size?
Month of Expenses - Array of Days - 31
Year of Expenses - Array of Months - 12

Test Operations:
What is the balance at the end of the month?

Final Operations:
Read the data file provided and store in the arrays
(month dat year amt purpose)
>>>>>>>Note that: month, day start at 1<<<<<<<
Using the stored data:
Calculate and output
	1. the total expanses for the year
	2. the total expenses for each purpose for the year
	3. the total expenses for each month
	4. the total expenses for each purpose for each month
Ask the user for:
	1. a day and output the expenses for that day
	2. a purpose and output all expenses for that purpose

Do these operations as functions so that the main
is not crowded.


******************************************/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// constants
const int dsize = 24;
const int msize = 31;
const int ysize = 12;

struct date {
	int month, day, year;
	date(){}
};

struct expense {
	date x;
	double amt;
	string pur;
	expense(){
		amt=0;
		pur="";
	}
	void setExpense(int d, int m, int y, double a, string p){
		x.day=d;
		x.month=m;
		x.year=y;
		amt=a;
		pur=p;
	}
};

struct dailyExp {
	expense daily[dsize];
	int numtrans;
	dailyExp(){
		numtrans=0;
	}
	double getDailyAmt(){
		double sum=0;
		for(int i=0;i<numtrans;i++){
			sum+=daily[i].amt;
		}
		return sum;
	}
	double getPurAmt(string p){
		double purAmt=0;
		for(int i=0;i<numtrans;i++){
			if(daily[i].pur==p){
				purAmt+=daily[i].amt;
			}
		}
		return purAmt;
	}
	void addtrans(int d, int m, int y, double a, string p){
		daily[numtrans].setExpense(d,m,y,a,p);
		numtrans++;
	}
};

struct monthExp {
	dailyExp month[msize];
	monthExp(){}
	double getMonthAmt(){
		double sum=0;
		for(int i=0;i<msize;i++){
			sum+=month[i].getDailyAmt();
		}
		return sum;
	}
	double getPurMonthAmt(string p){
		double purAmt=0;
		for(int i=0;i<msize;i++){
			purAmt+=month[i].getPurAmt(p);
		}
		return purAmt;
	}
	void addtrans(int d, int m, int y, double a, string p) {
		month[d-1].addtrans(d, m, y, a, p);
	}
};

struct yearExp {
	monthExp year[ysize];
	yearExp(){}
	double getYearAmt(){
		double sum=0;
		for(int i=0;i<12;i++){
			sum+=year[i].getMonthAmt();
		}
		return sum;
	}
	double getPurYearAmt(string p){
		double purAmt=0;
		for(int i=0;i<12;i++){
			purAmt+=year[i].getPurMonthAmt(p);
		}
		return purAmt;
	}
	void addtrans(int d, int m, int y, double a, string p) {
		year[m-1].addtrans(d, m, y, a, p);
	}
	double getM(int m){
		return year[m].getMonthAmt();
	}
};

class expenseList {
	private:
		yearExp year;
	public:
		expenseList(){}
		void addExpense(int d, int m, int y, double a, string p) {
			year.addtrans(d, m, y, a, p);
		}
		void addData(string fname){
			ifstream file(fname);
			int d, m, y;
			double a;
			string p;
			if(file.fail()){
				cout << "Error: File Not Found!";
			}else {
				while(!file.eof()){
					file>>m>>d>>y>>a>>p;
					addExpense(d, m, y, a, p);
				}
			file.close();
			cout << "File found!"<<endl;
			}
		}
		void printTotalYear(){
			cout << "January: " << year.getM(0) << endl;
			cout << "February: " << year.getM(1) << endl;
			cout << "March: " << year.getM(2) << endl;
			cout << "April: " << year.getM(3) << endl;
			cout << "May: " << year.getM(4) << endl;
			cout << "June: " << year.getM(5) << endl;
			cout << "July: " << year.getM(6) << endl;
			cout << "August: " << year.getM(7) << endl;
			cout << "September: " << year.getM(8) << endl;
			cout << "October: " << year.getM(9) << endl;
			cout << "November: " << year.getM(10)<< endl;
			cout << "December: " << year.getM(11)<<endl;
			cout << "Total: " << year.getYearAmt() << endl;
		}
		void printAllAmtPurr(){
			cout<<"groceries:"<<year.getPurYearAmt("grocery")<<endl;
			cout<<"medical:"<<year.getPurYearAmt("medical")<<endl;
			cout<<"meals:"<<year.getPurYearAmt("meals")<<endl;
			cout<<"credit card:"<<year.getPurYearAmt("creditcard")<<endl;
			cout<<"misc:"<<year.getPurYearAmt("misc")<<endl;
			cout<<"transport:"<<year.getPurYearAmt("transport")<<endl;
		}
		void printAllAmtByMonth(){
			string yearNames[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
			string purr[6]={"grocery", "medical", "meals", "creditcard", "misc", "transport"};
			for(int i=0;i<12;i++){
				cout<<yearNames[i]<<":"<<endl;
				for(int j=0;j<6;j++){
					cout<<"\t"<<purr[j]<<": "<<year.year[i].getPurMonthAmt(purr[j])<<endl;
				}
			}
		}
		void printPurr(string p){
			double amt=year.getPurYearAmt(p);
			if(amt==0){
				cout << "The Purpose cannot be found!";
			}
			else{
				cout<<year.getPurYearAmt(p)<<endl;
			}
		}
		void printDay(int d, int m){
			cout<<year.year[m-1].month[d-1].getDailyAmt();
		}
};

int main(){
	expenseList y2019;
	y2019.addData("data1.txt");
	cout << "WELCOME TO THE EXPENSE CALCULATOR!!!!!!!!!!" << endl;
	cout << "This is how much money you spent throughout the year........" << endl;
	y2019.printTotalYear();
	cout << endl;
	cout << "This is how much you spent per purpose......" << endl;
	y2019.printAllAmtPurr();
	cout << endl;
	cout << "This is how much you spent per purpose per month......" << endl;
	y2019.printAllAmtByMonth();
	cout << endl << endl;
	string p;
	cout << "Enter a purpose: ";
	cin >> p;
	y2019.printPurr(p);
	cout << endl << endl;
	int d, m;
	cout << "Enter month: e.g(January is 1, December is 12): " << endl;
	cin >> m;
	cout << "Enter day: " << endl;
	cin>>d;
	cout << "Spent: ";
	y2019.printDay(d,m);
}
