/************************************************************************************
 * player.cpp	v0.3																*
 * Contains the definition of the member and member functions of the player class.	*
 * A Player should be able to set and change his name, set ships and bomb the 		*
 * enemies field 																	*
 * A Player should know if he stil has ships left, where to find his board and how	*
 * to bomb his oponents field.														*
 * Matthias Pfitzmayer		140415		madmayer@gmx.net							*
 ************************************************************************************/

 /***********************************************************************************
  * Changelog:
  * 140415	MP	@all	Definition of the Player class
  * 140416	MP	@all	Implementing Memberfunc of th Player class
  *
  ***********************************************************************************/

 /***********************************************************************************
  * to do:
  * [1]	MP	implement the player.set_ship(_len, _x1, _y1, _x2, _y2)
  *
  *
  ***********************************************************************************/

# include "game.h"
# include "my_headers.h"


/**
 * @brief Game::Game
 * std. constructor
 */
Game::Game(){

}


/**
 * @brief Game::~Game
 * destructor
 */
Game::~ Game() {

}


/**
 * @brief Game::init_game
 * put the Game into a defined status, where Player 1, the host is activ and Player 2 is waiting
 * for Player 1 to finish
 */
void Game::init_game() {
    Game::player.set_active();
}


/**
 * @brief Game::change_player_name
 * @param _name
 */
void Game::change_player_name(std::string& _name) {
    Game::player.set_name(_name);
}


/**
 * @brief Game::change_enemy_name
 * @param _name
 * a function that enables you to change the name of player 2 from an other
 * source e.g. from a graphic surface
 */
void Game::change_enemy_name(std::string& _name) {
    Game::enemy.set_name(_name);
}


/**
 * @brief get_player_name
 * @return
 */
std::string Game::get_player_name() {
    return Game::player.get_name();
}


/**
 * @brief get_enemy_name
 * @return
 */
std::string Game::get_enemy_name() {
    return Game::enemy.get_name();
}


/**
 * @brief Game::change_player_names
 * help function for terminal debugging, basically reads a string from
 * stdin and calls the player.set_name() func. from the player class
 */
void Game::change_player_names() {
    std::string player_name;
    std::string enemy_name;
    std::cout << "please enter the first players name:" << std::endl;
    std::cin >> player_name;
    Game::player.set_name(player_name);
    std::cout << "please enter the second players name:" << std::endl;
    std::cin >> enemy_name;
    Game::enemy.set_name(enemy_name);
}


/**
 * @brief Game::change_activity_status
 * this functioin rotates the activity status, if the first player is active
 * the second player should not be active and the other way round, that means
 * everytime player 1 is active and we call this function we want to set
 * player 2 active and player 1 not active
 *
 * @return bool active
 */
bool Game::change_activity_status() {
    if(Game::player.get_active()) {
        Game::player.set_not_active();
        Game::enemy.set_active();
        return Game::player.check_lose();       // FF 16.06: return true;
    }

    else if (Game::enemy.get_active()) {
        Game::enemy.set_not_active();
        Game::player.set_active();
        return Game::enemy.check_lose();       // FF 16.06: return false;
    }
    //return false;     //FF 16.06
}


/**
 * @brief Game::set_ship_routine
 * defines a prototype routine, that can be used to set a ship from the graphic surface
 */
bool Game::place_ships(Square* _sq1, Square* _sq2, Square* _sq3, Square* _sq4, Square* _sq5) {
    if(Game::player.return_board_ref().get_squares_empty(_sq1, _sq2, _sq3, _sq4, _sq5)) {
        Game::player.place_ship(_sq1, _sq2, _sq3, _sq4, _sq5);
        return true;     //FF eingefuegt
    }
    return false;       //FF true -> false
}
/*
bool Game::place_ships(size_t _type, size_t _num, size_t _x1, size_t _y1, size_t _x2, size_t _y2,
                       size_t _x3, size_t _y3, size_t _x4, size_t _y4, size_t _x5, size_t _y5) {
    if(Game::player.return_board_ref().get_squares_empty(_sq1, _sq2, _sq3, _sq4, _sq5)) {
        Game::player.place_ship(_sq1, _sq2, _sq3, _sq4, _sq5);
    }
    return true;
}*/


/**
 * @brief Game::set_ship_routine
 *
 */
