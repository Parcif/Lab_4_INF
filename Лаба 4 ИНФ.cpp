#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <iterator>
using namespace std;

void check_file(string res)
{
	for (int i = 0; i < res.size(); i++)
	{
		if (isalpha(res[i]) == 0)
			throw runtime_error("\nAhtung!!! A symbol is detected - not a letter!!! Select another file: ");
	}
}

void filefillarray(vector<string>& vec)
{
	string name;
	bool state = true;
	
	cout << "\nEnter the path to the file using double \\ in the format .txt: ";

	while (state)
	{
		getline(cin, name);

		ifstream file;
		file.open(name);

		try
		{
			if (file.is_open())  // Проверка отрылся файл или нет
				cout << "\nEverything is fine! The file is open!\n" << endl;
			else
			{
				cout << "\nFile not open!" << endl;
				throw runtime_error("\nSomething went wrong! Select another file: ");
			}

			for (int i = 0; !file.eof(); i++)  // filling the array
			{
				string inp;
				getline(file, inp);
				check_file(inp);
				vec.push_back(inp);
			}
			file.close();
			state = false;
		}
		catch (runtime_error& e)
		{
			cout << e.what();
		}
	}
}

string check_string()
{
	string res;
	bool state = true;

	while (state)
	{
		getline(cin, res);
		try 
		{
			for (int i = 0; i < res.size(); i++)
			{
				if (isalpha(res[i]) == 0)
					throw runtime_error("\nNot a letter detected!!! Repeat the input: ");
			}

			state = false;
			return res;
		}
		catch(runtime_error& e)
		{
			cout << e.what();
		}

	}
	
}

void check_infile_firstword(vector<string> vec, string &firstword, string str)
{
	cout << str;
	bool state = true;

	while (state)
	{
		firstword = check_string();

		auto it = find(vec.begin(), vec.end(), firstword);

		if (it == vec.end())
		{
			cout << "\nThere is no such word! Repeat the input: ";
		}
		else
		{
			state = false;
		}

	}

}

void botstep(vector<string> vec, string userword, string& botword)
{
	char endletter = userword[userword.size() - 1];
	
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i][0] == endletter)
			botword = vec[i];
	}
	cout << "\nBot says: " << botword << endl;
}

void userstep(vector<string> vec, string& userword, string botword, bool& breaker)
{
	char endletter = botword[botword.size() - 1];
	bool check_letter = false;
	bool check_presence = false;

	cout << "\nInput a word: ";
	userword = check_string();

	if (userword[0] == endletter)  // checking for the first letter
			check_letter = true;

	if (check_letter)  // checking for the presence of a word
	{
		for (int i = 0; i < vec.size(); i++)  
		{
			if (vec[i] == userword)
				check_presence = true;
		}
	}
	
	if (!check_letter)
	{
		breaker = false;
		cout << "\nYou disrupt the rules of the game!";
		cout << "\nGame over. You lose.\n";
	}
	else if (!check_presence)
	{
		breaker = false;
		cout << "\nThere is no such word!";
		cout << "\nGame over. You lose.\n";
	}

}

void game(vector<string> vec)
{
	bool breaker = true;
	string userword;
	string botword;

	check_infile_firstword(vec, userword, "\nInput a first word: ");
	
	while (breaker)
	{
		botstep(vec, userword, botword);
		userstep(vec, userword, botword, breaker);
	}

}


int main()
{
	vector<string> vec;

	
	filefillarray(vec);
	game(vec);
	

}
