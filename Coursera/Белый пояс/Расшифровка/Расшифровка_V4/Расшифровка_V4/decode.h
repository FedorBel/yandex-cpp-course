#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <bitset>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

void show(int& key);
void show(vector<int>& v);
void getInt(vector<string>& cts, vector<vector<int> >& cti);
void equal(vector<string>& cts);
void decode(vector<vector<int> >& cti, int& key, int& text);
void xOr_decode(vector<vector<int> >& cti, char& text);
void xOr_decode(vector<vector<int> >& cti, int& text);
void file_write(char& text, int size, int count, vector<vector<int>>& cti, int i);
void file_write(int& text, int size, int count, vector<vector<int>>& cti, int i);
void clear_file(string path);

void show(int& key)
{
	int *p = &key;
	int length = 83;
	for (int i = 0; i < length; i++)
	{
		cout << hex << p[i] << " ";
	}
	cout << endl;
}

void show(vector<int>& v)
{
	int length = v.size();
	for (int i = 0; i < length; i++)
	{
		cout << hex << v[i] << " ";
	}
	cout << endl;
}

void getInt(vector<string>& cts, vector<vector<int> >& cti)
{
	int tmp;
	string str = "0x12";
	int size = cts.size();
	int length = cts[10].length();
	for (int k = 0; k < size; k++)
	{
		for (int i = 0; i < length - 1; i += 2)
		{
			str[2] = cts[k][i];
			str[3] = cts[k][i + 1];
			tmp = stoi(str, 0, 16);
			cti[k].push_back(tmp);
		}
	}
}

void equal(vector<string>& cts)
{
	int size = cts.size();
	int targLength = cts[10].length();
	int bufLength;
	string buffer(targLength, 'a');
	for (int i = 0; i < size; i++)
	{
		if (cts[i].length() != targLength)
		{
			bufLength = cts[i].length() - targLength;
			int j = bufLength;
			int k = 0;
			for (k, j; j < cts[i].length(); j++)
			{
				if (k < targLength)
				{
					buffer[k] = cts[i][j];
					k++;
				}
			}
			cts[i] = buffer;
		}
	}
}

void decode(vector<vector<int> >& cti, int& key, int& text)
{
	int *pk = &key;
	int *pt = &text;
	int keySize = cti[10].size();


	for (int i = 0; i < keySize; i++)
	{
		pt[i] = cti[10][i] ^ pk[i];
	}
}

void xOr_decode(vector<vector<int>>& cti, char & text)
{
	char *pt = &text;
	int size = cti.size();
	int length = cti[10].size();
	int count = 0;
	int tmp;

	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < length; j++)
		{
			tmp = (cti[10][j] ^ cti[i][j]);
			pt[j] = (char)tmp;
		}
		count++;
		file_write(*pt, length, count, cti, i);
	}

	cout << "Writing complete!" << endl;
}

void xOr_decode(vector<vector<int>>& cti, int & text)
{
	int *pt = &text;
	int size = cti.size();
	int length = cti[10].size();
	int count = 0;

	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < length; j++)
		{
			pt[j] = (cti[10][j] ^ cti[i][j]);
		}
		count++;
		file_write(*pt, length, count, cti, i);
	}

	cout << "Writing complete!" << endl;
}

void file_write(char & text, int size, int count, vector<vector<int>>& cti, int i)
{
	string path = "xor_decode.txt";
	char *p = &text;

	fstream fs;
	fs.open(path, fstream::in | fstream::out | fstream::app);

	if (!fs.is_open())
	{
		cout << "Error!" << endl;
	}
	else
	{
		fs << "Text " << count << endl;

		fs << "Ct:\t|";

		for (int j = 0; j < size; j++)
		{
			fs << (char)cti[i][j] << "|\t|";
		}
		fs << endl << endl;
		fs << "Tt:\t|";
		for (int j = 0; j < size; j++)
		{
			fs << (char)cti[10][j] << "|\t|";
		}
		fs << endl << endl;
		fs << "xOr:\t|";
		for (int j = 0; j < size; j++)
		{
			fs << p[j] << "|\t|";
		}
		fs << endl << endl;
	}
	fs.close();
}

void file_write(int & text, int size, int count, vector<vector<int>>& cti, int i)
{
	string path = "xor.txt";
	int *p = &text;

	fstream fs;
	fs.open(path, fstream::in | fstream::out | fstream::app);

	if (!fs.is_open())
	{
		cout << "Error!" << endl;
	}
	else
	{
		fs << "Text " << count << endl;

		for (int j = 0; j < size; j++)
		{
			fs << hex << cti[i][j] << "|\t|";
		}
		fs << endl << endl;
		for (int j = 0; j < size; j++)
		{
			fs << hex << cti[10][j] << "|\t|";
		}
		fs << endl << endl;
		for (int j = 0; j < size; j++)
		{
			fs << hex << p[j] << "|\t|";
		}
		fs << endl << endl;
	}
	fs.close();
}

void clear_file(string path)
{
	ofstream fout;

	fout.open(path);

	if (!fout.is_open())
	{
		cout << "Error!" << endl;
	}
	else
	{

	}

	fout.close();
}

