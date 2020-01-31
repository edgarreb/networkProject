#ifndef CONNECTION_H
#define CONNECTION_H

#include "date.h"
#include "contact.h"
#include "fstream"
#include "misc.h"

class Connection{

    friend class Network;

    private:
    	string f_name;
    	string l_name;
    	Date *birthdate;
        Email *email;
        Phone *phone;
        Connection* next;
        Connection* prev;

    public:
        Connection();
        ~Connection();
        Connection(string filename);
        Connection(string f_name, string l_name, string bdate, string email, string phone);
    	void print_connection();
    	void set_connection();
    	void set_connection(string filename);
        bool operator==(const Connection& rhs);
        bool operator!=(const Connection& rhs);
        void write_connection(std::ofstream& output_file); //pointer to a filename as an argument
        vector <Connection*> friends;
        void makeFriend(Connection* newFriend);
};

#endif
