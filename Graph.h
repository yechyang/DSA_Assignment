#ifndef GRAPH_H
#define GRAPH_H

#include "Actor.h"
#include <iostream>

class Graph {
private:
    // **Structure for adjacency list nodes (Linked List)**
    struct ListNode {
        int actorId;
        ListNode* next;

        ListNode(int id) : actorId(id), next(nullptr) {}
    };

    // **Structure for each actor node in the graph**
    struct ActorNode {
        Actor* actor;
        ListNode* head;
        ActorNode* next;
    
        ActorNode(Actor* actorPtr) : actor(actorPtr), head(nullptr), next(nullptr) {}
    };    

    ActorNode* actorList;

    // **Finds an actor node by ID**
    // Searches for an actor in the graph.
    // Pre-condition: Actor ID must be valid.
    // Post-condition: Returns the ActorNode if found, otherwise returns nullptr.
    ActorNode* findActor(int actorId);

public:
    // **Constructor**
    // Purpose: Initializes an empty graph.
    // Pre-condition: None.
    // Post-condition: The graph is initialized with an empty actor list.
    Graph();

    // **Destructor**
    // Purpose: Cleans up memory by deleting all actors and their connections.
    // Pre-condition: Graph must exist.
    // Post-condition: All allocated memory for actors and their connections is freed.
    ~Graph();

    // **Adds an actor to the graph**
    // Purpose: Inserts an actor into the graph if they do not already exist.
    // Pre-condition: Actor pointer must be valid.
    // Post-condition: The actor is added to the graph.
    void addActor(Actor* actor);

    // **Adds a connection between two actors**
    // Purpose: Establishes a collaboration between two actors.
    // Pre-condition: Both actors must exist in the graph.
    // Post-condition: A bidirectional connection is created between the two actors.
    void addConnection(int actor1, int actor2);

    // **Displays all connections of an actor**
    // Purpose: Lists all co-actors of a given actor.
    // Pre-condition: The actor must exist in the graph.
    // Post-condition: Prints all co-actors at first and second levels.
    void displayConnections(Actor* actor);
};

#endif
