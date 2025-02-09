#include "Graph.h"
#include "Actor.h"
#include "Dictionary.h"

// **Constructor**
Graph::Graph() {
    actorList = nullptr;
}

// **Destructor**
// Time Complexity: O(N + E) Where N = number of actors, E = number of connections
Graph::~Graph() {
    ActorNode* currentActor = actorList;
    while (currentActor) {
        ListNode* neighbor = currentActor->head;
        while (neighbor) {
            ListNode* temp = neighbor;
            neighbor = neighbor->next;
            delete temp; // Free adjacency list memory
        } 
        ActorNode* temp = currentActor;
        currentActor = currentActor->next;
        delete temp;  // Free actor node memory
    }
}

// **Find an actor node in the graph**
// Searches for an actor by ID in the actor list
// Returns a pointer to the actor node if found, otherwise nullptr
// Time Complexity: O(N) (Worst case: iterate through all actors)
// Space Complexity: O(1)
Graph::ActorNode* Graph::findActor(int actorId) {
    ActorNode* current = actorList;
    while (current) {
        if (current->actor->getId() == actorId) return current;
        current = current->next;
    }
    return nullptr;
}

// **Add an actor to the graph (if not exists)**
// Time Complexity: O(N) (Search for existing actor before adding)
// Space Complexity: O(1) (Only storing a new node)
void Graph::addActor(Actor* actor) {
    if (findActor(actor->getId())) return; // Actor already exists

    ActorNode* newActorNode = new ActorNode(actor);
    newActorNode->next = actorList;
    actorList = newActorNode;
}

// **Add a connection (edge) between two actors**
// Creates an undirected edge (bi-directional relationship) between two actors
// Time Complexity: O(N) (Search for both actors) + O(E) (Check if connection exists) ≈ O(N)
// Space Complexity: O(1) (Only storing two new nodes if needed)
void Graph::addConnection(int actor1, int actor2) {
    ActorNode* actorNode1 = findActor(actor1);
    ActorNode* actorNode2 = findActor(actor2);

    if (!actorNode1 || !actorNode2) return; // Ensure both actors exist

    // **Check if the connection already exists before adding**
    ListNode* temp = actorNode1->head;
    while (temp) {
        if (temp->actorId == actor2) return; // Connection already exists
        temp = temp->next;
    }

    // **Add actor2 to actor1's adjacency list**
    ListNode* newNode1 = new ListNode(actor2);
    newNode1->next = actorNode1->head;
    actorNode1->head = newNode1;

    // **Add actor1 to actor2's adjacency list**
    ListNode* newNode2 = new ListNode(actor1);
    newNode2->next = actorNode2->head;
    actorNode2->head = newNode2;
}

// **Display all actors known by a particular actor**
// Uses BFS-like traversal to find direct and indirect connections
// Time Complexity: O(N + E) (Visits all actors and edges up to second level)
// Space Complexity: O(N) (Uses dictionaries to track visited actors)
void Graph::displayConnections(Actor* actor) {
    if (!actor) {
        std::cout << "Actor not found in the graph.\n";
        return;
    }

    ActorNode* actorNode = findActor(actor->getId());
    if (!actorNode) {
        std::cout << "Actor not found in the graph structure.\n";
        return;
    }

    // **Array to store known actors (direct and indirect)**
    const int maxActors = 17000;
    int knownActors[maxActors];
    int knownCount = 0;

    Dictionary<bool> processedActors; // Actors already displayed
    Dictionary<bool> level1Actors; // Direct co-actors

    // First-level connections (direct co-actors)
    ListNode* neighbor = actorNode->head;
    while (neighbor) {
        int coActorId = neighbor->actorId;

        // **Skip adding the actor themselves**
        if (coActorId == actor->getId()) {
            neighbor = neighbor->next;
            continue;
        }

        // **Only add unique co-actors**
        if (!processedActors.search(coActorId)) { // Avoid duplicates
            knownActors[knownCount++] = coActorId; // Store actor ID in the array
            processedActors.insert(coActorId, true); // Mark as processed
            level1Actors.insert(coActorId, true);  // Mark as a direct co-actor
        }
        neighbor = neighbor->next;
    }

    // Second-level connections (co-actors of co-actors)
    // This loop iterates through all the first-level actors and finds their co-actors.
    for (int i = 0; i < knownCount; ++i) {
        int level1ActorId = knownActors[i];
        if (!level1Actors.search(level1ActorId)) continue;  // **Ensure this actor was a direct connection before proceeding**

        ActorNode* level1Actor = findActor(level1ActorId);
        if (!level1Actor) continue;

        // **Iterate through the second-level co-actors**
        ListNode* level1Neighbor = level1Actor->head;
        while (level1Neighbor) {
            int secondLevelActorId = level1Neighbor->actorId;

            // **Skip adding the actor themselves**
            if (secondLevelActorId == actor->getId()) {
                level1Neighbor = level1Neighbor->next;
                continue;
            }

            // **Only add unique second-level connections**
            if (!processedActors.search(secondLevelActorId)) {
                knownActors[knownCount++] = secondLevelActorId;
                processedActors.insert(secondLevelActorId, true);
            }
            level1Neighbor = level1Neighbor->next;
        }
    }

    // Display known actors
    std::cout << "Actors known by " << actor->getName() << " (ID: " << actor->getId() << "):\n";
    for (int i = 0; i < knownCount; ++i) {
        ActorNode* knownActorNode = findActor(knownActors[i]);
        std::string coActorName = (knownActorNode) ? knownActorNode->actor->getName() : "Unknown";

        std::cout << "- Actor ID: " << knownActors[i] << " | Name: " << coActorName << std::endl;
    }
}