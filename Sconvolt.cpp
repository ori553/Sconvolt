/*
 ____                            _ _      ____ _
/ ___|  ___ ___  _ ____   _____ | | |_   / ___| |__   ___  ___ ___
\___ \ / __/ _ \| '_ \ \ / / _ \| | __| | |   | '_ \ / _ \/ __/ __|
 ___) | (_| (_) | | | \ V / (_) | | |_  | |___| | | |  __/\__ \__ \
|____/ \___\___/|_| |_|\_/ \___/|_|\__|  \____|_| |_|\___||___/___/


*/

/* ====================================================================
 *
 * The MIT License (MIT)
 * Copyright (c) 2015, Orest Sota
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * ====================================================================
 */




#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h> //include the header to initialize the image addon
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>

//extern unsigned long
long int count_board_combinations = 0;

#include <stdio.h>
using namespace std;

ALLEGRO_DISPLAY *Screen;
ALLEGRO_DISPLAY *Screen2;

//Functions needed to use the Sconvolt chess engine
#include "move.h"
#include "SconvoltClass.h"
#include "engine3.h"

#include <iostream>



int main()
{
    //Size in pixels of the display to be created
    int display_x = 1024;
    int display_y = 600;

    //Size in pizels of the chess board
    int board_size_x = 637;
    int board_size_y = 600;

    //4 variables representing the x/y coordinates in pixels where the mouse clicked, and where it's released
    int mouse_from_x;
    int mouse_from_y;
    int mouse_to_x;
    int mouse_to_y;

    int mode = 0; //0 for play, 1 for editor
    int piece_selected = -99; //Piece being selected for drag/drop in editor mode
    bool holding_piece = false; //if it's true, user is moving a piece to the board

    //Thinking becomes true while the computer is thinking
    bool thinking = false;
    bool mouse_button_is_down = false;

    //Standard Allegro graphic libraries initializers
   // ALLEGRO_DISPLAY *Screen;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT Event;



    bool Exit = false, OverButton = false;

    al_init();
    al_init_image_addon(); // this must be called to load images. has to be called after al_init

    //al_init_font_addon(); // initialize the font addon
    //al_init_ttf_addon();// initialize the ttf (True Type Font) addon


    //al_set_new_display_flags(ALLEGRO_RESIZABLE);

        Screen = al_create_display(display_x, display_y);
        if(Screen == NULL){
            al_show_native_message_box(Screen, "Error!", "Failed to create the display.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
            return -1;
        }



        event_queue = al_create_event_queue();
        if(event_queue == NULL){
            al_show_native_message_box(Screen, "Error!", "Failed to create the event queue.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
            return -1;
        }


        if(!al_install_keyboard()) { //setup the keyboard
            al_show_native_message_box(NULL, "Error!", "Failed to install keyboard.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
            return -1;
        }
        ALLEGRO_KEYBOARD_STATE keyState;

        if(!al_install_mouse()){
        al_show_native_message_box(NULL, "Error!", "Failed to install mouse.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
        }

    al_register_event_source(event_queue, al_get_display_event_source(Screen));
    al_register_event_source(event_queue, al_get_mouse_event_source()); ///Tell allegro to get events from the mouse




    #include "variables.h" //where all the bitmaps, fonts and other variables are defined


    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon

    ALLEGRO_FONT *font = al_load_ttf_font("Fonts/FFF_Tusj.ttf",26,0 );
    if (!font){
      fprintf(stderr, "Could not load 'pirulen.ttf'.\n");
      return -1;
   }

   ALLEGRO_FONT *font2 = al_load_ttf_font("Fonts/Capture_it.ttf",18,0 );
   ALLEGRO_FONT *font3 = al_load_ttf_font("Fonts/Capture_it.ttf",28,0 );


   //float r = red;
//float g = green;
//float b = blue;
float aaa = 0.5;
float bbbb = 0.9;

//al_draw_tinted_bitmap(alleg, al_map_rgba_f(0.2, 0.2, 0.2, 1.0), 320, 200, 0);
ALLEGRO_COLOR color = al_map_rgba_f(aaa, aaa, aaa, aaa);   //transparent
ALLEGRO_COLOR color2 = al_map_rgba_f(bbbb, bbbb, bbbb, bbbb); //stronger
ALLEGRO_COLOR color3 = al_map_rgba_f(0.4, 0.4, 0.4, 0.4);
//al_draw_tinted_bitmap(transparent, color, 200, 200, NULL);
//color3 = color;

cout<<"_____________________________" <<endl;
cout<<"Sconvolt Chess, by Orest Sota " << endl;
cout<<"_____________________________" <<endl;

//If we reached this point, Allegro is initialized
//---------------------------------------------------------
//---------------------------------------------------------
Sconvolt game1; //Declare an instance of sconvolt, for the chess game
game1.reset(); //It must be used after the creation, because it sets castling rights


//This is the loop of the game, Exit is a bool variable
while(Exit == false)
{


//al_clear_to_color(al_map_rgb(0,0,0)); //Clear screen

al_clear_to_color(al_map_rgb(40,40,40)); //Clear screen

    al_draw_text(font, al_map_rgb(255,255,255), board_size_x + 15, 15, NULL , "Sconvolt Chess 0.99.8");

    //al_draw_text(font2, al_map_rgb(255,255,255), board_size_x + 15, 400, NULL , to_string(evaluate (game1.bb)).c_str() );
    //cout<<"Board Evaluation: " << evaluate (game1.bb)<< endl;






    al_draw_scaled_bitmap(chessboard, 0, 0, al_get_bitmap_width(chessboard), al_get_bitmap_height(chessboard), 0, 0, board_size_x, board_size_y, 0);



al_draw_tinted_bitmap(reset, color, 907, 537, NULL);

al_draw_tinted_bitmap(exit, color, 907, 480, NULL);

 if (mode==0) al_draw_tinted_bitmap(about, color, 785, 537, NULL);



    if (mode==0){ ///Mode 0, it's play mode

    al_draw_tinted_bitmap(editor, color, 655, 171, NULL);

    al_draw_text(font2, al_map_rgb(255,255,255), board_size_x + 15, 90, NULL , "Click to change strenght (1-5)");

    }


    if (game1.user_depth==1) al_draw_tinted_bitmap(b1, color2, 650, 120, NULL); else al_draw_tinted_bitmap(b1, color, 650, 120, NULL);
    if (game1.user_depth==2) al_draw_tinted_bitmap(b2, color2, 710, 120, NULL); else al_draw_tinted_bitmap(b2, color, 710, 120, NULL);
    if (game1.user_depth==3) al_draw_tinted_bitmap(b3, color2, 770, 120, NULL); else al_draw_tinted_bitmap(b3, color, 770, 120, NULL);
    if (game1.user_depth==4) al_draw_tinted_bitmap(b4, color2, 830, 120, NULL); else al_draw_tinted_bitmap(b4, color, 830, 120, NULL);
    if (game1.user_depth==5) al_draw_tinted_bitmap(b5, color2, 890, 120, NULL); else al_draw_tinted_bitmap(b5, color, 890, 120, NULL);
    //if (game1.user_depth==6) al_draw_tinted_bitmap(b6, color2, 950, 120, NULL); else al_draw_tinted_bitmap(b6, color, 950, 120, NULL);



//al_draw_tinted_bitmap(undo, color, 797, 537, NULL);

if (game1.game_terminated == true)
al_draw_text(font3, al_map_rgb(232,36,36), (board_size_x/2) - 100, board_size_y/2, NULL , "Game Terminated, click Reset");


    if (mode==1){ ///Mode 1, it's editor mode
    al_draw_tinted_bitmap(play, color, 655, 171, NULL);
    al_draw_text(font2, al_map_rgb(255,255,255), board_size_x + 15, 90, NULL , "Click Play to start");
    al_draw_text(font2, al_map_rgb(255,255,255), board_size_x + 118, 181, NULL , "Move pawns to the board");

    //al_draw_bitmap(white_rook, 650, 220, NULL);
al_draw_scaled_bitmap(white_rook, 0, 0, al_get_bitmap_width(white_rook), al_get_bitmap_height(white_rook) ,
        650 , 220 ,   60,  60, 0);

al_draw_scaled_bitmap(white_knight, 0, 0, al_get_bitmap_width(white_knight), al_get_bitmap_height(white_knight) ,
        710 , 220 ,   60,  60, 0);

al_draw_scaled_bitmap(white_bishop, 0, 0, al_get_bitmap_width(white_bishop), al_get_bitmap_height(white_bishop) ,
        770 , 220 ,   60,  60, 0);

al_draw_scaled_bitmap(white_pawn, 0, 0, al_get_bitmap_width(white_pawn), al_get_bitmap_height(white_pawn) ,
        830 , 220 ,   60,  60, 0);

al_draw_scaled_bitmap(white_queen, 0, 0, al_get_bitmap_width(white_queen), al_get_bitmap_height(white_queen) ,
       890  , 220 ,   60,  60, 0);

al_draw_scaled_bitmap(white_king, 0, 0, al_get_bitmap_width(white_king), al_get_bitmap_height(white_king) ,
       950  , 220 ,   60,  60, 0);

//Now drawing Black pieces for the editor mode
al_draw_scaled_bitmap(black_rook, 0, 0, al_get_bitmap_width(black_rook), al_get_bitmap_height(black_rook) ,
        650 , 300 ,   60,  60, 0);

al_draw_scaled_bitmap(black_knight, 0, 0, al_get_bitmap_width(black_knight), al_get_bitmap_height(black_knight) ,
        710 , 300 ,   60,  60, 0);

al_draw_scaled_bitmap(black_bishop, 0, 0, al_get_bitmap_width(black_bishop), al_get_bitmap_height(black_bishop) ,
        770 , 300 ,   60,  60, 0);

al_draw_scaled_bitmap(black_pawn, 0, 0, al_get_bitmap_width(black_pawn), al_get_bitmap_height(black_pawn) ,
        830 , 300 ,   60,  60, 0);

al_draw_scaled_bitmap(black_queen, 0, 0, al_get_bitmap_width(black_queen), al_get_bitmap_height(black_queen) ,
       890  , 300 ,   60,  60, 0);

al_draw_scaled_bitmap(black_king, 0, 0, al_get_bitmap_width(black_king), al_get_bitmap_height(black_king) ,
       950  , 300 ,   60,  60, 0);

       al_draw_tinted_bitmap(standardboard, color, 820, 379, NULL);


al_draw_text(font2, al_map_rgb(255,255,255), board_size_x + 5, 397, NULL , "Choose your side");
   if (game1.user_side==1 && game1.human_vs_human==false ) al_draw_tinted_bitmap(whiteb, color2, 657, 430, NULL); else al_draw_tinted_bitmap(whiteb, color, 657, 430, NULL);
   if (game1.user_side==0 && game1.human_vs_human==false) al_draw_tinted_bitmap(blackb, color2, 657+120, 430, NULL); else al_draw_tinted_bitmap(blackb, color, 657 + 120, 430, NULL);
   if (game1.human_vs_human==true) al_draw_tinted_bitmap(no_cpu, color2, 657+120 + 105, 430, NULL); else al_draw_tinted_bitmap(no_cpu, color, 657 + 120+ 105, 430, NULL);



al_draw_text(font2, al_map_rgb(255,255,255), board_size_x + 5, 495, NULL , "Who starts first?");
   if (game1.whostartsfirst==1) al_draw_tinted_bitmap(whiteb, color2, 657, 533, NULL); else al_draw_tinted_bitmap(whiteb, color, 657, 533, NULL);
   if (game1.whostartsfirst==0) al_draw_tinted_bitmap(blackb, color2, 657+120, 533, NULL); else al_draw_tinted_bitmap(blackb, color, 657 + 120, 533, NULL);


//if (holding_piece) al_draw_tinted_bitmap(white_pawn, color2, Event.mouse.x, Event.mouse.y, NULL);
if (holding_piece) al_draw_scaled_bitmap(piece_on_hold, 0, 0, al_get_bitmap_width(piece_on_hold), al_get_bitmap_height(piece_on_hold) , Event.mouse.x-30 , Event.mouse.y-30, 60, 60, 0);



    }






//-------------------------------------------------------------------------
//-------------------------------------------------------------------------


    //This draws the contents of game1.bb on the screen, that's the board pieces
    for(int f1 = 0; f1 <= 7; f1++){
        for(int f2 = 0; f2 <= 7; f2++){
        if (game1.bb[f2][f1] == 1) al_draw_scaled_bitmap(white_pawn, 0, 0, al_get_bitmap_width(white_pawn), al_get_bitmap_height(white_pawn) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);
        if (game1.bb[f2][f1] == -1) al_draw_scaled_bitmap(black_pawn, 0, 0, al_get_bitmap_width(black_pawn), al_get_bitmap_height(black_pawn) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);
        if (game1.bb[f2][f1] == 4) al_draw_scaled_bitmap(white_rook, 0, 0, al_get_bitmap_width(white_rook), al_get_bitmap_height(white_rook) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);
        if (game1.bb[f2][f1] == -4) al_draw_scaled_bitmap(black_rook, 0, 0, al_get_bitmap_width(black_rook), al_get_bitmap_height(black_rook) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);
        if (game1.bb[f2][f1] == 3) al_draw_scaled_bitmap(white_knight, 0, 0, al_get_bitmap_width(white_knight), al_get_bitmap_height(white_knight) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);
        if (game1.bb[f2][f1] == -3) al_draw_scaled_bitmap(black_knight, 0, 0, al_get_bitmap_width(black_knight), al_get_bitmap_height(black_knight) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);
        if (game1.bb[f2][f1] == 2) al_draw_scaled_bitmap(white_bishop, 0, 0, al_get_bitmap_width(white_bishop), al_get_bitmap_height(white_bishop) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);
        if (game1.bb[f2][f1] == -2) al_draw_scaled_bitmap(black_bishop, 0, 0, al_get_bitmap_width(black_bishop), al_get_bitmap_height(black_bishop) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);
        if (game1.bb[f2][f1] == 5) al_draw_scaled_bitmap(white_queen, 0, 0, al_get_bitmap_width(white_queen), al_get_bitmap_height(white_queen) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);
        if (game1.bb[f2][f1] == 6) al_draw_scaled_bitmap(white_king, 0, 0, al_get_bitmap_width(white_king), al_get_bitmap_height(white_king) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);
        if (game1.bb[f2][f1] == -5) al_draw_scaled_bitmap(black_queen, 0, 0, al_get_bitmap_width(black_queen), al_get_bitmap_height(black_queen) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);
        if (game1.bb[f2][f1] == -6) al_draw_scaled_bitmap(black_king, 0, 0, al_get_bitmap_width(black_king), al_get_bitmap_height(black_king) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);

        }
    }



        if (al_is_event_queue_empty(event_queue) ){




            //if (mode==0) game1.check_if_game_finished();


                //Display last move
                int tes1, tes2, tes3, tes4;
                tes1 = (game1.j2) * (board_size_x/8) + 15;
                tes2 = (game1.j1) * (board_size_y/8) + 5 ;
                tes3 = (game1.j4) * (board_size_x/8) + 15;
                tes4 = (game1.j3) * (board_size_y/8) + 5 ;
                al_draw_tinted_bitmap(transparent2, color3, tes1, tes2, 0);
                al_draw_tinted_bitmap(transparent2, color3, tes3, tes4, 0);


        //If mouse button is down, highlight the possible moves of the selected pawn
        if (mouse_button_is_down){
        //-----------------------------------------------------------------------------------
                int tx; tx = (mouse_from_x/(board_size_x/8));
                int ty; ty = (mouse_from_y/(board_size_y/8));

                if (Event.mouse.x < board_size_x && Event.mouse.y < board_size_y){
                vector<movement> t2;
                t2.clear();

                returnMoves(t2, tx, ty, game1.bb, game1.user_side);
                //cout<< t1.size();


                //Show possible moves when hte user clicks on a certain pawn
                for (int k = 0; k< t2.size() /*, t2.size() > 0*/; k++){
                //circle(screen, (t1[k].toy+1) * (chessb_x/8) - ((chessb_x/8)/2) , (t1[k].tox+1) * (chessb_y/8) - ((chessb_y/8)/2), 5, makecol(255,70,70));

                //void al_draw_circle(float cx, float cy, float r, ALLEGRO_COLOR color,float thickness)

                //int tes1;
                //int tes2;

                //tes1 = ((t2[k].toy+1) * (board_size_x/8) - ((board_size_x/8)/2));
                //tes2 = ((t2[k].tox+1) * (board_size_y/8) - ((board_size_y/8)/2));

                tes1 = (t2[k].toy) * (board_size_x/8) + 15;
                tes2 = (t2[k].tox) * (board_size_y/8) + 5 ;



                al_draw_tinted_bitmap(transparent, color, tes1, tes2, 0);


                //Draw circle crashes on windows 7, but works on linux
                /*
                al_draw_circle(
                            ((t2[k].toy+1) * (board_size_x/8) - ((board_size_x/8)/2)) ,
                            ((t2[k].tox+1) * (board_size_y/8) - ((board_size_y/8)/2)),
                            15.3,
                            color,
                            10.3);
                            */
                }
                //if (thinking) al_draw_text(font, al_map_rgb(255,255,255), 600, 200, 0 , "I am thinking");
               }
            }
//------------------------------------------------------------------------------------

        al_flip_display();


        }




        al_wait_for_event(event_queue, &Event);



        if( Event.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP){

        mouse_button_is_down = false;

        //If mouse button is released, save its x/y coordinates
        mouse_to_x = Event.mouse.x;
        mouse_to_y = Event.mouse.y;



                //cout<<"Mouse_x = "<<Event.mouse.x<<endl;
                //cout<<"Mouse_y = "<<Event.mouse.y<<endl;


                //cout<<"Relevant position x: "<< (mouse_to_y/(board_size_y/8)) <<endl;

                //cout<<"Relevant position y: " << (mouse_to_x/(board_size_x/8)) << endl;

                //Convert mouse's x/y coordinates into board array coordinates (0-7)(0-7)
                int temp_from_x = (mouse_from_x/(board_size_x/8));
                int temp_from_y = (mouse_from_y/(board_size_y/8));
                int temp_to_x = (mouse_to_x/(board_size_x/8));
                int temp_to_y = (mouse_to_y/(board_size_y/8));

                /*
                cout<<"____DETECTED RELEASE____________________"<<endl;
                cout<<"mouse_from_x = "<<temp_from_x<<endl;
                cout<<"mouse_from_y = "<<temp_from_y<<endl;
                cout<<"mouse_to_x = "<<temp_to_x<<endl;
                cout<<"mouse_to_y = "<<temp_to_y<<endl;
                */

                if(mode==1 && piece_selected!= -99 && Event.mouse.x <= board_size_x && Event.mouse.y <= board_size_y){
                {
                game1.bb[temp_to_y][temp_to_x] = piece_selected; piece_selected = -99;
                holding_piece = false;

                }


                }

        if (mode==0){


                //cout<<"_____________________________" <<endl;

if ( game1.gamestarted == false && game1.human_vs_human==true) {game1.user_side = game1.whostartsfirst; game1.gamestarted = true;}

                if (game1.whostartsfirst != game1.user_side && game1.gamestarted == false && game1.human_vs_human==false){

                if (game1.user_side == 1) game1.generateMove(game1.user_depth,false);
                else  if (game1.user_side == 0) game1.generateMove(game1.user_depth,true);


                game1.makeMove();
                game1.gamestarted = true;
                }
                else


                //Given click and release from mouse, and after converting, check if move is allowed
                if( (game1.move_allowed( temp_from_x, temp_from_y,temp_to_x ,temp_to_y, game1.user_side)) == true
                    //&& !(would_king_be_on_check(temp_from_x, temp_from_y, temp_to_x ,temp_to_y, game1.bb))
                    && game1.game_terminated == false
                    )
                {

                game1.j1 = temp_from_y;
                game1.j2 = temp_from_x;
                game1.j3 = temp_to_y ;
                game1.j4 = temp_to_x ;



                /*
                if (would_king_be_on_check(8, 8, 8, 8, game1.bb))
                int button = al_show_native_message_box(
                Screen,
                "King is on check",
                "King is on check",

                "",


                NULL,
                ALLEGRO_MESSAGEBOX_OK_CANCEL
                );
                */


                //cout<<"Move allowed"<<endl;
            //thinking = true;




                game1.makeMove();


                if (mode==0 && game1.game_terminated==false) {
                int test = check_if_game_finished(game1.bb);
                if (test > 0 ) game1.game_terminated = true;
                //cout<<"Test returned: " << test<<endl;
                if (test==2) {cout<< "BLACK IS CHECKMATED" << endl; game1.who_won = 1;}
                if (test==1) {cout<< "WHITE IS CHECKMATED" << endl; game1.who_won = 0;}
                if (test==3) {cout<< "GAME FINISHED IN DRAW" << endl; game1.who_won = 3;}
                cout<<"________________________________"<<endl;
                }


                /*
                //If move is allowed, make move
                game1.bb[temp_to_y][temp_to_x]= game1.bb[temp_from_y][temp_from_x];
                game1.bb[temp_from_y][temp_from_x] = 0;
                */

                cout<<"USER chose move: " << game1.j1 << ", " << game1.j2 << " -> " << game1.j3 << ", " << game1.j4 <<endl;
                cout<<"__________________________"<<endl;

                al_clear_to_color(al_map_rgb(40,40,40)); //Clear screen

                al_draw_text(font, al_map_rgb(250,250,250), board_size_x + 15, board_size_y-50, 0 , "Thinking..");

                    //Draw pawns on the screen
                al_draw_scaled_bitmap(chessboard, 0, 0, al_get_bitmap_width(chessboard), al_get_bitmap_height(chessboard), 0, 0, board_size_x, board_size_y, 0);
                al_draw_text(font, al_map_rgb(255,255,255), board_size_x + 15, 15, NULL , "Sconvolt Chess 0.99.8");


            for(int f1 = 0; f1 <= 7; f1++){
                for(int f2 = 0; f2 <= 7; f2++){
                    if (game1.bb[f2][f1] == 1) al_draw_scaled_bitmap(white_pawn, 0, 0, al_get_bitmap_width(white_pawn), al_get_bitmap_height(white_pawn) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);
                    if (game1.bb[f2][f1] == -1) al_draw_scaled_bitmap(black_pawn, 0, 0, al_get_bitmap_width(black_pawn), al_get_bitmap_height(black_pawn) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);
                    if (game1.bb[f2][f1] == 4) al_draw_scaled_bitmap(white_rook, 0, 0, al_get_bitmap_width(white_rook), al_get_bitmap_height(white_rook) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);
                    if (game1.bb[f2][f1] == -4) al_draw_scaled_bitmap(black_rook, 0, 0, al_get_bitmap_width(black_rook), al_get_bitmap_height(black_rook) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);
                    if (game1.bb[f2][f1] == 3) al_draw_scaled_bitmap(white_knight, 0, 0, al_get_bitmap_width(white_knight), al_get_bitmap_height(white_knight) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);
                    if (game1.bb[f2][f1] == -3) al_draw_scaled_bitmap(black_knight, 0, 0, al_get_bitmap_width(black_knight), al_get_bitmap_height(black_knight) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);
                    if (game1.bb[f2][f1] == 2) al_draw_scaled_bitmap(white_bishop, 0, 0, al_get_bitmap_width(white_bishop), al_get_bitmap_height(white_bishop) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);
                    if (game1.bb[f2][f1] == -2) al_draw_scaled_bitmap(black_bishop, 0, 0, al_get_bitmap_width(black_bishop), al_get_bitmap_height(black_bishop) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);
                    if (game1.bb[f2][f1] == 5) al_draw_scaled_bitmap(white_queen, 0, 0, al_get_bitmap_width(white_queen), al_get_bitmap_height(white_queen) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);
                    if (game1.bb[f2][f1] == 6) al_draw_scaled_bitmap(white_king, 0, 0, al_get_bitmap_width(white_king), al_get_bitmap_height(white_king) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);
                    if (game1.bb[f2][f1] == -5) al_draw_scaled_bitmap(black_queen, 0, 0, al_get_bitmap_width(black_queen), al_get_bitmap_height(black_queen) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);
                    if (game1.bb[f2][f1] == -6) al_draw_scaled_bitmap(black_king, 0, 0, al_get_bitmap_width(black_king), al_get_bitmap_height(black_king) , (board_size_x/8)*f1+10 , (board_size_y/8)*f2+10 , 60, 60, 0);
                    }

                }


/*
                if (mode==0 && game1.game_terminated==false) {
                int test = check_if_game_finished(game1.bb);
                if (test > 0 ) game1.game_terminated = true;
                //cout<<"Test returned: " << test<<endl;
                if (test==2) {cout<< "BLACK IS CHECKMATED" << endl; game1.who_won = 1;}
                if (test==1) {cout<< "WHITE IS CHECKMATED" << endl; game1.who_won = 0;}
                cout<<"________________________________"<<endl;
                }
*/

                al_flip_display();




            if(game1.game_terminated == false){

                if (game1.human_vs_human == false)
                {
                if (game1.user_side == 1) game1.generateMove(game1.user_depth,false);
                else  if (game1.user_side == 0) game1.generateMove(game1.user_depth,true);

                game1.makeMove();
                } else
                    {
                        if(game1.user_side==1) game1.user_side=0; else game1.user_side=1;
                    }




                if (mode==0 && game1.game_terminated==false) {
                int test = check_if_game_finished(game1.bb);
                if (test > 0 ) game1.game_terminated = true;
                //cout<<"Test returned: " << test<<endl;
                if (test==2) {cout<< "BLACK IS CHECKMATED" << endl; game1.who_won = 1;}
                if (test==1) {cout<< "WHITE IS CHECKMATED" << endl; game1.who_won = 0;}
                if (test==3) {cout<< "GAME FINISHED IN DRAW" << endl; game1.who_won = 3;}
                //cout<<"________________________________"<<endl;
                }
}

cout<<"Sconvolt Engine: Chess Board Combinations Evaluated: " << count_board_combinations << endl;
count_board_combinations = 0;
    //cout<<"bb[8][2] = " << game1.bb[8][2] << endl;


                //game1.updateGameStats();
                //bool ciao = game1.is_white_king_on_check();
            //if (would_king_be_on_check(99, 0,9,9, game1.bb, 0)) cout<<"CHECK"<<endl;
            //if (would_king_be_on_check(99, 0,9,9, game1.bb, 1)) cout<<"CHECK"<<endl;



            cout<<"King's possible moves: "<<game1.check_king_possible_moves(game1.user_side)<<endl;

                } //End of bracket for "if_move_allowed"


                thinking = false;

        }


                al_flip_display();



                cout<<"CPU chose move: " << game1.j1 << ", " << game1.j2 << " -> " << game1.j3 << ", " << game1.j4 <<endl;
                cout<<"Current Board Evaluation: "<< evaluate(game1.bb)<<endl;


/*
                if (mode==0 && game1.game_terminated==false) {
                int test = check_if_game_finished(game1.bb);
                if (test > 0 ) game1.game_terminated = true;
                //cout<<"Test returned: " << test<<endl;
                if (test==2) {cout<< "BLACK IS CHECKMATED" << endl; game1.who_won = 1;}
                if (test==1) {cout<< "WHITE IS CHECKMATED" << endl; game1.who_won = 0;}
                if (test==3) {cout<< "GAME FINISHED IN DRAW" << endl; game1.who_won = 3;}
                cout<<"________________________________"<<endl;
                }
*/
                //} //else cout<<"Move NOT allowed"<<endl;



                //if (is_move_allowed(put_y, put_x, (mouse_y/(chessb_y/8)), (mouse_x/(chessb_x/8)), board)
        }





if (game1.game_terminated == true && game1.shown_dialog_for_game_terminated== false /*&& is_checkmate(game1.bb, true)*/)
{
//al_show_native_message_box(NULL, "Error!", "Game is Finished..", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
//al_flip_display();


if (game1.who_won==3){

  int button = al_show_native_message_box(
     Screen2,
     "Draw",
     "The game finished in a draw!",
     "Sconvolt Chess, click Reset Button to play Again"
     ""
     ""
     "",
     NULL,
     NULL
  );


game1.shown_dialog_for_game_terminated = true;
}

if (game1.who_won==1){

if (game1.user_side==1)
  int button = al_show_native_message_box(
     Screen2,
     "You won",
     "You won the game!",
     "Sconvolt Chess, click Reset Button to play Again"
     ""
     ""
     "",
     NULL,
     NULL
  );


  if (game1.user_side==0)
  int button = al_show_native_message_box(
     Screen2,
     "Game Over.. try again ",
     "Game Over.. try again",
     "Sconvolt Chess, click Reset Button to play Again"
     ""
     ""
     "",
     NULL,
     NULL
  );

}




if (game1.who_won==0){

if (game1.user_side==0)
  int button = al_show_native_message_box(
     Screen2,
     "You won",
     "You won the game!",
     "Sconvolt Chess, click Reset Button to play Again"
     ""
     ""
     "",
     NULL,
     NULL
  );


  if (game1.user_side==1)
  int button = al_show_native_message_box(
     Screen2,
     "Game Over.. try again ",
     "Game Over.. try again",
     "Sconvolt Chess, click Reset Button to play Again"
     ""
     ""
     "",
     NULL,
     NULL
  );

}


cout<<"WHO WON = " <<game1.who_won<<endl;

//game1.reset();
game1.shown_dialog_for_game_terminated = true;

}


        if(Event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) ///check if a mouse button was clicked
        {
            mouse_button_is_down = true;

                mouse_from_x = Event.mouse.x;
                mouse_from_y = Event.mouse.y;

                //If reset Button is clicked
                if (is_inside_button(mouse_from_x, mouse_from_y, 910, 538, 1008, 570 )) {
                game1.reset();
                if (mode==0) game1.reset();
                if (mode==1) { game1.empty_board();

                    }
                }
                if (is_inside_button(mouse_from_x, mouse_from_y, 652, 121, 695, 157 )) game1.user_depth = 1;
                if (is_inside_button(mouse_from_x, mouse_from_y, 712, 121, 760, 157 )) game1.user_depth = 2;
                if (is_inside_button(mouse_from_x, mouse_from_y, 772, 121, 820, 157 )) game1.user_depth = 3;
                if (is_inside_button(mouse_from_x, mouse_from_y, 832, 121, 880, 157 )) game1.user_depth = 4;
                if (is_inside_button(mouse_from_x, mouse_from_y, 892, 121, 940, 157 )) game1.user_depth = 5;
                //if (is_inside_button(mouse_from_x, mouse_from_y, 952, 121, 1000, 157 )) game1.user_depth = 6;

                //cout<<"New Difficulty chosen: " << game1.user_depth<<endl;

                //if (is_inside_button(mouse_from_x, mouse_from_y, 799, 537, 887, 573 )) game1.undo();

                if (is_inside_button(mouse_from_x, mouse_from_y, 908, 483, 987, 516 ) ) Exit=true;

                if (is_inside_button(mouse_from_x, mouse_from_y, 788, 540, 887, 573 ) && mode==0 )
                int button = al_show_native_message_box(
                    Screen,
                    "",
                    "Sconvolt Chess 0.99.7, by Orest Sota",
                    "I Hope you enjoy playing! "
                    "for the latest version, visit https://sourceforge.net/projects/sconvolt/"
                    ""
                    "",
                    NULL,
                    NULL
                    );



                //If button Editor is clicked
                if ((is_inside_button(mouse_from_x, mouse_from_y, 665, 171, 767, 209 )) && mode==0) {
                game1.game_terminated = false;
                game1.reset();
                mode=1;
                game1.empty_board();
                } else

                //If Button Play is clicked
                if ((is_inside_button(mouse_from_x, mouse_from_y, 665, 171, 770, 209 )) && mode==1) {

//cout<<"Button play pressed: can game start ? : "<<game1.can_GameStart()<<endl;
                if (game1.can_GameStart()==false){
                  int button = al_show_native_message_box(
                    Screen,
                    "Game cannot start",
                    "Game cannot start without at least 1 king for each side",
                    "Click on 'Standard Board' if you want to set the default chess board"
                    ""
                    ""
                    "",
                    NULL,
                    ALLEGRO_MESSAGEBOX_OK_CANCEL
                    );
                    }
                    else {

                        if (game1.is_board_empty())
                        game1.reset();
                        game1.gamestarted = false;
                    mode=0;
                    }
                    }

                if (mode==1) //Editor mode
                {


                if (is_inside_button(mouse_from_x, mouse_from_y , 650, 220, 650+60, 220+60)) {holding_piece = true; piece_on_hold = white_rook; piece_selected = 4;}
                if (is_inside_button(mouse_from_x, mouse_from_y , 710, 220, 710+60, 220+60)) {holding_piece = true; piece_on_hold = white_knight; piece_selected = 3;}
                if (is_inside_button(mouse_from_x, mouse_from_y , 770, 220, 770+60, 220+60)) {holding_piece = true; piece_on_hold = white_bishop; piece_selected = 2;}
                if (is_inside_button(mouse_from_x, mouse_from_y , 830, 220, 830+60, 220+60)) {holding_piece = true; piece_on_hold = white_pawn; piece_selected = 1;}
                if (is_inside_button(mouse_from_x, mouse_from_y , 890, 220, 950+60, 220+60)) {holding_piece = true; piece_on_hold = white_queen; piece_selected = 5;}
                if (is_inside_button(mouse_from_x, mouse_from_y , 950, 220, 950+60, 220+60)) {holding_piece = true; piece_on_hold = white_king; piece_selected = 6;}

                if (is_inside_button(mouse_from_x, mouse_from_y , 650, 300, 650+60, 300+60)) {holding_piece = true; piece_on_hold = black_rook;piece_selected = -4;}
                if (is_inside_button(mouse_from_x, mouse_from_y , 710, 300, 710+60, 300+60)) {holding_piece = true; piece_on_hold = black_knight;piece_selected = -3;}
                if (is_inside_button(mouse_from_x, mouse_from_y , 770, 300, 770+60, 300+60)) {holding_piece = true; piece_on_hold = black_bishop;piece_selected = -2;}
                if (is_inside_button(mouse_from_x, mouse_from_y , 830, 300, 830+60, 300+60)) {holding_piece = true; piece_on_hold = black_pawn;piece_selected = -1;}
                if (is_inside_button(mouse_from_x, mouse_from_y , 890, 300, 890+60, 300+60)) {holding_piece = true; piece_on_hold = black_queen;piece_selected = -5;}
                if (is_inside_button(mouse_from_x, mouse_from_y , 950, 300, 950+60, 300+60)) {holding_piece = true; piece_on_hold = black_king;piece_selected = -6;}

                if (is_inside_button(mouse_from_x, mouse_from_y , 661, 433, 755, 466)) {game1.user_side = 1; game1.human_vs_human = false;}
                if (is_inside_button(mouse_from_x, mouse_from_y , 781, 433, 867, 466)) {game1.user_side = 0; game1.human_vs_human = false;}

                if (is_inside_button(mouse_from_x, mouse_from_y , 890, 433, 990, 466)) game1.human_vs_human = true;

                if (is_inside_button(mouse_from_x, mouse_from_y , 661, 537, 755, 570)) {game1.whostartsfirst = 1;}
                if (is_inside_button(mouse_from_x, mouse_from_y , 781, 536, 867, 570)) {game1.whostartsfirst = 0;}



                if (is_inside_button(mouse_from_x, mouse_from_y , 821, 381, 1024, 417)) game1.reset();




    if (game1.whostartsfirst==1) al_draw_tinted_bitmap(whiteb, color2, 657, 533, NULL); else al_draw_tinted_bitmap(whiteb, color, 657, 533, NULL);
   if (game1.whostartsfirst==0) al_draw_tinted_bitmap(blackb, color2, 657+120, 533, NULL); else al_draw_tinted_bitmap(blackb, color, 657 + 120, 533, NULL);



                }


        }


        //Close when the user presses X
        if(Event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            Exit = true;
        }

} //End of bracket corresponding to the game loop

    al_destroy_event_queue(event_queue);
    al_destroy_display(Screen);

    return 0;
}
