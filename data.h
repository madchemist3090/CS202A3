// Alex Olson		CS202		Assignment 3
// data.h		5/16/2017

/*
   This header file contains class and function declarations necessary for
   the application as well as describing the class heirarchy for the application.
   The libraries and global constants are also defined in this file.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <cstring>

const int MAX = 100;		//Max string length
const int MAX_TREE_SIZE = 10;	//Max tree size

bool again(void);		//Let user repeat a task
void menu(void);		//Main menu for application

/***************************************************************************
				dataModules
***************************************************************************/
//Dynamic string class
class String
{
    public:
	//Constructors & Destructor
	String(void);
	String(const String& to_copy);
	String(const char* to_add);
	~String(void);

	//Overloaded Operators
	friend std::ostream& operator << (std::ostream&, const String&);
	friend std::istream& operator >> (std::istream&, String&);
	String& operator = (const String&);
	bool operator == (const String&) const;
	bool operator != (const String&) const;
	bool operator >  (const String&) const;
	bool operator >= (const String&) const;
	bool operator <  (const String&) const;
	bool operator <= (const String&) const;

	//Modified ASCII sum
	int hash(void); 
	int Length(void);
	char* info; //Dynamic character array

    protected:

	//Clear and update data
	void clear(void);
	void update(const char* to_add);
};


//Application base object
//Inherits name of application or website
class app: public String
{
    public:
	//Constructors
	app(void);
	app(const char* name, const char* type, int session_length, 
	    const char* action, const char* date);
	app(const char* name, const String& type, int session_length, 
	    const String& action, const String& date);
	app(const app& to_copy);

	//Overloaded Operators	
	app& operator = (const app&);
	friend std::ostream& operator << (std::ostream&, const app&);
	bool operator == (const app&) const;
	bool operator != (const app&) const;
	bool operator == (const char*) const;
	bool operator != (const char*) const;
	bool operator >  (const app&) const;
	bool operator >= (const app&) const;
	bool operator <  (const app&) const;
	bool operator <= (const app&) const;

	//Data management
	bool update_data(int session, char* action, char* date);
	int calculate_score(void);
	bool is_more_recent(const String& date) const;
	
	//Tree management
	void set_left(app* left);
	void set_right(app* right);
	app *& go_left(void);
	app *& go_right(void);
	bool if_left(void) const;
	bool if_right(void) const;
	bool is_empty(void) const;

    protected:
	//App data
	String application_type;
	int frequency_score;	
	int last_session_length;
	String last_user_action;
	String date_last_used;

	//Left and right children of binary tree
	app* left;
	app* right;
};



/***************************************************************************
			       dataStructures
***************************************************************************/
//Binary tree of applications
class binary_tree
{
    public:
	//Constructors and Destructor
	binary_tree(void);
	binary_tree(const binary_tree&);
	~binary_tree(void);

	//Overloaded Operators
	friend std::ostream& operator << (std::ostream&, const binary_tree&);
	binary_tree& operator += (const app&);	
	binary_tree& operator -= (const app&);
	friend binary_tree operator + (const binary_tree&, const app&);
	friend binary_tree operator + (const app&, const binary_tree&);
	friend binary_tree operator - (const binary_tree&, const app&);
	friend binary_tree operator - (const app&, const binary_tree&);
	
	//Tree management functions
	int insert(const app& to_add);
	int remove(const app& to_remove);
	bool is_full(void) const;
	app* retrieve(const char* to_find);

    protected:
	app* root;	    //Root of binary tree
	int tree_size;	    //Number of items in tree

	//Tree management functions
	void copy_tree(app *& dest, app* source);
	void clear(app *& root);
	int insert(app *& root, app* to_add);
	int remove(app *& root, const app& to_remove);	
	void display_tree(app* root) const;
	app* ios_helper(app *& root);
	int retrieve(app *& root, const char* to_find, app *& ret);
};


//Node containing binary tree and list management tools
class node: public binary_tree
{
    public:
	//Constructors
	node(void);
	node(const binary_tree& to_add);
	node(const node& to_copy);
	
	//Overloaded Operators
	bool operator == (const node&) const;
	bool operator != (const node&) const;	
	node& operator += (const app&);
	node& operator -= (const app&);

	//node management functions
	node *& go_next(void);
	void set_next(node* to_connect);

    protected:
	node* next;	    //Next binary tree in the list
};


//Frequency list of binary trees
class list
{
    public:
	//Constructors and Destructor
	list(void);
	list(const list& to_copy);
	~list(void);

	//Overloaded Operators	
	friend std::ostream& operator << (std::ostream&, const list&);
	list& operator += (const node&);	
	list& operator -= (const node&);
	list& operator += (const app&);	
	list& operator -= (const app&);
	friend list operator + (const list&, const node&);
	friend list operator + (const node&, const list&);
	friend list operator - (const list&, const node&);
	friend list operator - (const node&, const list&);	
	friend list operator + (const list&, const app&);
	friend list operator + (const app&, const list&);
	friend list operator - (const list&, const app&);
	friend list operator - (const app&, const list&);	

	//List management
	app* retrieve(const char* to_find) const;
	bool is_full(void) const;    //Full tree
	bool is_empty(void) const;   //Absent list

    protected:
	node* head;	//Head of linear linked list

	//List management functions
	void copy(node *& dest, node* source);
	void clear(node *& head);
	int insert(node *& head, const node& to_add);
	int remove(node *& head, const node& to_remove);
	void display_list(node* head) const;
	app* retrieve(node * head, const char* to_find) const;
};


//Application gateway
class user
{
    public:
	//Constructor
	user(void);

	//Menu Functions
	int find(void);
	void display(void) const;
	bool add(void);
	bool remove(void);
	bool load(void);

    protected:
	list app_list;	    //Application list

};



