#include "HelpFunctions.hpp"
#include <fstream>
#include <iostream>

//string readFile(const string& fileName)
//{
//	iostream file;
//	file.
//}

bool HelpFunc::readSpamDatabase(const string& fileName, vector<SpamMail>& tokens)
{
	ifstream file(fileName);
	string token;
	SpamMail tempMail;

	if (file.is_open())
	{
		while (file.good())
		{
			for (int i = 0; i < 48; i++)
			{
				getline(file, token, ',');
				tempMail.wordFreq[i] = stof(token);

			}
			for (int i = 0; i < 6; i++)
			{
				getline(file, token, ',');
				tempMail.charFreq[i] = stof(token);

			}
			getline(file, token, ',');
			tempMail.capitalLengthAverage = stof(token);
			getline(file, token, ',');
			tempMail.capitalLengthLongest = stoi(token);
			getline(file, token, ',');
			tempMail.capitalLengthTotal = stoi(token);
			getline(file, token, '\n');
			tempMail.spam = (stoi(token) == 1 ? true : false);
			tokens.push_back(tempMail);
		}
	}
	else
		return false;

	return true;
}
