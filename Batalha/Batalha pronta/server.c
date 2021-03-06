 //Battleship Server
            #include <stdio.h> //For basic I/O operations
          //  #include <conio.h>      //For _getch(); to pause the program
//            #include <winsock2.h>   //For network operations
  //          #include <windows.h>    //Needed by winsock
//            #include <ws2tcpip.h>   //Used for and addrinfo related functions
            #include <time.h>       //For rand()
            #define BUFLEN 64       //Default buffer length
            #define PORT "3490"     //Port to be used

            #pragma warning(push)
            #pragma warning(disable:4996)

//            using namespace std;

            //Global ship names and corresponding letters
            char *Shipnames[5] = {
                "Aircraft Carrier",
                "BattleShip",
                "Destroyer",
                "Submarine",
                "patrol Boat",
            };

            char Letter[5] = { 'A', 'B', 'D', 'S', 'P' };

            struct Ship
            {
                //To keep track of hits
                char Hitbox[5];

                //X & Y positions
                int X;
                int Y;

                //Length of ship
                int len;

                //Direction
                //true = vertical (Y)
                //false = horizontal (X)
                bool Direction;
            };

            //Translates letter cords to numbers
            //eg: A5 = 15, B7 = 27, E3 = 53
            int TransLettoNumb(char *Cord)
            {
                char Letters[8] = {
                    'A',
                    'B',
                    'C',
                    'D',
                    'E',
                    'F',
                    'G',
                    'H',
                };

                char Lowercase[8] = {
                    'a',
                    'b',
                    'c',
                    'd',
                    'e',
                    'f',
                    'g',
                    'h',
                };

                //Check through upper case
                for (int x = 0; x < 8; x++)
                {
                    if (Cord[0] == Letters[x])
                        return x + 1;
                }

                //check through lower case
                for (int x = 0; x < 8; x++)
                {
                    if (Cord[0] == Lowercase[x])
                        return x + 1;
                }

                return 0;
            }

            bool sendl(int sockfd, bool hit)
            {
                char *Line = new char[BUFLEN];

                if (hit)
                {
                    Line = "Hit!";
                }
                else
                {
                    Line = "Miss!";
                    cout << "Miss!" << endl;
                }

                bool var = true;

                if (send(sockfd, Line, strlen(Line), 0) == SOCKET_ERROR)
                    var = false;

                return var;
            }

            //For checking if the client hit a boat
            bool Checkhit(Ship ships[], char Cord[], int sockfd)
            {
                //Translate cords to ints
                int Ycord = (Cord[1] - 48);
                int Xcord = TransLettoNumb(Cord);

                //Length of ship
                int Len;

                //For each ship
                for (int n = 0; n < 4; n++)
                {
                    //Set length
                    if (n == 0)
                        Len = 5;
                    else if (n == 1)
                        Len = 4;
                    else if (n == 2)
                        Len = 3;
                    else if (n == 3)
                        Len = 3;
                    else if (n == 4)
                        Len = 2;

                        //loop through the hitbox
                        for (int i = 0; i < Len; i++)
                        {
                            //If the x cord equals the ships cords plus hitbox (i), test y cords
                            if (Xcord == (ships[n].X + i))
                            {
                                //loop through the hitbox
                                for (int i = 0; i < Len; i++)
                                {
                                    //If the y cord equals the ships cords plus hitbox (i)
                                    if (Ycord == (ships[n].X + i))
                                    {
                                        //the ship was hit, update the hitbox
                                        ships[n].Hitbox[i] = 'X';
                                        {
                                            cout << Shipnames[n] << " was hit!"<< endl;

                                            //send hit
                                            sendl(sockfd, true);

                                            //Send which ship was hit
                                            send(sockfd, Shipnames[n], strlen(Shipnames[n]), 0);

                                            return true;
                                        }
                    }
                    }
                    }
                    }
                    }

                //The ship was not hit
                return false;
            }

            void PlaceShips(Ship ships[])
            {
                int randnumb;

                //For each ship
                for (int n = 0; n < 5; n++)
                {
                    //Randomize direction
                    randnumb = rand() % 2;

                    if (randnumb == 1)
                        ships[n].Direction = true;
                    else
                        ships[n].Direction = false;

                    do
                    {
                        randnumb = 0;

                        //randomize x
                        ships[n].X = rand() % 8 + 1;

                        //randomize y
                        ships[n].Y = rand() % 8 + 1;

                        //If direction is true, check y
                        if (ships[n].Direction)
                        {
                            //If the ship hit the wall
                            if ((ships[n].Y + ships[n].len) > 8)
                                randnumb = 1;
                        }
                        else //else check x
                        {
                            //If the ship hit the wall
                            if ((ships[n].X + ships[n].len) > 8)
                                randnumb = 1;
                        }

                    } while (randnumb > 0);
                }
            }

            int main()
            {
                //Quit flag
                bool quit = false;

                //Initialize random seed
                srand(time(NULL));

                //Declare ships
                Ship ships[5];

                //Initialize ship lengths
                ships[1].len = 5;
                ships[2].len = 4;
                ships[3].len = 3;
                ships[4].len = 3;
                ships[5].len = 2;

                //Hit counter
                int HitCounter = 0;

                //Declare some winsock variables
                int status;                                 //To keep track of errors
                WSADATA wsaData;                            //For winsock initialization
                SOCKET ListenSocket = INVALID_SOCKET;       //Socket for listening on
                SOCKET ClientSocket = INVALID_SOCKET;       //Socket for communicating with client
                struct addrinfo *result = NULL;             //struct to hold address information
                struct addrinfo address;                    //struct to hold connection information
                char recvbuf[BUFLEN];                       //Buffer for receiving information
                char sendbuf[BUFLEN];                       //Buffer for sending

                // Initialize Winsock
                status = WSAStartup(MAKEWORD(2, 2), &wsaData);
                if (status != 0)
                {
                    cout << "failed to initialize winsock" << endl;
                    _getch();
                    return 1;
                }

                ZeroMemory(&address, sizeof(address));
                address.ai_family = AF_INET;
                address.ai_socktype = SOCK_STREAM;
                address.ai_protocol = IPPROTO_TCP;
                address.ai_flags = AI_PASSIVE;

                //Get IP and port info
                status = getaddrinfo(NULL, PORT, &address, &result);
                if (status != 0)
                {
                    cout << "getaddrinfo failed with error: " << WSAGetLastError() << endl;
                    freeaddrinfo(result);
                    _getch();
                    return 1;
                }

                //Create a socket for listening
                ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
                if (ListenSocket == INVALID_SOCKET)
                {
                    cout << "failed to create socket with error: " << WSAGetLastError() << endl;
                    freeaddrinfo(result);
                    _getch();
                    return 1;
                }

                //Bind to the port
                status = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
                if (status == SOCKET_ERROR)
                {
                    cout << "failed with error " << WSAGetLastError() << " binding to port " << PORT << endl;
                    freeaddrinfo(result);
                    _getch();
                    return 1;
                }
                else cout << "binded to port " << PORT << endl;

                //Done with the results
                freeaddrinfo(result);

                //Server loop
                while (quit == false)
                {
                    //Listening for client connections
                    //5 is the amount of clients that can wait on queue
                    status = listen(ListenSocket, 5);
                    if (status == SOCKET_ERROR)
                    {
                        cout << "listen() failed with error: " << WSAGetLastError() << endl;
                        closesocket(ListenSocket);
                        WSACleanup();
                        _getch();
                        return 0;
                    }

                    //Accept client connection
                    ClientSocket = accept(ListenSocket, NULL, NULL);
                    if (ClientSocket == INVALID_SOCKET)
                    {
                        cout << "accept failed with error: " << WSAGetLastError() << endl;
                        closesocket(ClientSocket);
                        WSACleanup();
                        _getch();
                        return 1;
                    }
                    else cout << "connection accepted from client" << endl;

                    //set up game...

                    int cord;

                    //Initialize ship hitboxes
                    for (int x = 0; x <5; x++)
                    {
                        //Initialize hitbox
                        for (int i = 0; i<5; i++)
                            ships[x].Hitbox[i] = Letter[x];
                    }


                    //Randomize ship locations
                    PlaceShips(ships);

                    status = 1;

                    //Game loop
                    while (status > 0)
                    {
                        ///Receive client's bomb cords
                        status = recv(ClientSocket, recvbuf, BUFLEN, 0);

                        cout << endl << "client bombed square " << recvbuf[0] << recvbuf[1] << endl;

                        //Check if it was a hit or miss and reply to client
                        if (!Checkhit(ships, recvbuf, ClientSocket))
                            sendl(ClientSocket, false);
                        else
                            HitCounter++;

                        status = 0;

                        //generate random cord
                        do
                        {
                            cord = rand() % 8;

                            if (cord >= 0 && cord < 9)
                                sendbuf[0] = (cord + 65);
                            else
                                status = 1;

                            cord = rand() % 8;
                            if (cord >= 0 && cord < 9)
                                sendbuf[1] = (cord + 49);
                            else
                                status = 1;
                        } while (status == 1);

                        //send cord guess
                        send(ClientSocket, sendbuf, BUFLEN, 0);

                        cout << endl << "guessing " << sendbuf[0] << sendbuf[1] << endl;

                        //recv hit or miss
                        status = recv(ClientSocket, recvbuf, BUFLEN, 0);

                        //Display hit/miss
                        for (int x = 0; x < status; x++)
                        {
                            cout << recvbuf[x];
                        }

                        cout << endl;

                        //If all the boxes have been hit
                        if (HitCounter == 17)
                        {
                            //send game complete
                            strcpy(sendbuf, "game complete!");
                            cout << sendbuf << endl;
                            send(ClientSocket, sendbuf, BUFLEN, 0);
                        }
                    }
                    cout << "client disconnected" << endl;
                }

                _getch();
                return 0;
            }