void Game::player_set_ship_routine() {
    Board& field = Game::player.return_board_ref();
    size_t xa, ya, xe, ye, x3, y3, x4, y4, x5, y5;
    size_t& _xa = xa;
    size_t& _ya = ya;
    size_t& _xe = xe;
    size_t& _ye = ye;
    size_t& _x3 = x3;
    size_t& _y3 = y3;
    size_t& _x4 = x4;
    size_t& _y4 = y4;
    size_t& _x5 = x5;
    size_t& _y5 = y5;

    Square *_sq1, *_sq2, *_sq3, *_sq4, *_sq5;

    std::cout << Game::player.get_name() << " place your ships on the field" << std::endl;

    /**
     * itterate over the player.subm[] starting with 1 till player.num_subm
     * reading individual start and end position koordinates from stdin and
     * put them on the board
     */
    for(size_t count = 1; count <= Game::player.get_num_submarines(); count++) {
        Submarine& subm_ref = Game::player.get_Submarine_ref(count);
        while(!(subm_ref.get_ship_set())) {
            bool legal = false;

            while(!legal) {

                legal = Game::read_ship_coordinates(_xa, _ya, _xe, _ye);
                if(legal) {
                    std::cout << "submarine has been placed at : " << _xa << " / " << ya
                              << "    " << xe << " / " << ye << std::endl;
                }
                else {
                    std::cout << "your coordinates were off the board, try again. " << std::endl;
                }
            }

            _sq1 = field.get_Square_ptr(xa, ya);
            _sq2 = field.get_Square_ptr(xe, ye);

              if(Game::player.place_ship(_sq1, _sq2)) {
                subm_ref.set_ship(_sq1, _sq2);
            }
        }
    }

    Game::player.print_field();

    /**
     * itterate over the player.dest[] starting with 1 till player.num_dest
     * reading individual start and end position koordinates from stdin and
     * put them on the board
     */
    for(size_t count = 1; count <= Game::player.get_num_destroyer(); count++) {
        Destroyer& dest_ref = Game::player.get_Destroyer_ref(count);
        while(!(dest_ref.get_ship_set())) {
            bool legal = false;

            while(!legal) {
                legal = Game::read_ship_coordinates(_xa, _ya, _xe, _ye, _x3, _y3);
                if(legal) {
                    std::cout << "destroyer has been placed at : " << _xa << " / " << ya
                              << "    " << _x3 << " / " << _y3 << "    " <<xe << " / " <<
                           ye << std::endl;
                }
                else {
                    std::cout << "your coordinates were off the board, try again. " << std::endl;
                }
            }


            _sq1 = field.get_Square_ptr(xa, ya);
            _sq2 = field.get_Square_ptr(x3, y3);
            _sq3 = field.get_Square_ptr(xe, ye);

            if(Game::player.place_ship(_sq1, _sq2, _sq3)) {
                dest_ref.set_ship(_sq1, _sq2, _sq3);
            }
        }
    }

    Game::player.print_field();

    /**
     * itterate over the player.bash[] startin with 1 till player.num_bash
     * reading individual start and end position koordinates from stdin and
     * put them on the board
     */
    for(size_t count = 1; count <= Game::player.get_num_battleships(); count++) {
        Battleship& bash_ref = Game::player.get_BattleShip_ref(count);
        while(!(bash_ref.get_ship_set())) {
            bool legal = false;

            while(!legal) {
                legal = Game::read_ship_coordinates(_xa, _ya, _xe, _ye, _x3, _y3, _x4, _y4);

                if(legal) {
                    std::cout << "battleship has been placed at : " << _xa << " / " << ya
                              << "    " << _x3 << " / " << _y3 << "    " << _x4 << " / " <<
                          _y4 << "    " << _xe << " / " << _ye << std::endl;
                }
                else {
                    std::cout << "your coordinates were off the board, try again. " << std::endl;
                }
            }

            _sq1 = field.get_Square_ptr(xa, ya);
            _sq2 = field.get_Square_ptr(x3, y3);
            _sq3 = field.get_Square_ptr(x4, y4);
            _sq4 = field.get_Square_ptr(xe, ye);


            if(Game::player.place_ship(_sq1, _sq3, _sq4, _sq2)) {
                bash_ref.set_ship(_sq1, _sq3, _sq4, _sq2);
            }
        }
    }

    Game::player.print_field();

    /**
     * itterate over the player.airc[] starting with 1 till player.num_airc
     * and reading each air carriers individuall start and ending point
     * koordinates from stdin and put them on the field
     */
    for(size_t count = 1; count <= Game::player.get_num_aircarrier(); count++) {
        AirCarrier& airc_ref = Game::player.get_AirCarrier_ref(count);
        while(!(airc_ref.get_ship_set())) {
            bool legal = false;
            while(!legal) {
                legal = Game::read_ship_coordinates(_xa, _ya, _xe, _ye, _x3, _y3, _x4, _y4, _x5, _y5);

                if(legal) {
                    std::cout << "battleship has been placed at : " << _xa << " / " << ya
                              << "    " << _x3 << " / " << _y3 << "    " << _x4 << " / " <<
                          _y4 << "    " << _x5 << " / " << _y5 << "    " << _xe << " / " <<
                          _ye << std::endl;
                }
                else {
                    std::cout << "your coordinates were off the board, try again. " << std::endl;
                }
            }

            _sq1 = field.get_Square_ptr(xa, ya);
            _sq2 = field.get_Square_ptr(x3, y3);
            _sq3 = field.get_Square_ptr(x4, y4);
            _sq4 = field.get_Square_ptr(x5, y5);
            _sq5 = field.get_Square_ptr(xe, ye);

            if(Game::player.place_ship(_sq1, _sq2, _sq3, _sq4, _sq5)) {
                airc_ref.set_ship(_sq1, _sq2, _sq3, _sq4, _sq5);
            }
        }
    }

    Game::player.change_activ_status();
    Game::player.print_field();
    Game::player.print_ships();
}


