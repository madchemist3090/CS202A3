// Alex Olson		CS202		Assignment 3
// operators.cpp	5/16/2017

/*
   This file contains probably way too many overloaded operators that let
   the objects interact more smoothly on wider scope. Most operators just 
   call functions from the class in which they operate on.
*/

#include "data.h"

/***************************************************************************
			        String class
***************************************************************************/
//Output and Input
std::ostream& operator << (std::ostream& out, const String& s)
{
    return out << s.info;
}
std::istream& operator >> (std::istream& in, String& s)
{
    in.get(s.info, MAX, '\n'); in.ignore(MAX, '\n');
    return in;
}


//Assignment
String& String::operator = (const String& s)
{
    if (this == &s)
	return *this;
    
    delete [] this->info;
    this->info = new char[strlen(s.info) + 1];
    strcpy(this->info, s.info);
    
    return *this;
}


//Equal and Not Equal Comparisons
bool String::operator == (const String& s) const
{
    if (!strcmp(this->info, s.info))
	return true;
    return false;
}
bool String::operator != (const String& s) const
{
    if (strcmp(this->info, s.info))
	return true;
    return false;
}


//Alphabetically Greater (or Equal)
bool String::operator > (const String& s) const
{ 
    if (strcmp(this->info, s.info) > 0)
	return true;
    return false;
}
bool String::operator >= (const String& s) const
{
    if (strcmp(this->info, s.info) >= 0)
	return true;
    return false;
}


//Alphabetically Lesser (or Equal)
bool String::operator < (const String& s) const
{
    if (strcmp(this->info, s.info) < 0)
	return true;
    return false;
}
bool String::operator <= (const String& s) const
{
    if (strcmp(this->info, s.info) <= 0)
	return true;
    return false;
}



/***************************************************************************
			       app class
***************************************************************************/
//Assignment
app& app::operator = (const app& a)
{
    if (this == &a)
	return *this;
    delete [] this->info;
    this->info = new char[strlen(a.info + 1)];
    strcpy(this->info, a.info);
    this->application_type = a.application_type;
    this->frequency_score = a.frequency_score;
    this->last_session_length = a.last_session_length;
    this->last_user_action = a.last_user_action;
    this->date_last_used = a.date_last_used;
    return *this;
}


//Output
std::ostream& operator << (std::ostream& out, const app& a)
{
    out << "\nApplication:\t\t\t" << a.info
	<< "\nApplication type:\t\t" << a.application_type
	<< "\nLast session length (minutes):\t" << a.last_session_length
	<< "\nLast action:\t\t\t" << a.last_user_action
	<< "\nDate last used (YYYY/MM/DD):\t" << a.date_last_used;
    return out;
}


//Equal/Not Equal
bool app::operator == (const app& a) const
{
    if (strcmp(this->info, a.info) == 0)
	return true;
    return false;
}
bool app::operator != (const app& a) const
{
    if (strcmp(this->info, a.info) != 0)
	return true;
    return false;
}
bool app::operator == (const char* info) const
{
    if (strcmp(this->info, info) == 0)
	return true;
    return false;
}
bool app::operator != (const char* info) const
{
    if (strcmp(this->info, info) != 0)
	return true;
    return false;
}


//Alphabetically Greater (or Equal)
bool app::operator > (const app& a) const
{ 
    if (strcmp(this->info, a.info) > 0)
	return true;
    return false;
}
bool app::operator >= (const app& a) const
{
    if (strcmp(this->info, a.info) >= 0)
	return true;
    return false;
}


//Alphabetically Lesser (or Equal)
bool app::operator < (const app& a) const
{
    if (strcmp(this->info, a.info) < 0)
	return true;
    return false;
}
bool app::operator <= (const app& a) const
{
    if (strcmp(this->info, a.info) <= 0)
	return true;
    return false;
}


/***************************************************************************
				binary_tree class
***************************************************************************/
//Output
std::ostream& operator << (std::ostream& out, const binary_tree& b)
{
    b.display_tree(b.root);
    return out;
}


//Compound Opererators
binary_tree& binary_tree::operator += (const app& a)
{
    this->insert(a);
    return *this;
}
binary_tree& binary_tree::operator -= (const app& a)
{
    this->remove(a);
    return *this;
}


//Addition and Subtraction (Here as a courtesy, large performance hit)
binary_tree operator + (const binary_tree& b, const app& a)
{
    binary_tree* temp = new binary_tree(b);
    *temp += a;
    return *temp;
}
binary_tree operator + (const app& a, const binary_tree& b)
{    
    binary_tree* temp = new binary_tree(b);
    *temp += a;
    return *temp;
}
binary_tree operator - (const binary_tree& b, const app& a)
{
    binary_tree* temp = new binary_tree(b);
    *temp -= a;
    return *temp;
}
binary_tree operator - (const app& a, const binary_tree& b)
{
    binary_tree* temp = new binary_tree(b);
    *temp -= a;
    return *temp;
}



/***************************************************************************
				node class
***************************************************************************/
//Equality Operators
bool node::operator == (const node& n) const
{
    if (this->root == n.root)
	return true;
    return false;
}
bool node::operator != (const node& n) const
{
    if (this->root != n.root)
	return true;
    return false;
}
node& node::operator += (const app& a)
{
    this->insert(a);
    return *this;
}
node& node::operator -= (const app& a)
{
    this->remove(a);
    return *this;
}



/***************************************************************************
				list class
***************************************************************************/
//Output
std::ostream& operator << (std::ostream& out, const list& p)
{
    p.display_list(p.head);
    return out;
}


//Compound Operators
list& list::operator += (const node& n)	
{
    this->insert(this->head, n);
    return *this;
}
list& list::operator -= (const node& n)
{
    this->remove(this->head, n);
    return *this;
}
list& list::operator += (const app& a)
{
    this->head->insert(a);
    return *this;
}
list& list::operator -= (const app& a)
{
    this->head->remove(a);
    return *this;
}


//Addition and Subtraction (Here as a courtesy, large performance hit)
list operator + (const list& p, const node& n)
{
    list* temp = new list(p);
    *temp += n;
    return *temp;
}
list operator + (const node& n, const list& p)
{
    list* temp = new list(p);
    *temp += n;
    return *temp;
}
list operator - (const list& p, const node& n)
{
    list* temp = new list(p);
    *temp -= n;
    return *temp;
}
list operator - (const node& n, const list& p)
{
    list* temp = new list(p);
    *temp -= n;
    return *temp;
}
list operator + (const list& p, const app& a)
{
    list* temp = new list(p);
    *temp += a;
    return *temp;
}
list operator + (const app& a, const list& p)
{
    list* temp = new list(p);
    *temp += a;
    return *temp;
}
list operator - (const list& p, const app& a)
{
    list* temp = new list(p);
    *temp -= a;
    return *temp;
}
list operator - (const app& a, const list& p)
{
    list* temp = new list(p);
    *temp -= a;
    return *temp;
}



