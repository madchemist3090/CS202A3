// Alex Olson		CS202		Assignment 3
// dataStructures.h	5/16/2017

/*
   This file contains the data structures, abstract data types, and a gateway
   class that acts as the only point of contact for the rest of the classes
   in order to help simplify the menu application. The classes create a self-
   organizing list of applications ordered in a binary tree which is located
   within a linear linked list. Data used more ofter filters torwards the top
   of the list.
*/

#include "data.h"

/***************************************************************************
			    binary_tree class
***************************************************************************/
//Default Constructor
//INPUT: void
binary_tree::binary_tree(void)
{
   root = NULL;
   tree_size = 0;
}


//Copy constructor
//INPUT: tree to copy
binary_tree::binary_tree(const binary_tree& source)
{
    copy_tree(root, source.root);
    tree_size = source.tree_size;
}


//Destructor
//INPUT: tree to clear
binary_tree::~binary_tree(void)
{
    clear(root);
}


//[WRAPPER]Insert an app into the binary tree
//INPUT: application to add to the tree
//OUTPUT: success = 1, failure = 0
int binary_tree::insert(const app& to_add)
{
    if (!strlen(to_add.info)) return 0;	    //Error check
    app* temp = new app(to_add);	    //Copy app to insert
    ++tree_size;			    //Increment tree size
    
    //Insert app into tree
    if (!root)
    {
	root = temp;
	return 1;
    }
    else return insert(root, temp);
}
//Protected recursive call
int binary_tree::insert(app *& root, app* to_add)
{
    if (!root) 
    {
	root = to_add;
	return 1;
    }
    if (*to_add < *root)
	return insert(root->go_left(), to_add);
    else
	return insert(root->go_right(), to_add);
}


//Remove an app from the binary tree
//INPUT: app to remove
//OUTPUT: 1 for successful removal, 0 for non-success
int binary_tree::remove(const app& to_remove)
{
    if (!strlen(to_remove.info) || !root) return 0; //Error check
    return remove(root, to_remove);
}
//Protected recursive call
int binary_tree::remove(app *& root, const app& to_remove)
{
    if(!root)
	return 0;
    int ret = 0;
    ret += remove(root->go_left(), to_remove);
    ret += remove(root->go_right(), to_remove);

    //If a match is found
    if (*root == to_remove)
    {
	--tree_size;
	ret += 1;
	app* temp;
	//Case 1: No children
	if (!root->go_left() && !root->go_right())
	{
	    delete root;
	    root = NULL;
	}
	//Case 2: 2 Children
	else if (root->go_left() && root->go_right())
	{
	    temp = ios_helper(root->go_right());
	    temp->set_left(root->go_left());
	    temp->set_right(root->go_right());
	    delete root;
	    root = temp;
	}
	//Case 3: Only 1 Child
	else
	{
	    //Left Child
	    if (!root->go_right())
	    {
		temp = root;
		root = root->go_left();
		delete temp;
		temp = NULL;
	    }
	    //Right Child
	    else
	    {
		temp = ios_helper(root->go_right());
		temp->set_right(root->go_right());
		delete root;
		root = temp;
	    }
	}
    }
    return ret;
}


//Determines if a tree is full
//INPUT: void
//OUTPUT: true if tree is full, false otherwise
bool binary_tree::is_full(void) const
{
    if (tree_size >= MAX_TREE_SIZE)
	return true;
    return false;
}


//Retrieve an occurence of an app
//INPUT: app name to find
//OUTPUT: application
app* binary_tree::retrieve(const char* to_find)
{
    if (!to_find) return NULL;	//Error check
    app* ret = NULL;		//For returning app of interest
    int found = retrieve(root, to_find, ret);
    if (!found) ret = NULL;
    return ret;
}
//Protected recursive call
int binary_tree::retrieve(app *& root, const char* to_find, app*& ret)
{
    if (!root) return 0;    //Error check
    int found = 0;	    //Number of items found

    //Search by app name
    found += retrieve(root->go_left(), to_find, ret);
    found += retrieve(root->go_right(), to_find, ret);
    if (!strcmp(root->info,to_find))
    {
	++found;
	ret = root;
    }
    return found;    
}


