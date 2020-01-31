#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>
#include <dirent.h>

Network::Network(){

    head = NULL;
    tail = NULL;
    count = 0;
}


Network::Network(string filename){

	loadDB(filename);
}


Network::~Network(){

    Connection* ptr = head;
    while(head != NULL){
        ptr = head->next;
        delete head;
        head = ptr;
        count--;
    }
}


void Network::push_front(Connection* newEntry){

    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL){
        head->prev = newEntry;
    }
    else{
        tail = newEntry;
    }

    head = newEntry;
    count++;
}


void Network::push_back(Connection* newEntry){

    // Adds a new Connection (newEntry) to the back of LL
    newEntry->next = NULL;
    newEntry->prev = tail;

    if(tail != NULL){
        tail->next = newEntry;
    }
    else{
        head = newEntry;
    }

    tail = newEntry;
    count++;
}


Connection* Network::search(Connection* searchEntry){

    // Searches the Network for searchEntry
    // if found, returns a pointer to it, else returns NULL
    Connection* ptr = head;

    while(ptr != NULL){

        if(*ptr == *searchEntry){
                return ptr;
        }

        ptr = ptr->next;
    }

    return NULL;
}


Connection* Network::search(string c_name){

    Connection* ptr = head;

    while(ptr != NULL){

        string first_name = ptr->f_name;
        string last_name = ptr->l_name;

        if(codeName(first_name, last_name) == c_name){
                return ptr;
        }

        ptr = ptr->next;
    }

    return NULL;
}


Connection* Network::search(string fname, string lname){

	string d_bdate = "1/1/1970";
	string d_email = "(default) default@email.com";
	string d_phone = "(default) 000-000-0000";

	Connection* ptr = NULL;
	ptr = new Connection(fname, lname, d_bdate, d_email, d_phone);

	return search(ptr);
}


