#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public: 
    Person(const string& n, const string& occ) : name(n), occupation(occ) {}

    string Name() const { return name; }
    string Occupation() const { return occupation; }

    virtual void Walk(const string& destination) const {
        cout << Occupation() << ": " << Name() << " walks to: " << destination << endl;
    };

private:
    string name;
    string occupation;
};

class Student : public Person {
public:

    Student(const string& name, const string& favouriteSong) : Person(name, "Student"), favourite_song(favouriteSong) {}

    void Learn() const {
        cout << Occupation() << ": " << Name() << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        Person::Walk(destination);
        SingSong();
    }

    void SingSong() const {
        cout << Occupation() << ": " << Name() << " sings a song: " << favourite_song << endl;
    }

private:
    string favourite_song;
};


class Teacher : public Person {
public:

    Teacher(const string& name, const string& subj) : Person(name, "Teacher"), subject(subj) {}

    void Teach() const {
        cout << Occupation() << ": " << Name() << " teaches: " << subject << endl;
    }

private:
    string subject;
};


class Policeman : public Person {
public:
    Policeman(const string& name) : Person(name, "Policeman") {}

    void Check(const Person& p) const {
        cout << Occupation() << ": " << Name() << " checks " << p.Occupation() << ". " << p.Occupation() << "'s name is: " << p.Name() << endl;
    }
};

void VisitPlaces(const Person& person, const vector<string>& places) {
    for (auto p : places) {
        person.Walk(p);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}