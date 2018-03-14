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

Define_Module(Node);

void Node::initialize()
{
    inG = gate("in");
    outG = gate("out");
    addr = par("id");
    if(addr == 1){
            cMessage* event = new cMessage();
            scheduleAt(0,event);
    }
}

void Node::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
            Pkt* newMsg = new Pkt();
            newMsg->setId(1);
            newMsg->setSrc(addr);
            newMsg->setDest(2);
            newMsg->setType(msgType::Data);
            send(newMsg,outG);
    }
    else{
        Pkt* oldMsg = check_and_cast<Pkt*>(msg);
        if (oldMsg->getType()==msgType::Data) {

            Pkt* newMsg = new Pkt();
            newMsg->setId(oldMsg->getId());
            newMsg->setSrc(addr);
            newMsg->setDest(oldMsg->getSrc());
            newMsg->setType(msgType::Ack);
            send(newMsg,outG);
        }
        if (oldMsg->getType()==msgType::Ack ) {

            Pkt* newMsg = new Pkt();
            newMsg->setId(oldMsg->getId()+1);
            newMsg->setSrc(addr);
            newMsg->setDest(oldMsg->getSrc());
            newMsg->setType(msgType::Data);

            count++;
            if(count!=10){
                send(newMsg,outG);
            }

        }
    }
}
