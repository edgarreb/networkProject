#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <string>

using namespace std;

class Contact {

	protected:
		string type;

	public:
		virtual void print() = 0;
	    virtual string get_contact(string style="full") = 0;
		virtual void set_contact() = 0;
};


class Email: public Contact{

	private:
    	string email_addr;

	public:
    	Email(string type, string email_addr);

	public:
		void print();
		string get_contact(string style = "full");
		void set_contact();
};


class Phone: public Contact{

	private:
		long int phone_num;

	public:
	    Phone(string type, string phone_number);

	public:
		void print();
		string get_contact(string style = "full");
		void set_contact();

};

#endif
