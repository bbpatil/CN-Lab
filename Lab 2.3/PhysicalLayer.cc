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

#include "PhysicalLayer.h"

Define_Module(PhysicalLayer);

void PhysicalLayer::initialize()
{
    fromDLL = gate("fromDLL");
        toDLL = gate("toDLL");
        fromCM = gate("fromCM");
        toCM = gate("toCM");
        address = par("id");
}

void PhysicalLayer::handleMessage(cMessage *msg)
{
    if(address == 1){
        if(msg->getArrivalGate() == fromDLL){
            DL_PDU* dpdu = check_and_cast<DL_PDU*>(msg);
            P_PDU* ppdu = new P_PDU();
            ppdu ->encapsulate(dpdu);
            send(ppdu, toCM);
        }

        else if(msg->getArrivalGate() == fromCM){
            P_PDU* old = check_and_cast<P_PDU*>(msg);
            send(old, toDLL);
        }
    }

    if(address == 2){
        if(msg->getArrivalGate() == fromDLL){
            DL_PDU* dpdu = check_and_cast<DL_PDU*>(msg);
            P_PDU* ppdu = new P_PDU();
            ppdu -> encapsulate(dpdu);
            send(ppdu, toCM);
        }

        else if(msg->getArrivalGate() == fromCM){
            P_PDU* old = check_and_cast<P_PDU*>(msg);
            //DL_PDU* n = new DL_PDU();
            //n = check_and_cast<DL_PDU*>(old->decapsulate());
            send(old, toDLL);
            //delete old;
        }
    }

}