//////////////////////////////////PROTECTED///////////////////////////////////
//Copy a binary tree
//INPUT: destination tree, source tree
//OUTPUT: void
void binary_tree::copy_tree(app*& dest, app* source)
{
    //Set the leaf tips to NULL
    if (!source)
    {
	source = dest = NULL;
	return;
    }

    //Copy and traverse
    dest = new app(*source);
    copy_tree(dest->go_left(), source->go_left());
    copy_tree(dest->go_right(), source->go_right());
    return;
}


//Clear out a binary tree
//INPUT: tree to clear
//OUTPUT: void
void binary_tree::clear(app *& root)
{
    //Recurse through the tree and remove on the way back
    if (!root) return;
    clear(root->go_left());
    clear(root->go_right());
    delete root; root = NULL;
    return;
}


//Recursively display the tree
//INPUT: tree to display
//OUTPUT: void
void binary_tree::display_tree(app* root) const
{
    if (!root) return;
    display_tree(root->go_left());
    std::cout << *root << "\n\n";
    display_tree(root->go_right());
    return;
}


//Removes IOS and returns a temp copy of it's data
//Note: The copy should be deleted when finished using it in a containing function
//INPUT: Branch to scan IOS
//OUTPUT: IOS app
app* binary_tree::ios_helper(app *& root)
{
    //Check fo data
    if (!root) return NULL;
    //Base case: found IOS
    if (!root->go_left())
    {
	app* ret = new app(*root);		//Copy IOS data
	app* to_remove = root;			//Mark IOS node for removal
	root = root->go_right();		//Shift tree around IOS
	delete to_remove; to_remove = NULL;	//Remove IOS node
	return ret;				//Return IOS data
    }
    //Recursively traverse to IOS
    return ios_helper(root->go_left());
}


/***************************************************************************
			    node class
***************************************************************************/
//Default Constructor
//INPUT: void
node::node(void)
{
    next = NULL;
}


//Binary Tree Constructor
//INPUT: binary tree to add
node::node(const binary_tree& to_add): binary_tree(to_add)
{
    next = NULL;
}


//Copy Constructor
//INPUT: node to copy
node::node(const node& to_copy): binary_tree(to_copy)
{
    next = NULL;
}


//Traverse to next node in the list
//INPUT: void
//OUTPUT: next node in list
node*& node::go_next(void)
{
    return next;
}


//Connect next pointer to another node
//INPUT: next connection
//OUTPUT: void
void node::set_next(node* to_connect)
{
    next = to_connect;
    return;
}



/***************************************************************************
			    list class
***************************************************************************/
//Default Constructor
//INPUT: void
list::list(void)
{
    head = NULL;
}


//Copy Constructor
//INPUT: void
list::list(const list& to_copy)
{
    copy(head, to_copy.head);
}


//Destructor
//INPUT: void
list::~list(void)
{
    clear(head);
}


//Find an application in the list
//INPUT: application name to find
//OUTPUT: mathing application if founf, NULL otherwise
app* list::retrieve(const char* to_find) const
{
    if (!strlen(to_find)) return NULL;
    return retrieve(head, to_find);
}
//Protected recursive call
app* list::retrieve(node * head, const char* to_find) const
{
    if (!head) return NULL;
    app* ret = NULL;
    ret = head->retrieve(to_find);
    if (!ret) ret = retrieve(head->go_next(), to_find);
    return ret;
}


//Determine if a node is full
//INPUT: void
//OUTPUT: true if full, false otherwise
bool list::is_full(void) const
{
    if (!head) return false;
    if (head->is_full()) return true;
    return false;
}


//Determine if list is empty
//INPUT: void
//OUTPUT: true if empty, false otherwise
bool list::is_empty(void) const
{
    if (!head) return true;
    return false;
}


//////////////////////////////////PROTECTED///////////////////////////////////
//Recursively copy a list
//INPUT: empty list, list to copy
//OUTPUT: void
void list::copy(node *& dest, node* source)
{
    //Copy list on the way forward
    if (!source)
    {
	dest = NULL;
	return;
    }
    dest = new node(*source);
    return copy(dest->go_next(), source->go_next());
}


//Recursively clear the list
//INPUT: head of list to clear
//OUTPUT: void
void list::clear(node *& head)
{
    //Recurse and delete on the way back
    if (!head) return;
    clear(head->go_next());
    delete head; head = NULL;
    return;
}


