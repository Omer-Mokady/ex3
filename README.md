## Ex3 - Advanced Programming 1 Course
__Authors__
* Omer Mokady
* Gal Seidner
#
__Coding Style__

[google coding style](https://google.github.io/styleguide/cppguide.html)
#
__Flight Simulator__

We worked with FlightGear 2019.1.1.

[Download link](https://www.flightgear.org/)

#
__Our Mission__

We got a task of creting parser and lexer, and break a given text file full with made up programming language to tokens.

Later on, we had to interprate the tokens, and create an inheritance based program which taking cate of possible commands and conditions suce as while loops and if statments.

the given programming lanuage we had to process is a lenguage ment to run a flight simulator .

Therefore, we needed to build sockets over TCP/IP protocol, bots server and client side.

In the server side we recieved and maintained flight data given to us from the simulator.

In the client side we updated the simulator based on the instructions found in the given file.

Both sockets and the data manegment runs along the program side by side using multy threading and singelton design pattern.

We also implemented Command pattern to controll all possible commands, and the composite design pattern to maintain the parser that runs the whole flow of the program. 
#
__Goals__

- [x] Create functioning lexer and parser for a given file.

- [X] Create server and client sides for connection with a flight simulator, using sockets over TCP/IP protocol. 

- [X] Make the flight simulator work and the plain to flight!
#
__Needed files__

* txt file - conatains the programming language instructions and commands.
* xml file - conatains the full paths for sending instructions to the simulator. 

note that the xml file should also be inside the simulator protocls on **your** computer for coordination between your code and the simulator.
#
__How to use it__

If you want to use our code to run the simulator, you need to follow the instructions below:

**NOTICE - our code supports multy threading, so if you are working with CLion IDE, you'll need to add the line "set(CMAKE_CXX_FLAGS -pthread)" into the CMakeList.txt, outherwise it won't work!**
1. you need to download the cpp and header files.

2. Save the txt file described under "Needed files" in the CmakeFiles.

3. Download the simulator from the link attached above.

4. inside the simulato, in Settings -> Additioal Settings write to following two lines:
   - --generic=socket,out,10,127.0.0.1,5400,tcp,generic_small (127.0.0.1 - ip address and 5400=port number the simulator needs to connect to, generic_small is the name of the xml file.)
   - --telnet=socket,in,10,127.0.0.1,5402,tcp (127.0.0.1=ip address and 5402=port number that the simulator is listening on.)
5. run the code.

6. press on "Fly!".
