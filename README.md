## Targets:
- Learning how to change the already implemented code, going back and forth!
- OOP, protected and private, friend
- OOP, dependency of implementation for different classes
- Virtual functions
- Main menu design
- Running commands from C++ code
- Getting feedback from OS, if file exists
- Connecting to USC Viterbi servers
- Copying files between local machine and server

## Background:
This purpose of this program is to build a network of people whom you can interact with (via email/text). The network will store individuals birth dates, name, phone number, and email. From a main menu you will be able to access this information along with additional features such as saving your friends to a file, adding new friends, searching for friends etc... The network was implemented usingg a linked list.

## Main Menu:
- Look at the misc.cpp and misc.h to see how we are printing the banner to our Trojan-Book!
- Start with Main Menu (showMenu), here is our suggestion for the sequence of implementation, based on how you can debug your code. Try to test your code after each implementation, this means your code should be bug free in those options.
    - Option 8, printing the database. We implement the print first so you can debug your code. Test your code before going to the next step!
    - Option 3, adding a new connection, only if it does not exist
    - Option 1, save network
    - Option 2, load network. When load network is selected, you need to print all the files in this same directory that have .db format. You need to check if the file exists or not, if not, prompt the warning, if it is a valid file, prompt as shown in the code mentioning the number of the connections loaded.  
    - Option 4 and 5: searching a connection and removing it.
    - Option 6: send an email option has been already implemented for you. You need to run the code from a server, like viterbi servers. Instructions are given at the end of this instruction.  
    - Option 7: *Optional!* if you have macbook you are welcomed to implement this method. We will send out the solution for this part after the deadline.


## Running code on viterbi servers:
By default, you all have a user in viterbi servers. Follow these steps to connect to viterbi-scf1 (or viterbi-scf2) servers:
- Make sure you are connected to internet with USC Secure Wireless (for wifi) or Lan (inside USC domain).
- If you are not in USC domain, use VPN (instructions are here: https://itservices.usc.edu/vpn/)
- From your terminal create a secure shell to connect to the server:
    - *$> ssh TommyTrojan@viterbi-scf1.usc.edu* (TommyTrojan is your own USC user)
- You can transfer your files from local machine (your laptop) to the server and in the opposite direction using secure copy *scp* command:
    - From local machine to server: *$> scp fileName TommyTrojan@viterbi-scf1.usc.edu:<addres-in-server>*
    - From server to local machine: *$> scp TommyTrojan@viterbi-scf1.usc.edu:~/folderName/folderName/fileName <address-in-local-machine>*
    - As an example, I copy my network.cpp file to the server with this command:
    - *scp \~/Documents/Courses/EE355/PA1/network.cpp abri442@viterbi-scf1.usc.edu:\~/workspace/PA1_in_server/*
    - Or you can copy the folder completely like this:
    - *scp -r \~/Documents/Courses/EE355/PA/ abri442@viterbi-scf1.usc.edu:\~/workspace/*
