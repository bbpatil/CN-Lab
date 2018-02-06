//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "node.h"
#include<packet_m.h>
using namespace std;
using namespace omnetpp;

Define_Module(Node);

void Node::initialize()
{
    in=gate("in");
    out=gate("out");
    //cMessage* msg = new cMessage();
    EV << "self";
    //scheduleAt(msg,0);

    if(strcmp("n1",getName())==0){
            cMessage* msg = new cMessage();
            scheduleAt(0,msg);
    }

    /*if(strcmp("n1",getName())==0){
        //cMessage *msg = new cMessage("testMsg");
        send(msg,"out");
    }*/
}

void Node::handleMessage(cMessage *msg)
{
    cMessage* msg2 = new cMessage();
    if(msg->isSelfMessage()){
        EV << "sample";
        //std::cout<<"selfMessage"<<std::endl;
        //send(msg,"out");
        //cout<<""
        delete msg;

        send(msg2,out);
    }
    else{
        std::cout<<"NotSelfMessage"<<std::endl;
        //send(msg,"out");
        send(msg2,out);
    }
}
