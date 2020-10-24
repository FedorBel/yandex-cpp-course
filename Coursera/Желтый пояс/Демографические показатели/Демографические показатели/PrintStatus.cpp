void PrintStats(vector<Person> persons)
{
	cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;

	auto border = partition(persons.begin(), persons.end(),
		[](Person i) {return i.gender == Gender::FEMALE; });
	cout << "Median age for females = " << ComputeMedianAge(persons.begin(), border) << endl;

	border = partition(persons.begin(), persons.end(),
		[](Person i) {return i.gender == Gender::MALE; });
	cout << "Median age for males = " << ComputeMedianAge(persons.begin(), border) << endl;

	border = partition(persons.begin(), persons.end(),
		[](Person i) {return i.gender == (Gender::FEMALE) && (i.is_employed == true); });
	cout << "Median age for employed females = " << ComputeMedianAge(persons.begin(), border) << endl;

	border = partition(persons.begin(), persons.end(),
		[](Person i) {return i.gender == (Gender::FEMALE) && (i.is_employed == false); });
	cout << "Median age for unemployed females = " << ComputeMedianAge(persons.begin(), border) << endl;

	border = partition(persons.begin(), persons.end(),
		[](Person i) {return i.gender == (Gender::MALE) && (i.is_employed == true); });
	cout << "Median age for employed males = " << ComputeMedianAge(persons.begin(), border) << endl;

	border = partition(persons.begin(), persons.end(),
		[](Person i) {return i.gender == (Gender::MALE) && (i.is_employed == false); });
	cout << "Median age for unemployed males = " << ComputeMedianAge(persons.begin(), border) << endl;
}