/**
 * @brief Game::enemy_set_ship_routine
 * this member function mirrors the Game::player_set_ship_routine() and does basically
 * the same thing it was created to enable console debugging before the network interface
 * was created to show that the program is working
 */
void Game::enemy_set_ship_routine() {
    Board& field = Game::enemy.return_board_ref();
    size_t xa, ya, xe, ye, x3, y3, x4, y4, x5, y5;
    size_t& _xa = xa;
    size_t& _ya = ya;
    size_t& _xe = xe;
    size_t& _ye = ye;
    size_t& _x3 = x3;
    size_t& _y3 = y3;
    size_t& _x4 = x4;
    size_t& _y4 = y4;
    size_t& _x5 = x5;
    size_t& _y5 = y5;

    Square *_sq1, *_sq2, *_sq3, *_sq4, *_sq5;

    std::cout << Game::enemy.get_name() << " place your ships on the field" << std::endl;

    for(size_t count = 1; count <= Game::enemy.get_num_submarines(); count++) {
        Submarine& subm_ref = Game::enemy.get_Submarine_ref(count);
        while(!(subm_ref.get_ship_set())) {
            bool legal = false;

            while(!legal) {
                legal = Game::read_ship_coordinates(_xa, _ya, _xe, _ye);

                if(legal) {
                    std::cout << "submarine has been placed at : " << _xa << " / " << ya
                              << "    " << xe << " / " << ye << std::endl;
                }

                else {
                    std::cout << "your coordinates were off the board, try again. " << std::endl;
                }
            }

            _sq1 = field.get_Square_ptr(xa, ya);
            _sq2 = field.get_Square_ptr(xe, ye);

              if(Game::enemy.place_ship(_sq1, _sq2)) {
                subm_ref.set_ship(_sq1, _sq2);
            }
        }
    }

    Game::enemy.print_field();

    for(size_t count = 1; count <= Game::enemy.get_num_destroyer(); count++) {
        Destroyer& dest_ref = Game::enemy.get_Destroyer_ref(count);
        while(!(dest_ref.get_ship_set())) {
            bool legal = false;

            while(!legal) {
                legal = Game::read_ship_coordinates(_xa, _ya, _xe, _ye, _x3, _y3);

                if(legal) {
                    std::cout << "destroyer has been placed at : " << _xa << " / " << ya
                              << "    " << _x3 << " / " << _y3 << "    " <<xe << " / " <<
                           ye << std::endl;
                }

                else {
                    std::cout << "your coordinates were off the board, try again. " << std::endl;
                }
            }

            _sq1 = field.get_Square_ptr(xa, ya);
            _sq2 = field.get_Square_ptr(x3, y3);
            _sq3 = field.get_Square_ptr(xe, ye);

            if(Game::enemy.place_ship(_sq1, _sq2, _sq3)) {
                dest_ref.set_ship(_sq1, _sq2, _sq3);
            }
        }
    }

    Game::enemy.print_field();

    for(size_t count = 1; count <= Game::enemy.get_num_battleships(); count++) {
        Battleship& bash_ref = Game::enemy.get_BattleShip_ref(count);
        while(!(bash_ref.get_ship_set())) {
            bool legal = false;

            while(!legal) {
                legal = Game::read_ship_coordinates(_xa, _ya, _xe, _ye, _x3, _y3, _x4, _y4);

                if(legal) {
                    std::cout << "battleship has been placed at : " << _xa << " / " << ya
                              << "    " << _x3 << " / " << _y3 << "    " << _x4 << " / " <<
                          _y4 << "    " << _xe << " / " << _ye << std::endl;
                }

                else {
                    std::cout << "your coordinates were off the board, try again. " << std::endl;
                }
            }
            _sq1 = field.get_Square_ptr(xa, ya);
            _sq2 = field.get_Square_ptr(x3, y3);
            _sq3 = field.get_Square_ptr(x4, y4);
            _sq4 = field.get_Square_ptr(xe, ye);


            if(Game::enemy.place_ship(_sq1, _sq3, _sq4, _sq2)) {
                bash_ref.set_ship(_sq1, _sq3, _sq4, _sq2);
            }
        }
    }

    Game::enemy.print_field();

    for(size_t count = 1; count <= Game::enemy.get_num_aircarrier(); count++) {
        AirCarrier& airc_ref = Game::enemy.get_AirCarrier_ref(count);
        while(!(airc_ref.get_ship_set())) {
            bool legal = false;

            while(!legal) {
                legal = Game::read_ship_coordinates(_xa, _ya, _xe, _ye, _x3, _y3, _x4, _y4, _x5, _y5);

                if(legal) {
                    std::cout << "battleship has been placed at : " << _xa << " / " << ya
                              << "    " << _x3 << " / " << _y3 << "    " << _x4 << " / " <<
                          _y4 << "    " << _x5 << " / " << _y5 << "    " << _xe << " / " <<
                          _ye << std::endl;
                }

                else {
                    std::cout << "your coordinates were off the board, try again. " << std::endl;
                }
            }

            _sq1 = field.get_Square_ptr(xa, ya);
            _sq2 = field.get_Square_ptr(x3, y3);
            _sq3 = field.get_Square_ptr(x4, y4);
            _sq4 = field.get_Square_ptr(x5, y5);
            _sq5 = field.get_Square_ptr(xe, ye);

            if(Game::enemy.place_ship(_sq1, _sq2, _sq3, _sq4, _sq5)) {
                airc_ref.set_ship(_sq1, _sq2, _sq3, _sq4, _sq5);
            }
        }
    }

    Game::enemy.change_activ_status();
    Game::enemy.print_field();
    Game::enemy.print_ships();
}


