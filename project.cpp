#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>	 // dynamic array
#include <algorithm> //for sorting

using namespace std;

void operateOnAirportData(const string &file_name, stringstream &userInput, stringstream &programOutput)
{

	ifstream infile(file_name);

	if (!infile.is_open())
	{
		cerr << "Failed to open the file." << endl;
		programOutput << "Failed to open the file." << endl;
	}

	int rows = 0;
	int columns = 0;
	int columnToRead = 5;		// column index of maximumn temperature column
	double maxColumnValue = -1; // declare some irrelevant value
	string maxTempYear;
	string maxTempMonth;
	string maxTempDay;

	double minColumnValue = 30;
	string minTempYear;
	string minTempMonth;
	string minTempDay;

	vector<double> temperatures; // variable to store all temperature values
	string line;
	while (getline(infile, line))
	{
		rows++;
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] == ',')
			{
				columns++;
			}
		}

		// to find hottest day of he year
		// then to display temp,date and year of when max temprature is measured
		stringstream iss(line, stringstream::in | stringstream::out);
		string token;
		int currentColumn = 0;

		while (getline(iss, token, ','))
		{
			if (currentColumn == 2)
			{
				maxTempYear = token;
			}
			else if (currentColumn == 3)
			{
				maxTempMonth = token;
			}
			else if (currentColumn == 4)
			{
				maxTempDay = token;
			}
			else if (columnToRead == currentColumn)
			{
				try
				{
					double columnValue = stod(token);
					temperatures.push_back(columnValue); // stores temperatures of the temperature record column
					if (columnValue > maxColumnValue)
					{
						maxColumnValue = columnValue;
						maxTempMonth = token;
						maxTempDay = token;
						maxTempYear = token;
					}
					if (columnValue < minColumnValue)
					{
						minColumnValue = columnValue;
						minTempMonth = maxTempMonth;
						minTempDay = maxTempDay;
						minTempYear = maxTempYear;
					}
				}
				catch (const std::exception &e)
				{
					std::cerr << e.what() << '\n';
					programOutput << e.what() << endl;
				}

				break; // break when desired max value is obtained
			}
			currentColumn++;
		}
	}
	cout << "You have chosen file: " << file_name << endl;
	cout << "Number of rows: " << rows << endl;
	cout << "Number of columns: " << columns << endl;
	cout << "Hottest date of the year is - " << maxTempYear << ":" << maxTempMonth << ":" << maxTempDay << " ";
	cout << "Where maximum temperature is : " << maxColumnValue << endl;
	cout << "Coldest date of the year is - " << minTempYear << ":" << minTempMonth << ":" << minTempDay << " ";
	cout << "Where minimum temperature is : " << minColumnValue << endl;

	// store the standard output to the variable
	programOutput << "You have chosen file: " << file_name << endl
				  << "Number of rows: " << rows << endl
				  << "Number of columns: " << columns << endl
				  << "Hottest date of the year is - " << maxTempYear << ":" << maxTempMonth << ":" << maxTempDay << " "
				  << "Where maximum temperature is : " << maxColumnValue << endl
				  << "Coldest date of the year is - " << minTempYear << ":" << minTempMonth << ":" << minTempDay << " "
				  << "Where minimum temperature is : " << minColumnValue << endl;

	// calculate mean temperature
	double sum = 0;
	size_t size = temperatures.size();
	for (const double &temp : temperatures)
	{
		sum += temp;
	}
	double meanTemperature = sum / size;
	cout << "Mean temperature for given year is: " << meanTemperature << endl;
	programOutput << "Mean temperature for given year is: " << meanTemperature << endl;

	// calculate median temperature
	std::sort(temperatures.begin(), temperatures.end());
	double medianTemperature;
	if (size % 2 == 0)
	{
		medianTemperature = (temperatures[size / 2 - 1] + temperatures[size / 2]) / 2.0;
	}
	else
	{
		medianTemperature = temperatures[size / 2];
	}
	cout << "Median temperature for the year is: " << medianTemperature << endl;
	programOutput << "Median temperature for the year is: " << medianTemperature << endl;

	infile.close();
}

int main()
{
	// open a log file to store all information
	ofstream logFile("log.txt");
	if (!logFile.is_open())
	{
		cerr << "Failed to open log file." << endl;
		return 1;
	}

	char continueChoice;
	do
	{
		// Message to the user
		// Message

		stringstream userInput; // creates stringstream variable to capture userinput
		stringstream programOutput;

		int choice;
		cout << "Which airport data you want to view : 1.Bendigo Airport or 2.Avalon Airport or 3.Both ?" << endl;

		cin >> choice;
		// capture user input
		userInput << "Which airport data you want to view : 1.Bendigo Airport or 2.Avalon Airport or 3.Both ?" << endl;
		userInput << "User choice: " << choice << endl;

		switch (choice)
		{
		case 1:
		{
			string file_name = "Bendigo-Airport-Temperature-Data-2022.csv";
			operateOnAirportData(file_name, userInput, programOutput);
			break;
		}
		case 2:
		{
			string file_name = "Avalon-Airport-Temperature-Data-2022.csv";
			operateOnAirportData(file_name, userInput, programOutput);
			break;
		}
		case 3:
		{
			// code
			break;
		}
		default:
			cout << "Invalid choice." << endl;
			programOutput << "Invalid choice." << endl;
			break;
		}

		// Write captured user input and  program output to the log file
		logFile
			<< "User Input:\n"
			<< userInput.str() << "\nProgram Output:\n"
			<< programOutput.str()
			<< endl;

		logFile.close();

		cout << "Do you want to continue (c) or exit (e)?" << endl;
		cin >> continueChoice;

	} while (continueChoice == 'c' || continueChoice == 'C');

	if (continueChoice == 'e' || continueChoice == 'E')
	{
		cout << "You have exited the program. Thank you for using it!" << endl;
	}

	return 0;
}