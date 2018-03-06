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

#include "DataLinkLayer.h"

Define_Module(DataLinkLayer);

void DataLinkLayer::initialize()
{
    fromAL = gate("fromAL");
    toAL = gate("toAL");
    fromPL = gate("fromPL");
    toPL = gate("toPL");
    address = par("id");
}

void DataLinkLayer::handleMessage(cMessage *msg)
{
    if(address == 1){
        if(msg->getArrivalGate() == fromAL){
            A_PDU* apdu = check_and_cast<A_PDU*>(msg);
            DL_PDU* dlpdu = new DL_PDU();
            dlpdu->encapsulate(apdu);
            dlpdu -> setId(apdu -> getId() % 2);
            send(dlpdu, toPL);
        }

        else if(msg->getArrivalGate() == fromPL){
            P_PDU* ppdu = check_and_cast<P_PDU*>(msg);
            DL_PDU* dlpdu = new DL_PDU();
            dlpdu = check_and_cast<DL_PDU*>(ppdu->decapsulate());
            send(dlpdu, toAL);
        }
    }

    if(address == 2){
        if(msg->getArrivalGate() == fromAL){
                A_PDU* apdu = check_and_cast<A_PDU*>(msg);
                DL_PDU* dlpdu = new DL_PDU();
                dlpdu -> encapsulate(apdu);
                send(dlpdu, toPL);
            }

            else if(msg->getArrivalGate() == fromPL){
                P_PDU* ppdu = check_and_cast<P_PDU*>(msg);
                DL_PDU* dlpdu = new DL_PDU();
                dlpdu = check_and_cast<DL_PDU*>(ppdu->decapsulate());
                send(dlpdu, toAL);
                delete ppdu;
            }
    }


}