/**
 * @brief Game::bomb_field_routine
 * this member function is another help function for terminal debugging purposes.
 *
 */
void Game::bomb_field_routine() {
    size_t xb, yb;
    size_t& _xb = xb;
    size_t& _yb = yb;

     Game::player.set_active();

    while(!(Game::player.get_lost()) & !(Game::enemy.get_lost())) {
        bool on_board = false;

        while(! on_board) {
            on_board = false;
            if(Game::player.get_active()) {
                std::cout << Game::player.get_name() << " please select the field you want to bomb" << std::endl;
                on_board = Game::read_bomb_coordinates(_xb, _yb);
            }
            else if (Game::enemy.get_active()) {
                std::cout << Game::enemy.get_name() << " please select the field you want to bomb" << std::endl;
                on_board = Game::read_bomb_coordinates(_xb, _yb);
            }
            else {
                std::cout << "there is no active player!" << std::endl;
            }
            std::cout << "please try again, all values between 1 and " << Game::player.return_board_ref().get_lenght()
                      << " are valid" << std::endl;
        }

        if(Game::player.get_active()) {
            Game::player.bomb_enemy_field(Game::enemy.return_board_ref(), xb, yb);
            Game::player_print_boards();
            Game::enemy_print_ships();
        }

        else if(Game::enemy.get_active()) {
            Game::enemy.bomb_enemy_field(Game::player.return_board_ref(), xb, yb);
            Game::enemy_print_boards();
            Game::player_print_ships();
        }

        Game::change_activity_status();


        if(Game::player.get_lost()) {
            std::cout << Game::enemy.get_name() << " has won the game" << std::endl;
        }
        else if (Game::enemy.get_lost()) {
            std::cout << Game::player.get_name() << " has won the game" << std::endl;
        }
    }
}


