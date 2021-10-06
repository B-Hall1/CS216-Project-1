/*
 * File: imdb.h
 * Course: CS216-00x
 * Project: Project 1
 * Purpose: Declaration of IMDB class
 *          This class represents a movie-actor database
 *          It contains two private data memebers:
 *             movies_db: represents a mapping from a movie (title) to a set of actors (names) in this movie
 *             actors_db: represents a mapping from a actor (name) to a set of movies (titles) in which this actor is
 */
/* Blair Hall
CS 216-001
*/
#include "imdb.h"
#include <regex>
#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

        IMDB::IMDB()         // default constructor
{

 }       // insert a pair <movieTitle, the set of actor names in this movie>
        // this function is optional to this project
 void IMDB::insert_a_movie(string movieTitle, set<string> actorNames)      
{	if (!isExistingMovie(movieTitle))
		movies_db[movieTitle] = actorNames;
	{ movies_db[movieTitle].insert(actorNames.begin(), actorNames.end());       
	}
for (auto it = actorNames.begin(); it != actorNames.end(); it++)
{
	if (actors_db.find(*it) == actors_db.end())
	{
		set<string> movies;
		movies.insert(movieTitle);
		actors_db[*it] = movies;
	}
	else
	{
		actors_db[*it].insert(movieTitle);
	}
    }
        // insert a pair<actorName, the set of movieTitle of this actor>
}
        void IMDB::insert_an_actor(string actorName, set<string> movieTitles)
{	if (!isExistingActor(actorName))
		actors_db[actorName] = movieTitles;
	{ 
	    actors_db[actorName].insert(movieTitles.begin(), movieTitles.end());
	}
for (auto it = movieTitles.begin(); it != movieTitles.end(); it++)
	if (movies_db.find(*it) == movies_db.end())
	{
		set<string> actors;
		actors.insert(actorName);
		movies_db[*it] = actors;
	}
	else
	{
		movies_db[*it].insert(actorName);
	}
}


 // return the matched movie title from the map
        
        // use passing in parameter, movieTitle, as the pattern to match 
        // one existing movie in the map
        // otherwise return empty string
        string IMDB::matchExistingMovie(string movieTitle) const
{
	string matchedMovie;
	bool found = false;
	//generate the regular expression to match
	//which contains movieTitle as a substring
	// note that it performs case insensitive matching
	regex reg(movieTitle, regex_constants::icase);
	auto it = movies_db.begin();
	while (!found && it != movies_db.end())
	{ 
//	    cout << it->first << endl;
	    if (regex_search(it->first, reg))
	    {
		found = true;
		matchedMovie = it->first;
	    }
	    else
		it++;
	}
	return matchedMovie;
}

        // check if a movieTitle does exist in the map
        // return true if it does; otherwise return false
        bool IMDB:: isExistingMovie(string movieTitle) const
{	if (movies_db.find(movieTitle) != movies_db.end())
		return true;
	else
		return false;
}
        
        // check if an actorName does exist in the map
        // return true if it does; otherwise return false
        bool IMDB::isExistingActor(string actorName) const
{	if (actors_db.find(actorName) != actors_db.end())
		return true;
	else
		return false;
}
        // return a set of movie titles which actorName is in
        // if the passing in parameter: actorName, is not in the database, 
        //      display message and return an empty set
        set<string> IMDB::find_movies_for_an_actor(string actorName) const
{	if (!isExistingActor(actorName))
	{ cout << actorName << " is not in database" << endl;
		return set<string>();
}
	return actors_db.at(actorName);
}
        // return a set of actor names which are all in the movieTitle
        // if the passing in parameter: movieTitle is not in the database, 
        //      display message and return an empty set
        set<string> IMDB::find_actors_in_a_movie(string movieTitle) const
{	if(!isExistingMovie(movieTitle))
	{ cout << movieTitle << " is not in database" << endl;
	return set<string>(); 
	}
	return movies_db.at(movieTitle);
	}    
        // you are allowed to add more member functions if you need

   /* private:    
        map<string, set<string> > movies_db;    // map of <movie title, set of actors in this movie> 
        map<string, set<string> > actors_db;    // map of <actor name, set of movies this actor is in>
};

#endif   /* IMDB_H */

