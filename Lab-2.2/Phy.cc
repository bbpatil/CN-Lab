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

#include "Phy.h"
#include"P_PDU_m.h"
Define_Module(Phy);

void Phy::initialize()
{
    // TODO - Generated method body
}

void Phy::handleMessage(cMessage *msg)
{
    /*cMessage* msg2 = new cMessage();
        std::cout<<"NotSelfMessage(PHY)"<<std::endl;
        if(strcmp("data->phy",getName())==0){
            std::cout<<"data->phy"<<endl;
            send(msg2,"phy->");
        }
        if(strcmp("phy->data",getName())==0){
            std::cout<<"phy->data"<<endl;
            send(msg2,"data->app");
        }
        */

    if(strcmp("Din",msg->getArrivalGate()->getBaseName())==0){
        DL_PDU* message = dynamic_cast<DL_PDU*>(msg);
        P_PDU *myMessage = new P_PDU();
        myMessage->encapsulate(message);
        send(myMessage,"out");
    }
    else{
        DL_PDU* message = dynamic_cast<DL_PDU*>(msg);
        A_PDU* myMessage = dynamic_cast<A_PDU*>(message->decapsulate());
        send(myMessage,"Pin");
    }
}
