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

#include "Data.h"


using namespace std;
using namespace omnetpp;

Define_Module(Data);

void Data::initialize()
{
    // TODO - Generated method body
}

void Data::handleMessage(cMessage *msg)
{
    cMessage* msg2 = new cMessage();
    std::cout<<"NotSelfMessage(DATA)"<<std::endl;
    if(strcmp("app->data",getName())==0){
        std::cout<<"app->data"<<endl;
        send(msg2,"data->phy");
    }
    if(strcmp("phy->data",getName())==0){
        std::cout<<"phy->data"<<endl;
        send(msg2,"data->app");
    }
}
