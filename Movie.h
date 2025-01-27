#ifndef MOVIE_H
#define MOVIE_H

#include <string>
using namespace std;

class Actor; // Forward declaration

struct MovieAVLNode;

// Linked list node for storing relationships
struct ActorNode {
    Actor* actor;
    ActorNode* next;

    ActorNode(Actor* actor) : actor(actor), next(nullptr) {}
};

class Movie {
private:
    int id;            // Movie's unique ID
    string title;         // Movie title
    string plot;          // Movie plot
    int releaseYear;      // Release year of the movie
    ActorNode* actorHead; // Head of the linked list of actors
    float rating; // Movie's rating

public:
    // Constructor
    Movie(const int& id = 0, const string& title = "", const string& plot = "", int releaseYear = 0);

    // Destructor
    ~Movie();

    // Getter methods
    int getId() const;
    string getTitle() const;
    string getPlot() const;
    int getReleaseYear() const;
    float getRating() const;

    // Setter methods
    void setId(const int& id);
    void setTitle(const string& title);
    void setPlot(const string& plot);
    void setReleaseYear(int releaseYear);
    void setRating(float newRating);

    // Add an actor to the movie's list
    void addActor(Actor* actor);

    // Update movie details
    void updateDetails(const string& newTitle, const string& newPlot, int newReleaseYear);

    // Display movie details and their actors
    void display() const;

    // Get sorted actors by name
    Actor** getSortedActors(int& count) const;

    Movie** sortMoviesByRating(Movie** movies, int count) const;

    // AVL Tree utility methods (static)
    static int getHeight(MovieAVLNode* node);
    static int getBalance(MovieAVLNode* node);
    static MovieAVLNode* rotateLeft(MovieAVLNode* x);
    static MovieAVLNode* rotateRight(MovieAVLNode* y);
    static MovieAVLNode* insertIntoAVL(MovieAVLNode* node, Movie* movie);
    static void inOrderTraversal(MovieAVLNode* node);
    static void freeAVLTree(MovieAVLNode* node);

    // Sort movies using AVL tree
    static void sortMoviesByReleaseYear(Movie** movies, int count);

    ActorNode* getActorHead() const;
};

#endif