//Insert a node into the list
//INPUT: head of list to add to, node to add
//OUTPUT: success = 1, fail = 0
int list::insert(node *& head, const node& to_add)
{
    node* temp = new node(to_add);  //Copy data to add
    if (!head) head = temp;	    //Insert into beginning of list
    else
    {
	temp->set_next(head);
	head = temp;
    }
    return 1;
}


//Recursively remove a node from the list
//INPUT: head of list to add to, node to add
//OUTPUT: success = 1, fail = 0
int list::remove(node *& head, const node& to_remove)
{
    int ret = 0;	    //Return flag
    if (!head) return ret;  //Error check
    ret += remove(head->go_next(), to_remove);
    
    //If a match is found, remove it
    if(*head == to_remove)
    {
	++ret;
	node* temp = head;
	head = head->go_next();
	delete temp; temp = NULL;
    }
    return ret;	
}


//Recursively display all applications in the list
//INPUT: head of list to display
//OUPUT: void
void list::display_list(node* head) const
{
    if (!head) return;
    std::cout << "\nUsage Group\n" << *head;
    return display_list(head->go_next());
}



/***************************************************************************
			    user class
***************************************************************************/
//Default Constructor
//INPUT: void
user::user(void) {}


//Tries to find an app in the structure, if it does not exist, then it will
//Prompt the user for app info to add and add it to the list. Otherwise, the
//app gets moved to the top of the list
//INPUT: void
//OUTPUT: number of items added to the list (0 if the app is already present)
int user::find(void)
{
    char to_find[MAX];		//App name to search for
    std::cout << "\nWhat is the application name you want to search for?: ";
    std::cin.get(to_find, MAX, '\n'); std::cin.ignore(MAX, '\n');
    if (!strlen(to_find)) return 0;	//Error check
    
    char tempType[MAX];		//Temp app type
    int tempLength;		//Temp app usage
    char tempAction[MAX];	//Temp user action
    char tempDate[MAX];		//Temp date last used
    app* to_add = NULL;		//App to add
    app* temp = app_list.retrieve(to_find); //Look for the app first
    node* tempNode = NULL;	//New list node if necessary
    
    //If the app was not found, add it to the beginning of the list
    if (!temp)
    {
	//Gather app data from the user
	std::cout << "\nThe app could not be found, it will now be added to the list"
	          << "\nWhat is the app type? (social media, gaming, school, etc.): ";
	std::cin.get(tempType, MAX, '\n'); std::cin.ignore(MAX, '\n');
	std::cout << "\nWhat was the last session length?   minutes: ";
	std::cin >> tempLength; std::cin.ignore(MAX, '\n');
	std::cout << "\nWhat was the last user action?: ";
	std::cin.get(tempAction, MAX, '\n'); std::cin.ignore(MAX, '\n');
	std::cout << "\nWhat was the date of last usage?   YYYY/MM/DD: ";
	std::cin.get(tempDate, MAX, '\n'); std::cin.ignore(MAX, '\n');
	to_add = new app(to_find, tempType, tempLength, tempAction, tempDate);
	
	//If a new node in the list is needed
	if (app_list.is_empty() || app_list.is_full())
	{
	    tempNode = new node;
	    *tempNode += *to_add;
	    app_list += *tempNode;
	}
	
	//Else, add it to an existing tree
	else app_list += *to_add;
    }
    
    //Else, the app was found, move it to the beginning of the list
    else
    {
	//Copy found data for list reinsertion
	to_add = new app(*temp);

	//Update to_add with new user data
	std::cout << "\nThe app was found, time to update the data"
		  << "\nWhat was the last session length?   minutes: ";
	std::cin >> tempLength; std::cin.ignore(MAX, '\n');
	std::cout << "\nWhat was the last user action?: ";
	std::cin.get(tempAction, MAX, '\n'); std::cin.ignore(MAX, '\n');
	std::cout << "\nWhat was the date of last usage?   YYYY/MM/DD: ";
	std::cin.get(tempDate, MAX, '\n'); std::cin.ignore(MAX, '\n');
	to_add->update_data(tempLength, tempAction, tempDate);
	app_list -= *temp;
	app_list += *to_add;
    }

    //Clear out any temporary memory
    delete to_add; to_add = NULL;
    delete tempNode; tempNode = NULL;
    return 1;
}


