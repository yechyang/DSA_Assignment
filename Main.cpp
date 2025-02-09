#include <iostream>
#include <fstream>
#include <sstream>
#include "Dictionary.h"
#include "AVLTree.h"
#include "Actor.h"
#include "Movie.h"
#include "Graph.h"
#include <limits>
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
void loadActors(const string& filename, Dictionary<Actor>& actorTable, AVLTree<Actor>& actorTree, Graph& actorGraph) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening " << filename << endl;
        return;
    }

    skipHeader(file);
    int count = 0;

    string line, id, name, birthYear;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, birthYear);

        int year = safeStoi(birthYear);
        int intId = safeStoi(id);

        if (intId == -1 || name.empty() || year == -1) {
            continue;
        }

        if (name.front() == '"' && name.back() == '"') {
            name = name.substr(1, name.length() - 2);
        }

        actorTable.insert(intId, Actor(intId, name, year));
        Actor* actorPtr = actorTable.search(intId);

        if (actorPtr) {
            // 🔥 Ensure AVL tree gets a VALID pointer
            actorTree.insert(actorPtr);
            count++;
        } else {
            cerr << "Error: Actor insertion failed!" << endl;
        }
    }

    file.close();
    cout << "Actors loaded from " << filename << endl;
    cout << "Actors loaded: " << count << " from " << filename << endl;
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
// Function to manually trim whitespace from a string (no STL)
void trimString(string& str) {
    int start = 0, end = str.length() - 1;

    // Trim leading spaces
    while (start <= end && (str[start] == ' ' || str[start] == '\t' || str[start] == '\n' || str[start] == '\r')) {
        start++;
    }

    // Trim trailing spaces
    while (end >= start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n' || str[end] == '\r')) {
        end--;
    }

    // Extract the trimmed string
    str = str.substr(start, end - start + 1);
}

