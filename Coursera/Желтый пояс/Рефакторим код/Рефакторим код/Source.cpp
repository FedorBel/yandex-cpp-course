//#include "pch.h"
#include <iostream>
#include <string>
#include<vector>

using namespace std;

class Human {
public:
	Human(const string& name, const string& type) : Name(name), Type(type) {}

	virtual void Walk(const string& destination) const {
		cout << Type << ": " << Name << " walks to: " << destination << endl;
	}

	const string Name;
	const string Type;
};

class Student : public Human {
public:

	Student(const string& name, const string& favouriteSong) : Human(name, "Student"),
		FavouriteSong(favouriteSong) {}

	void Learn() {
		cout << "Student: " << Name << " learns" << endl;
	}

	void Walk(const string& destination) const {
		Human::Walk(destination);
		SingSong();
	}

	void SingSong() const {
		cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
	}

private:
	const string FavouriteSong;
};

class Teacher : public Human {
public:

	Teacher(const string& name, const string& subject) : Human(name, "Teacher"),
		Subject(subject) {}

	void Teach() {
		cout << "Teacher: " << Name << " teaches: " << Subject << endl;
	}

private:
	const string Subject;
};


class Policeman : public Human {
public:
	Policeman(const string& name) : Human(name, "Policeman") {}

	void Check(Human& h) {
		cout << Type << ": " << Name << " checks " << h.Type
			<< ". " << h.Type << "'s name is: " << h.Name << endl;
	}
};

void VisitPlaces(Human& h, const vector<string>& places) {
	for (auto p : places) {
		h.Walk(p);
	}
}

int main()
{
	Teacher t("Jim", "Math");
	Student s("Ann", "We will rock you");
	Policeman p("Bob");

	VisitPlaces(t, { "Moscow", "London" });
	p.Check(s);
	VisitPlaces(s, { "Moscow", "London" });
	return 0;
}

