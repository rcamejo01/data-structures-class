#include "expense.h"
#include <iterator>
#include <vector>
// expense *******************************
// constructor

vecexpense::vecexpense(){
	exps = NULL;
	numexp = 0;
	currexp = -1;
	factor = 1;

}

vecexpense::~vecexpense(){
	if (exps != NULL) {
		delete []exps; //square brackets will delete everything apart of exps
	}
}

int vecexpense::addExpense(expense e){
//make variable that makes arrays:
	expense *tempArray; //null means 0
//allocate space for tempArray:
	tempArray = new expense[numexp+1]; //new datatype[size] 
//copy data
	for (int i = 0; i < numexp; i++) {
		tempArray[i] = exps[i]; //tempArray as a location
	}
//put e into location tempArray:
	tempArray[numexp] = e; //e added to array
//delete exps because it has the old size //added in by me
	delete []exps;
//need exps to look at new data coming from tempArray:
	exps = tempArray;
//increment numexp by one to remind it that there is one more space in the array
	numexp++;

	return numexp;
}

void vecexpense::print (ostream &out ){ //goes through exps array and prints out each expense
	for(int i = 0; i < numexp; i++) {
		exps[i].print(out);
	}
}

expense vecexpense::getExpense(int n)
{
	return exps[n];
}

expense::expense() {
	amt = 0.0;
	purpose = "null";
}

// sets amt and purpose
void expense::setExpense(double a, string p) {
	amt = a;
	purpose = p;
}

// print the expense
void expense::print(ostream &out) {
	out << "Expense:" << endl;
	out << "\tAmount=$" << fixed << setprecision(2) << setfill('0') << amt << endl;
	out << "\tPurpose=" << purpose << endl;
}


// expense *******************************

// daily   *******************************
// constructor
daily::daily() {
	numexp = 0;
	day = -1;
}

/*
//expense vector:
void daily::expenseVector(vector<expense> exps) { //should my vector function loop through the expenses and set it equal to numexps? //took semi out
	//for loop will read through the list of data
	for(int i = 0; i < exps.size(); i++) {
		numexp = exps[i].getAmt;
	}
}*/

// adds expense to exps array if it has space
// increments number of expenses stored for day
// returns number of expenses for the day 
int daily::addExpense(double a, string p) {
		class expense xtemp;
		xtemp.setExpense(a,p);
		numexp=exps.addExpense(xtemp);
	return numexp;
}

// iterate through the exps array to sum up
// all expenses for the day
// note that it has to use expense getAmt() on the
// expenses as amt is private in expense
double daily::getDailyExpense() {
	double total = 0.0;
	int i;
	for(i=0;i<numexp;i++) {
		class expense xtemp;
		xtemp=exps.getExpense(i);
		total += xtemp.getAmt();
	}
	return total;
}

// iterate thru the exps array to print all 
// expenses for the day
// uses expenses print method to prnt each
// expense
void daily::print(ostream &out) {

	int i;
	out << "Daily=======================\n";
	out << "Day = " << day << endl;
	out << "# of Expenses = " << numexp << endl;
	for(i=0;i<numexp;i++) 
	{
		class expense xtemp;
		xtemp=exps.getExpense(i);
		xtemp.print(out);
	}
	cout << "Daily=======================\n";

}


// daily   *******************************


// monthly *******************************
// constructor
monthly::monthly() {
	month = -1;
	maxdays = 0;
}

// sets the month to m and also uses mdays array
// to set the maxdays at the same time
// also iterates thru the days array of daily to
// set each day value
void monthly::setMonth(int m) {
	month = m;
	maxdays = mday[month];
	int i;
	for(i=0;i<maxdays;i++) {
		days[i].setDay(i+1);
	}
}


// adds and expense for a day d
// checks that the day is valid for the month and
// then uses d as index to the days array to find 
// the required day and calls the daily addExpense
// for that day
// daily's addExpense already makes sure not to
// exceed the max number of expenses
void monthly::addExpense(int d, double a, string p) {
	if ((d>0)&&(d<=maxdays)) {
		days[d-1].addExpense(a,p);
	} else {
		cerr << "monthly::addExpense: day out of range\n";
	}
}


// return the total expense for a specific day d
// checks that the day is valid for the month and
// then uses d as index to the days array to find 
// the required day and calls the daily getDailyExpense
// for that day
double monthly::getDailyExpense(int d) {
	double total = 0.0;
	if ((d>0)&&(d<=maxdays)) {
		total = days[d-1].getDailyExpense();
	}
	return total;
}

// returns the total expenses for the month
// iterates thru each day for the month and
// uses the previous method to get the total
// expense for each day
double monthly::getMonthlyExpense() {
	double total = 0.0;
	int i;
	for(i=1;i<=maxdays;i++) {
		total += getDailyExpense(i);
	}
	return total;
}