/**
 * @brief Game::read_ship_coordinates
 * this is a help function it is used within the game class to read x and y coordinates
 * for ships of 2 Squaes lenght, it also checks if the coordinates are within board
 * range. It returns true if they are.
 *
 * @param _xa
 * @param _ya
 * @param _xe
 * @param _ye
 * @return
 */
bool Game::read_ship_coordinates(size_t &_xa, size_t &_ya, size_t &_xe, size_t &_ye) {
    bool legal = false;

    std::cout << "enter the first 'x' cordinate:    ";
    std::cin >> _xa;

    std::cout << "enter the first 'y' cordinate:    ";
    std::cin >> _ya;

    std::cout << "enter the second 'x' coordinate:  ";
    std::cin >> _xe;

    std::cout << "enter the second 'y' coordinate:  ";
    std::cin >> _ye;

    if(_xe == _xa) {
        //std::cout << "vertically" << std::endl;
        _ye = (_ya + 1);

    }

    else if(_ye == _ya) {
        //std::cout << "horizontally" << std::endl;
        _xe = (_xa + 1);
    }

    else {
        //std::cout << "Ship must be set vertically" << std::endl;
        return legal;
    }

    if((_xe <= 10) & (_ye <= 10) & (_xa <= 10) & (_ya <= 10)) {
        legal = true;
    }

    return legal;
}


/**
 * @brief Game::read_ship_coordinates
 * this is a help function it is used within the game class to read x and y coordinates
 * for ships of 3 Squaes lenght from stdin, it also checks if the coordinates are within
 * board range. It returns true if they are.
 *
 * @param _xa
 * @param _ya
 * @param _xe
 * @param _ye
 * @param _x3
 * @param _y3
 * @return
 */
bool Game::read_ship_coordinates(size_t &_xa, size_t &_ya, size_t &_xe, size_t &_ye, size_t &_x3, size_t &_y3) {
    bool legal = false;

    std::cout << "enter the first 'x' cordinate:    ";
    std::cin >> _xa;

    std::cout << "enter the first 'y' cordinate:    ";
    std::cin >> _ya;

    std::cout << "enter the second 'x' coordinate:  ";
    std::cin >> _xe;

    std::cout << "enter the second 'y' coordinate:  ";
    std::cin >> _ye;

    if(_xe == _xa) {
        //std::cout << "vertically" << std::endl;
        _x3 = _xa;

        _ye = (_ya + 2);
        _y3 = (_ya + 1);
    }

    if(_ye == _ya) {
        //std::cout << "horizontally" << std::endl;
        _y3 = _ya;

        _xe = (_xa + 2);
        _x3 = (_xa + 1);
    }
    if((_xe <= 10)& (_ye <= 10) & (_xa <= 10) & (_ya <= 10) & (_x3 <= 10) & (_y3 <= 10)) {
        legal = true;
    }

    return legal;
}


/**
 * @brief Game::read_ship_coordinates
 * this is a help function it is used within the game class to read x and y coordinates
 * for ships of 4 Squaes lenght, it also checks if the coordinates are within board
 * range. It returns true if they are.
 *
 * @param _xa
 * @param _ya
 * @param _xe
 * @param _ye
 * @param _x3
 * @param _y3
 * @param _x4
 * @param _y4
 * @return bool legal
 */
bool Game::read_ship_coordinates(size_t &_xa, size_t &_ya, size_t &_xe, size_t &_ye, size_t &_x3, size_t &_y3, size_t &_x4, size_t &_y4) {
    bool legal = false;

    std::cout << "enter the first 'x' cordinate:    ";
    std::cin >> _xa;

    std::cout << "enter the first 'y' cordinate:    ";
    std::cin >> _ya;

    std::cout << "enter the second 'x' coordinate:  ";
    std::cin >> _xe;

    std::cout << "enter the second 'y' coordinate:  ";
    std::cin >> _ye;

    if(_xe == _xa) {
        //std::cout << "vertically" << std::endl;
        _x3 = _xa;
        _x4 = _xa;

        _ye = (_ya + 3);
        _y3 = (_ya + 1);
        _y4 = (_ya + 2);
    }

    if(_ye == _ya) {
        //std::cout << "horizontally" << std::endl;
        _y3 = _ya;
        _y4 = _ya;

        _xe = (_xa + 3);
        _x3 = (_xa + 1);
        _x4 = (_xa + 2);
    }
    if((_xe <= 10) & (_ye <= 10) & (_xa <= 10) & (_ya <= 10) & (_x3 <= 10) & (_y3 <= 10)
      &(_x4 <= 10) & (_y4 <=10)) {
        legal = true;
    }

    return legal;
}


