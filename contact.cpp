#include "contact.h"

Email::Email(string type, string email_addr){

	this->type = type;
	this->email_addr = email_addr;
}


void Email::set_contact(){

    cout << "Enter the type of email address: ";
    // some code here
	cin >> this->type;
    cout << "Enter email address: ";
    // some code here
	cin >> this->email_addr;
}


string Email::get_contact(string style){

	// Note: We have default argument in declaration and not in definition!
    if (style=="full")
	    return "(" + type + ") " + email_addr;
    else
        return email_addr;
}


void Email::print(){

	// Note: get_contact is called with default argument
	cout << get_contact() << endl;
}


Phone::Phone(string type, string num){

	this->type = type;

	long int area_code;
    long int number;

	if(num.find("-") == 3 && num.find("-", 4) == 7){

        string area = num.substr(0,3);
        string middle_digit = num.substr(4,3);
        string last_digit = num.substr(8);
        string last_number = middle_digit + last_digit;

        area_code = atoi(area.c_str());
        number = atoi(last_number.c_str());
        this->phone_num = area_code*10000000 + number;
    }
	else if(num.find("-") == 3 && num.find("-", 4) > 7){

        area_code = atoi((num.substr(0,3)).c_str());
        number = atoi((num.substr(4)).c_str());
        this->phone_num = area_code*10000000 + number;
    }
    else{

		area_code = atoi((num.substr(0,3)).c_str());
        number = atoi((num.substr(3)).c_str());
        this->phone_num = area_code*10000000 + number;
    }
}


void Phone::set_contact(){

	cout <<"Enter the type of phone number: ";
		cin >> this->type;
	cout << "Enter the phone number: ";
	string num;
		cin >> num;

	long int area_code;
    long int number;

    if(num.find("-") == 3 && num.find("-", 4) == 7){

        string area = num.substr(0,3);
        string middle_digit = num.substr(4,3);
        string last_digit = num.substr(8);
        string last_number = middle_digit + last_digit;

        area_code = atoi(area.c_str());
        number = atoi(last_number.c_str());
        this->phone_num = area_code*10000000 + number;
    }
	else if(num.find("-") == 3 && num.find("-", 4) > 7){

        area_code = atoi((num.substr(0,3)).c_str());
        number = atoi((num.substr(4)).c_str());
        this->phone_num = area_code*10000000 + number;
    }
    else{

        area_code = atoi((num.substr(0,3)).c_str());
        number = atoi((num.substr(3)).c_str());
        this->phone_num = area_code*10000000 + number;
    }

}


string Phone::get_contact(string style){

	string phone = to_string(phone_num);

	if (style == "full"){
		return "(" + type + ") " + phone;
	}
	else {
		return phone;
	}
}


void Phone::print(){

    // Note: get_contact is called with default argument
	cout << get_contact() << endl;
}
