#include "Movie.h"
#include "Actor.h"
#include <iostream>
using namespace std;

// Constructor
Movie::Movie(const int& id, const string& title, const string& plot, int releaseYear)
    : id(id), title(title), plot(plot), releaseYear(releaseYear), actorHead(nullptr) {}

// Destructor
Movie::~Movie() {
    ActorNode* current = actorHead;
    while (current) {
        ActorNode* temp = current;
        current = current->next;
        delete temp;
    }
}

// Getter methods
int Movie::getId() const { return id; }
string Movie::getTitle() const { return title; }
string Movie::getPlot() const { return plot; }
int Movie::getReleaseYear() const { return releaseYear; }

// Setter methods
void Movie::setId(const int& id) { this->id = id; }
void Movie::setTitle(const string& title) { this->title = title; }
void Movie::setPlot(const string& plot) { this->plot = plot; }
void Movie::setReleaseYear(int releaseYear) { this->releaseYear = releaseYear; }

// Add an actor to the movie's list
void Movie::addActor(Actor* actor) {
    ActorNode* newNode = new ActorNode(actor);
    newNode->next = actorHead;
    actorHead = newNode;
}


void Movie::updateDetails(const string& newTitle, const string& newPlot, int newReleaseYear) {
    if (!newTitle.empty()) {
        title = newTitle;
    }
    if (!newPlot.empty()) {
        plot = newPlot;
    }
    if (newReleaseYear > 0) {
        releaseYear = newReleaseYear;
    }
    cout << "Movie details updated successfully." << endl;
}


// Display movie details and their actors
void Movie::display() const {
    cout << "Movie ID: " << id << ", \nTitle: " << title
         << ", \nPlot: " << plot << ", \nRelease Year: " << releaseYear << endl;
    cout << "\nActors in this movie:" << endl;

    ActorNode* current = actorHead;
    if (!current) {
        cout << "No actors in this movie." << endl;
        return;
    }

    while (current) {
        // Display both actor ID and name
        cout << " - ID: " << current->actor->getId()
             << ", Name: " << current->actor->getName() << endl;
        current = current->next;
    }
}