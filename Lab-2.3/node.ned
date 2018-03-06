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

module Node
{
    parameters:
        int nid;
        @display("bgb=572,298");
    gates:
        input fromNode;
        output toNode;
    submodules:
        AL: ApplicationLayer {
            id = nid;
            @display("p=35,92");
        }
        DL: DataLinkLayer {
            id = nid;
            @display("p=220,92");
        }
        PL: PhysicalLayer {
            id = nid;
            @display("p=426,92");
        }
    connections:
        PL.toCM --> toNode;
        PL.fromCM <-- fromNode;
        AL.toDL --> DL.fromAL;
        AL.fromDL <-- DL.toAL;
        DL.toPL --> PL.fromDLL;
        DL.fromPL <-- PL.toDLL;
}
