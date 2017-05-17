//Battleship Client
            #include <iostream>     //For basic I/O operations
            #include <conio.h>      //For _getch(); to pause the program
            #include <winsock2.h>   //For network operations
            #include <windows.h>    //Needed by winsock
            #include <ws2tcpip.h>   //Used for and addrinfo related functions
            #include <string>       //For string functions
            #include <time.h>       //For rand() functions
            #define BUFLEN 64       //Default buffer length
            #define PORT "3490"     //Port to be used

            using namespace std;

            //Global ship names and corresponding letters
            string Shipnames[5] = {
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

                //the length of the ship
                int len;

                //X & Y positions
                int X;
                int Y;

                //Direction
                //true = vertical (Y)
                //false = horizontal (X)
                bool Direction;
            };

            bool SendLine(int sockfd, string desc)
            {
                char *Text = new char[BUFLEN];

                cout << desc << endl;
                cin.getline(Text, BUFLEN, '\n');

                if (strcmp(Text, "V") == 0 || strcmp(Text, "v") == 0)
                {
                    delete[] Text;
                    return true;
                }

                if (send(sockfd, Text, BUFLEN, 0) == SOCKET_ERROR)
                    cout << "server down" << endl;

                delete[] Text;
                return false;
            }

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
                        return x+1;
                }

                //check through lower case
                for (int x = 0; x < 8; x++)
                {
                    if (Cord[0] == Lowercase[x])
                        return x+1;
                }

                return 0;
            }

            void UpdateShipGrid(char Grid[8][8], Ship ships[])
            {


            }

            //For checking if the server hit a boat
            bool Checkhit(Ship ships[], char Cord[], char ShipGrid[8][8])
            {
                //Translate cords to ints
                int Xcord = TransLettoNumb(Cord);
                int Ycord = (Cord[1] - 48); //we -48 to convert from ascii value

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
                                    //the ship was hit, update the hitbox and grid
                                    ships[n].Hitbox[i] = 'X';
                                    UpdateShipGrid(ShipGrid, ships);
                                    return true;
                                }
                            }
                        }
                    }
                }

                //The ship was not hit
                return false;
            }

            bool sendl(int sockfd, bool hit)
            {
                char *Line = new char[BUFLEN];

                if (hit)
                {
                    Line = "Hit!";
                    cout << "Hit!" << endl;
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

            void DisplayGrid(char GridA[8][8], char GridB[8][8])
            {
                cout << "     Hit Grid          Ship Grid   " << endl;
                cout << "  A B C D E F G H   A B C D E F G H" << endl;
                for (int n = 1; n < 9; n++)
                {
                    cout << n << " ";

                    for (int i = 0; i < 8; i++)
                    {
                        cout << GridA[n][i] << " ";
                    }

                    cout << "| ";

                    for (int t = 0; t < 8; t++)
                    {
                        cout << GridB[n][t] << " ";
                    }
                    cout << endl;
                }
            }

            void InitGrid(char grid[8][8], Ship ships[])
            {
                //For the first dimension (x)
                for (int n = 0; n < 9; n++)
                {
                    //For the second dimension (y)
                    for (int i = 0; i < 9; i++)
                    {
                        //Give the box an empty space
                        grid[i][n] = ' ';
                    }

                }
            }

            void PlaceShips(Ship ships[], char Grid[8][8])
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
                            else
                            {
                                //Place each hitbox on grid
                                for (int i = 0; i < ships[n].len; i++)
                                    Grid[ships[n].X][(ships[n].Y + i)] = ships[n].Hitbox[i];
                            }
                        }
                        else //else check x
                        {
                            //If the ship hit the wall
                            if ((ships[n].X + ships[n].len) > 8)
                                randnumb = 1;
                            else
                            {
                                //Place each hitbox on grid
                                for (int i = 0; i < ships[n].len; i++)
                                    Grid[(ships[n].X + i)][ships[n].Y] = ships[n].Hitbox[i];
                            }

                        }

                    } while (randnumb > 0);
                }
            }

            int main(int argc, char **argv)
            {
                // Validate the parameters
                if (argc != 2)
                {
                    cout << "Syntax: <server-ip>" << endl;
                    _getch();
                    return 1;
                }

                //Quit flag
                bool quit = false;

                //Keep track of hits
                int HitCounter = 0;

                //Initialize random seed
                srand(time(NULL));

                //Declare ships
                Ship ships[5];

                //Initialize ship lengths
                ships[0].len = 5;
                ships[1].len = 4;
                ships[2].len = 3;
                ships[3].len = 3;
                ships[4].len = 2;

                //Declare some winsock variables
                int status;                                 //To keep track of errors
                WSADATA wsaData;                            //For winsock initialization
                SOCKET ServerSocket = INVALID_SOCKET;       //Socket for communicating with server
                struct addrinfo *result = NULL;             //struct to hold address information
                struct addrinfo *Pointer = NULL;            //struct to hold point to next ip
                struct addrinfo address;                    //struct to hold connection information
                char recvbuf1[BUFLEN];                      //Buffer for receiving information
                char recvbuf2[BUFLEN];                      //Extra Buffer for receiving information
                char sendbuf[BUFLEN];                       //Buffer for sending information

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
                status = getaddrinfo(argv[1], PORT, &address, &result);
                if (status != 0)
                {
                    cout << "getaddrinfo failed with error: " << WSAGetLastError() << endl;
                    freeaddrinfo(result);
                    _getch();
                    return 1;
                }

                // Attempt to connect to an address until one succeeds
                for (Pointer = result; Pointer != NULL; Pointer = Pointer->ai_next) {

                    // Create a SOCKET for connecting to server
                    ServerSocket = socket(Pointer->ai_family, Pointer->ai_socktype, Pointer->ai_protocol);
                    if (ServerSocket == INVALID_SOCKET)
                    {
                        printf("socket failed with error: %ld\n", WSAGetLastError());
                        WSACleanup();
                        _getch();
                        return 1;
                    }

                    // Connect to server.
                    status = connect(ServerSocket, Pointer->ai_addr, (int)Pointer->ai_addrlen);
                    if (status == SOCKET_ERROR)
                    {
                        closesocket(ServerSocket);
                        ServerSocket = INVALID_SOCKET;
                        continue;
                    }
                    break;
                }



                if (ServerSocket == INVALID_SOCKET)
                {
                    cout << "could not connect " << endl;
                    _getch();
                    return 1;
                }
                else
                    cout << "connected to " << argv[1] << ":" << PORT << endl;

                //Done with the results
                freeaddrinfo(result);

                //set up game...

                //Grids that will be displayed
                char HitGrid[8][8];
                char ShipGrid[8][8];

                //Initialize grids
                InitGrid(HitGrid, ships);
                InitGrid(ShipGrid, ships);

                //Initialize ship hitboxes
                for (int x = 0; x <5; x++)
                {
                    //Initialize hitbox
                    for (int i = 0; i<5; i++)
                        ships[x].Hitbox[i] = Letter[x];
                }

                //Randomize ship locations
                PlaceShips(ships, ShipGrid);

                status = 1;

                while (status > 0)
                {
                    //Ask for cords
                    cout << "Enter a coord to bomb or press v to view grid" << endl;
                    cin.getline(sendbuf, BUFLEN, '\n');


                    //If user type 'v' then display grids
                    while (strcmp(sendbuf, "V") == 0 || strcmp(sendbuf, "v") == 0)
                    {
                        //Display the grids
                        DisplayGrid(HitGrid, ShipGrid);

                        //Ask for cords
                        cout << endl << "Enter a coord to bomb or press v to view grid" << endl;
                        cin.getline(sendbuf, BUFLEN, '\n');
                    }

                    //send cords
                    send(ServerSocket, sendbuf, BUFLEN, 0);

                    //recv hit/miss
                    status = recv(ServerSocket, recvbuf1, BUFLEN, 0);

                    //If we hit a ship, mark it on the hit grid
                    if (recvbuf1[0] == 'H')
                    {
                        //Recieve ship that was hit
                        status = recv(ServerSocket, recvbuf2, BUFLEN, 0);

                        //Display shipname
                        for (int x = 0; x < status; x++)
                        {
                            cout << recvbuf2[x];
                        }

                        cout << " was hit!" << endl;

                        //Update the hit grid
                        HitGrid[(sendbuf[1] - 48)][(TransLettoNumb(sendbuf) -1)] = recvbuf2[0];
                    }
                    else
                    {
                        HitGrid[(sendbuf[1] - 48)][(TransLettoNumb(sendbuf) - 1)] = 'X';

                        //Display hit/miss
                        for (int x = 0; x < status; x++)
                        {
                            cout << recvbuf1[x];
                        }

                        cout << endl;
                    }

                    //recv cord
                    status = recv(ServerSocket, recvbuf1, BUFLEN, 0);

                    cout << endl << "server bombed cord " << recvbuf1[0] << recvbuf1[1] << endl;

                    //Check if it was a hit or miss and reply to server
                    if (!Checkhit(ships, recvbuf1, ShipGrid))
                        sendl(ServerSocket, false);
                    else
                    {
                        sendl(ServerSocket, true);

                        //Add to hit counter
                        HitCounter++;
                    }

                    //update the ship grid
                    ShipGrid[(recvbuf1[1] - 48)][(TransLettoNumb(recvbuf1) - 1)] = 'X';

                    //Clear buffer
                    memset(recvbuf1, 0, sizeof(recvbuf1));
                    memset(recvbuf2, 0, sizeof(recvbuf2));

                    if (HitCounter > 17)
                    {
                        cout << endl << "the server one the game!" << endl;
                        _getch();
                        return 0;
                    }
                }

                _getch();
                return 0;
            }
