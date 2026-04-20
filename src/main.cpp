#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
//Class to represent each farm record, encapsulating all relevant data and providing safe access through getters.
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

//Class to analyze the farm data, providing methods to load data from a CSV file and generate various reports based on the loaded data.
class FarmAnalyzer {
private:
	vector<FarmRecord> records;
public:
	//opening file aand reading data
	bool loadData(string filename) {
		ifstream file(filename);
		if (!file.is_open()) {
			cout << "Error opening file: " << filename << endl;
			return false;
		}

		string line;
		getline(file, line);

		// Read each line of the CSV file and create FarmRecord objects
		while (getline(file, line)) {
			stringstream ss(line);
			string tempYear, season, tempDay, tempCropsSold;
			string tempCropRev, tempLiveRev, tempExp, tempTotalRev, tempNetProfit;

			getline(ss, tempYear, ',');
			getline(ss, season, ',');
			getline(ss, tempDay, ',');
			getline(ss, tempCropsSold, ',');
			getline(ss, tempCropRev, ',');
			getline(ss, tempLiveRev, ',');
			getline(ss, tempExp, ',');
			getline(ss, tempTotalRev, ',');
			getline(ss, tempNetProfit, ',');

			//convert string data to appropriate types
			int year = stoi(tempYear);
			int day = stoi(tempDay);
			int cropsSold = stoi(tempCropsSold);
			double cropRevenue = stod(tempCropRev);
			double livestockRevenue = stod(tempLiveRev);
			double expenses = stod(tempExp);
			double totalRevenue = stod(tempTotalRev);
			double netProfit = stod(tempNetProfit);

			FarmRecord record(year, season, day, cropsSold, cropRevenue, livestockRevenue, expenses, totalRevenue, netProfit);
			records.push_back(record);
		}
		file.close();
		return true;
	}
	//helper function to see how many rows we loaded
	int getRecordCount() const {
		return records.size();
	}
	//report 1: profit by season
	void reportProfitBySeason() {
		// Implementation to calculate and report profit by season
		double springProfit = 0, summerProfit = 0, fallProfit = 0, winterProfit = 0;

		for (const FarmRecord& record : records){
			if (record.getSeason() == "Spring") {
				springProfit += record.getNetProfit();
			}
			else if (record.getSeason() == "Summer") {
				summerProfit += record.getNetProfit();
			}
			else if (record.getSeason() == "Fall") {
				fallProfit += record.getNetProfit();
			}
			else if (record.getSeason() == "Winter") {
				winterProfit += record.getNetProfit();
			}
		}
		//printing the report
		cout << "\n============================================\n";
		cout << "         REPORT 1: PROFIT BY SEASON         \n";
		cout << "============================================\n";
		cout << "Spring Net Profit:  $" << springProfit << "\n";
		cout << "Summer Net Profit:  $" << summerProfit << "\n";
		cout << "Fall Net Profit:    $" << fallProfit << "\n";
		cout << "Winter Net Profit:  $" << winterProfit << "\n";
		cout << "============================================\n\n";
	}
	//report 2: revenue source comparison
	void reportRevenueSourceComparison() const {
		double totalCropRevenue = 0.0;
		double totalLivestockRevenue = 0.0;

		for (const FarmRecord& record : records) {
			totalCropRevenue += record.getCropRevenue();
			totalLivestockRevenue += record.getLivestockRevenue();
		}

		cout << "============================================\n";
		cout << "        REPORT 2: REVENUE COMPARISON        \n";
		cout << "============================================\n";
		cout << "Total Crop Revenue:      $" << totalCropRevenue << "\n";
		cout << "Total Livestock Revenue: $" << totalLivestockRevenue << "\n";
		cout << "============================================\n\n";
	}

