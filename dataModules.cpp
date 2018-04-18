// Alex Olson		CS202		Assignment 3
// dataModules.h	5/16/2017

/*
   This file contains the smaller "building block" classes used to construct
   the data structures and abstract data types as well as some gloabal
   functions used in main().
*/

#include "data.h"

/***************************************************************************
			        Global Functions
***************************************************************************/
//Determines if the user wishes to repeat a task
//INPUT: void
//OUTPUT: true if repeat is desired, false otherwise
bool again(void)
{
    char selection;
    std::cout << "\nAgain? (y|n): ";
    std::cin >> selection; std::cin.ignore(MAX, '\n');
    selection = toupper(selection);
    if (selection == 'Y')
	return true;
    return false;
}


//Runs the menu that is executed by the application
//INPUT: void
//OUTPUT: void
void menu(void)
{ 
    user go;			//User identification
    char selection = 'a';	//User menu selection

   //First attempt to load data from a file
    if (!go.load())
    {
	std::cout << "\nThere was an error loading from the file";
	return;
    }
    
    do
    {
	std::cout << "\n\n\tWhat do you want to do?"
		  << "\n --> (f)ind an application"
		  << "\n --> (d)isplay all applications"
		  << "\n --> (a)dd an application"
		  << "\n --> (r)emove an application"
		  << "\n --> (q)uit"
		  << "\n\n Selection: ";
	std::cin >> selection; std::cin.ignore(MAX, '\n');
	selection = toupper(selection);
    
	switch (selection)
	{
	    //Find an app
	    case 'F': if(!go.find()) 
		std::cout << "\n The app is present";
		break;
	    
	    //Display all apps
	    case 'D': go.display();
		std::cout << "\n Most recent apps up top";
		break;

	    //Add an app
	    case 'A': if(!go.add())
		std::cout << "\n There was nothing to add";
		break;

	    //Remove an app
	    case 'R': if(!go.remove())
		std::cout << "\n There was nothing to remove";
		break;

	    //Default
	    default: break;
	}
    } while (selection != 'Q');	    //Repeat until time to quit
    return;
}



/***************************************************************************
			        String class
***************************************************************************/
//Default Constructor
//INPUT: void
String::String(void)
{
    info = NULL;
}


//Copy Constructor
//INPUT: String to copy
String::String(const String & to_copy)
{
    String(to_copy.info);
}


//Char Constructor
//INPUT: char array to add
String::String(const char * to_add)
{
    update(to_add);
}


//Destructor
//INPUT: void
String::~String(void)
{
    clear();
}


//Caclulate modified ASCII sum of data (for frequency score calculation)
//INPUT: void
//OUTPUT: modified sum (for YYYY/MM/DD)
int String::hash(void)
{
    int i = 0;			    //Loop counter
    int length = strlen(info);	    //Loop max
    int sum = 0;		    //ASCII sum
    for (i = 0; i < length; ++i)
    {
	sum += info[i];		    //Sum up the numbers from the date
	sum -= (i*5);		    //Adjust for magnitude
    } 
    return sum;
}


//Calculate the string length of the object data
//INPUT: void
//OUTPUT: length of string object
int String::Length(void)
{
    return strlen(info);
}


//////////////////////////////////PROTECTED///////////////////////////////////
//Clears out any dynamic memory
//INPUT: void
//OUTPUT: void
void String::clear(void)
{
    if (info) delete [] info;
    info = NULL;
    return;
}


//Update the string with new data
//INPUT: string to add
//OUTPUT: void
void String::update(const char * to_add)
{
    if(to_add)
    {
	info = new char[strlen(to_add) + 1];
	strcpy(info, to_add);
    }
    else info = NULL;
    return;
}



/***************************************************************************
			         app class
***************************************************************************/
//Default Constructor
//INPUT: void
app::app(void)
{
    frequency_score = 1;
    last_session_length = 0;
    left = right = NULL;
}


//Object Constructor (basic data types)
//INPUT: app name, session length, user's last action, date used YYYY/MM/DD
app::app(const char* name, const char* type, int session_length, 
	 const char* action, const char* date): 
    String(name)
{
    application_type = type;
    frequency_score = 1;
    last_session_length = session_length;
    last_user_action = action;
    date_last_used = date;
    left = right = NULL;
}


//Object Constructor (class data types)
//INPUT: app name, session length, last action, date used YYYY/MM/DD
app::app(const char* name, const String& type, int session_length, 
	 const String& action, const String& date): 
    String(name)
{
    application_type = type;
    frequency_score = 1;
    last_session_length = session_length;
    last_user_action = action;
    date_last_used = date;
    left = right = NULL;
}


//Copy Constructor
//INPUT: app to copy
app::app(const app& to_copy): String(to_copy.info)
{
    application_type = to_copy.application_type;
    frequency_score = to_copy.frequency_score;
    last_session_length = to_copy.last_session_length;
    last_user_action = to_copy.last_user_action;
    date_last_used = to_copy.date_last_used;
    left = right = NULL;
}


//Update object data with new usage information
//INPUT: session length (minutes), user's last action, date used YYYY/MM/DD
//OUTPUT: False if invalid input, True otherwise
bool app::update_data(int session, char* action, char* date)
{
    if ((session < 0) || !strlen(action) || (strlen(date) != 10))
	return false;
    last_session_length = session;
    last_user_action = action;
    date_last_used = date;
    return true;
}


//Calculate a frequency score (after app data members are updated)
//INPUT: void
//OUTPUT: frequency score
int app::calculate_score(void)
{
    frequency_score += date_last_used.hash() + last_session_length;
    return frequency_score;
}


//For comparing app frequencies
//INPUT: app data to compare (date in format YYYY/MM/DD)
//OUTPUT: true if comparison is more recent, false otherwise
bool app::is_more_recent(const String& date) const
{
    if (date > date_last_used)
	return true;
    return false;
}


//Connect left child
//INPUT: app to connnect to 
//OUTPUT: void
void app::set_left(app* connection)
{
    left = connection;
    return;
}


//Connect right child
//INPUT: app to connext to
//OUTPUT: void
void app::set_right(app* connection)
{
    right = connection;
    return;
}


//Traverse left
//INPUT: void
//OUTPUT: left child
app *& app::go_left(void)
{
    return left;
}


//Traverse right
//INPUT: void
//OUTPUT: right child
app *& app::go_right(void)
{
    return right;
}


//Check if left child exists
//INPUT: void 
//OUTPUT: true if left child exists, false otherwise 
bool app::if_left(void) const
{
    if (left) return true;
    return false;
}


//Check if right child exists
//INPUT: void 
//OUTPUT: true if right child exists, false otherwise 
bool app::if_right(void) const
{
    if (right) return true;
    return false;
}


//Check if the app is holding any data
//INPUT: void
//OUTPUT: true if there is data, false otherwise
bool app::is_empty(void) const
{
    if (info) return true;
    return false;
}



