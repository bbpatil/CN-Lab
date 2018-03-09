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
int count=10;

void Node::initialize()
{
    inGate=gate("in");                  // intializing parameters from node.h file.
    outGate=gate("out");
    address=par("id");
    //count=9;                            // if count==0 we stop.
    if(address==1){
        cMessage* event=new cMessage();
        scheduleAt(0,event);
    }
}

void Node::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(msg->isSelfMessage()){
        if (uniform(0, 1) < 0.5) {
                        EV << "\"Losing\" message.\n";
                        EV << "value of count"<<count<<"\n";
                        bubble("message lost");  // making animation more informative...
                        delete msg;
                        // still we send message cause we want to send 10 messages if count is not zero.
                        if(count>0){
                            EV << "value of count "<<count<<"\n";
                            Pckts* p=new Pckts();
                            p->setId(1);
                            p->setSrc(1);
                            p->setDest(2);
                            p->setType(0);
                            send(p,outGate);                // send packet.
                        }
        }
        else {
            count--;
            EV << "value of count "<<count<<"\n";
            if(count>0){
                        Pckts* p=new Pckts();
                        p->setId(1);
                        p->setSrc(1);
                        p->setDest(2);
                        p->setType(0);
                        send(p,outGate);                // send packet.
            }
        }
    }
    else{
        EV << "From else count "<<count<<"\n";
        Pckts* m=check_and_cast<Pckts*>(msg);
        if(m->getType()==0){    // this means type is data.
            // we are at node 2 we need to do random delay.
            if(m->isSelfMessage()){

                Pckts* a=new Pckts();
                a->setId(2);
                a->setSrc(2);
                a->setDest(1);
                     a->setType(1);      // cause now we send ack.
                                send(a,outGate);
            }
            else{
                simtime_t delay = rand()%10;
                EV << "Message arrived, starting to wait " << delay << " secs...\n";
                scheduleAt(simTime()+delay, m);
            }
        }
        else{
           /* // we received an ack and it is for node 1.

                if(count>0){
                    count--;
                    EV << "IF count"<<count<<"...\n";
                    Pckts* p=new Pckts();
                    p->setId(10-count);
                    p->setSrc(1);
                    p->setDest(2);
                    p->setType(0);
                    send(p,outGate);
                }
                else{
                    EV << "we are done........\n";
                }
                */
        }
    }
}
