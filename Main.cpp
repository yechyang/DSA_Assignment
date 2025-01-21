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
        getline(ss, name, ',');
        getline(ss, birthYear);

        int year = safeStoi(birthYear);
        if (id.empty() || name.empty() || year == -1) {
            cerr << "Skipping invalid actor record: " << line << endl;
            continue;
        }
        int intId = safeStoi(id);
        if (intId == -1) {
            cerr << "Skipping invalid actor record: " << line << endl;
            continue;
        }
        
        Actor actor(intId, name, year);
        actorTable.insert(intId, actor);
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
        cout << "Enter your choice: ";
        cin >> choice;

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
            // Display all actors in a movie
            int movieId;
            cout << "Enter Movie ID: ";
            cin >> movieId;

            Movie* movie = movieTable.search(movieId);
            if (movie) {
                movie->display();
            } else {
                cerr << "Error: Movie not found." << endl;
            }
        } else if (choice == 5) {
            // Display all movies of an actor
            int actorId;
            cout << "Enter Actor ID: ";
            cin >> actorId;

            Actor* actor = actorTable.search(actorId);
            if (actor) {
                actor->display();
            } else {
                cerr << "Error: Actor not found." << endl;
            }
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
        } else {
            cerr << "Invalid choice. Please try again." << endl;
        }
    }
}

// Main function
int main() {
    Dictionary<Actor> actorTable(100); // Actor hash table
    Dictionary<Movie> movieTable(100); // Movie hash table

    // Load data from CSV files
    loadActors("actors.csv", actorTable);
    loadMovies("movies.csv", movieTable);
    loadCast("cast.csv", actorTable, movieTable);

    // Run the application
    runApplication(actorTable, movieTable);

    // Save data back to CSV files
    saveActorsToCSV("actors.csv", actorTable);
    saveMoviesToCSV("movies.csv", movieTable);
    saveCastToCSV("cast.csv", actorTable);

    return 0;
}