#include <zmq.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include "zmq.hpp"
#include <sstream>
#include <string>
#include <iostream>
#include <zconf.h>
#include <vector>
#include <signal.h>
#include <sstream>
#include <set>
#include <algorithm>

using namespace std;


zmq::context_t context(1);
string adr = "tcp://127.0.0.1:300";
string command;
vector<int> childesId;
vector<unique_ptr<zmq::socket_t>> sockets;

void funcKill() {
    int id;
    cin >> id;

    if (childesId.empty()) {
        cout << "Error: there isn't nodes" << endl;
    } else {

        for (int indexOfSockets{0}; indexOfSockets < sockets.size(); ++indexOfSockets) {

            if (childesId[indexOfSockets] == id) {
                string killMessage = "KillYourself";
                zmq::message_t message(killMessage.size());
                memcpy(message.data(), killMessage.c_str(), killMessage.size());
                sockets[indexOfSockets]->send(message);

                sockets[indexOfSockets]->unbind(adr + to_string(childesId[indexOfSockets]));

                childesId.erase(childesId.begin() + indexOfSockets);
                sockets.erase(sockets.begin() + indexOfSockets);

                cout << "Node deleted successfully" << endl;

                break;
            } else {
                string killMessage = command + " " + to_string(id);
                zmq::message_t message(killMessage.size());
                memcpy(message.data(), killMessage.c_str(), killMessage.size());

                sockets[indexOfSockets]->send(message);
                sockets[indexOfSockets]->recv(message);
                string receiveMessage(static_cast<char*>(message.data()), message.size());

                if (receiveMessage[0] == 'O' && receiveMessage[1] == 'K') {
                    cout << receiveMessage << endl;
                    break;
                } else if (receiveMessage == "Error: there isn`t node with this id" &&
                           indexOfSockets == sockets.size() - 1) {
                    cout << receiveMessage << endl;
                    break;
                }
            }
        }
    }
}

void Exec(int childId){
    auto socket = make_unique<zmq::socket_t>(context, ZMQ_REP);

    socket->bind(adr+to_string(childId)); // child_id
    string new_adr = adr+to_string(childId);

    char* adr_ = new char[new_adr.size() + 1];
    memcpy(adr_, new_adr.c_str(), new_adr.size() + 1);

    char* id_ = new char[to_string(childId).size() + 1];
    memcpy(id_, to_string(childId).c_str(), to_string(childId).size() + 1);

    char* args[] = {"./child", adr_, id_, NULL};

    int processId = fork();
    if (processId < 0) {
        cerr << "Unable to create first worker node" << endl;
        childId = 0;
        exit(1);
    } else if (processId == 0) {
        execv("./child", args);
    }
    zmq::message_t message;
    if(socket->recv(message)){
        cout<<"\n";
    }

    childesId.push_back(childId);
    sockets.push_back(std::move(socket));

    string recievedMessage(static_cast<char*>(message.data()), message.size());
    cout << recievedMessage << endl;
    
    delete[] adr_;
    delete[] id_;
}

void CreateNode(){
    int parent, child;
    cin >> child >> parent;

    if(parent==-1){
        if(find(childesId.begin(), childesId.end(), child)!=childesId.end()){
            cout<<"Error: this node already exists\n";
            return;
        }
        Exec(child);
    }else{
        string messageStr = "create " + to_string(child) + " " + to_string(parent);

        for(size_t i=0;i<sockets.size(); ++i){
            zmq::message_t message(messageStr.size());
            memcpy(message.data(), messageStr.c_str(), messageStr.size());
            sockets[i]->send(message);
            sockets[i]->recv(message);
            string recievedMessage(static_cast<char*>(message.data()), message.size());

            cout<< recievedMessage<<"\n";
            break;
        }
    }
}

void ExecFunc() {
    string str, str1;
    vector<string> str_vec;
    getline(cin, str);
    std::istringstream iss(str);
    while(iss>>str1){
        str_vec.push_back(str1);
    }

    string messageString;
    if(str_vec.size()==3)
        messageString = "exec " + str_vec[0] + " " + str_vec[1] + " " + str_vec[2];
    if(str_vec.size()==2)
        messageString = "exec " + str_vec[0] + " " + str_vec[1];

    for (int indexOfSockets{0}; indexOfSockets < sockets.size(); ++indexOfSockets) {

        zmq::message_t message(messageString.size());
        memcpy(message.data(), messageString.c_str(), messageString.size());

        sockets[indexOfSockets]->send(message);
        sockets[indexOfSockets]->recv(message);
        string receiveMessage(static_cast<char*>(message.data()), message.size());

        if (receiveMessage[0] == 'T' && receiveMessage[1] == 'h' && receiveMessage[2] == 'e') {
            cout << receiveMessage << endl;
            break;
        } else if (receiveMessage == "Error: id: Not found" &&
                   indexOfSockets == sockets.size() - 1) {
            cout << receiveMessage << endl;
            break;
        }

    }

}

void funcExit() {
    for (int indexOfSockets{0}; indexOfSockets < sockets.size(); ++indexOfSockets) {

        if (childesId[indexOfSockets]) {
            string killMessage = "Kill";
            zmq::message_t message(killMessage.size());
            memcpy(message.data(), killMessage.c_str(), killMessage.size());

            sockets[indexOfSockets]->send(message);
        }
        sockets[indexOfSockets]->close();

    }

    cout << "All node was deleted" << endl;
    context.close();
    exit(0);
}

void funcPing() {
    int miliseconds;
    cin >> miliseconds;

    if (childesId.empty()) {
        cout << "OK: 0" << endl;
    } else {

        string messageString = "ping " +to_string(miliseconds);

        for (int indexOfSockets{0}; indexOfSockets < sockets.size(); ++indexOfSockets) {

            zmq::message_t message(messageString.size());
            memcpy(message.data(), messageString.c_str(), messageString.size());
            sockets[indexOfSockets]->send(message);
            sockets[indexOfSockets]->recv(message);
            string receiveMessage(static_cast<char*>(message.data()), message.size());

        }
    }
}

int main ()
{
    string command;
    while(cin>>command){
        if(command=="create"){
            CreateNode();
        }
        if(command=="exec"){
            ExecFunc();
        }
        if(command=="exit"){
            funcExit();
        }
        if(command=="kill"){
            funcKill();
        }
        if(command=="ping"){
            funcPing();
        }
    }
}
