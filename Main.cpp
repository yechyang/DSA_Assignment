#include <iostream>
#include <fstream>
#include <sstream>
#include "Dictionary.h"
#include "AVLTree.h"
#include "Actor.h"
#include "Movie.h"
#include "Graph.h"
#include <ctime>

using namespace std;

// Function to validate and convert string to int
int safeStoi(const string& str) {
    try {
        return stoi(str);
    } catch (...) {
        return -1; // Invalid value
    }
}

// Function to skip headers in CSV
void skipHeader(ifstream& file) {
    string header;
    getline(file, header);
}

// Function to load actors from a CSV file
void loadActors(const string& filename, Dictionary<Actor>& actorTable,AVLTree<Actor>& actorTree, Graph& actorGraph) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening " << filename << endl;
        return;
    }

    skipHeader(file); // Skip the header row

    string line, id, name, birthYear;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, id, ',');
        getline(ss, name, ',');   // Name may have double quotes
        getline(ss, birthYear);

        int year = safeStoi(birthYear);
        int intId = safeStoi(id);

        if (intId == -1 || name.empty() || year == -1) {
            continue;
        }

        if (name.front() == '"' && name.back() == '"') {
            name = name.substr(1, name.length() - 2);
        }

        cout << "Loaded Actor: [" << name << "]" << endl;

        actorTable.insert(intId, Actor(intId, name, year));
        Actor* actorPtr = actorTable.search(intId);
        if (actorPtr) {
            actorTree.insert(actorPtr);
        }
    }

    file.close();
    cout << "Actors loaded from " << filename << endl;
}

// Function to load movies from a CSV file
void loadMovies(const string& filename, Dictionary<Movie>& movieTable,AVLTree<Movie>& movieTree) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening " << filename << endl;
        return;
    }

    skipHeader(file); // Skip the header row

    string line, id, title, plot, releaseYear;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, id, ',');
        getline(ss, title, ',');
        getline(ss, plot, ',');
        getline(ss, releaseYear);

        int year = safeStoi(releaseYear);
        if (id.empty() || title.empty() || year == -1) {
            continue;
        }
        int intId = safeStoi(id);
        if (intId == -1) {
            continue;
        }

        Movie movie(intId, title, plot, year);
        movieTable.insert(intId, movie);

        std::cout << "Loading Movie: " << title << " (" << year << ")" << std::endl;

        Movie* moviePtr = movieTable.search(intId);
        if (moviePtr) {
            movieTree.insert(moviePtr);
        }
    }
    file.close();
    cout << "Movies loaded from " << filename << endl;
}

// Function to load cast relationships from a CSV file
void loadCast(const string& filename, Dictionary<Actor>& actorTable, Dictionary<Movie>& movieTable, Graph& actorGraph) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening " << filename << endl;
        return;
    }

    skipHeader(file); // Skip header

    string line, actorId, movieId;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, actorId, ',');
        getline(ss, movieId);

        int intActorId = safeStoi(actorId);
        int intMovieId = safeStoi(movieId);
        
        if (intActorId == -1 || intMovieId == -1) {
            continue;
        }

        Actor* actor = actorTable.search(intActorId);
        Movie* movie = movieTable.search(intMovieId);

        if (actor && movie) {
            actor->addMovie(movie);
            movie->addActor(actor);
            actorGraph.addActor(actor); // **Pass the Actor* instead of ID**
            
            // Add edges between all actors in the same movie
            int numActors;
            Actor** actorsInMovie = movie->getSortedActors(numActors);
            for (int i = 0; i < numActors; ++i) {
                if (actorsInMovie[i]->getId() != intActorId) {
                    actorGraph.addConnection(intActorId, actorsInMovie[i]->getId());
                }
            }
            delete[] actorsInMovie;
        }
    }

    file.close();
    cout << "Cast relationships loaded and graph built from " << filename << endl;
}

// Global variables for filtering logic
Actor** allActors = nullptr;
int totalActors = 0;

