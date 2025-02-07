// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include "Dictionary.h"
// #include "Actor.h"
// #include "Movie.h"

// using namespace std;

// // Display functions for Dictionary
// void displayActor(void* value) {
//     Actor* actor = static_cast<Actor*>(value);
//     actor->display();
// }

// void displayMovie(void* value) {
//     Movie* movie = static_cast<Movie*>(value);
//     movie->display();
// }

// // Function to validate and convert string to int
// int safeStoi(const string& str) {
//     try {
//         return stoi(str);
//     } catch (...) {
//         return -1; // Invalid value
//     }
// }

// // Function to skip headers in CSV
// void skipHeader(ifstream& file) {
//     string header;
//     getline(file, header);
// }

// // Function to load actors from a CSV file
// void loadActors(const string& filename, Dictionary& actorTable) {
//     ifstream file(filename);
//     if (!file.is_open()) {
//         cerr << "Error opening " << filename << endl;
//         return;
//     }

//     skipHeader(file); // Skip the header row

//     string line, id, name, birthYear;
//     while (getline(file, line)) {
//         stringstream ss(line);
//         getline(ss, id, ',');
//         getline(ss, name, ',');
//         getline(ss, birthYear);

//         int year = safeStoi(birthYear);
//         if (id.empty() || name.empty() || year == -1) {
//             cerr << "Skipping invalid actor record: " << line << endl;
//             continue;
//         }

//         Actor* actor = new Actor(id, name, year);
//         actorTable.insert(id, actor);
//     }
//     file.close();
//     cout << "Actors loaded from " << filename << endl;
// }

// // Function to load movies from a CSV file
// void loadMovies(const string& filename, Dictionary& movieTable) {
//     ifstream file(filename);
//     if (!file.is_open()) {
//         cerr << "Error opening " << filename << endl;
//         return;
//     }

//     skipHeader(file); // Skip the header row

//     string line, id, title, plot, releaseYear;
//     while (getline(file, line)) {
//         stringstream ss(line);
//         getline(ss, id, ',');
//         getline(ss, title, ',');
//         getline(ss, plot, ',');
//         getline(ss, releaseYear);

//         int year = safeStoi(releaseYear);
//         if (id.empty() || title.empty() || year == -1) {
//             cerr << "Skipping invalid movie record: " << line << endl;
//             continue;
//         }

//         Movie* movie = new Movie(id, title, plot, year);
//         movieTable.insert(id, movie);
//     }
//     file.close();
//     cout << "Movies loaded from " << filename << endl;
// }

// // Function to load cast relationships from a CSV file
// void loadCast(const string& filename, Dictionary& actorTable, Dictionary& movieTable) {
//     ifstream file(filename);
//     if (!file.is_open()) {
//         cerr << "Error opening " << filename << endl;
//         return;
//     }

//     skipHeader(file); // Skip the header row

//     string line, actorId, movieId;
//     while (getline(file, line)) {
//         stringstream ss(line);
//         getline(ss, actorId, ',');
//         getline(ss, movieId);

//         Actor* actor = static_cast<Actor*>(actorTable.search(actorId));
//         Movie* movie = static_cast<Movie*>(movieTable.search(movieId));

//         if (actor && movie) {
//             actor->addMovie(movie);
//             movie->addActor(actor);
//         } else {
//             cerr << "Skipping invalid cast relationship: " << line << endl;
//         }
//     }
//     file.close();
//     cout << "Cast relationships loaded from " << filename << endl;
// }

// // Menu-driven application
// void runApplication(Dictionary& actorTable, Dictionary& movieTable) {
//     int choice;

//     while (true) {
//         cout << "\nMovie Application Menu\n";
//         cout << "1. Add new actor\n";
//         cout << "2. Add new movie\n";
//         cout << "3. Add an actor to a movie\n";
//         cout << "4. Display all actors in a movie\n";
//         cout << "5. Display all movies of an actor\n";
//         cout << "6. Exit\n";
//         cout << "Enter your choice: ";
//         cin >> choice;