void Network::printDB(){

    cout << "Number of connections: " << count << endl;
    cout << "------------------------------" << endl;
    Connection* ptr = head;

    while(ptr != NULL){
        ptr->print_connection();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}


void Network::saveDB(string filename){

    ofstream output_file;

    // clear the file before opening it
    output_file.open(filename.c_str(), std::ofstream::out | std::ofstream::trunc);
    output_file.close();

    output_file.open(filename, std::ios::out | std::ios::app);

	Connection* ptr = head;

	while(ptr != NULL){
		ptr->write_connection(output_file);
        ptr = ptr->next;

	}

	output_file.close();
}


void Network::loadDB(string filename){

    // Loads the netwrok from file <filename>
    // The format of the input file is similar to saveDB
    // Look at network studentDB.txt as a template
    // Phone number can be with dashes or without them

	ifstream input_file;
	input_file.open(filename.c_str());

	Connection* ptr = head;
	while(head != NULL){
		ptr = head->next;
		delete head;
		head = ptr;
		count--;
	}

	head = NULL;
	tail = NULL;

	string buff, f_name, l_name, bdate, email, phone, trash;

    vector <string> temp;

    while (getline(input_file, buff)){

        temp.clear();
        l_name = buff.substr(0,buff.find(","));
        f_name = buff.substr(buff.find(",") + 2);
        individual.push_back(f_name + ", " + l_name);

        getline(input_file, bdate);
        getline(input_file, email);
        getline(input_file, phone);
        getline(input_file, buff);

        while(buff.compare(0, 5, "-----") != 0){

            temp.push_back(buff);
            getline(input_file, buff);
        }

        individualFriends.push_back(temp);

        Connection* newEntry = new Connection(f_name, l_name, bdate, email, phone);
        this->push_back(newEntry);
    }

    input_file.close();

    for (int i=0; i<individual.size(); i++){

        string first_name = individual[i].substr(0, individual[i].find(","));
        string last_name = individual[i].substr(individual[i].find(",") + 2);
        Connection* individual_ptr = search(first_name, last_name);
        //cout << "individual: " << individual[i] << endl;

        for (int j=0; j<individualFriends[i].size(); j++){

            Connection* friend_ptr = search(individualFriends[i][j]);
            if(friend_ptr != NULL){
                individual_ptr->makeFriend(friend_ptr);
            }
        }
    }
}


bool Network::remove(string fname, string lname){

    string d_bdate = "1/1/1970";
    string d_email = "(default) default@email.com";
    string d_phone = "(default) 000-000-0000";
    Connection* newEntry = new Connection(fname, lname, d_bdate, d_email, d_phone);

    Connection* ptr = this->search(newEntry);
    Connection* nextElement = ptr->next;
    Connection* prevElement = ptr->prev;

    string C_Name = codeName(fname, lname);

    Connection* pointer = head;

    while(pointer != NULL)
    {
        for(int i = 0; i < pointer->friends.size(); i++){

            if(codeName(pointer->friends[i]->f_name, pointer->friends[i]->l_name) == C_Name){
                pointer->friends.erase(pointer->friends.begin() + i);
            }
        }

        pointer = pointer->next;
    }

    if (this->search(newEntry) != NULL)
    {
        // if we are removing the last element
        if(nextElement == NULL){

            prevElement->next = NULL;
            tail = prevElement;
            delete ptr;
            delete newEntry;
            count--;
            return 1;
        }
        else if(prevElement == NULL){

            nextElement->prev = NULL;
            head = nextElement;
            delete ptr;
            delete newEntry;
            count--;
            return 1;
        }
        else if(prevElement != NULL && nextElement != NULL){

            nextElement->prev = prevElement;
            prevElement->next = nextElement;
            delete ptr;
            delete newEntry;
            count--;
            return 1;
        }
        else{

            delete newEntry;
            return false;
        }
    }
}


void Network::sendEmail(string addr, string subject, string content, string attachment = ""){

    // Sending a command looks like:
    // echo "content" | mailx -s "subject" -a "attachment" addr;
	string command;

    content = "\"" + content + "\"";
    subject = "\"" + subject + "\"";
	attachment = "\"" + attachment + "\"";

	//command = "echo " + content + " | mailx -s " + subject + " -a " + attachment + " " + addr;
    command = "echo " + content + " | mailx -s " + subject + " " + addr;
	system(command.c_str());
}


void Network::showMenu(){

    int opt;
    while(1){
        cout << "\033[2J\033[1;1H";
        printMe("banner"); // from misc library

        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new connection \n";
        cout << "4. Remove a connection \n";
        cout << "5. Search \n";
        cout << "6. Send an email \n";
        cout << "7. Send an iMessage \n";
        cout << "8. Print database \n";
        cout << "9. Connect \n";
        cout << "\nSelect an option ... ";

        if (cin >> opt){

            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else{

            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }

        // You may need these variables! Add more if you want!
        string fname, lname, fileName, bdate;
        cout << "\033[2J\033[1;1H";

        if (opt==1){

            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
		          cin >> fileName;
		    saveDB(fileName);
            cout << "Network saved in " << fileName << endl;
        }
        else if (opt==2){

            cout << "Loading network database \n";

    		DIR* dir;
    		struct dirent* ent;
    		char targetFolderAddr[] = "./";

            string temp;
    		if ((dir = opendir ("./")) != NULL){

    			while ((ent = readdir (dir)) != NULL){

                  	temp = ent->d_name;

    				if(temp.length() >= 4){

    					if(temp.substr(temp.length() - 3) == ".db"){
    						cout << ent->d_name << endl;
    					}
    				}
              	}

    			closedir (dir);
    		}

            cout << "Enter the name of the load file: ";

            // If file with name FILENAME does not exist:
            cin >> fileName;

            int flag = 0;
            if ((dir = opendir ("./")) != NULL){

                while ((ent = readdir (dir)) != NULL){

                    if(fileName == ent->d_name){

                        loadDB(fileName);
                        flag = 1;
                        // If file is loaded successfully, also print the count of connections in it:
				        cout << "Network loaded from " << fileName << " with " << count << " connections \n";
                   		break;
                    }
                }

    			if(flag == 0){
    				cout << "File FILENAME does not exist!" << endl;
    			}
    			if(flag == 1){
    				flag = 0;
    			}

                closedir (dir);
            }
        }
        else if (opt == 3){

            // Add a new Connection ONLY if it does not exists!
            cout << "Adding a new connection \n";

            Connection* ptr = new Connection();

    		if(search(ptr) == NULL){
                push_front(ptr);
    		}
    		else{

                cout << "Connection already exists" << endl;
                delete ptr;
    		}
        }
        else if (opt == 4){

            cout << "Removing a connection \n";
            cout << "First name: ";
            getline(cin, fname);
            cout << "Last name: ";
            getline(cin,lname);

            if(search(fname, lname) == NULL){

                // if not found:
                cout << "Connection not found! \n";
            }
            else{

                // if found:
                remove(fname, lname);
                cout << "Connection removed! \n";
            }
        }
        else if (opt==5){

            cout << "Searching: \n";
            cout << "First Name: ";
            cin >> fname;
            cout << "Last Name: ";
            cin >> lname;

            // if found: print connection
            if(search(fname, lname) != NULL){

                Connection* ptr = search(fname, lname);
                ptr->print_connection();
            }
            else{

                // if not,
                cout << "Not found! \n";
            }
        }
        else if (opt==6){

            cout << "Sending email to: \n";
            cout << "First Name: ";
            std::getline (std::cin, fname);
            cout << "Last Name: ";
            std::getline (std::cin, lname);
            Connection* ptr = search(fname, lname);

            if(ptr){
                string subject, content, attachment;
                cout << "Sending email to: \n";
                ptr->print_connection();
                cout << "Subject: ";
                std::getline (std::cin, subject);
                cout << "Content: ";
                std::getline (std::cin, content);
                cout << "Attachment: ";
                std::getline (std::cin, attachment);
                string addr = ptr->email->get_contact("1");
                sendEmail(addr, subject, content, attachment);
            }
            else{
                cout << "Contact not found! \n";
            }
        }
        else if (opt==7){
            cout << "Option currently not available\n";
        }
        else if (opt==8){

            cout << "Network Database: \n";
            printDB();
        }
        else if (opt==9){

            string f1, l1;
            string f2, l2;

            cout << "Make Friends" << endl;
            cout << "Connection 1" << endl;

            cout << "First Name: ";
                getline(cin, f1);
            cout << "Last Name: ";
                getline(cin, l1);

            if(search(f1,l1) == NULL){
                cout << "Connection not found";
            }
            else{

                cout << "Connection 2" << endl;
                cout << "First Name: ";
                getline(cin, f2);
                cout << "Last Name: ";
                getline(cin, l2);

                if(search(f2,l2) == NULL){
                    cout << "Connection not found";
                }
                else{

                    search(f1,l1)->makeFriend(search(f2,l2));
                    search(f2,l2)->makeFriend(search(f1,l1));
                    cout << "Connection sucessful";
                }
            }
        }
        else{
            cout << "Nothing matched!\n";
        }

        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline (std::cin, temp);
        cout << "\033[2J\033[1;1H";

    }
}