// prints one day using d as an index to the days
// array and calling the daily print method for that day
void monthly::printOneDay(ostream &out, int d) {
	if ((d>0)&&(d<=maxdays)) {
		days[d-1].print(out);
	} else {
		cerr << "monthly::printOneDay: day out of range\n";
	}
}

// iterates thru the days array and print the expenses
// for each day, note it uses the previous method to
// print one day
void monthly::print(ostream &out) {
	int i;
	out << "Monthly==============================\n";
	out << "Month = " << month << endl;
	out << "# of Days = " << maxdays << endl;
	for(i=1;i<=maxdays;i++) {
		printOneDay(out, i);
	}
	out << "Monthly==============================\n";
}
	

// monthly *******************************


// yearly  *******************************
// constructor
// note it initializes the months with the appropriate
// month value
yearly::yearly() {
	year = -1;
	int i;
	for(i=0;i<12;i++) {
		months[i].setMonth(i+1);
	}
}

// adds an expense for a month n and day d
// checks the m is in range 1 -> 12
// uses m as an index to the months array and 
// calls the monthly addExpense for that month 
// with d as a parameter
// monthly's addExpense already checks if the day
// is valid
void yearly::addExpense(int m, int d, double a, string p) {
	if ((m>0)&&(m<=12)) {
		months[m-1].addExpense(d,a,p);
	}
	else {
		cerr << "yearly::addExpense: month out of range\n";
	}
}

// checks the m is in range 1 -> 12
// uses m as an index to the months array and 
// calls the monthly getDailyExpense for that month 
// with d as a parameter
double yearly::getDailyExpense(int m, int d) {
	double total = 0.0;
	if ((m>0)&&(m<=12)) {
		total = months[m-1].getDailyExpense(d);
	}
	return total;
}

// checks the m is in range 1 -> 12
// uses m as an index to the months array and 
// calls the monthly getMonthlyExpense for that month 
double yearly::getMonthlyExpense(int m) {
	double total = 0.0;
	if ((m>0)&&(m<=12)) {
		total = months[m-1].getMonthlyExpense();
	}
	return total;

}

// returns the total expenses for the year
// iterates thru the months and calls the previous
// method to get the expenses for each month
double yearly::getYearlyExpense() {
	double total = 0.0;
	int i;
	for(i=1;i<=12;i++) {
		total += getMonthlyExpense(i);
	}
	return total;
}

// load data
// opens the file and reads each line and uses
// yearly's addExpense to add the expense to the
// year using the month and day read from the file
// yearly's addExpense already checks the month is
// valid
// returns how many lines read
int yearly::loadDataFromFile(string fname) {
	int count = 0;
	ifstream fin(fname);
	if (fin.fail()) {
		cerr << "Error reading file\n";
		return count;
	}
	int m,d,y;
	double a;
	string p;
	while(1) {
		fin >> m >> d >> y >> a >> p;
		if (fin.fail()) break;
		addExpense(m,d,a,p);
		count++;
	}
	setYear(y);
	fin.close();
	return count;
}

// print the expenses for a specific day d of a
// specific monnth m
// checks m is valid and uses it as index to months
// array and monthly printOneDay with d as a parameter
// monthly's printOneDay already checks the day is
// valid
void yearly::printOneDay(ostream &out, int m, int d) {
	if ((m>0)&&(m<=12)) {
		months[m-1].printOneDay(out,d);
	}
	else {
		cerr << "yearly::printOneDay: month out of range\n";
	}
}

// print expense for a month m
// check m is valid and use monthly print to
// print the month
// montjly's print already iterates for the correct
// number of days
void yearly::printOneMonth(ostream &out, int m) {
	if ((m>0)&&(m<=12)) {
		months[m-1].print(out);
	}
	else {
		cerr << "yearly::printOneMonth: month out of range\n";
	}

}

// print the whole year of expenses
// iterates thu the months and uses previous method
// to print each month
void yearly::print(ostream &out) {
	int i;
	out << "Yearly==============================\n";
	out << "year = " << year << endl;
	for (i=1;i<=12;i++) {
		printOneMonth(out,i);
	}
	out << "Yearly==============================\n";

}

// yearly  *******************************

int main() {

	cout << "Program Started\n";

	yearly y;
	/*
	y.setYear(1999);
	y.addExpense(1,1,10.5,"test");
	y.addExpense(1,1,1.5,"test");
	y.addExpense(1,2,11.5,"test");
	y.addExpense(2,1,15.5,"test");
	*/

	cout << "y size = " << sizeof(y) << endl;
	y.loadDataFromFile("data1.txt");
	y.printOneDay(cout,1,1);
	y.printOneMonth(cout,1);

	cout << y.getDailyExpense(1,1) << endl;
	int i;
	for(i=1;i<=12;i++) {
		cout << "month=" << i << ",total=" << y.getMonthlyExpense(i) << endl;
	}
	cout << y.getYearlyExpense() << endl;


	return 0;
}
