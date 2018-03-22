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

#include "nlNode.h"

Define_Module(NlNode);

void NlNode::initialize()
{
    counter = 0;
    id = par("id");
    mid = 1;
    src = 2;
    dest = intuniform(1,5);
    while(dest == src)
    {
        dest = intuniform(1,5);
    }

    toX = gate("toX");
    fromX = gate("fromX");
    toY = gate("toY");
    fromY = gate("fromY");
    toZ = gate("toZ");
    fromZ = gate("fromZ");

    if(id == 1)
    {
        GateMap.insert ( std::pair<int,cGate*>(2,toX) );
        GateMap.insert ( std::pair<int,cGate*>(3,toY) );
        GateMap.insert ( std::pair<int,cGate*>(4,toZ) );
        GateMap.insert ( std::pair<int,cGate*>(5,toY) );

    }
    if(id == 2)
    {
        GateMap.insert ( std::pair<int,cGate*>(1,toX) );
        GateMap.insert ( std::pair<int,cGate*>(3,toY) );
        GateMap.insert ( std::pair<int,cGate*>(4,toX) );
        GateMap.insert ( std::pair<int,cGate*>(5,toZ) );

    }
    if(id == 3)
    {

        GateMap.insert ( std::pair<int,cGate*>(1,toY) );
        GateMap.insert ( std::pair<int,cGate*>(2,toX) );
        GateMap.insert ( std::pair<int,cGate*>(4,toY) );
        GateMap.insert ( std::pair<int,cGate*>(5,toZ) );


    }
    if(id == 4)
    {
        GateMap.insert ( std::pair<int,cGate*>(1,toX) );
        GateMap.insert ( std::pair<int,cGate*>(2,toX) );
        GateMap.insert ( std::pair<int,cGate*>(3,toX) );
        GateMap.insert ( std::pair<int,cGate*>(5,toX) );

    }
    if(id == 5)
    {
        GateMap.insert ( std::pair<int,cGate*>(1,toX) );
        GateMap.insert ( std::pair<int,cGate*>(2,toY) );
        GateMap.insert ( std::pair<int,cGate*>(3,toX) );
        GateMap.insert ( std::pair<int,cGate*>(4,toX) );
    }

    if(id == src)
    {
        cMessage* msg = new cMessage();
        scheduleAt(0,msg);

    }
}
void NlNode::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
       Pkt* newmsg = new Pkt();
       newmsg->setMid(mid%2);
       newmsg->setSrc(src);
       newmsg->setDest(dest);
       newmsg->setMsgType(PktType::Data);
       send(newmsg,GateMap.find(dest)->second);
       EV<<"SRC :"<<src<<endl;
       EV<<"Dest : "<<dest<<endl;

    }
    else
    {
        Pkt* oldMsg = check_and_cast<Pkt*>(msg);
        if(id != oldMsg->getDest())
        {
           Pkt* newmsg = new Pkt();
           newmsg->setMid(oldMsg->getMid());
           newmsg->setSrc(oldMsg->getSrc());
           newmsg->setDest(oldMsg->getDest());
           newmsg->setMsgType(oldMsg->getMsgType());
           send(newmsg,GateMap.find(newmsg->getDest())->second);
        }
        if(id == oldMsg->getDest())
        {

            if(oldMsg->getMsgType() == PktType::Data)
            {
               Pkt* newmsg = new Pkt();
               newmsg->setMid(oldMsg->getMid()+1);
               newmsg->setSrc(oldMsg->getDest());
               newmsg->setDest(oldMsg->getSrc());
               newmsg->setMsgType(PktType::Ack);
               send(newmsg,GateMap.find(newmsg->getDest())->second);
               delete(msg);
            }
            else
            {
                if(counter >= 10)
                    delete(msg);
                else
                {
                    counter++;
                    EV<<"Counter :: "<<counter<<endl;
                    dest = intuniform(1,5);
                    while(dest == src)
                    {
                        dest = intuniform(1,5);
                    }
                   Pkt* newmsg = new Pkt();
                   newmsg->setMid((oldMsg->getMid()+1)%2);
                   newmsg->setSrc(src);
                   newmsg->setDest(dest);
                   newmsg->setMsgType(PktType::Data);
                   send(newmsg,GateMap.find(newmsg->getDest())->second);
                   EV<<"SRC :"<<src<<endl;
                   EV<<"Dest : "<<dest<<endl;
                   delete(msg);
                }
            }

        }
    }
}
