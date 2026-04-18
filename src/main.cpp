#include <iostream>
#include <string>
#include <vector>

using namespace std;

class FarmRecord {
private:
    int year;
    string season;
    int day;
	int cropsSold;
    double cropRevenue;
	double livestockRevenue;
    double expenses;
	double totalRevenue;
	double netProfit;

public:
	//constructor to initialize the farm record
    FarmRecord(int y, string s, int d, int cs, double cr, double lr, double e, double tr, double np) {
		year = y;
		season = s;
		day = d;
		cropsSold = cs;
		cropRevenue = cr;
		livestockRevenue = lr;
		expenses = e;
		totalRevenue = tr;
		netProfit = np;
    }
	//getter to safetly access the private data
	int getYear() const { return year; }
	string getSeason() const { return season; }
	int getDay() const { return day; }
	int getCropsSold() const { return cropsSold; }
	double getCropRevenue() const { return cropRevenue; }
	double getLivestockRevenue() const { return livestockRevenue; }
	double getExpenses() const { return expenses; }
	double getTotalRevenue() const { return totalRevenue; }
	double getNetProfit() const { return netProfit; }
};

int main(){
	cout << "FarmRecord class added successfully!" << endl;
    return 0;
}