//         if (choice == 1) {
//             // Add new actor
//             string id, name;
//             int birthYear;
//             cout << "Enter Actor ID: ";
//             cin >> id;
//             cout << "Enter Actor Name: ";
//             cin.ignore();
//             getline(cin, name);
//             cout << "Enter Birth Year: ";
//             cin >> birthYear;
//             Actor* actor = new Actor(id, name, birthYear);
//             actorTable.insert(id, actor);
//             cout << "Actor added successfully!" << endl;
//         } else if (choice == 2) {
//             // Add new movie
//             string id, title, plot;
//             int releaseYear;
//             cout << "Enter Movie ID: ";
//             cin >> id;
//             cout << "Enter Movie Title: ";
//             cin.ignore();
//             getline(cin, title);
//             cout << "Enter Movie Plot: ";
//             getline(cin, plot);
//             cout << "Enter Release Year: ";
//             cin >> releaseYear;
//             Movie* movie = new Movie(id, title, plot, releaseYear);
//             movieTable.insert(id, movie);
//             cout << "Movie added successfully!" << endl;
//         } else if (choice == 3) {
//             // Add an actor to a movie
//             string actorId, movieId;
//             cout << "Enter Actor ID: ";
//             cin >> actorId;
//             cout << "Enter Movie ID: ";
//             cin >> movieId;

//             Actor* actor = static_cast<Actor*>(actorTable.search(actorId));
//             Movie* movie = static_cast<Movie*>(movieTable.search(movieId));

//             if (actor && movie) {
//                 actor->addMovie(movie);
//                 movie->addActor(actor);
//                 cout << "Relationship added successfully!" << endl;
//             } else {
//                 cerr << "Error: Actor or Movie not found." << endl;
//             }
//         } else if (choice == 4) {
//             // Display all actors in a movie
//             string movieId;
//             cout << "Enter Movie ID: ";
//             cin >> movieId;
//             cout << endl;

//             Movie* movie = static_cast<Movie*>(movieTable.search(movieId));
//             if (movie) {
//                 movie->display();
//             } else {
//                 cerr << "Error: Movie not found." << endl;
//             }
//         } else if (choice == 5) {
//             // Display all movies of an actor
//             string actorId;
//             cout << "Enter Actor ID: ";
//             cin >> actorId;
            

//             Actor* actor = static_cast<Actor*>(actorTable.search(actorId));
//             if (actor) {
//                 actor->display();
//             } else {
//                 cerr << "Error: Actor not found." << endl;
//             }
//         } else if (choice == 6) {
//             // Exit
//             cout << "Exiting application. Goodbye!" << endl;
//             break;
//         } else {
//             cerr << "Invalid choice. Please try again." << endl;
//         }
//     }
// }

// // Main function
// int main() {
//     Dictionary actorTable(100); // Actor hash table
//     Dictionary movieTable(100); // Movie hash table

//     // Load data from CSV files
//     loadActors("actors.csv", actorTable);
//     loadMovies("movies.csv", movieTable);
//     loadCast("cast.csv", actorTable, movieTable);

//     // Run the application
//     runApplication(actorTable, movieTable);

//     return 0;
// }

#include <iostream>
#include <fstream>
#include <sstream>
#include "Dictionary.h"
#include "Actor.h"
#include "Movie.h"

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
void loadActors(const string& filename, Dictionary<Actor>& actorTable) {
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
            cerr << "Skipping invalid actor record: " << line << endl;
            continue;
        }

        if (name.front() == '"' && name.back() == '"') {
            name = name.substr(1, name.length() - 2);
        }

        cout << "Loaded Actor: [" << name << "]" << endl;

        actorTable.insert(intId, Actor(intId, name, year));
    }

    file.close();
    cout << "Actors loaded from " << filename << endl;
}

// Function to load movies from a CSV file
void loadMovies(const string& filename, Dictionary<Movie>& movieTable) {
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
            cerr << "Skipping invalid movie record: " << line << endl;
            continue;
        }
        int intId = safeStoi(id);
        if (intId == -1) {
            cerr << "Skipping invalid actor record: " << line << endl;
            continue;
        }

        Movie movie(intId, title, plot, year);
        movieTable.insert(intId, movie);
    }
    file.close();
    cout << "Movies loaded from " << filename << endl;
}