// Menu-driven application
void runApplication(Dictionary<Actor>& actorTable, Dictionary<Movie>& movieTable, AVLTree<Actor>& actorTree, AVLTree<Movie>& movieTree, Graph& actorGraph) {
    int choice;

    while (true) {
        cout << "\n-----------------Movie Application Menu-----------------\n";
        cout << "1.  Add new actor\n";
        cout << "2.  Add new movie\n";
        cout << "3.  Add an actor to a movie\n";
        cout << "4.  Update actor details\n";
        cout << "5.  Update movie details\n";
        cout << "6.  Display actors by age range\n";
        cout << "7.  Display movies made within past 3 years\n";
        cout << "8.  Display all movies of an actor\n";
        cout << "9.  Display all actors in a movie\n";
        cout << "10. Display a list of all actors that a particular actor knows.\n";
        cout << "11. Update actor rating" << endl;
        cout << "12. Update movie rating" << endl;
        cout << "13. Display minimum rating for Movie.\n";
        cout << "14. Display minimum rating for Actor.\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;
        if (choice == 1) {
            // Add new actor
            int id;
            string name;
            int birthYear;

            // Input validation for ID
            cout << "Enter Actor ID: ";
            while (!(cin >> id) || id < 0) {
                cerr << "Invalid ID. Please enter a positive integer." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter Actor ID: ";
            }

            // Check if Actor ID already exists
            if (actorTable.search(id) != nullptr) {
                cerr << "Error: Actor ID already exists!" << endl;
                return;
            }

            // Input validation for Name
            cin.ignore();
            while (true) {
                cout << "Enter Actor Name: ";
                getline(cin, name);
                trimString(name);  // Manually trim whitespace

                if (!name.empty()) {
                    break;
                }
                cerr << "Error: Actor name cannot be empty. Please enter a valid name." << endl;
            }

            // Input validation for Birth Year
            cout << "Enter Birth Year: ";
            while (!(cin >> birthYear) || birthYear < 1800 || birthYear > 2025) {
                cerr << "Invalid Birth Year. Please enter a valid year (1800-2025)." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter Birth Year: ";
            }

            // Insert actor
            try {
                Actor actor(id, name, birthYear);
                actorTable.insert(id, actor);
                cout << "Actor added successfully!" << endl;

                Actor* actorPtr = actorTable.search(id);
                if (actorPtr) {
                    actorTree.insert(actorPtr);
                } else {
                    cerr << "Error: Actor insertion failed!" << endl;
                }
            } catch (const exception& e) {
                cerr << "Exception occurred: " << e.what() << endl;
            }
        } else if (choice == 2) {
            int movieId;
            string title, plot;
            int releaseYear;

            // Input validation for Movie ID
            cout << "Enter Movie ID: ";
            while (!(cin >> movieId) || movieId < 0) {
                cerr << "Invalid ID. Please enter a positive integer." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter Movie ID: ";
            }

            // Check if Movie ID already exists
            if (movieTable.search(movieId) != nullptr) {
                cerr << "Error: Movie ID already exists!" << endl;
                return;
            }

            // Input validation for Movie Title
            cin.ignore();
            while (true) {
                cout << "Enter Movie Title: ";
                getline(cin, title);
                trimString(title);

                if (!title.empty()) {
                    break;
                }
                cerr << "Error: Movie title cannot be empty. Please enter a valid title." << endl;
            }

            // Input validation for Movie Plot
            while (true) {
                cout << "Enter Movie Plot: ";
                getline(cin, plot);
                trimString(plot);

                if (!plot.empty()) {
                    break;
                }
                cerr << "Error: Movie plot cannot be empty. Please enter a valid plot." << endl;
            }

            // Input validation for Release Year
            cout << "Enter Release Year (1888-2025): ";
            while (!(cin >> releaseYear) || releaseYear < 1888 || releaseYear > 2025) {
                cerr << "Invalid Release Year. Please enter a valid year (1888-2025)." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter Release Year: ";
            }

            // Insert movie
            try {
                Movie movie(movieId, title, plot, releaseYear);
                movieTable.insert(movieId, movie);
                cout << "Movie added successfully!" << endl;

                Movie* moviePtr = movieTable.search(movieId);
                if (moviePtr) {
                    movieTree.insert(moviePtr);
                } else {
                    cerr << "Error: Movie insertion failed!" << endl;
                }
            } catch (const exception& e) {
                cerr << "Exception occurred: " << e.what() << endl;
            }
        } else if (choice == 3) {
            int searchOption;

            // Ask the user how they want to search
            while (true) {
                cout << "Choose search method:\n";
                cout << "1. Add actor to movie by ID\n";
                cout << "2. Add actor to movie by Name/Title\n";
                cout << "Enter choice (1 or 2, or 0 to return to menu): ";

                if (!(cin >> searchOption) || (searchOption != 1 && searchOption != 2 && searchOption != 0)) {
                    cerr << "Invalid choice. Please enter 1, 2, or 0 to return.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (searchOption == 0) {
                    cout << "Returning to main menu.\n";
                    return;  // Exit to main menu
                }
                break;
            }

            Actor* actor = nullptr;
            Movie* movie = nullptr;

            if (searchOption == 1) {
                // ✅ **Search by ID**
                int actorId, movieId;

                // Keep prompting until a valid actor ID is entered or user exits
                while (true) {
                    cout << "Enter Actor ID (Enter 0 to return to menu): ";
                    if (!(cin >> actorId) || actorId < 0) {
                        cerr << "Invalid Actor ID. Please enter a positive integer or 0 to return.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    if (actorId == 0) {
                        cout << "Returning to main menu.\n";
                        return;
                    }

                    actor = actorTable.search(actorId);
                    if (actor) break; // Actor found
                    cerr << "Error: Actor with ID " << actorId << " not found. Try again.\n";
                }

                // Keep prompting until a valid movie ID is entered or user exits
                while (true) {
                    cout << "Enter Movie ID (Enter 0 to return to menu): ";
                    if (!(cin >> movieId) || movieId < 0) {
                        cerr << "Invalid Movie ID. Please enter a positive integer or 0 to return.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    if (movieId == 0) {
                        cout << "Returning to main menu.\n";
                        return;
                    }

                    movie = movieTable.search(movieId);
                    if (movie) break; // Movie found
                    cerr << "Error: Movie with ID " << movieId << " not found. Try again.\n";
                }
            } 
            else if (searchOption == 2) {
                // ✅ **Search by Name & Title**
                string actorName, movieTitle;
                int actorMatchCount, movieMatchCount;

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Flush input buffer

                // Keep prompting until a valid actor name is entered or user exits
                while (true) {
                    cout << "Enter Actor Name (Enter 0 to return to menu): ";
                    getline(cin, actorName);
                    
                    trimString(actorName);

                    if (actorName == "0") {
                        cout << "Returning to main menu.\n";
                        return;
                    }

                    Actor** matchedActors = actorTable.searchByName(actorName, actorMatchCount);
                    if (matchedActors && actorMatchCount > 0) {
                        if (actorMatchCount == 1) {
                            actor = matchedActors[0]; // Only one match
                        } else {
                            // If multiple matches, let the user choose
                            cout << "\nMultiple actors found:\n";
                            for (int i = 0; i < actorMatchCount; ++i) {
                                cout << "(" << i + 1 << ") " << matchedActors[i]->getName() << " (ID: " << matchedActors[i]->getId() << ")" << endl;
                            }

                            int choice;
                            while (true) {
                                cout << "Select the correct actor (1 - " << actorMatchCount << ", or 0 to return): ";
                                if (!(cin >> choice) || choice < 0 || choice > actorMatchCount) {
                                    cerr << "Invalid selection. Please enter a number between 1 and " << actorMatchCount << ", or 0 to return.\n";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    continue;
                                }
                                if (choice == 0) {
                                    cout << "Returning to main menu.\n";
                                    delete[] matchedActors;
                                    return;
                                }
                                actor = matchedActors[choice - 1];
                                break;
                            }
                        }
                        delete[] matchedActors;
                        break;
                    } else {
                        cerr << "Error: Actor not found. Try again.\n";
                    }
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Flush input buffer

                // Keep prompting until a valid movie title is entered or user exits
                while (true) {
                    cout << "Enter Movie Title (Enter 0 to return to menu): ";
                    getline(cin, movieTitle);
                    
                    trimString(movieTitle);

                    if (movieTitle == "0") {
                        cout << "Returning to main menu.\n";
                        return;
                    }

                    Movie** matchedMovies = movieTable.searchByTitle(movieTitle, movieMatchCount);
                    if (matchedMovies && movieMatchCount > 0) {
                        if (movieMatchCount == 1) {
                            movie = matchedMovies[0]; // Only one match
                        } else {
                            // If multiple matches, let the user choose
                            cout << "\nMultiple movies found:\n";
                            for (int i = 0; i < movieMatchCount; ++i) {
                                cout << "(" << i + 1 << ") " << matchedMovies[i]->getTitle() << " (ID: " << matchedMovies[i]->getId() << ")" << endl;
                            }

                            int choice;
                            while (true) {
                                cout << "Select the correct movie (1 - " << movieMatchCount << ", or 0 to return): ";
                                if (!(cin >> choice) || choice < 0 || choice > movieMatchCount) {
                                    cerr << "Invalid selection. Please enter a number between 1 and " << movieMatchCount << ", or 0 to return.\n";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    continue;
                                }
                                if (choice == 0) {
                                    cout << "Returning to main menu.\n";
                                    delete[] matchedMovies;
                                    return;
                                }
                                movie = matchedMovies[choice - 1];
                                break;
                            }
                        }
                        delete[] matchedMovies;
                        break;
                    } else {
                        cerr << "Error: Movie not found. Try again.\n";
                    }
                }
            }

            // Add actor to movie (if not already linked)
            if (!actor->getMovies().contains(movie) && !movie->getActors().contains(actor)) {
                actor->addMovie(movie);
                movie->addActor(actor);
                cout << "Relationship added successfully!" << endl;
            } else {
                cerr << "Error: Actor is already associated with this movie." << endl;
            }
        } else if (choice == 4) {
            // Update actor details by searching for name
            string actorName;
            int matchCount;
            Actor** actors = nullptr;

            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Flush input buffer

            while (true) {
                cout << "Enter Actor Name to update (Enter 0 to return to menu): ";

                if (!getline(cin, actorName) || actorName.empty()) {
                    cerr << "Error: Actor name cannot be empty. Please enter a valid name or enter 0 to return.\n";
                    continue;
                }

                trimString(actorName);

                if (actorName == "0") {
                    cout << "Returning to main menu.\n";
                    return;  // **Returns to menu instead of exiting**
                }

                actors = actorTable.searchByName(actorName, matchCount);

                if (actors && matchCount > 0) {
                    break; // Exit search loop
                }

                cerr << "Error: Actor not found. Please enter a valid name or enter 0 to return.\n";
            }

            // Display matched actors
            cout << "\nActors found:\n";
            for (int i = 0; i < matchCount; ++i) {
                cout << "(" << i + 1 << ") " << actors[i]->getName() << " (ID: " << actors[i]->getId() << ")" << endl;
            }

            // User selects an actor
            int choice;
            while (true) {
                cout << "\nEnter the number of the actor you want to update (Enter 0 to return to menu): ";
                if (!(cin >> choice) || choice < 0 || choice > matchCount) {
                    cerr << "Invalid selection. Please enter a number between 1 and " << matchCount << " or enter 0 to return.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (choice == 0) {
                    cout << "Returning to main menu.\n";
                    delete[] actors;
                    return;  // **Returns to menu instead of exiting**
                }
                break;
            }

            // Retrieve selected actor
            Actor* selectedActor = actors[choice - 1];
            delete[] actors;  // Free allocated memory

            actorTree.remove(selectedActor);

            // Get new details
            string newName;
            int newBirthYear;

            // **Input validation for new name**
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ✅ Flush input buffer once
            cout << "Enter new name (leave empty to keep current, Enter 0 to skip): ";
            getline(cin, newName);
            trimString(newName);

            if (newName == "0") {
                cout << "Skipping name update.\n";
                newName = selectedActor->getName(); // Keep existing name
            } else if (newName.empty()) {
                newName = selectedActor->getName(); // Keep existing name
            }

            // **Input validation for birth year**
            while (true) {
                cout << "Enter new birth year (enter 0 to keep current, Enter -1 to return to menu): ";
                if (!(cin >> newBirthYear) || (newBirthYear != 0 && newBirthYear != -1 && (newBirthYear < 1800 || newBirthYear > 2025))) {
                    cerr << "Invalid Birth Year. Please enter a valid year (1800-2025), 0 to keep current, or -1 to return.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (newBirthYear == -1) {
                    cout << "Returning to main menu.\n";
                    return;  // **Returns to menu instead of exiting**
                }
                if (newBirthYear == 0) {
                    newBirthYear = selectedActor->getBirthYear(); // Keep existing birth year
                }
                break;
            }

            // **Update the actor's details**
            selectedActor->updateDetails(newName, newBirthYear);
            actorTree.insert(selectedActor);

            cout << "\nActor details updated successfully!\n";

            // **Display updated actor details**    
            cout << "\nUpdated actor details:\n";
            cout << "- ID: " << selectedActor->getId() << endl;
            cout << "- Name: " << selectedActor->getName() << endl;
            cout << "- BirthYear: " << selectedActor->getBirthYear() << endl;

        }
        else if (choice == 5) {
            
            // Update movie details by searching for title
            string movieTitle;
            int matchCount;
            Movie** movies = nullptr;

            // Input validation for movie title
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Flush input buffer
            while (true) {
                cout << "Enter Movie Title to update (Enter 0 to return to menu): ";
                if (!getline(cin, movieTitle) || movieTitle.empty()) {
                    cerr << "Error: Movie title cannot be empty. Please enter a valid title or enter 0 to return.\n";
                    continue;
                }

                trimString(movieTitle);

                if (movieTitle == "0") {
                    cout << "Returning to main menu.\n";
                    return;  // **Returns to menu instead of exiting the program**
                }

                movies = movieTable.searchByTitle(movieTitle, matchCount);

                if (movies && matchCount > 0) {
                    break;  // Exit search loop
                }

                cerr << "Error: Movie not found. Please enter a valid title or enter 0 to return.\n";
            }

            // Display matched movies
            cout << "\nMovies found:\n";
            for (int i = 0; i < matchCount; ++i) {
                cout << "(" << i + 1 << ") " << "- ID: " << movies[i]->getId()
                    << ", Title: " << movies[i]->getTitle()
                    << ", Year: " << movies[i]->getReleaseYear() << endl;
            }

            // User selects a movie
            int choice;
            while (true) {
                cout << "\nEnter the number of the movie you want to update (Enter 0 to return to menu): ";
                if (!(cin >> choice) || choice < 0 || choice > matchCount) {
                    cerr << "Invalid selection. Please enter a number between 1 and " << matchCount << " or enter 0 to return.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (choice == 0) {
                    cout << "Returning to main menu.\n";
                    delete[] movies;
                    return;  // **Returns to menu instead of exiting**
                }
                break;
            }

            // Retrieve selected movie
            Movie* selectedMovie = movies[choice - 1];
            delete[] movies;  // Free allocated memory

            movieTree.remove(selectedMovie);

            // Get new details
            string newTitle, newPlot;
            int newReleaseYear;

            // **Input validation for new title**
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ✅ Flush input buffer once
            cout << "Enter new title (leave empty to keep current, Enter 0 to skip): ";
            getline(cin, newTitle);
            trimString(newTitle);

            if (newTitle == "0") {
                cout << "Skipping title update.\n";
                newTitle = selectedMovie->getTitle(); // Keep existing title
            } else if (newTitle.empty()) {
                newTitle = selectedMovie->getTitle(); // Keep existing title
            }

            // **Input validation for new plot**
            cout << "Enter new plot (leave empty to keep current, Enter 0 to skip): ";
            getline(cin, newPlot);
            trimString(newPlot);

            if (newPlot == "0") {
                cout << "Skipping plot update.\n";
                newPlot = selectedMovie->getPlot(); // Keep existing plot
            } else if (newPlot.empty()) {
                newPlot = selectedMovie->getPlot(); // Keep existing plot
            }

            // **Input validation for release year**
            while (true) {
                cout << "Enter new release year (enter 0 to keep current, Enter -1 to return to menu): ";
                if (!(cin >> newReleaseYear) || (newReleaseYear != 0 && newReleaseYear != -1 && (newReleaseYear < 1888 || newReleaseYear > 2025))) {
                    cerr << "Invalid Release Year. Please enter a valid year (1888-2025), 0 to keep current, or -1 to return.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (newReleaseYear == -1) {
                    cout << "Returning to main menu.\n";
                    return;  // **Returns to menu instead of exiting**
                }
                if (newReleaseYear == 0) {
                    newReleaseYear = selectedMovie->getReleaseYear(); // Keep existing year
                }
                break;
            }

            // **Update movie details if necessary**
            selectedMovie->updateDetails(newTitle, newPlot, newReleaseYear);
            movieTree.insert(selectedMovie);

            cout << "\nMovie details updated successfully!\n";

            // **Display updated movie details**    
            cout << "\nUpdated movie details:\n";
            cout << "- ID: " << selectedMovie->getId() << endl;
            cout << "- Title: " << selectedMovie->getTitle() << endl;
            cout << "- Plot: " << selectedMovie->getPlot() << endl;
            cout << "- ReleaseYear: " << selectedMovie->getReleaseYear() << endl;

            
        } else if (choice == 6) {
            int minAge, maxAge;

            // Input validation for minimum age
            while (true) {
                cout << "Enter the minimum age (Enter 0 to return to menu): ";
                if (!(cin >> minAge) || minAge < 0) {
                    cerr << "Invalid age. Please enter a positive integer or 0 to return.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                if (minAge == 0) {
                    cout << "Returning to main menu.\n";
                    return;  // **Returns to menu instead of exiting**
                }
                break;
            }

            // Input validation for maximum age
            while (true) {
                cout << "Enter the maximum age (Enter 0 to return to menu): ";
                if (!(cin >> maxAge) || maxAge < 0) {
                    cerr << "Invalid age. Please enter a positive integer or 0 to return.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                if (maxAge == 0) {
                    cout << "Returning to main menu.\n";
                    return;  // **Returns to menu instead of exiting**
                }

                if (minAge > maxAge) {
                    cerr << "Invalid range. Ensure that minimum age <= maximum age.\n";
                    continue;
                }
                break;
            }

            // Display actors in the specified age range
            actorTree.displayActorsInAgeRange(minAge, maxAge);
        } else if (choice == 7) {
            int currentYear = 2025;
            int pastyear = currentYear - 3;

            cout << "\nMovies released in the past 3 years (sorted by year):\n";
            movieTree.displayMoviesInRange(pastyear, currentYear);
        } else if (choice == 8) {
            string actorName;
            int matchCount;
            Actor** actors = nullptr;

            // Flush input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            while (true) {
                cout << "Enter Actor name (Enter 0 to return to menu): ";

                if (!getline(cin, actorName) || actorName.empty()) {
                    cerr << "Error: Actor name cannot be empty. Please enter a valid name or enter 0 to return.\n";
                    continue;
                }

                trimString(actorName);

                if (actorName == "0") {
                    cout << "Returning to main menu.\n";
                    return;  // **Returns to menu instead of exiting**
                }

                actors = actorTable.searchByName(actorName, matchCount);

                if (actors && matchCount > 0) {
                    break;  // **Exit loop when valid actor is found**
                }

                cerr << "Error: Actor not found. Please enter a valid name or enter 0 to return.\n";
            }

            // Display matched actors
            cout << "\nActors found:\n";
            for (int i = 0; i < matchCount; ++i) {
                cout << "(" << i + 1 << ") " 
                    << "- ID: " << actors[i]->getId() 
                    << ", Name: " << actors[i]->getName() 
                    << ", BirthYear: " << actors[i]->getBirthYear() 
                    << ", Rating: " << actors[i]->getRating() << endl;
            }

            // User selects an actor
            int choice;
            while (true) {
                cout << "Enter the number of the actor you want (Enter 0 to return to menu): ";
                if (!(cin >> choice) || choice < 0 || choice > matchCount) {
                    cerr << "Invalid selection. Please enter a number between 1 and " << matchCount << " or enter 0 to return.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (choice == 0) {
                    cout << "Returning to main menu.\n";
                    delete[] actors;
                    return;  // **Returns to menu instead of exiting**
                }
                break;
            }

            // Retrieve selected actor
            Actor* selectedActor = actors[choice - 1];
            delete[] actors;  // Free allocated memory

            // Display actor details
            cout << "\nActor details:\n";
            cout << "- ID: " << selectedActor->getId() << endl;
            cout << "- Name: " << selectedActor->getName() << endl;
            cout << "- BirthYear: " << selectedActor->getBirthYear() << endl;
            cout << "- Rating: " << selectedActor->getRating() << endl;

            // Ask user how they want to display movies
            int sortChoice;
            while (true) {
                cout << "\nChoose how to display movies:\n";
                cout << "1. Display all movies of an actor sorted alphabetically\n";
                cout << "2. Display all movies of an actor sorted by rating\n";
                cout << "Enter choice (1 or 2, or press 0 to return): ";

                if (!(cin >> sortChoice)) {
                    cerr << "Invalid input. Please enter a number (1, 2, or 0 to return).\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (sortChoice == 0) {
                    cout << "Returning to main menu.\n";
                    return;
                } else if (sortChoice == 1 || sortChoice == 2) {
                    break; // Valid input
                } else {
                    cerr << "Invalid choice. Please enter 1 or 2, or press 0 to return.\n";
                }
            }

            // Get and display movies based on sorting choice
            int movieCount;
            Movie** sortedMovies = nullptr;

            if (sortChoice == 1) {
                sortedMovies = selectedActor->getSortedMovies(movieCount);  // Alphabetical order
                cout << "\nMovies starring " << selectedActor->getName() << " (Sorted Alphabetically):\n";
            } else if (sortChoice == 2) {
                sortedMovies = selectedActor->sortMoviesByRating(movieCount);  // By Rating
                cout << "\nMovies starring " << selectedActor->getName() << " (Sorted by Rating):\n";
            }

            // Display movies
            if (movieCount == 0 || sortedMovies == nullptr) {
                cout << "\nThis actor has not acted in any movies.\n";
            } else {
                for (int i = 0; i < movieCount; ++i) {
                    cout << "- ID: " << sortedMovies[i]->getId() 
                        << ", Title: " << sortedMovies[i]->getTitle() 
                        << ", Year: " << sortedMovies[i]->getReleaseYear();
                    if (sortChoice == 2) {
                        cout << ", Rating: " << sortedMovies[i]->getRating();  // Include rating if sorted by rating
                    }
                    cout << endl;
                }
            }

            delete[] sortedMovies; // Free allocated memory
            sortedMovies = nullptr;
        } else if (choice == 9) {
            string movieName;
            int matchCount;
            Movie** movies = nullptr;

            // Flush input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            while (true) {
                cout << "Enter Movie title (Enter 0 to return to menu): ";

                if (!getline(cin, movieName) || movieName.empty()) {
                    cerr << "Error: Movie title cannot be empty. Please enter a valid title or enter 0 to return.\n";
                    continue;
                }

                trimString(movieName);

                if (movieName == "0") {
                    cout << "Returning to main menu.\n";
                    return;  // **Returns to menu instead of exiting**
                }

                movies = movieTable.searchByTitle(movieName, matchCount);

                if (movies && matchCount > 0) {
                    break;  // **Exit loop when valid movie is found**
                }

                cerr << "Error: Movie not found. Please enter a valid title or enter 0 to return.\n";
            }

            // Display matched movies
            cout << "\nMovies found:\n";
            for (int i = 0; i < matchCount; ++i) {
                cout << "(" << i + 1 << ") " << "- ID: " << movies[i]->getId()
                    << ", Title: " << movies[i]->getTitle()
                    << ", Year: " << movies[i]->getReleaseYear()
                    << ", Rating: " << movies[i]->getRating() << endl;
            }

            // User selects a movie
            int choice;
            while (true) {
                cout << "Enter the number of the movie you want (Enter 0 to return to menu): ";
                if (!(cin >> choice) || choice < 0 || choice > matchCount) {
                    cerr << "Invalid selection. Please enter a number between 1 and " << matchCount << " or enter 0 to return.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (choice == 0) {
                    cout << "Returning to main menu.\n";
                    delete[] movies;
                    return;  // **Returns to menu instead of exiting**
                }
                break;
            }

            // Retrieve selected movie
            Movie* selectedMovie = movies[choice - 1];
            delete[] movies;  // Free allocated memory

            // Display movie details
            cout << "\nMovie details:\n";
            cout << "- ID: " << selectedMovie->getId() << endl;
            cout << "- Title: " << selectedMovie->getTitle() << endl;
            cout << "- Year: " << selectedMovie->getReleaseYear() << endl;
            cout << "- Plot: " << selectedMovie->getPlot() << endl;
            cout << "- Rating: " << selectedMovie->getRating() << endl;

            // Ask user how they want to display actors
            int sortChoice;
            while (true) {
                cout << "\nChoose how to display actors in this movie:\n";
                cout << "1. Display actors sorted alphabetically\n";
                cout << "2. Display actors sorted by rating\n";
                cout << "Enter choice (1 or 2, or press 0 to return): ";

                if (!(cin >> sortChoice)) {
                    cerr << "Invalid input. Please enter a number (1, 2, or 0 to return).\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (sortChoice == 0) {
                    cout << "Returning to main menu.\n";
                    return;
                } else if (sortChoice == 1 || sortChoice == 2) {
                    break; // Valid input
                } else {
                    cerr << "Invalid choice. Please enter 1 or 2, or press 0 to return.\n";
                }
            }

            // Get and display actors based on sorting choice
            int actorCount;
            Actor** sortedActors = nullptr;

            if (sortChoice == 1) {
                sortedActors = selectedMovie->getSortedActors(actorCount);  // Alphabetical order
                cout << "\nActors in \"" << selectedMovie->getTitle() << "\" (Sorted Alphabetically):\n";
            } else if (sortChoice == 2) {
                sortedActors = selectedMovie->sortActorsByRating(actorCount);  // By Rating
                cout << "\nActors in \"" << selectedMovie->getTitle() << "\" (Sorted by Rating):\n";
            }

            // Display actors
            if (actorCount == 0 || sortedActors == nullptr) {
                cout << "\nThis movie has no actors recorded.\n";
            } else {
                for (int i = 0; i < actorCount; ++i) {
                    cout << "(" << i + 1 << ") " 
                        << "- ID: " << sortedActors[i]->getId()
                        << ", Name: " << sortedActors[i]->getName();
                    
                    if (sortChoice == 2) {
                        cout << ", BirthYear: " << sortedActors[i]->getBirthYear()
                            << ", Rating: " << sortedActors[i]->getRating();  // Include rating if sorted by rating
                    }
                    cout << endl;
                }
            }

            delete[] sortedActors; // Free allocated memory
            sortedActors = nullptr;
        } else if (choice == 10) {
            string actorName;
            int matchCount;
            Actor** actors = nullptr;

            // Flush input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            while (true) {
                cout << "Enter Actor Name (Enter 0 to return to menu): ";
                
                if (!getline(cin, actorName) || actorName.empty()) {
                    cerr << "Error: Actor name cannot be empty. Please enter a valid name or enter 0 to return.\n";
                    continue;
                }

                trimString(actorName);

                if (actorName == "0") {
                    cout << "Returning to main menu.\n";
                    return;  // **Returns to menu instead of exiting**
                }

                actors = actorTable.searchByName(actorName, matchCount);

                if (actors && matchCount > 0) {
                    break;  // **Exit loop when valid actor is found**
                }

                cerr << "Error: Actor not found. Please enter a valid name or enter 0 to return.\n";
            }

            // Display matched actors
            cout << "\nActors found:\n";
            for (int i = 0; i < matchCount; ++i) {
                cout << "(" << i + 1 << ") " << "- ID: " << actors[i]->getId() 
                    << ", Name: " << actors[i]->getName() 
                    << ", BirthYear: " << actors[i]->getBirthYear() << endl;
            }

            // User selects an actor
            int choice;
            while (true) {
                cout << "Enter the number of the actor you want (Enter 0 to return to menu): ";
                if (!(cin >> choice) || choice < 0 || choice > matchCount) {
                    cerr << "Invalid selection. Please enter a number between 1 and " << matchCount << " or enter 0 to return.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (choice == 0) {
                    cout << "Returning to main menu.\n";
                    delete[] actors;
                    return;  // **Returns to menu instead of exiting**
                }
                break;
            }

            // Retrieve selected actor
            Actor* selectedActor = actors[choice - 1];
            delete[] actors;  // Free allocated memory

            // Display known actors
            actorGraph.displayConnections(selectedActor);
        } else if (choice == 11) {
           string actorName;
            int matchCount;
            Actor** actors = nullptr;

            // Flush input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            while (true) {
                cout << "Enter Actor Name (Enter 0 to return to menu): ";
                
                if (!getline(cin, actorName) || actorName.empty()) {
                    cerr << "Error: Actor name cannot be empty. Please enter a valid name or enter 0 to return.\n";
                    continue;
                }

                trimString(actorName);

                if (actorName == "0") {
                    cout << "Returning to main menu.\n";
                    return;  // **Returns to menu instead of exiting**
                }

                actors = actorTable.searchByName(actorName, matchCount);

                if (actors && matchCount > 0) {
                    break;  // **Exit loop when valid actor is found**
                }

                cerr << "Error: Actor not found. Please enter a valid name or enter 0 to return.\n";
            }

            // Display matched actors
            cout << "\nActors found:\n";
            for (int i = 0; i < matchCount; ++i) {
                cout << "(" << i + 1 << ") " << "- ID: " << actors[i]->getId() 
                    << ", Name: " << actors[i]->getName() 
                    << ", BirthYear: " << actors[i]->getBirthYear() << endl;
            }

            // User selects an actor
            int choice;
            while (true) {
                cout << "Enter the number of the actor you want to update (Enter 0 to return to menu): ";
                if (!(cin >> choice) || choice < 0 || choice > matchCount) {
                    cerr << "Invalid selection. Please enter a number between 1 and " << matchCount << " or enter 0 to return.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (choice == 0) {
                    cout << "Returning to main menu.\n";
                    delete[] actors;
                    return;  // **Returns to menu instead of exiting**
                }
                break;
            }

            // Retrieve selected actor
            Actor* selectedActor = actors[choice - 1];
            delete[] actors;  // Free allocated memory

            // Ask for new rating
            float newRating;
            while (true) {
                cout << "Enter new rating (0.0 to 10.0, Enter -1 to return to menu): ";
                if (!(cin >> newRating) || newRating < -1.0 || newRating > 10.0) {
                    cerr << "Invalid rating. Please enter a value between 0.0 and 10.0 or enter -1 to return.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (newRating == -1.0) {
                    cout << "Returning to main menu.\n";
                    return;
                }
                break;
            }

            // Set the new rating
            selectedActor->setRating(newRating);

            cout << "\nRating updated successfully for " << selectedActor->getName() << "!" << endl;
        }  else if (choice == 12) {
            // Update movie rating using movie title search
            string movieTitle;
            int matchCount;
            Movie** movies = nullptr;

            // Flush input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            while (true) {
                cout << "Enter Movie Title (Enter 0 to return to menu): ";
                
                if (!getline(cin, movieTitle) || movieTitle.empty()) {
                    cerr << "Error: Movie title cannot be empty. Please enter a valid title or enter 0 to return.\n";
                    continue;
                }

                trimString(movieTitle);

                if (movieTitle == "0") {
                    cout << "Returning to main menu.\n";
                    return;  // **Returns to menu instead of exiting**
                }

                movies = movieTable.searchByTitle(movieTitle, matchCount);

                if (movies && matchCount > 0) {
                    break;  // **Exit loop when valid movie is found**
                }

                cerr << "Error: Movie not found. Please enter a valid title or enter 0 to return.\n";
            }

            // Display matched movies
            cout << "\nMovies found:\n";
            for (int i = 0; i < matchCount; ++i) {
                cout << "(" << i + 1 << ") " << "- ID: " << movies[i]->getId() 
                    << ", Title: " << movies[i]->getTitle() 
                    << ", Year: " << movies[i]->getReleaseYear() << endl;
            }

            // User selects a movie
            int choice;
            while (true) {
                cout << "Enter the number of the movie you want to update (Enter 0 to return to menu): ";
                if (!(cin >> choice) || choice < 0 || choice > matchCount) {
                    cerr << "Invalid selection. Please enter a number between 1 and " << matchCount << " or enter 0 to return.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (choice == 0) {
                    cout << "Returning to main menu.\n";
                    delete[] movies;
                    return;  // **Returns to menu instead of exiting**
                }
                break;
            }

            // Retrieve selected movie
            Movie* selectedMovie = movies[choice - 1];
            delete[] movies;  // Free allocated memory

            // Ask for new rating
            float newRating;
            while (true) {
                cout << "Enter new rating (0.0 to 10.0, Enter -1 to return to menu): ";
                if (!(cin >> newRating) || newRating < -1.0 || newRating > 10.0) {
                    cerr << "Invalid rating. Please enter a value between 0.0 and 10.0 or enter -1 to return.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (newRating == -1.0) {
                    cout << "Returning to main menu.\n";
                    return;
                }
                break;
            }

            // Set the new rating
            selectedMovie->setRating(newRating);

            cout << "\nRating updated successfully for \"" << selectedMovie->getTitle() << "\"!" << endl;
        
        
        } else if (choice == 13) {
            float minRating;
            // Input validation for minimum rating
            while (true) {
                cout << "Enter minimum movie rating (0.0 to 10.0, Enter -1 to return to menu): ";

                if (!(cin >> minRating)) {
                    cerr << "Invalid input. Please enter a number between 0.0 and 10.0 or enter -1 to return.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (minRating == -1) {
                    cout << "Returning to main menu.\n";
                    return;  // **Returns to menu instead of exiting**
                }

                if (minRating < 0.0 || minRating > 10.0) {
                    cerr << "Invalid rating. Please enter a number between 0.0 and 10.0.\n";
                    continue;
                }

                break;  // Valid rating input, exit loop
            }

            // Allocate memory for movie storage
            recentMovies = new Movie*[movieTable.getSize()];
            movieCount = 0;

            // Collect all movies into the array
            movieTable.display(collectAllMovies);

            if (movieCount == 0) {
                cout << "\nNo movies found in the database.\n";
                delete[] recentMovies;
                return;  // **Return to menu instead of exiting**
            }

            // Filter and recommend movies based on the rating
            Movie tempMovie;  // Temporary object to call the recommendation method
            tempMovie.recommendMoviesByRating(recentMovies, movieCount, minRating);

            // Free allocated memory
            delete[] recentMovies;
            recentMovies = nullptr;         
            
        
        } else if (choice == 14) {
            float minRating;
            // Input validation for minimum actor rating
            while (true) {
                cout << "Enter minimum actor rating (0.0 to 10.0, Enter -1 to return to menu): ";

                if (!(cin >> minRating)) {
                    cerr << "Invalid input. Please enter a number between 0.0 and 10.0 or enter -1 to return.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (minRating == -1) {
                    cout << "Returning to main menu.\n";
                    return;  // **Returns to menu instead of exiting**
                }

                if (minRating < 0.0 || minRating > 10.0) {
                    cerr << "Invalid rating. Please enter a number between 0.0 and 10.0.\n";
                    continue;
                }

                break;  // Valid rating input, exit loop
            }

            // Allocate memory for actor storage
            allActors = new Actor*[actorTable.getSize()];
            totalActors = 0;

            // Collect all actors into the array
            actorTable.display(collectActors);

            if (totalActors == 0) {
                cout << "\nNo actors found in the database.\n";
                delete[] allActors;
                return;  // **Return to menu instead of exiting**
            }

            // Filter and recommend actors based on the rating
            Actor tempActor;  // Temporary object to call the method
            tempActor.recommendActorsByRating(allActors, totalActors, minRating);

            // Free allocated memory
            delete[] allActors;
            allActors = nullptr;
           
        } else if (choice == 0) {
            // Exit
            cout << "Exiting application. Goodbye!" << endl;
            break;
        } else {
            cout << "Wrong Input. Please try again." << endl;
        }
    }
}

// Function to compute the key for actor sorting
int computeActorKey(Actor* actor) {
    return ((2025 - actor->getBirthYear()) * 10000) + (actor->getId() % 10000);
}

// Function to compute the key for movie sorting
int computeMovieKey(Movie* movie) {
    return (movie->getReleaseYear() * 10000) + (movie->getId() % 10000);
}
// Main function
int main() {
    Dictionary<Actor> actorTable;
    Dictionary<Movie> movieTable;
    
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