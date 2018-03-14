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

#include "application.h"
#include "string.h"

Define_Module(Application);

void Application::initialize()
{
    from_dl = gate("from_dl");
    to_dl = gate("to_dl");
    id = par("aid");
    count = par("count");
    if(id == 1){
        cMessage* start = new cMessage();
        scheduleAt(0, start);
        count++;
    }
}

void Application::handleMessage(cMessage *msg)
{
    if(msg -> isSelfMessage()){
        A_PDU* a = new A_PDU();
        a->setType("Data");
        send(a, to_dl);
    } else {
        A_PDU* a = check_and_cast<A_PDU*>(msg);
        if(strcmp(a->getType(),"Data") == 0){
            A_PDU* a = new A_PDU();
            a->setType("ACK");
            send(a, to_dl);
        } else {
            if(count <= 10){
                A_PDU* a = new A_PDU();
                a->setType("Data");
                send(a, to_dl);
                count++;
            }
        }
    }
}
