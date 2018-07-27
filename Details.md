# Pick-To-Light
Pick-to-Light System is an advanced paperless picking system providing an innovative, streamlined and cost-effective solution to simplify the order fulfillment process in ware- houses or distribution centers


Requirement No 1 – Default Screen
Description Inputs System Power ON or no data from sever
Process Default Screen
Output No display on SSDs

Requirement No 2 – Mode Selection
Description Inputs MODE (INT) Key,
Process Switch between the Node configuration and Operation Mode
Output On alternate press of MODE (INT) key the Node should
toggle between Configuration Mode and Operation Mode
In Operation Mode:
Display should be blank (Default Screen)
In Configuration Mode:
The display should display
U-St


Requirement No 2.1 – Configuration Menu
Description Inputs MODE (INT), CF (SW15) , INC (SW16) , ACK (SW17) Keys
Process Provide a menu to update the stock in server, set the Node ID
Output On press of MODE (INT) Key, Display (SSD) should change to
Configuration Mode
The display should display
U-St
On press of ACK (SWI7) the display should
n-id
Pressing the ACK (SW17) Key repeatedly the menu should
start from beginning again.


Requirement No 3 – Node ID Configuration
Description Inputs MODE (INT), INC (SW15) , CF (SW16) , ACK (SW17) Keys
Process Set the node ID based on the user input
Output Select n-id from Configuration Menu
Press CF (SWI5) Key to enter Node ID. The display should
show
XXXX - Where XXXX is the current Node ID
Press the CF (SW15) Key to choose field
Press INC (SW16) Key to increment number. The number
should roll over after reaching 9
The Node ID should be saved to EEPROM
Press ACK (SW17) to update the new Node ID 

Requirement No 4 – Operation Mode
Description Inputs Server Data
Process Receive and display the data from the server
Output The Display should display the data received from server
Pick Indicator (LED8) should toggle every 500 msecs

Requirement No 5 – Send Picked
`Description Inputs ACK (SW17) key
Process Send the acknowledgement to the server
Output On press of ACK (SW17) the Node should send the
acknowledgement the server
The display should go blank
The Pick Indicator (LED8) should go OFF



Requirement No 5.1– Update the picked items
Description Inputs INC (SW15) and DEC (SW16) Keys
Process Update the item count and send it to the server
Output On press of INC (SW15) Key, the displayed count should be
incremented
On press pf DEC (SW16) Key, the displayed count should be
decremented
On press of ACK (SW17) Key, the Node should send the
acknowledgement the server
The display should go blank
The Pick Indicator (LED8) should go OFF

Requirement No 6 – Update Stock
Description Inputs MODE (INT), INC (SW15) , CF (SW16) , ACK (SW17) Keys
Process Update the new stock arrived and send it to the server
Output Select U-St from Configuration Menu
Press CF (SWI5) Key to enter item count. The display should
show
0000
Press the CF (SW15) Key to choose field
Press INC (SW16) Key to increment number. The number
should roll over after reaching 9
Press ACK (SW17) to transmit data to server.


User Interfaces

The display should be blank after power up
On press of MODE Key the mode should
change to Config Mode. Should display the
menu to update the count to the server or to
configure the Node ID.


By pressing the ACK key you should be able
to scroll the menu

On repeat press of ACK key the menu should
roll over.

On press of the CF Key the current menu
field should be selected.

The current segment should be indicated by
the decimal point of the SSD.

One every press of the CF Key the decimal
point should move indiacting the selected
digit.

The INC Key should be used to increment the
digit on the selected SSD. The digit should increment upto 9 and then roll over to 0 again.

In case of the Node ID setting the new ID should be stored to the EEPROM and in case of
update count the current count should be sent to the server.

Both should happen on press of the ACK key

Wait till the server send any data so that it
can be displayed
Operation Mode (No Data)

The Node should display the data once
received from the server.

Should be possible to increase or decrease
the displayed data to indicate the amount
picked

The Pick Indicator should toggle for 500 msecs.

On press of the ACK Key the picked data should be sent back to the server

Describe the logical characteristics of each interface between the application and other
hardware, software, and communication protocols.

Pick2Light is a client server network topology. The network used in this project is CAN
because of its simplicity and amount of data being transferred.

Board Jumper Settings : 

DIP2: 1 – 7 OFF and 8 ON
DIP1: All OFF
DIP3: All OFF
J5: Connected
J8: Connected
J9: Connected
J10: Connected
K7: CAN Interface (Twisted Pair)

































