#include <iostream>
#include "HelpFunctions.hpp"

using namespace std;

int main()
{
	cout << "Reading data" << endl;
	vector<SpamMail> spamData;
	if (!HelpFunc::readSpamDatabase("spambase.data", spamData))
	{
		cerr << "Failed to load the spambase! Check file location!" << endl;
		return -1;
	}
	cout << "Read a total of " << spamData.size() << " rows.\n";



	cin.ignore();
	return 0;
}