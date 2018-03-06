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

#include "ApplicationLayer.h"

Define_Module(ApplicationLayer);

void ApplicationLayer::initialize()
{   count=0;
    fromDL = gate("fromDL");
    toDL = gate("toDL");
    address = par("id");
    if(address == 1){
        cMessage* event= new cMessage();
        count++;
        scheduleAt(0,event);

    }
}

void ApplicationLayer::handleMessage(cMessage *msg)
{

    if(msg -> isSelfMessage()){
        A_PDU* a_pdu = new A_PDU();
        a_pdu -> setId(++id);
        a_pdu -> setType(1);
        send(a_pdu, toDL);
    }

    else if(address == 2){
        DL_PDU* oldMsg = check_and_cast<DL_PDU*>(msg);
        A_PDU* newMsg = new A_PDU();
        newMsg -> setId(oldMsg -> getId());
        newMsg -> setType(2);
        send(newMsg,toDL);
    }

    else if(address == 1){
        A_PDU* newMsg = new A_PDU();
        //DL_PDU* oldMsg = check_and_cast<DL_PDU*>(msg);
        newMsg -> setType(1);
        newMsg -> setId(++id);
        count++;

        if(count <= 10){
            send(newMsg, toDL);
        }
    }

}
