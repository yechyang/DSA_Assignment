#ifndef MOVIEAVLNODE_H
#define MOVIEAVLNODE_H

#include "Movie.h"

// Linked list node for storing movies with the same release year
struct MovieListNode {
    Movie* movie;
    MovieListNode* next;

    MovieListNode(Movie* movie) : movie(movie), next(nullptr) {}
};

// AVL Tree Node
struct MovieAVLNode {
    int releaseYear;             // The release year (used as the key)
    MovieListNode* movieList;    // Linked list of movies for this year
    int height;                  // Height of the node in the AVL tree
    MovieAVLNode* left;          // Pointer to the left child
    MovieAVLNode* right;         // Pointer to the right child

    MovieAVLNode(Movie* movie)
        : releaseYear(movie->getReleaseYear()),
          movieList(new MovieListNode(movie)),
          height(1),
          left(nullptr),
          right(nullptr) {}
};

#endif
