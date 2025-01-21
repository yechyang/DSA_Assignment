#include "Actor.h"
#include "Movie.h"
#include <iostream>
using namespace std;

// Constructor
Actor::Actor(const int& id, const string& name, int birthYear)
    : id(id), name(name), birthYear(birthYear), movieHead(nullptr) {}

// Destructor
Actor::~Actor() {
    MovieNode* current = movieHead;
    while (current) {
        MovieNode* temp = current;
        current = current->next;
        delete temp;
    }
}

// Getter methods
int Actor::getId() const { return id; }
string Actor::getName() const { return name; }
int Actor::getBirthYear() const { return birthYear; }

// Setter methods
void Actor::setId(const int& id) { this->id = id; }
void Actor::setName(const string& name) { this->name = name; }
void Actor::setBirthYear(int birthYear) { this->birthYear = birthYear; }

// Add a movie to the actor's list
void Actor::addMovie(Movie* movie) {
    MovieNode* newNode = new MovieNode(movie);
    newNode->next = movieHead;
    movieHead = newNode;
}

// New method to return the head of the movie list
const MovieNode* Actor::getMovies() const {
    return movieHead;
}

void Actor::updateDetails(const string& newName, int newBirthYear) {
    if (!newName.empty()) {
        name = newName;
    }
    if (newBirthYear > 0) {
        birthYear = newBirthYear;
    }
    cout << "Actor details updated successfully." << endl;
}

// Display actor details and their movies
void Actor::display() const {
    cout << "Actor ID: " << id << ", \nName: " << name << ", \nBirth Year: " << birthYear << endl;
    cout << "\nMovies:" << endl;

    MovieNode* current = movieHead;
    while (current) {
        current->movie->display();
        current = current->next;
    }
}

