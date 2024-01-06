#include <zmq.h>
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
#include <thread>
#include <map>
#include <signal.h>
#include <chrono>
using namespace std::chrono_literals;





using namespace std;

string adr;
string adrChild = "tcp://127.0.0.1:300";
zmq::context_t context(1);
zmq::socket_t mainSocket(context, ZMQ_REQ);
zmq::context_t contextChild(1);
zmq::socket_t childSocket(contextChild, ZMQ_REP);
int idThisNode, childNodeId;
bool no_exit = true;
map<string, int> dict;

void sendMessage(const string& messageString, zmq::socket_t& socket) {
    zmq::message_t messageBack(messageString.size());
    memcpy(messageBack.data(), messageString.c_str(), messageString.size());

    if (!socket.send(messageBack)) {
        cerr << "Error: can't send message from node with pid " << getpid() << endl;
    }
}

void funcKill(string receivedMessage) {
    int idProcToKill;
    string command;
    string copy = receivedMessage;

    std::stringstream iss(receivedMessage);
    iss>>command;
    iss>>idProcToKill;

    if (childNodeId == 0) {
        sendMessage("Error: there isn`t node with this id child", mainSocket);
    } else {
        if (childNodeId == idProcToKill) {
            sendMessage("OK: " + to_string(childNodeId), mainSocket);
            sendMessage("DIE", childSocket);
            childSocket.unbind(adrChild);
            adrChild = "tcp://127.0.0.1:300";
            childNodeId = 0;
        } else {
            zmq::message_t message(copy.size());
            memcpy(message.data(), copy.c_str(), copy.size());
            childSocket.send(message);
            childSocket.recv(message);
            mainSocket.send(message);
        }
    }
}


void Create(string recievedMessage){
    string command;
    int recievedChild, recievedParent;
    std::istringstream iss(recievedMessage); 
    iss>>command;
    iss>>recievedChild;
    iss>>recievedParent;

    if(childNodeId==0 && recievedParent==idThisNode){
        childNodeId = recievedChild;
        childSocket.bind(adrChild + to_string(childNodeId));
        adrChild += to_string(childNodeId);

        
        char* adrChildTmp = new char[adrChild.size() + 1];
        memcpy(adrChildTmp, adrChild.c_str(), adrChild.size() + 1);
        char* childIdTmp = new char[to_string(childNodeId).size() + 1];
        memcpy(childIdTmp, to_string(childNodeId).c_str(), to_string(childNodeId).size() + 1);
        char* args[] = {"./child", adrChildTmp, childIdTmp, NULL};
        int processId = fork();

        if(processId==0){
            execv("./child", args);
        } else if (processId < 0) {
            cerr << "Error in forking in node with pid: " << getpid() << endl;
        } else {
            zmq::message_t messageFromNode;

            if (!childSocket.recv(messageFromNode)) {
                cerr << "Error: can't receive message from child node in node with pid:" << getpid()
                         << endl;
            }

            if (!mainSocket.send(messageFromNode)) {
                cerr << "Error: can't send message to main node from node with pid:" << getpid() << endl;
            }
        }
        delete[] adrChildTmp;
        delete[] childIdTmp;
    }

    else if (childNodeId == 0 && recievedParent != idThisNode) {
        sendMessage("Error: there is no such parent", mainSocket);
    } else if (childNodeId != 0 && recievedParent == idThisNode) {
        sendMessage("Error: this parent already has a child", mainSocket);
    } else {
        sendMessage(recievedMessage, childSocket);
        zmq::message_t message;
        if (!childSocket.recv(message)) {
            cerr << "Error: can't receive message from child node in node with pid: " << getpid() << endl;
        }
        if (!mainSocket.send(message)) {
            cerr << "Error: can't send message to main node from node with pid: " << getpid() << endl;
        }
    }
}   


void Exec(string receivedMessage) {
    int idProc;
    string com;
    std::istringstream iss1(receivedMessage); 
    iss1>>com;
    iss1>>idProc;
    string returnMessage;

    if (idProc == idThisNode) {
        std::this_thread::sleep_for(1s);
        thread workThread([&, receivedMessage](){
            vector<string> commands;
            std::istringstream iss2(receivedMessage); 
            string command;
            string answer;
            while(iss2>>command){
                commands.push_back(command);
            }
            if(commands.size()==4){
                dict[commands[2]] = stoi(commands[3]);
                returnMessage = "The child process saved data";
            }
            if(commands.size()==3){
                answer = "OK:" + to_string(idThisNode)+": ";
                answer+=to_string(dict[commands[2]]);
                returnMessage = "The child process give data succesfully";
            }
            std::cout <<"\n"<<answer<< endl;
        });

        workThread.join();

        sendMessage(returnMessage, mainSocket);

    } else {

        if (childNodeId == 0) {
            sendMessage("Error: id: Not found", mainSocket);
        } else {
            zmq::message_t message(receivedMessage.size());
            memcpy(message.data(), receivedMessage.c_str(), receivedMessage.size());

            if (!childSocket.send(message)) {
                cerr << "Error: can't send message to child node from node with pid: " << getpid() << endl;
            }
            if (!childSocket.recv(message)) {
                cerr << "Error: can't receive message from child node in node with pid: " << getpid() << endl;
            }
            if (!mainSocket.send(message)) {
                cerr << "Error: can't send message to main node from node with pid: " << getpid() << endl;
            }
        }
    }
}

void funcPing(string receivedMessage) {
    string copyMessage = receivedMessage;
    int miliseconds;
    string command;

    std::stringstream iss(receivedMessage);
    iss>>command;
    iss>>miliseconds;
    int seconds =miliseconds/1000;
    thread ping_thread([&](){
        while(no_exit){
            sleep(seconds);
            cout<<idThisNode<<": OK\n";
        }
    });

    ping_thread.detach();

        if (childNodeId == 0) {
            sendMessage("OK: 0", mainSocket);
        } else {
            zmq::message_t message(copyMessage.size());
            memcpy(message.data(), copyMessage.c_str(), copyMessage.size());
            childSocket.send(message);
            childSocket.recv(message);
            mainSocket.send(message);
        }
}

int main (int argc, char* argv[])
{
    adr = argv[1];
    mainSocket.connect(argv[1]);
    idThisNode = std::stoi(argv[2]);

    sendMessage("OK: " + to_string(getpid()), mainSocket);
    childNodeId = 0;
    while(1){
        zmq::message_t messageMain;
        mainSocket.recv(messageMain);
        string receivedMessage(static_cast<char*>(messageMain.data()), messageMain.size());
        string command;

        std::istringstream iss(receivedMessage); 
        iss>>command;
        if(command=="create"){
            Create(receivedMessage);
        }else if(command=="exec"){
            Exec(receivedMessage);
        }else if(command=="ping"){
            funcPing(receivedMessage);
        }else if(command=="KillYourself"){
            funcKill(receivedMessage);
        }else if(command== "Kill"){
            if(childNodeId!=0){
                sendMessage("Kill", childSocket);
                childSocket.unbind(adrChild);   
            }
            mainSocket.unbind(adr);
            no_exit=false;
            usleep(1000000);
            return 0;
        }
    }
}
