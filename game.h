/************************************************************************************
 * game.h v0.6  																	*
 * Contains the definition of the player class 										*
 *                                                                                  *
 * Matthias Pfitzmayer		140515		madmayer@gmx.net							*
 ************************************************************************************/

 /***********************************************************************************
  * Changelog:
  * 140516	MP	@all	definition of the game class
  *
  *
  ***********************************************************************************/

# ifndef GAME_H
# define GAME_H

# include "Player/player.h"


/**
 * @brief The Game class
 */
class Game {
private:
   Player player;   /**< this is going to be the player using the device*/
   Player enemy;    /**< this is the second player later on connected via Network*/

protected:
   bool read_ship_coordinates(size_t &_xa, size_t &_ya, size_t &_xe, size_t &_ye);

   bool read_ship_coordinates(size_t &_xa, size_t &_ya, size_t &_xe, size_t &_ye, size_t &_x3, size_t &_y3);

   bool read_ship_coordinates(size_t &_xa, size_t &_ya, size_t &_xe, size_t &_ye, size_t &_x3, size_t &_y3,
                              size_t &_x4, size_t &_y4);

   bool read_ship_coordinates(size_t &_xa, size_t &_ya, size_t &_xe, size_t& _ye, size_t& _x3, size_t& _y3,
                   size_t& _x4, size_t& _y4, size_t& _x5, size_t& y5);

   bool read_bomb_coordinates(size_t& _xb, size_t& _yb);

   void print_commands(char* msg);

public:
    Game();
    //Game(Insert Network functionality here);
    ~Game();

    void init_game();

    void change_player_name(std::string& _name);
    void change_enemy_name(std::string& _name);

    std::string get_player_name();
    std::string get_enemy_name();

    bool change_activity_status();

    void bomb_square(Square* _sq);
    bool place_ships(Square* _sq1, Square* _sq2, Square* sq3 = NULL, Square* _sq4 = NULL, Square* _sq5 = NULL);

    Board& getBoardRef();       //FF 02.06
    Board& getEnemyBoardRef();  //FF 10.06
    bool getEnemyState();       //FF 10.06
    bool getPlayerState();      //FF 10.06

    // help functions for terminal debugging
    void change_player_names();
    void player_set_ship_routine();

    void player_set_ship_test();
    void enemy_set_ship_test();

    void enemy_set_ship_routine();

    void bomb_field_routine();

    bool bomb_square();
    void player_print_boards();
    void enemy_print_boards();
    void player_print_ships();
    void enemy_print_ships();
};

#endif // GAME_H
