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
        Actor* actor;  // Store pointer to Actor instead of just ID
        ListNode* head;  // Head of adjacency list (co-actors)
        ActorNode* next; // Pointer to the next actor in the graph
    
        ActorNode(Actor* actorPtr) : actor(actorPtr), head(nullptr), next(nullptr) {}
    };    

    ActorNode* actorList; // **Head of actor nodes in the graph**

    // **Helper function to find an actor node**
    ActorNode* findActor(int actorId);

public:
    Graph();
    ~Graph();

    void addActor(Actor* actor);
    void addConnection(int actor1, int actor2);
    void displayConnections(Actor* actor);
};

#endif