//Display all app in the list
//INPUT: void
//OUTPUT: void
void user::display(void) const
{
    std::cout << "\n Applications\n\n" << app_list;
    return;
}


//Add an application to the list
//INPUT: void
//OUTPUT: true if successful, false otherwise
bool user::add(void)
{
    char tempName[MAX];		//Temp app name
    char tempType[MAX];		//Temp app type
    int tempLength;		//Temp usage time
    char tempAction[MAX];	//Temp user action
    char tempDate[MAX];		//Temp date last used
    app* to_add = NULL;		//Gathers temp data into an app to add
    node* tempNode = NULL;	//New list node if necessary

    //Gather app data from user
    std::cout << "\nWhat is the name of the application?: ";
    std::cin.get(tempName, MAX, '\n'); std::cin.ignore(MAX, '\n');
    std::cout << "\nWhat is the app type? (social media, gaming, school, etc.): ";
    std::cin.get(tempType, MAX, '\n'); std::cin.ignore(MAX, '\n');
    std::cout << "\nWhat was the last session length?   minutes: ";
    std::cin >> tempLength; std::cin.ignore(MAX, '\n');
    std::cout << "\nWhat was the last user action?: ";
    std::cin.get(tempAction, MAX, '\n'); std::cin.ignore(MAX, '\n');
    std::cout << "\nWhat was the date of last usage?   YYYY/MM/DD: ";
    std::cin.get(tempDate, MAX, '\n'); std::cin.ignore(MAX, '\n');
    to_add = new app(tempName, tempType, tempLength, tempAction, tempDate);
    if(!to_add) return false;	//Error check

    //If a new node in the list is needed
    if (app_list.is_empty() || app_list.is_full())
    {
	tempNode = new node;
	*tempNode += *to_add;
	app_list += *tempNode;
    }

    //Else, add it to an existing tree
    else app_list += *to_add;

    //Clear out any temporary memory
    delete to_add; to_add = NULL;
    delete tempNode; tempNode = NULL;
    return true;
}


//Remove an application from the list
//INPUT: void
//OUTPUT: true if successful, false otherwise
bool user::remove(void)
{
    char to_find[MAX];	//App to search for
    std::cout << "\nEnter the application name to remove: ";
    std::cin.get(to_find, MAX, '\n'); std::cin.ignore(MAX, '\n');
    app* temp = app_list.retrieve(to_find);	//Look for the app to remove
    
    //Return false if the app could not be found
    if (!temp) return false;

    //Else remove the app and return true
    app_list -= *temp;
    return true;
}


//Load an external file into the data structure
//INPUT: void
//OUTPUT: true if successful load, false otherwise
bool user::load(void)
{
    std::ifstream read;
    char ch;			//For checking input
    char tempName[MAX];		//Temp app name
    char tempType[MAX];		//Temp app type
    int tempLength;		//Temp usage time
    char tempAction[MAX];	//Temp user action
    char tempDate[MAX];		//Temp date last used
    app* to_add = NULL;		//Gathers temp data into an app to add
    node* tempNode = NULL;	//New list node if necessary


    //Open the file and check for data
    read.open("app.txt");
    ch = read.peek();
    if (!read || !ch) return false;

    //Read data in from the file
    while (ch && !read.eof())
    {
	read.get(tempName, MAX, ':'); read.ignore(MAX, ':');
	read.get(tempType, MAX, ':'); read.ignore(MAX, ':');
	read >> tempLength; read.ignore(MAX, ':');
	read.get(tempAction, MAX, ':'); read.ignore(MAX, ':');
	read.get(tempDate, MAX, ':'); read.ignore(MAX, ':');

	to_add = new app(tempName, tempType, tempLength, tempAction, tempDate);


	//If a new node in the list is needed
	if (app_list.is_empty() || app_list.is_full())
	{
	    tempNode = new node;
	    *tempNode += *to_add;
	    app_list += *tempNode;
	}

	//Else, add it to an existing tree
	else app_list += *to_add;

	//Clear out any temporary memory
	delete to_add; to_add = NULL;
	delete tempNode; tempNode = NULL;

	//Skip to next line in file and check for a character
	read.get(ch);
	ch = read.peek();
    
    }
    
    //Close and clear the file input
    read.close();
    read.clear();
    return true;
}








