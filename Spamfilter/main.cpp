#include <iostream>
#include <cmath>
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

	SpamMail spamMin = spamData[0];
	SpamMail spamMax = spamData[0];
	SpamMail spam = spamData[0];
	SpamMail hamMax = spamData[0];
	SpamMail ham = spamData[0];
	memset(&spamMin, 0, sizeof(SpamMail));
	int spamCounter = 0;
	int hamCounter = 0;

	for (int s = 1; s < spamData.size(); s++)
	{
		if (spamData[s].spam)
		{
			spamCounter++;
			for (int i = 0; i < 48; i++)
			{
				spamMin.wordFreq[i] = fminf(spamMin.wordFreq[i], spamData[s].wordFreq[i]);
				spamMax.wordFreq[i] = fmaxf(spamMax.wordFreq[i], spamData[s].wordFreq[i]);
				spam.wordFreq[i] += spamData[s].wordFreq[i];
			}
		}
		else {
			hamCounter++;
			for (int i = 0; i < 48; i++)
			{
				//hamMin.wordFreq[i] = fminf(hamMin.wordFreq[i], spamData[s].wordFreq[i]);
				hamMax.wordFreq[i] = fmaxf(hamMax.wordFreq[i], spamData[s].wordFreq[i]);
				ham.wordFreq[i] += spamData[s].wordFreq[i];
			}
		}
	}

	//for (int i = 0; i < 48; i++)
	//	cout << spamMax.wordFreq[i] << "\t- " << hamMax.wordFreq[i] << "\t" << HelpFunc::names[i] << endl;
	int failCounter = 0;
	bool darnArray[48] = { false };
	float darnFactor = 3;
	int dagnabbit = 0;
	for (int i = 0; i < 48; i++)
	{
		cout << HelpFunc::names[i] << endl
			<< spamMax.wordFreq[i] << "\t- " << hamMax.wordFreq[i] << endl
			<< spam.wordFreq[i]/(float)spamCounter << "\t- " << ham.wordFreq[i]/(float)hamCounter << "\t" << endl;
		//if (spamMax.wordFreq[i] > hamMax.wordFreq[i] && spam.wordFreq[i] > ham.wordFreq[i])
		//	cout << "SPAM\n";
		//else if (spamMax.wordFreq[i] < hamMax.wordFreq[i] && spam.wordFreq[i] < ham.wordFreq[i])
		//	cout << "HAM\n";
		//else
		//{
		//	cout << "Fail.\n";
		//	failCounter++;
		//}

		float spamAvg = spam.wordFreq[i] / (float)spamCounter;
		float hamAvg = ham.wordFreq[i] / (float)hamCounter;
		if (spamAvg < hamAvg)
		{
			if (spamAvg * darnFactor > hamAvg)
			{
				darnArray[i] = true;
				dagnabbit++;
			}
		}
		else
		{
			if (hamAvg * darnFactor > spamAvg)
			{
				darnArray[i] = true;
				dagnabbit++;
			}
		}


	}

	cout << "DAGNABBIT: " << dagnabbit << endl;
	for (int i = 0; i < 48; i++)
	{
		if(darnArray[i])
			cout << HelpFunc::names[i] << endl
			<< spam.wordFreq[i] / (float)spamCounter << "\t- " << ham.wordFreq[i] / (float)hamCounter << "\t" << endl;
	}

	vector<SpamMailDisc> spamDataDisc;

	for (int i = 0; i < spamData.size(); i++)
	{
		SpamMailDisc spamDiscTemp;
		for (int j = 0; j < 48; j++)
		{
			if (darnArray[j])
				spamDiscTemp.word[j] = Attrib::DAMN;
			else
			{
				float& word = spamData[i].wordFreq[j];
				float hamW = fabsf(word - ham.wordFreq[j] / (float)hamCounter);
				float spamW = fabsf(word - spam.wordFreq[j] / (float)spamCounter);
				if (hamW < spamW)
					spamDiscTemp.word[j] = Attrib::HAM;
				else
					spamDiscTemp.word[j] = Attrib::SPAM;

			}
		}
		spamDiscTemp.spam = spamData[i].spam;
		spamDataDisc.push_back(spamDiscTemp);
	}

	SpamMailDisc instance = spamDataDisc[0];
	for (int i = 1; i < spamDataDisc.size(); i++)
	{
		SpamMailDisc& compare = spamDataDisc[i];
		if (compare.spam)
		{
			for (int j = 0; j < 48; j++)
			{
				if (compare.word[j] != instance.word[j])
					instance.word[j] = Attrib::DAMN;
			}
		}
	}

	cout << "Fail: " << failCounter << endl;
	cin.ignore();
	return 0;
}