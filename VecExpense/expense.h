#ifndef EXPENSE_H_
#define EXPENSE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

// const array to remember days of month (not doing leap year)
// start with 0 so months start at 1
const int mday[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

// expense class
class expense {
private:
	double amt;
	string purpose;

public:
	// default constructor
	expense();
	
	// setter
	void setExpense(double,string);

	// getter
	double getAmt() { return amt; }

	// print an expense
	void print(ostream&);

};

class vecexpense {
private:
	expense *exps;
	int numexp;
	int currexp;
	int factor;
public:
	vecexpense();

	~vecexpense();
	
	int addExpense(expense e);

	void print(ostream&);

	expense getExpense(int e);
	
};

// daily expense class
class daily {
private:
	vecexpense exps;
	int numexp;
	int day;

public:
	// default constructor
	daily();

	// add an expense
	int addExpense(double, string);

	// setter
	void setDay(int d) { day = d; }

	// get total for day
	double getDailyExpense();

	// print all expenses for day
	void print(ostream&);

};

class monthly {
private:
	daily days[31];
	int maxdays;
	int month;

public:
	monthly();

	// setter
	// setting the month also sets the maxdays
	// and sets the day value for each day
	void setMonth(int m);

	// add and expense for a day
	void addExpense(int, double, string);

	// get totals
	double getDailyExpense(int);
	double getMonthlyExpense();

	// print
	void printOneDay(ostream&, int);
	void print(ostream&);

};

class yearly {
private:
	monthly months[12];
	int year;

public:
	// constructor
	// creating a year also sets all the months
	yearly();

	// setter
	void setYear(int y) { year = y; }

	// add an expense for a month and day
	void addExpense(int, int, double, string);

	// get totals
	double getDailyExpense(int,int);
	double getMonthlyExpense(int);
	double getYearlyExpense();

	// load data
	int loadDataFromFile(string);

	// print
	void printOneDay(ostream&, int, int);
	void printOneMonth(ostream&, int);
	void print(ostream&);

};

#endif