// Standalone function to collect actors into an array
void collectActors(const Actor& actor) {
    allActors[totalActors++] = const_cast<Actor*>(&actor);
}
// Standalone function to collect all movies into an array


// Global variables for movie collection
Movie** recentMovies = nullptr;
int movieCount = 0;
int currentYear = 2025;
void collectAllMovies(const Movie& movie) {
    recentMovies[movieCount++] = const_cast<Movie*>(&movie);
}

// Free-standing function to filter movies
void collectRecentMovies(const Movie& movie) {
    if (movie.getReleaseYear() >= currentYear - 3) {
        recentMovies[movieCount++] = const_cast<Movie*>(&movie);
    }
}


// Menu-driven application
void runApplication(Dictionary<Actor>& actorTable, Dictionary<Movie>& movieTable, AVLTree<Actor>& actorTree, AVLTree<Movie>& movieTree, Graph& actorGraph) {
    int choice;

    while (true) {
        cout << "\nMovie Application Menu\n";
        cout << "1. Add new actor\n";
        cout << "2. Add new movie\n";
        cout << "3. Add an actor to a movie\n";
        cout << "4. Display all actors in a movie\n";
        cout << "5. Display all movies of an actor\n";
        cout << "6. Exit\n";
        cout << "7. Update actor details\n";
        cout << "8. Update movie details\n";
        cout << "9. Display actors by age range\n";
        cout << "10. Display Movies Within past 3 years\n";
        cout << "11. Display a list of all actors that a particular actor knows.\n";
        cout << "12. Update Actor Rating" << endl;
        cout << "13. Update Movie Rating" << endl;
        cout << "14. Display Actor By Rating" << endl;
        cout << "15. Display Movie By Rating" << endl;
        cout << "16. Recommendations based on rating of Movie.\n";
        cout << "17. Recommendations based on rating of Actor (with Movies).\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;
        if (choice == 1) {
            // Add new actor
            int id;
            string name;
            int birthYear;
            cout << "Enter Actor ID: ";
            cin >> id;
            cout << "Enter Actor Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Birth Year: ";
            cin >> birthYear;
            Actor actor(id, name, birthYear);
            actorTable.insert(id, actor);
            cout << "Actor added successfully!" << endl;
            Actor* actorPtr = actorTable.search(id);

            if (actorPtr) {
                actorTree.insert(actorPtr);
                cout << "Actor added successfully to Dictionary and AVL Tree!" << endl;
            } else {
                cerr << "Error: Actor insertion failed!" << endl;
            }
        } else if (choice == 2) {
            // Add new movie
            int id;
            string title, plot;
            int releaseYear;
            cout << "Enter Movie ID: ";
            cin >> id;
            cout << "Enter Movie Title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter Movie Plot: ";
            getline(cin, plot);
            cout << "Enter Release Year: ";
            cin >> releaseYear;
            Movie movie(id, title, plot, releaseYear);
            movieTable.insert(id, movie);
            cout << "Movie added successfully!" << endl;

            Movie* moviePtr = movieTable.search(id);

            if (moviePtr) {
                // Insert into the AVL Tree
                movieTree.insert(moviePtr);
            } else {
                cerr << "Error: Movie insertion failed!" << endl;
            }
        } else if (choice == 3) {
            // Add an actor to a movie
            int actorId, movieId;
            cout << "Enter Actor ID: ";
            cin >> actorId;
            cout << "Enter Movie ID: ";
            cin >> movieId;

            Actor* actor = actorTable.search(actorId);
            Movie* movie = movieTable.search(movieId);

            if (actor && movie) {
                actor->addMovie(movie);
                movie->addActor(actor);
                cout << "Relationship added successfully!" << endl;
            } else {
                cerr << "Error: Actor or Movie not found." << endl;
            }
        } else if (choice == 4) {
            string movieName;
            cout << "Enter Movie name: ";
            cin.ignore();
            getline(cin, movieName);  // Use getline to capture full movie name

            int matchCount;
            Movie** movies = movieTable.searchByTitle(movieName, matchCount);

            if (!movies) {
                cerr << "Error: Movie not found." << endl;
                return;
            }

            // Display matched movies
            cout << "Movies found:" << endl;
            for (int i = 0; i < matchCount; ++i) {
                cout << "(" << i + 1 << ") " << "- ID: " << movies[i]->getId() << ", Title: " << movies[i]->getTitle() << " (Year: " << movies[i]->getReleaseYear() << ")" << endl;
            }

            // User selects a movie
            int choice;
            cout << "Enter the number of the movie you want: ";
            cin >> choice;

            if (choice < 1 || choice > matchCount) {
                cerr << "Invalid selection." << endl;
                delete[] movies;
                return;
            }

            // Retrieve selected movie
            Movie* selectedMovie = movies[choice - 1];
            delete[] movies;  // Free allocated memory

            // Get and display sorted actors in the selected movie
            int actorCount;
            Actor** sortedActors = selectedMovie->getSortedActors(actorCount);

            cout << "Actors in the movie \"" << selectedMovie->getTitle() << "\" (sorted alphabetically):" << endl;
            for (int i = 0; i < actorCount; ++i) {
                cout << "- ID: " << sortedActors[i]->getId() << ", Name: " << sortedActors[i]->getName() << endl;
            }

            delete[] sortedActors; // Free allocated memory
        }
        else if (choice == 5) {
            string actorName;
            cout << "Enter Actor name: ";
            cin.ignore();
            getline(cin, actorName);  // Use getline to capture full actor name

            int matchCount;
            Actor** actors = actorTable.searchByName(actorName, matchCount);

            if (!actors) {
                cerr << "Error: Actor not found." << endl;
                return;
            }

            // Display matched actors
            cout << "Actors found:" << endl;
            for (int i = 0; i < matchCount; ++i) {
                cout << "(" << i + 1 << ") " << "- ID: " << actors[i]->getId() << ", Name: " << actors[i]->getName() << " (BirthYear: " << actors[i]->getBirthYear() << ")" << endl;
            }

            // User selects an actor
            int choice;
            cout << "Enter the number of the actor you want: ";
            cin >> choice;

            if (choice < 1 || choice > matchCount) {
                cerr << "Invalid selection." << endl;
                delete[] actors;
                return;
            }

            // Retrieve selected actor
            Actor* selectedActor = actors[choice - 1];
            delete[] actors;  // Free allocated memory

            // Get and display sorted movies for the selected actor
            int movieCount;
            Movie** sortedMovies = selectedActor->getSortedMovies(movieCount);

            cout << "Movies starring " << selectedActor->getName() << " (sorted alphabetically):" << endl;
            for (int i = 0; i < movieCount; ++i) {
                cout << "- Title: " << sortedMovies[i]->getTitle()
                    << ", Year: " << sortedMovies[i]->getReleaseYear() << endl;
            }

            delete[] sortedMovies; // Free allocated memory
        } else if (choice == 6) {
            // Exit
            cout << "Exiting application. Goodbye!" << endl;
            break;
        } else if (choice == 7) {
            // Update actor details by searching for name
            string actorName;
            cout << "Enter Actor Name to update: ";
            cin.ignore();
            getline(cin, actorName);

            int matchCount;
            Actor** actors = actorTable.searchByName(actorName, matchCount);

            if (!actors) {
                cerr << "Error: Actor not found." << endl;
                return;
            }

            // Display matched actors
            cout << "\nActors found:\n";
            for (int i = 0; i < matchCount; ++i) {
                cout << "(" << i + 1 << ") " << "- ID: " << actors[i]->getId() << ", Name: " << actors[i]->getName() << " (BirthYear: " << actors[i]->getBirthYear() << ")" << endl;
            }

            // User selects an actor
            int choice;
            cout << "Enter the number of the actor you want to update: ";
            cin >> choice;

            if (choice < 1 || choice > matchCount) {
                cerr << "Invalid selection." << endl;
                delete[] actors;
                return;
            }

            // Retrieve selected actor
            Actor* selectedActor = actors[choice - 1];
            delete[] actors;  // Free allocated memory

            // Get new details
            string newName;
            int newBirthYear;
            cout << "Enter new name (leave empty to keep current): ";
            cin.ignore();
            getline(cin, newName);
            cout << "Enter new birth year (enter 0 to keep current): ";
            cin >> newBirthYear;

            int oldBirthYear = selectedActor->getBirthYear();

            // If birth year is updated, remove & reinsert using update()
            if (newBirthYear != 0 && newBirthYear != oldBirthYear) {
                Actor updatedActor = *selectedActor;  // Copy existing data
                updatedActor.updateDetails(newName, newBirthYear);  // Update fields

                actorTree.update(selectedActor, &updatedActor);
            } else {
                // Simply update details without AVL rebalancing
                selectedActor->updateDetails(newName, newBirthYear);
            }
            
            cout << "\nActor details updated successfully!" << endl;
        } else if (choice == 8) {
            // Update movie details by searching for title
            string movieTitle;
            cout << "Enter Movie Title to update: ";
            cin.ignore();
            getline(cin, movieTitle);

            int matchCount;
            Movie** movies = movieTable.searchByTitle(movieTitle, matchCount);

            if (!movies) {
                cerr << "Error: Movie not found." << endl;
                return;
            }

            // Display matched movies
            cout << "\nMovies found:\n";
            for (int i = 0; i < matchCount; ++i) {
                cout << "(" << i + 1 << ") " << "- ID: " << movies[i]->getId() << ", Title: " << movies[i]->getTitle() << " (Year: " << movies[i]->getReleaseYear() << ")" << endl;
            }

            // User selects a movie
            int choice;
            cout << "Enter the number of the movie you want to update: ";
            cin >> choice;

            if (choice < 1 || choice > matchCount) {
                cerr << "Invalid selection." << endl;
                delete[] movies;
                return;
            }

            // Retrieve selected movie
            Movie* selectedMovie = movies[choice - 1];
            delete[] movies;  // Free allocated memory

            movieTree.remove(selectedMovie);

            // Get new details
            string newTitle, newPlot;
            int newReleaseYear;
            cout << "Enter new title (leave empty to keep current): ";
            cin.ignore();
            getline(cin, newTitle);
            cout << "Enter new plot (leave empty to keep current): ";
            getline(cin, newPlot);
            cout << "Enter new release year (enter 0 to keep current): ";
            cin >> newReleaseYear;

            selectedMovie->updateDetails(newTitle, newPlot, newReleaseYear);

            movieTree.insert(selectedMovie);
            cout << "\nMovie details updated successfully!" << endl;
        } else if (choice == 9) {
            int minAge, maxAge;
            cout << "Enter the minimum age (x): ";
            cin >> minAge;
            cout << "Enter the maximum age (y): ";
            cin >> maxAge;
        
            if (minAge > maxAge) {
                cout << "Invalid range. Ensure that minimum age <= maximum age." << endl;
                return;
            }
        
            // Directly use AVL Tree to search and display actors
            actorTree.displayActorsInAgeRange(minAge, maxAge);
        } else if (choice == 10) {
            int currentYear = 2025;
            int pastyear = currentYear - 3;

            std::cout << "\nAll Movies in AVL Tree (Sorted by Year & ID):\n";
            movieTree.displayAllMovies();

            cout << "\nMovies released in the past 3 years (sorted by year):\n";
            movieTree.displayMoviesInRange(pastyear, currentYear);
        } else if (choice == 11) {
           // Search for an actor by name instead of ID
           string actorName;
           cout << "Enter Actor Name: ";
           cin.ignore();
           getline(cin, actorName);

           int matchCount;
           Actor** actors = actorTable.searchByName(actorName, matchCount);

           if (!actors) {
               cerr << "Error: Actor not found." << endl;
               return;
           }

           // Display matched actors
           cout << "\nActors found:\n";
           for (int i = 0; i < matchCount; ++i) {
               cout << "(" << i + 1 << ") " << actors[i]->getName() << " (ID: " << actors[i]->getId() << ")" << endl;
           }

           // User selects an actor
           int choice;
           cout << "Enter the number of the actor you want: ";
           cin >> choice;

           if (choice < 1 || choice > matchCount) {
               cerr << "Invalid selection." << endl;
               delete[] actors;
               return;
           }

           // Retrieve selected actor
           Actor* selectedActor = actors[choice - 1];
           delete[] actors;  // Free allocated memory

            // Display known actors
            actorGraph.displayConnections(selectedActor);
        }  else if (choice == 12) {
            // Update actor rating using actor name search
            string actorName;
            cout << "\nEnter Actor Name: ";
            cin.ignore();  // Clear input buffer
            getline(cin, actorName);  // Allow full actor name input

            int matchCount;
            Actor** actors = actorTable.searchByName(actorName, matchCount);

            if (!actors) {
                cerr << "Error: Actor not found." << endl;
                return;
            }

            // Display matched actors
            cout << "\nActors found:\n";
            for (int i = 0; i < matchCount; ++i) {
                cout << "(" << i + 1 << ") " << "- ID: " << actors[i]->getId() << ", Name: " << actors[i]->getName() << " (BirthYear: " << actors[i]->getBirthYear() << ")" << endl;
            }

            // Let user pick an actor from the list
            int choice;
            cout << "Enter the number of the actor you want to update: ";
            cin >> choice;

            if (choice < 1 || choice > matchCount) {
                cerr << "Invalid selection." << endl;
                delete[] actors;
                return;
            }

            // Retrieve selected actor
            Actor* selectedActor = actors[choice - 1];
            delete[] actors;  // Free allocated memory

            // Ask for new rating
            float newRating;
            cout << "Enter new rating (0.0 to 10.0): ";
            cin >> newRating;
            selectedActor->setRating(newRating);

            cout << "\nRating updated successfully for " << selectedActor->getName() << "!" << endl;
        } else if (choice == 13) {
            // Update movie rating using movie title search
            string movieTitle;
            cout << "\nEnter Movie Title: ";
            cin.ignore();  // Clear input buffer
            getline(cin, movieTitle);  // Allow full movie title input

            int matchCount;
            Movie** movies = movieTable.searchByTitle(movieTitle, matchCount);

            if (!movies) {
                cerr << "Error: Movie not found." << endl;
                return;
            }

            // Display matched movies
            cout << "\nMovies found:\n";
            for (int i = 0; i < matchCount; ++i) {
                cout << "(" << i + 1 << ") "<< "- ID: " << movies[i]->getId() << ", Title: " << movies[i]->getTitle() << " (Year: " << movies[i]->getReleaseYear() << ")" << endl;
            }

            // Let user pick a movie from the list
            int choice;
            cout << "Enter the number of the movie you want to update: ";
            cin >> choice;

            if (choice < 1 || choice > matchCount) {
                cerr << "Invalid selection." << endl;
                delete[] movies;
                return;
            }

            // Retrieve selected movie
            Movie* selectedMovie = movies[choice - 1];
            delete[] movies;  // Free allocated memory

            // Ask for new rating
            float newRating;
            cout << "Enter new rating (0.0 to 10.0): ";
            cin >> newRating;
            selectedMovie->setRating(newRating);

            cout << "\nRating updated successfully for \"" << selectedMovie->getTitle() << "\"!" << endl;
        } else if (choice == 14) {
            // Collect all actors from the hash table
            allActors = new Actor*[actorTable.getSize()];
            totalActors = 0;

            actorTable.display(collectActors); // Collect all actors into allActors array

            if (totalActors == 0) {
                cout << "\nNo actors available to display." << endl;
            } else {
                // Sort the actors by rating
                allActors[0]->sortActorsByRating(allActors, totalActors);

                // Display sorted actors
                cout << "\nActors sorted by rating (highest to lowest):" << endl;
                for (int i = 0; i < totalActors; ++i) {
                    cout << "- ID: " << allActors[i]->getId()
                        << ", Name: " << allActors[i]->getName()
                        << ", Rating: " << allActors[i]->getRating() << endl;
                }
            }

            delete[] allActors; // Free allocated memory
            allActors = nullptr;
        } else if (choice == 15) {
            // Collect all movies from the hash table
            recentMovies = new Movie*[movieTable.getSize()];
            movieCount = 0;

            movieTable.display(collectAllMovies); // Collect all movies into recentMovies array

            if (movieCount == 0) {
                cout << "\nNo movies available to display." << endl;
            } else {
                // Sort the movies by rating
                recentMovies[0]->sortMoviesByRating(recentMovies, movieCount);

                // Display sorted movies
                cout << "\nMovies sorted by rating (highest to lowest):" << endl;
                for (int i = 0; i < movieCount; ++i) {
                    cout << "- ID: " << recentMovies[i]->getId()
                        << ", Title: " << recentMovies[i]->getTitle()
                        << ", Rating: " << recentMovies[i]->getRating() << endl;
                }
            }

            delete[] recentMovies; // Free allocated memory
            recentMovies = nullptr;
        } else if (choice == 16) {

            int subChoice;
            cout << "\nRecommendation Options:\n";
            cout << "1. Recommend by Minimum Rating\n";
            cout << "2. Recommend by Year\n";
            cout << "Enter your choice: ";
            cin >> subChoice;

            recentMovies = new Movie*[movieTable.getSize()];
            movieCount = 0;

            movieTable.display(collectAllMovies);

            Movie tempMovie;  // Temporary object to call the recommendation methods

            if (subChoice == 1) {
                float minRating;
                cout << "Enter minimum movie rating: ";
                cin >> minRating;
                tempMovie.recommendMoviesByRating(recentMovies, movieCount, minRating);
            } 
            else if (subChoice == 2) {
                int year;
                cout << "Enter the year: ";
                cin >> year;
                tempMovie.recommendMoviesByYear(recentMovies, movieCount, year);
            } 
            else {
                cout << "Invalid choice!" << endl;
            }

            delete[] recentMovies;  // Free allocated memory
        } else if (choice == 17) {
            float minRating;
            cout << "Enter minimum actor rating: ";
            cin >> minRating;

            allActors = new Actor*[actorTable.getSize()];
            totalActors = 0;

            actorTable.display(collectActors); // Collect all actors into allActors array

            Actor tempActor;  // Temporary object to call the method
            tempActor.recommendActorsByRating(allActors, totalActors, minRating);
        } else {
            cerr << "Invalid choice. Please try again." << endl;
        }
    }
}

// Function to compute the key for actor sorting
int computeActorKey(Actor* actor) {
    return (2025 - actor->getBirthYear()) * 1000000 + actor->getId();
}

// Function to compute the key for movie sorting
int computeMovieKey(Movie* movie) {
    return movie->getReleaseYear() * 1000000 + movie->getId();
}
// Main function
int main() {
    Dictionary<Actor> actorTable; // Actor hash table
    Dictionary<Movie> movieTable; // Movie hash table

    AVLTree<Actor> actorTree(computeActorKey);
    AVLTree<Movie> movieTree(computeMovieKey);

    Graph actorGraph;
    
    // Load data from CSV files
    loadActors("actors.csv", actorTable, actorTree,actorGraph);
    loadMovies("movies.csv", movieTable, movieTree);
    loadCast("cast.csv", actorTable, movieTable,actorGraph);
    // Run the application
    runApplication(actorTable, movieTable,actorTree, movieTree,actorGraph);

    return 0;
}