// Function to load cast relationships from a CSV file
void loadCast(const string& filename, Dictionary<Actor>& actorTable, Dictionary<Movie>& movieTable) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening " << filename << endl;
        return;
    }

    skipHeader(file); // Skip the header row

    string line, actorId, movieId;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, actorId, ',');
        getline(ss, movieId);
        int intActorId = safeStoi(actorId);
        if (intActorId == -1) {
            cerr << "Skipping invalid actor record: " << line << endl;
            continue;
        }
        int intMovieId = safeStoi(movieId);
        if (intMovieId == -1) {
            cerr << "Skipping invalid actor record: " << line << endl;
            continue;
        }

        Actor* actor = actorTable.search(intActorId);
        Movie* movie = movieTable.search(intMovieId);

        if (actor && movie) {
            actor->addMovie(movie);
            movie->addActor(actor);
        } else {
            cerr << "Skipping invalid cast relationship: " << line << endl;
        }
    }
    file.close();
    cout << "Cast relationships loaded from " << filename << endl;
}

// Helper function to write actor data to file
void writeActorToFile(const Actor& actor, ofstream& file) {
    file << actor.getId() << "," << actor.getName() << "," << actor.getBirthYear() << "\n";
}

// Wrapper function for Dictionary's display
void writeActor(const Actor& actor) {
    extern ofstream* globalFile; // Declare a global file pointer
    writeActorToFile(actor, *globalFile);
}

// Helper function to write movie data to file
void writeMovieToFile(const Movie& movie, ofstream& file) {
    file << movie.getId() << "," << movie.getTitle() << "," << movie.getPlot() << "," << movie.getReleaseYear() << "\n";
}

// Wrapper function for Dictionary's display
void writeMovie(const Movie& movie) {
    extern ofstream* globalFile; // Declare a global file pointer
    writeMovieToFile(movie, *globalFile);
}

// Helper function to write actor-movie relationships to file
ofstream* castFile;
void writeCastToFile(const Actor& actor, ofstream& file) {
    for (const MovieNode* movieNode = actor.getMovies(); movieNode != nullptr; movieNode = movieNode->next) {
        file << actor.getId() << "," << movieNode->movie->getId() << "\n";
    }
}

// Wrapper function for Dictionary's display
void writeCast(const Actor& actor) {
    extern ofstream* globalFile; // Declare a global file pointer
    writeCastToFile(actor, *globalFile);
}

ofstream* globalFile; // Global file pointer
// Function to save actors to CSV
void saveActorsToCSV(const string& filename, const Dictionary<Actor>& actorTable) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening " << filename << " for writing." << endl;
        return;
    }

    // Write CSV header
    file << "id,name,birthYear\n";

    // Set the global file pointer
    globalFile = &file;

    // Write actor data
    actorTable.display(writeActor);

    // Reset the global file pointer
    globalFile = nullptr;

    file.close();
    cout << "Actors saved to " << filename << endl;
}
// Function to save movies to CSV
void saveMoviesToCSV(const string& filename, const Dictionary<Movie>& movieTable) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening " << filename << " for writing." << endl;
        return;
    }

    // Write CSV header
    file << "id,title,plot,releaseYear\n";

    // Set the global file pointer
    globalFile = &file;

    // Write movie data
    movieTable.display(writeMovie);

    // Reset the global file pointer
    globalFile = nullptr;

    file.close();
    cout << "Movies saved to " << filename << endl;
}

