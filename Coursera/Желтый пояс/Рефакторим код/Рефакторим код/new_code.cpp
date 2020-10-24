#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human
{
public:

	virtual void Walk(string destination) const {
		cout << job << ": " << name << " walks to: " << destination << endl;
	}
	string GetName() const { return name; }
	string GetJob() const { return job; }

protected:
	string name;
	string job;
};

class Student : public Human {
public:

	Student(string name, string favouriteSong) {
		this->name = name;
		FavouriteSong = favouriteSong;
		job = "Student";
	}

	void Learn() const {
		cout << "Student: " << this->name << " learns" << endl;
	}

	void Walk(string destination) const override {
		cout << "Student: " << this->name << " walks to: " << destination << endl;
		cout << "Student: " << this->name << " sings a song: " << FavouriteSong << endl;
	}

	void SingSong() const {
		cout << "Student: " << this->name << " sings a song: " << FavouriteSong << endl;
	}

private:
	string FavouriteSong;
};


class Teacher : public Human {
public:

	Teacher(string name, string subject) {
		this->name = name;
		Subject = subject;
		job = "Teacher";
	}

	void Teach() const {
		cout << "Teacher: " << this->name << " teaches: " << Subject << endl;
	}

private:
	string Subject;
};


class Policeman : public Human {
public:
	Policeman(string name) {
		this->name = name;
		job = "Policeman";
	}

	void Check(Human& h) const
	{
		cout << "Policeman: " << this->name << " checks " << h.GetJob() << ". " << h.GetJob() << "'s name is: " << h.GetName() << endl;
	}
};

void VisitPlaces(const Human& hum, const vector<string>& places)
{
	for (const auto& p : places) {
		hum.Walk(p);
	}
}


int main() {
	Teacher t("Jim", "Math");
	Student s("Ann", "We will rock you");
	Policeman p("Bob");
	Human h;

	VisitPlaces(t, { "Moscow", "London" });
	p.Check(s);
	VisitPlaces(s, { "Moscow", "London" });
	return 0;
}