/**
 * @brief Game::read_ship_coordinates
 * this is a help function it is used within the game class to read x and y coordinates
 * for ships of 5 Squaes lenght, it also checks if the coordinates are within board
 * range. It returns true if they are.
 *
 * @param lenght
 * @param _xa
 * @param _ya
 * @param _x2
 * @param _y2
 * @param _x3
 * @param _y3
 * @param _x4
 * @param _y4
 * @param _x5
 * @param _y5
 * @return bool legal
 */
bool Game::read_ship_coordinates(size_t &_xa, size_t &_ya, size_t &_xe, size_t &_ye, size_t &_x3, size_t &_y3, size_t &_x4, size_t &_y4, size_t &_x5, size_t &_y5) {
    bool legal = false;

    std::cout << "enter the first 'x' cordinate:    ";
    std::cin >> _xa;

    std::cout << "enter the first 'y' cordinate:    ";
    std::cin >> _ya;

    std::cout << "enter the second 'x' coordinate:  ";
    std::cin >> _xe;

    std::cout << "enter the second 'y' coordinate:  ";
    std::cin >> _ye;

    if(_xe == _xa) {
        //std::cout << "vertically" << std::endl;
        _x3 = _xa;
        _x4 = _xa;
        _x5 = _xa;

        _ye = (_ya + 4);
        _y3 = (_ya + 1);
        _y4 = (_ya + 2);
        _y5 = (_ya + 3);
    }

    if(_ye == _ya) {
        //std::cout << "horizontally" << std::endl;
        _y3 = _ya;
        _y4 = _ya;
        _y5 = _ya;

        _xe = (_xa + 4);
        _x3 = (_xa + 1);
        _x4 = (_xa + 2);
        _x5 = (_xa + 3);
    }

    if((_xe <= 10) & (_ye <= 10) & (_xa <= 10) & (_ya <= 10) & (_x3 <= 10) & (_y3 <= 10)
      &(_x4 <= 10) & (_y4 <=10) & (_x5 <= 10) & (_y5 <= 10)) {
        legal = true;
    }

    return legal;
}


/**
 * @brief Game::read_bomb_coordinates
 * this function enables each player to read a x and a y coordinate from
 * stdin, checks if they are still on the board, if they are this func. will
 * return true
 *
 * @param _xb
 * @param _yb
 * @return bool legal
 */
bool Game::read_bomb_coordinates(size_t &_xb, size_t &_yb) {
    bool legal = false;
    std::cout << "enter the 'x' cordinate:    ";
    std::cin >> _xb;

    std::cout << "enter the 'y' cordinate:    ";
    std::cin >> _yb;

    //std::cout << _xb << "   " << _yb << std::endl;

    if((_xb <= 10) & (_yb <= 10)) {
        legal = true;
        std::cout << "on_board should be true by now if 1 -> " << legal << std::endl;
    }

    return legal;
}


/**
 * @brief Game::player_print_boards
 */
void Game::player_print_boards() {
    Game::player.print_field();
    Game::player.print_enemy_field(Game::enemy.return_board_ref());
}


/**
 * @brief Game::player_print_ships
 */
void Game::player_print_ships() {
    Game::player.print_ships();
}


/**
 * @brief Game::enemy_print_boards
 */
void Game::enemy_print_boards() {
    Game::player.print_field();
    Game::player.print_enemy_field(Game::player.return_board_ref());
}


/**
 * @brief Game::enemy_print_ships
 */
void Game::enemy_print_ships() {
    Game::enemy.print_ships();
}