	//report 3: strategy and growth recommendations
	void generateStrategyRecommendations() const {
		double totalCropRevenue = 0;
		double totalLivestockRevenue = 0;
		double springProfit = 0, summerProfit = 0, fallProfit = 0, winterProfit = 0;

		for (const FarmRecord& record : records){
			totalCropRevenue += record.getCropRevenue();
			totalLivestockRevenue += record.getLivestockRevenue();

			if (record.getSeason() == "Spring") springProfit += record.getNetProfit();
			else if (record.getSeason() == "Summer") summerProfit += record.getNetProfit();
			else if (record.getSeason() == "Fall") fallProfit += record.getNetProfit();
			else if (record.getSeason() == "Winter") winterProfit += record.getNetProfit();
		}

		cout << "=============================================\n";
		cout << " REPORT 3: STRATEGY & GROWTH RECOMMENDATIONS \n";
		cout << "=============================================\n";

		//determine which area is making more money and give recommendations
		if (totalCropRevenue > totalLivestockRevenue * 1.5) {
			cout << "Crops are heavily outperforming livestock. \n";
			cout << "Recommendation: Invest heavily in sprinklers and seeds to maximize the advantage. \n";
		} else if (totalLivestockRevenue > totalCropRevenue) {
			cout << "* Livestock is highly profitable for you right now.\n";
			cout << "  Recommendation: Upgrade barns/coops and purchase more animals.\n";
		}
		else {
			cout << "* Your farm is well balanced between crops and livestock.\n";
			cout << "  Recommendation: Maintain this balance; scale up whichever requires less daily energy.\n";
		}

		//seasonal insights
		double maxProfit = springProfit;
		string bestSeason = "Spring";

		//checking if other seasons beat current max
		if (summerProfit > maxProfit) { maxProfit = summerProfit; bestSeason = "Summer"; }
		if (fallProfit > maxProfit) { maxProfit = fallProfit; bestSeason = "Fall"; }
		if (winterProfit > maxProfit) { maxProfit = winterProfit; bestSeason = "Winter"; }

		cout << "\n* " << bestSeason << " has historically been your most profitable season.\n";
		cout << "  Recommendation: Save money the season prior to buy maximum seeds/supplies for " << bestSeason << " 1st.\n";
		cout << "============================================\n\n";
	}
};

//Class 3: UserInterface, this class manages menu and keeps separate from data and analysis logic
class UserInterface {
private:
	FarmAnalyzer analyzer;
	bool isloaded; 
public:
	UserInterface() { isloaded = false; }

	void initializeData() {
		if (analyzer.loadData("../../../files/stardew_dataset.csv")) {
		cout << "\n[System]: Successfully loaded " << analyzer.getRecordCount() << " farm records.\n\n";
		isloaded = true;
		}
		else {
			cout << "\n[System - ERROR]: Failed to find or load the CSV file.\n\n";
		}
	}

	void displayMenu() {
		cout << "*** STARDEW VALLEY FARM ANALYZER ***\n";
		cout << "1. View Profit by Season\n";
		cout << "2. View Revenue Source Comparison\n";
		cout << "3. View Strategy Recommendations\n";
		cout << "4. Exit Program\n";
		cout << "Enter your choice: ";
	}
	//main loop of the prg
	void run() {
		initializeData(); //load dataset
		//if failed to load, exit program
		if (!isloaded) {
			return;
		}
		int choice = 0;
		//keeps looping until user chooses to exit
		while (choice != 4) {
			displayMenu();
			cin >> choice;
			cout << "\n";

			switch (choice) {
				case 1:
					analyzer.reportProfitBySeason();
					break;
				case 2:
					analyzer.reportRevenueSourceComparison();
					break;
				case 3:
					analyzer.generateStrategyRecommendations();
					break;
				case 4:
					cout << "Exiting program. Happy farming!\n";
					break;
				default:
					cout << "Invalid choice. Please enter a number between 1 and 4.\n";
			}
		}
	}


};

int main(){
	UserInterface ui;
	ui.run();

	return 0;
}