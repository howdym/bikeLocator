// bikeLocator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// TODO: Test functions again.

#include "pch.h"
#include <iostream>
#include <mysqlx/xdevapi.h>
#include <fstream>
#include <thread>
using ::std::cout;
using ::std::endl;
using ::std::cin;
using ::std::getline;
using namespace ::mysqlx;

void write(Table table)
{
	std::string temp;
	cout << "Enter in the condition. ";
	cin.ignore();
	getline(cin, temp);
	string value = temp;
	
	RowResult docs = table.select().having(value).execute();

	Row doc = docs.fetchOne();
	std::vector<string> name;
	std::vector<double> lat;
	std::vector<double> longitude;
	for (int i = 0; doc; ++i, doc = docs.fetchOne())
	{
		cout << "doc#" << i << ": " << doc << endl;
		for (row_count_t j = 0; j < docs.getColumnCount(); j++)
		{
			if (j == 1)
			{
				cout << doc[j] << endl;
				name.emplace_back(doc[j]);
			}
			else if (j == 3)
			{
				cout << doc[j] << endl;
				lat.emplace_back(doc[j]);
			}
			else if (j == 4)
			{
				cout << doc[j] << endl;
				longitude.emplace_back(doc[j]);
			}
		}
		cout << endl;
	}
	cout << "Done!" << endl;

	std::ofstream myfile;
	myfile.open("display.xml");
	myfile << "<root>\n";
	for (unsigned long long i = 0; i < name.size(); i++)
	{
		std::string temp = "\t<place name =\"";
		std::string comp = "&";
		std::string replace = "&amp;";
		std::string endq = "\"";
		std::string latitude = " latitude=\"";
		std::string lng = " longitude=\"";
		std::string end = "\"/>";
		for (unsigned long long j = 0; j < name[i].length(); j++)
		{
			std::string a = name[i];
			if (a.substr(j, 1) == comp)
			{
				temp += replace;
			}
			else
			{
				temp += a.substr(j, 1);
			}
		}
		temp += endq;
		temp += latitude + std::to_string(lat[i]) + endq;
		temp += lng + std::to_string(longitude[i]) + end;
		myfile << temp << "\n";
	}
	myfile << "</root>";
	myfile.close();
}

void change(Table coll)
{
	std::string edit;
	std::string idNum;
	int decision;
	cout << "What do you want to edit? \n";
	cout << "Id (0), Name (1), City (2), Latitude (3), Longitude (4), Dpcapacity (5), Online Date (6): ";
	cin >> decision;
	cout << "What is the new value: ";
	cin.ignore();
	getline(cin, edit);
	cout << "What is the id number: ";
	cin >> idNum;
	
	std::map<int, std::string> ref;
	ref[0] = "id";
	ref[1] = "name";
	ref[2] = "city";
	ref[3] = "latitude";
	ref[4] = "longitude";
	ref[5] = "dpcapacity";
	ref[6] = "online_date";
	std::string condition = "id = " + idNum;
	coll.update().set(ref[decision], edit).where(condition).execute();
}

void add(Table coll)
{
	int temp_id, temp_dpcapacity;
	double temp_lat, temp_lng;
	std::string temp_name, temp_city, temp_date;
	cout << "What is the id: ";
	cin >> temp_id;
	cout << "What is the name: ";
	cin.ignore();
	getline(cin, temp_name);
	cout << "What is the city: ";
	cin >> temp_city;
	cout << "What is the latitude: ";
	cin >> temp_lat;
	cout << "What is the longitude: ";
	cin >> temp_lng;
	cout << "What is the bike storage capacity: ";
	cin >> temp_dpcapacity;
	cout << "What is the date posted (use YYYY-MM-DD HH:MM:SS format): ";
	cin.ignore();
	getline(cin, temp_date);
	coll.insert("id", "name", "city", "latitude", "longitude", "dpcapacity", "online_date")
		.values(temp_id, temp_name, temp_city, temp_lat, temp_lng, temp_dpcapacity, temp_date)
		.execute();
}

void process(int decision, Table coll)
{
	
	if (decision == 1)
	{
		change(coll);
		// Run edit function
		// Make a dictionary for corresponding fields
	}
	else if (decision == 2)
	{
		add(coll);
	}
	else if (decision == 4)
	{
		write(coll);
	}
}

int main(int argc, const char* argv[]) {
try {
	const char *url = (argc > 1 ? argv[1] : "mysqlx://root:marcjiang123@127.0.0.1");
	cout << "Creating session on " << url
		<< " ..." << endl;
	Session sess(url);

	//cout << "Session accepted, creating collection..." << endl;
	Schema sch = sess.getSchema("sys");
	Table coll = sch.getTable("bikelocator", true);
	sess.sql("USE sys").execute();

	int decision;
	cout << "What do you want to do? \n";
	cout << "Edit (1), Add (2), Delete (3), Write(4): ";
	std::cin >> decision;

	if (decision == 3)
	{
		std::string condition;
		cout << "Enter in the condition: ";
		cin.ignore();
		getline(cin, condition);
		condition = "DELETE FROM bikelocator WHERE " + condition;
		sess.sql(condition).execute();
	}
	else 
	{
		process(decision, coll);
	}
	
	// Functions!!
	// coll.update().set("id", expr("id - 1")).where("id = 0").execute();
	// 
	// coll.insert("id", "name", "city", "latitude", "longitude", "dpcapacity", "online_date")
	//	 .values(0, "Jack", "Chicago", 4, 5, 12, "2019-09-19 06:48:00")
	//	 .execute();
	// 
	// sess.sql("DELETE FROM bikelocator WHERE id = -1").execute();
	
	
	//
	// Below is how to display the info.

	
}
//
	
catch (const mysqlx::Error &err)
{
	cout << "ERROR: " << err << endl;
	return 1;
}
catch (std::exception &ex)
{
	cout << "STD EXCEPTION: " << ex.what() << endl;
	return 1;
}
catch (const char *ex)
{
	cout << "EXCEPTION: " << ex << endl;
	return 1;
}
}

// Game Plan:
// Modify: Prompt what id
//		   Prompt edited value
//		   Use provided function.
//
// Remove: Prompt what id
//         Use provided function.
//
// Add: Prompt required fields
//      Use sample function.
//
// Modify: Ask what field they want to search using
//		   Make response for each field
//		   Use what is given above

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