/**
 * @brief Game::player_set_ship_test
 * a help function that creates the following pattern on player 1's board
 *
 * this is the your board:
 * A B C D E F G H I K
 *|X| |X|X| | |X|X|X| | 1
 *|X| | | | | | | | | | 2
 *| | |X| |X|X|X|X| | | 3
 *|X| |X| | | | | | | | 4
 *|X| |X| |X| | |X| | | 5
 *| | | | |X| | |X| | | 6
 *|X| |X| |X| | |X| |X| 7
 *|X| |X| |X| | |X| |X| 8
 *| | |X| | | | |X| |X| 9
 *|X|X| | |X|X|X| | |X| 10
 */
void Game::player_set_ship_test() {

    /**
     * set submarines
     */
    Game::player.place_ship(1, 1, 1, 1, 1, 2);
    Game::player.place_ship(1, 2, 1, 4, 1, 5);
    Game::player.place_ship(1, 3, 1, 7, 1, 8);
    Game::player.place_ship(1, 4, 1, 10, 2, 10);
    Game::player.place_ship(1, 5, 3, 1, 4, 1);

    /**
     * set destroyer
     */
    Game::player.place_ship(2, 1, 3, 3, 3, 4, 3, 5);
    Game::player.place_ship(2, 2, 3, 7, 3, 8, 3, 9);
    Game::player.place_ship(2, 3, 7, 1, 8, 1, 9, 1);
    Game::player.place_ship(2, 4, 5, 10, 6, 10, 7, 10);

    /**
     * set all battleships
     */
    Game::player.place_ship(3, 1, 5, 3, 6, 3, 7, 3, 8, 3);
    Game::player.place_ship(3, 2, 5, 5, 5, 6, 5, 7, 5, 8);
    Game::player.place_ship(3, 3, 10, 7, 10, 8, 10, 9, 10, 10);

    /**
     * set the air carrier
     */
    Game::player.place_ship(4, 1, 8, 5, 8, 6, 8, 7, 8, 8, 8, 9);

    Game::player.print_field();
}


/**
 * @brief Game::enemy_set_ship_test
 * a help function that creates the following pattern on player 2's board
 *
 * this is the your board:
 *  A B C D E F G H I K
 * |X| |X|X| | |X|X|X| | 1
 * |X| | | | | | | | | | 2
 * | | |X| |X|X|X|X| | | 3
 * |X| |X| | | | | | | | 4
 * |X| |X| |X| | |X| | | 5
 * | | | | |X| | |X| | | 6
 * |X| |X| |X| | |X| |X| 7
 * |X| |X| |X| | |X| |X| 8
 * | | |X| | | | |X| |X| 9
 * |X|X| | |X|X|X| | |X| 10
 */

void Game::enemy_set_ship_test() {
    /**
     * set submarines
     */
    Game::enemy.place_ship(1, 1, 1, 1, 1, 2);
    Game::enemy.place_ship(1, 2, 1, 4, 1, 5);
    Game::enemy.place_ship(1, 3, 1, 7, 1, 8);
    Game::enemy.place_ship(1, 4, 1, 10, 2, 10);
    Game::enemy.place_ship(1, 5, 3, 1, 4, 1);

    /**
     * set destroyer
     */
    Game::enemy.place_ship(2, 1, 3, 3, 3, 4, 3, 5);
    Game::enemy.place_ship(2, 2, 3, 7, 3, 8, 3, 9);
    Game::enemy.place_ship(2, 3, 7, 1, 8, 1, 9, 1);
    Game::enemy.place_ship(2, 4, 5, 10, 6, 10, 7, 10);

    /**
     * set all battleships
     */
    Game::enemy.place_ship(3, 1, 5, 3, 6, 3, 7, 3, 8, 3);
    Game::enemy.place_ship(3, 2, 5, 5, 5, 6, 5, 7, 5, 8);
    Game::enemy.place_ship(3, 3, 10, 7, 10, 8, 10, 9, 10, 10);

    /**
     * set the air carrier
     */
    Game::enemy.place_ship(4, 1, 8, 5, 8, 6, 8, 7, 8, 8, 8, 9);

    Game::enemy.print_field();
}

// Not part of the original game class:
Board& Game::getBoardRef()
{
    return player.return_board_ref();
}

Board& Game::getEnemyBoardRef()
{
    return enemy.return_board_ref();
}

bool Game::getEnemyState()
{
    return enemy.get_active();
}

bool Game::getPlayerState()
{
    return player.get_active();
}

void Game::setStartActivity(bool host)
{
    if(host){
        player.set_active();
        enemy.set_not_active();
    }
    else{
        player.set_not_active();
        enemy.set_active();
    }
}