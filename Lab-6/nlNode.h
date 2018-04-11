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

#ifndef __NETWORKLAYER_NLNODE_H_
#define __NETWORKLAYER_NLNODE_H_

#include <omnetpp.h>
#include <Pkt_m.h>
#include <map>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class NlNode : public cSimpleModule
{
    int id;
    int mid;
    int src;
    int dest;
    int counter;
    cGate* toX;
    cGate* fromX;
    cGate* toY;
    cGate* fromY;
    cGate* toZ;
    cGate* fromZ;
    //int CostNode[5];

    std::map<int,cGate*> GateMap;
    std::map<int,cGate*> Basic;
    std::map<int,cGate*> Modify;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
