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
//
// TODO documentation
//
network Network
{
    submodules:
        A: NlNode{
        	id = 1;
        }
        B: NlNode{
        	id = 2;
        }
        C: NlNode {
           id = 3;
        }
        D: NlNode{
        	id = 4;
        }
        E: NlNode{
        	id = 5;
        }
    connections allowunconnected:

        A.toX --> B.fromX;
        B.toX --> A.fromX;
        B.toY --> C.fromX;
        C.toX --> B.fromY;
        A.toZ --> D.fromX;
        D.toX --> A.fromZ;
        C.toY --> A.fromY;
        A.toY --> C.fromY;
        C.toZ --> E.fromX;
        E.toX --> C.fromZ;
        B.toZ --> E.fromY;
        E.toY --> B.fromZ;

}

