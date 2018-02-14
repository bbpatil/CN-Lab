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
    	int id;
    @display("bgb=206,246");
    gates:
        input in;
        output out;

    submodules:
        data: Data {
            @display("p=103,91");
        }
        phy: Phy {
            @display("p=103,166");
        }
        app: App {

            @display("p=103,29");
        }
    connections:
        in --> phy.Nin;
        phy.Dout --> data.Ain;
        app.Dout --> data.Ain;
        data.Aout --> app.Din;
        data.Pout --> phy.Din;
        phy.Nout --> out;
}
