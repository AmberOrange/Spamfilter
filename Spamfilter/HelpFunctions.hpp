#ifndef HELPFUNCTIONS_HPP
#define HELPFUNCTIONS_HPP

#include <vector>

#include <string>

using namespace std;

struct SpamMail
{
	float wordFreq[48];
	float charFreq[6];
	float capitalLengthAverage;
	int capitalLengthLongest;
	int capitalLengthTotal;
	bool spam;
};

namespace HelpFunc
{
	bool readSpamDatabase(const string& fileName, vector<SpamMail>& tokens);

}


#endif