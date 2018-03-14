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

network TwoNode
{
    @display("bgb=301,320");
    submodules:
        Node1: Node {
            @display("p=60,68");
            id = 1;
        }
        Node2: Node {
            @display("is=vl;p=235,68");
        	id = 2;
        }
    connections:
        Node1.out --> {  delay = 100ms; } --> Node2.in;
        Node1.in <-- {  delay = 100ms; } <-- Node2.out;
}