// Function to save cast relationships to CSV
void saveCastToCSV(const string& filename, const Dictionary<Actor>& actorTable) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening " << filename << " for writing." << endl;
        return;
    }

    // Write CSV header
    file << "actorId,movieId\n";

    // Set the global file pointer
    globalFile = &file;

    // Write actor-movie relationships
    actorTable.display(writeCast);

    // Reset the global file pointer
    globalFile = nullptr;

    file.close();
    cout << "Cast relationships saved to " << filename << endl;
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
void runApplication(Dictionary<Actor>& actorTable, Dictionary<Movie>& movieTable) {
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
                cout << i + 1 << ". " << movies[i]->getTitle() << " (Year: " << movies[i]->getReleaseYear() << ")" << endl;
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ✅ Clears leftover input
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
                cout << i + 1 << ". " << actors[i]->getName() << " (ID: " << actors[i]->getId() << ")" << endl;
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
            // Update actor details
            int actorId;
            cout << "Enter Actor ID to update: ";
            cin >> actorId;

            Actor* actor = actorTable.search(actorId);
            if (actor) {
                string newName;
                int newBirthYear;
                cout << "Enter new name (leave empty to keep current): ";
                cin.ignore();
                getline(cin, newName);
                cout << "Enter new birth year (enter 0 to keep current): ";
                cin >> newBirthYear;

                actor->updateDetails(newName, newBirthYear);
            } else {
                cerr << "Error: Actor not found." << endl;
            }
        } else if (choice == 8) {
            // Update movie details
            int movieId;
            cout << "Enter Movie ID to update: ";
            cin >> movieId;

            Movie* movie = movieTable.search(movieId);
            if (movie) {
                string newTitle, newPlot;
                int newReleaseYear;
                cout << "Enter new title (leave empty to keep current): ";
                cin.ignore();
                getline(cin, newTitle);
                cout << "Enter new plot (leave empty to keep current): ";
                getline(cin, newPlot);
                cout << "Enter new release year (enter 0 to keep current): ";
                cin >> newReleaseYear;

                movie->updateDetails(newTitle, newPlot, newReleaseYear);
            } else {
                cerr << "Error: Movie not found." << endl;
            }
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

            // Collect all actors into a dynamic array
            allActors = new Actor*[actorTable.getSize()];
            totalActors = 0; // Reset total actor count

            // Use the standalone function
            actorTable.display(collectActors);
            // Filter and sort actors by age range
            int filteredCount = 0;
            Actor** filteredActors = Actor::filterAndSortByAge(allActors, totalActors, minAge, maxAge, filteredCount);

            // Display the filtered and sorted actors
            if (filteredCount > 0) {
                cout << "Actors with age between " << minAge << " and " << maxAge << " (sorted by age):" << endl;
                for (int i = 0; i < filteredCount; ++i) {
                    int age = 2025 - filteredActors[i]->getBirthYear();
                    cout << "Actor ID: " << filteredActors[i]->getId()
                        << ", Name: " << filteredActors[i]->getName()
                        << ", Age: " << age << endl;
                }
            } else {
                cout << "No actors found in the specified age range." << endl;
            }

            // Free allocated memory
            delete[] allActors;
            delete[] filteredActors;
        } else if (choice == 10) {
            // Allocate memory for recent movies
            recentMovies = new Movie*[movieTable.getSize()];
            movieCount = 0;

            // Collect movies released in the past 3 years
            movieTable.display(collectRecentMovies);

            if (movieCount > 0) {
                // Sort movies using AVL tree
                Movie::sortMoviesByReleaseYear(recentMovies, movieCount);
            } else {
                cout << "No movies found from the past 3 years." << endl;
            }

            // Free allocated memory
            delete[] recentMovies;
            recentMovies = nullptr;
        } else if (choice == 11) {
            int actorId;
            cout << "Enter Actor ID: ";
            cin >> actorId;

            Actor* actor = actorTable.search(actorId);
            if (actor) {
                actor->displayKnownActors();
            } else {
                cerr << "Actor not found." << endl;
            }
        }  else if (choice == 12) {
                // Update actor rating
                int actorId;
                cout << "\nEnter Actor ID: ";
                cin >> actorId;

                Actor* actor = actorTable.search(actorId);
                if (actor) {
                    float newRating;
                    cout << "Enter new rating (0.0 to 10.0): ";
                    cin >> newRating;
                    actor->setRating(newRating);
                    cout << "\nRating updated successfully!" << endl;
                } else {
                    cerr << "Actor not found." << endl;
                }
        } else if (choice == 13) {
            // Update movie rating
            int movieId;
            cout << "\nEnter Movie ID: ";
            cin >> movieId;

            Movie* movie = movieTable.search(movieId);
            if (movie) {
                float newRating;
                cout << "Enter new rating (0.0 to 10.0): ";
                cin >> newRating;
                movie->setRating(newRating);
                cout << "\nRating updated successfully!" << endl;
            } else {
                cerr << "Movie not found." << endl;
            }
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

// Main function
int main() {
    Dictionary<Actor> actorTable(1000); // Actor hash table
    Dictionary<Movie> movieTable(100); // Movie hash table

    // Load data from CSV files
    loadActors("actors.csv", actorTable);
    loadMovies("movies.csv", movieTable);
    loadCast("cast.csv", actorTable, movieTable);

    // Run the application
    runApplication(actorTable, movieTable);

    // // Save data back to CSV files
    // saveActorsToCSV("actors.csv", actorTable);
    // saveMoviesToCSV("movies.csv", movieTable);
    // saveCastToCSV("cast.csv", actorTable);

    return 0;
}