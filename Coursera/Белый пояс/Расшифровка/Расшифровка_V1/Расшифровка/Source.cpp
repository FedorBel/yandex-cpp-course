#include <iostream>
#include <string>
#include <sstream>
#include <bitset>
#include <cmath>
#include <vector>

using namespace std;

void show(string& c);
void show(vector<int>& v);
void getInt(string& c, vector<int>& v);
void spaceFind(vector<int>& v1, vector<int>& v2, vector<int>& v3, vector<int>& find);

int main()
{
	/*string test = "0x31";
	istringstream stream(test);
	int i;
	stream >> hex >> i;

	cout << '"' << test << "\": " << i << "(0x" << hex << i << ")\n";
	bitset<16> bitset = i;

	// 'to_string' вернет строку std::string формата '000...0111'
	cout << "Binary : " << bitset.to_string<char, char_traits<char>, allocator<char> >() << endl;*/

	string c1 = "315c4eeaa8b5f8aaf9174145bf43e1784b8fa00dc71d885a804e5ee9fa40b16349c146fb778cdf2d3aff021dfff5b403b510d0d0455468aeb98622b137dae857553ccd8883a7bc37520e06e515d22c954eba5025b8cc57ee59418ce7dc6bc41556bdb36bbca3e8774301fbcaa3b83b220809560987815f65286764703de0f3d524400a19b159610b11ef3e";
	string c2 = "000000000000000000000000000000000000000000000000000000234c02ecbbfbafa3ed18510abd11fa724fcda2018a1a8342cf064bbde548b12b07df44ba7191d9606ef4081ffde5ad46a5069d9f7f543bedb9c861bf29c7e205132eda9382b0bc2c5c4b45f919cf3a9f1cb74151f6d551f4480c82b2cb24cc5b028aa76eb7b4ab24171ab3cdadb8356f";
	string c3 = "";
	string c4 = "";
	string c5 = "";
	string c6 = "";
	string c7 = "";
	string c8 = "";
	string c9 = "";
	string c10 = "";
	string target = "";


	/*
	show(c1);
	show(c2);
	show(xor1);
	cout << endl;
	*/

	vector<int> ct1;
	vector<int> ct2;
	vector<int> ct3;
	vector<int> ct4;
	vector<int> ct5;
	vector<int> ct6;
	vector<int> ct7;
	vector<int> ct8;
	vector<int> ct9;
	vector<int> ct10;
	vector<int> targetT;
	vector<int> find;

	getInt(c1, ct1);
	getInt(c2, ct2);
	//getInt(xor1, xort1);

	for (int i = 0; i < ct1.size(); i++)
	{
		int tmp;
		tmp = ct1[i] ^ ct2[i];
		xort1.push_back(tmp);
	}

	show(ct1);
	show(ct2);
	show(xort1);

	cout << endl << endl;

	spaceFind(ct1, ct2, xort1, find);

	for (int i = 0; i < find.size(); i++)
	{
		cout << hex << ct1[find[i]] << " ";
	}
	cout << endl;

	for (int i = 0; i < find.size(); i++)
	{
		cout << hex << ct2[find[i]] << " ";
	}
	cout << endl;

	for (int i=0; i < find.size(); i++)
	{
		cout << hex << xort1[find[i]] << " ";
	}
	cout << endl;

	system("pause");
	return 0;
}

void show(string& c)
{
	int length = c.length();
	for (int i = 0; i < length-1; i+=2)
	{
		cout << c[i] << c[i + 1] << " ";
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

void getInt(string& c, vector<int>& v)
{
	int tmp;
	string str = "0x12";
	int length = c.length();
	for (int i = 0, j = 0; i < length-1; i+=2, j++)
	{
		str[2] = c[i];
		str[3] = c[i+1];
		tmp = stoi(str, 0, 16);
		v.push_back(tmp);
	}
}

void spaceFind(vector<int>& v1, vector<int>& v2, vector<int>& v3, vector<int>& find)
{
	int min;
	int length = v1.size();

	for (int i = 0; i < length; i++)
	{
		min = abs(v1[i] - v2[i]);
		if (min == v3[i] && v2[i]!=0)
		{
			find.push_back(i);
		}
	}
}