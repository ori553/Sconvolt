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




#include <vector>
#include <iostream>

class Sconvolt {
public:

    int j1=8,j2=8,j3=8,j4=8;
    int user_depth = 3;
    //bool user_side = true;

    bool shown_dialog_for_game_terminated = false;
    bool game_terminated = false;
    int who_won = -5;
    int user_side = 1; //1 for white, 0 for black

    bool gamestarted = false;
    int whostartsfirst = 1; //1 for white, 0 for black


    bool human_vs_human = false;

    int lastmovej1, lastmovej2, lastmovej3, lastmovej4;

    vector<movement> history;


    int  bb[9][8]


     = {
                    {-4,-3,-2,-5,-6,-2,-3,-4},
                    {-1,-1,-1,-1,-1,-1,-1,-1},
                    { 0, 0, 0, 0, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0},
                    { 1, 1, 1, 1, 1, 1, 1, 1},
                    { 4, 3, 2, 5, 6, 2, 3, 4},
                    { 1, 1, 1, 1, 1, 1, 1, 1}
                    };





    int  standard_bb[9][8] //copied to the current bb when reset is called
     = {
                    {-4,-3,-2,-5,-6,-2,-3,-4},
                    {-1,-1,-1,-1,-1,-1,-1,-1},
                    { 0, 0, 0, 0, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0},
                    { 1, 1, 1, 1, 1, 1, 1, 1},
                    { 4, 3, 2, 5, 6, 2, 3, 4},
                    { 1, 1, 1, 1, 1, 1, 1, 1}
                    };

///bb info:
/*
bb[8][0] = true; //Down-Right
bb[8][1] = true; //Down-Left
bb[8][2] = true; //UP-Right
bb[8][3] = true; //UP-Left

[8][4] If it's 0, white didn't castle, if it's 1, white castled
[8][5]If it's 0, black didn't castle, if it's 1, black castled

[8][6] = 0 If last move was a pawn that moved 2 squares at a time
[8][7] = 0; If en/passant happened
*/

int AlphaBetaMin( int alpha, int beta, int depth, bool sid);
int AlphaBetaMax( int alpha, int beta, int depth, bool sid);

bool move_allowed (int startx, int starty, int tox, int toy, int side);
void generateMove(int strength, int side);
void makeMove();
void reset();
void empty_board();
void undo();
bool is_board_empty();
bool can_GameStart();
bool is_white_king_on_check();
int check_king_possible_moves(int side);


//bool would_king_be_on_check(int x1, int  y1, int x2, int y2, int tem_bb[][8]);

//int check_if_game_finished(int t1bb[][8]);

void showBoard();



};

int check_if_game_finished(int t1bb[9][8]);

void Sconvolt::makeMove(){


//-------------------------------------------------FOR CASTLING
//Cancel castling DOWN-RIGHT
if (bb[j1][j2] == 6) bb[8][0] = false; //If White King moved, cancel the right to castle
if (j1==7 && j2 == 7) bb[8][0] = false; //If White Rook on the right moved, cancel the right to castle

//Cancel castling DOWN-LEFT
if (bb[j1][j2] == 6) bb[8][1] = false; //If White King moved, cancel the right to castle
if (j1==7 && j2 == 0) bb[8][1] = false; //If White Rook on the right moved, cancel the right to castle


//Cancel castling UP-RIGHT
if (bb[j1][j2] == -6) bb[8][2] = false; //If White King moved, cancel the right to castle
if (j1==0 && j2 == 7) bb[8][2] = false; //If White Rook on the right moved, cancel the right to castle


if (bb[j1][j2] == -6) bb[8][3] = false; //If White King moved, cancel the right to castle
if (j1==0 && j2 == 0) bb[8][3] = false; //If White Rook on the right moved, cancel the right to castle



///[8][4]
///If it's 0, white didn't castle, if it's 1, white castled
///[8][5]
///If it's 0, black didn't castle, if it's 1, black castled


//DOWN RIGHT, If Castling move is detected, move rook too
if (j1 == 7 && j2 == 4 && j3 == 7 && j4 ==6) {bb[7][5] = 4; bb[7][7] = 0; bb[8][4] = 1;}

//DOWN LEFT, If Castling move is detected, move rook too
if (j1 == 7 && j2 == 4 && j3 == 7 && j4 ==2) {bb[7][3] = 4; bb[7][0] = 0; bb[8][4] = 1;}

//UP-RIGHT, If Castling move is detected, move rook too
if (j1 == 0 && j2 == 4 && j3 == 0 && j4 ==6) {bb[0][5] = -4; bb[0][7] = 0; bb[8][5] = 1;}

//UP-LEFT, If Castling move is detected, move rook too
if (j1 == 0 && j2 == 4 && j3 == 0 && j4 ==2) {bb[0][3] = -4; bb[0][0] = 0; bb[8][5] = 1;}

//---------------------------------------------------------------------------------------

//Pawn moving 2 squares detection, if it's true, bb[8][6] = 1; otherwise else bb[8][6] = 0;
if ((bb[j1][j2] == 1 && j1==6 && j3==4) || (bb[j1][j2] == -1 && j1==1 && j3==3))
        {
            bb[8][6] = 1;
            cout<<"Pawn moved 2 squares detected" << endl;
        }

        else bb[8][6] = 0;


//----------------------FOR THE MOVE-----------------------------------------------------
                bb[j3][j4]= bb[j1][j2];
                bb[j1][j2] = 0;

                movement temp;
                temp.startx = j1;
                temp.starty = j2;
                temp.tox = j3;
                temp.toy = j4;
                history.push_back(temp);

//--------------------------------------FOR SWITCH TO QUEEN----------------------------
                //Change to queen if pawn reaches the limit
                for (int i = 0; i<= 7; i++) if (bb[0][i] == 1) bb[0][i] = 5;

                for (int i = 0; i<= 7; i++) if (bb[7][i] == -1) bb[7][i] = -5;
//-------------------------------------------------------------------------------------
}


void Sconvolt::showBoard(){
cout<<"Board: "<<endl;
            for (int t1 = 0; t1<= 7; t1++){
                for (int t2 = 0; t2<=7; t2++){
                cout<<bb[t1][t2];
                if (bb[t1][t2]<0) cout<<"  ";
                else cout<<"   ";

                }
                cout<<endl;
            }

}




bool Sconvolt::move_allowed (int startx, int starty, int tox, int toy, int side)

{


//Extract possible moves for the starting cell, if no move is found between the possible moves, then the move is not allowed

    if ((startx == tox) && (starty == toy)) {
        //cout<<"same position click detected, move not allowed"<<endl;
        return false;
        }

    if (bb[starty][startx] == 0) return false;

    vector<movement> t1;
    t1.clear();
    //t1 = returnMoves(startx, starty, bb, 1);

    //returnMoves(t1, startx, starty, bb, 1);

    returnMoves(t1, startx, starty, bb, side);


    //Move is allowed only if the move will not bring the king into check


    if (would_king_be_on_check(startx, starty, tox ,toy, bb, side))
    //if (this->move_allowed(startx, starty, tox, toy, side))
    {

    /*
        int button = al_show_native_message_box(
     Screen,
     "King",
     "Watch your King, you can't make that move",
     ""
     ""
     "",
     NULL,
     NULL
        );
    */

    cout<<"If you make that move, the king would be in check, not allowed ";
    return false;
    }


    for (int k = 0; k< t1.size() /*&& t1.size()>0*/; k++){
    if (
        (startx == t1[k].starty) &&
        (starty == t1[k].startx) &&
        (tox == t1[k].toy) &&
        (toy == t1[k].tox)

    )
    {
       if((bb[t1[k].startx][t1[k].starty] >0) && side == true ) return true;
       //else
       if((bb[t1[k].startx][t1[k].starty] <0) && side == false ) return true;
    }

    }

//cout<<"Move not allowed"<<endl;

return false;
}

void Sconvolt::generateMove(int strength, int side)
{

user_depth = strength;

    if (side == false) AlphaBetaMin(-30000, 30000, user_depth, /*side*/ false);

    if (side == true) AlphaBetaMax(-30000, 30000, user_depth, /*side*/ true);

}


void Sconvolt::reset()
{


j1=8; j2=8; j3=8;j4=8;

                for (int i = 0; i<=7 ; i++)
                for (int j = 0; j<= 7 ; j++)
                bb[i][j]= standard_bb[i][j];

    bool castling_down_right = true;
    bool castling_down_left = true;

//Castling rights back to true
bb[8][0] = 1;
bb[8][1] = 1;
bb[8][2] = 1;
bb[8][3] = 1;

bb[8][4] = 0; //If it's 0, white didn't castle, if it's 1, white castled
bb[8][5] = 0; //If it's 0, black didn't castle, if it's 1, black castled

bb[8][6] = 0; //If last move was a pawn that moved 2 squares at a time
bb[8][7] = 0; //If en/passant happened

gamestarted = false;

                history.clear();
                //user_side = 1;
                game_terminated = false;
                shown_dialog_for_game_terminated=false;
}


void Sconvolt::empty_board()
{

                for (int i = 0; i<=7 ; i++)
                for (int j = 0; j<= 7 ; j++)
                bb[i][j]= 0;

                history.clear();

}

bool Sconvolt::is_board_empty()
{

                for (int i = 0; i<=7 ; i++)
                for (int j = 0; j<= 7 ; j++)
                if (bb[i][j]!=0) return false;

    return true;

}

void Sconvolt::undo()
{
cout<<"Undo clicked"<<endl;
}

int Sconvolt::check_king_possible_moves(int side)
{
int k_x1;
int k_y1;

if (side==1){
                //Look for white king
                for (int i = 0; i<=7 ; i++){
                    for (int j = 0 ;j<= 7 ; j++){
                    if (bb[i][j]==6){
                    k_x1 = j;
                    k_y1 = i;
                            }
                        }
                    }
            }


if (side==0){
                //Look for black king
                for (int i = 0; i<=7 ; i++){
                    for (int j = 0 ;j<= 7 ; j++){
                    if (bb[i][j]==-6){
                    k_x1 = j;
                    k_y1 = i;
                            }
                        }
                    }
                }

    vector<movement> t4;
    t4.clear();
    //t1 = returnMoves(startx, starty, bb, 1);

    //returnMoves(t1, startx, starty, bb, 1);

    returnMoves(t4, k_x1, k_y1, bb, side);

    return t4.size();



}





//Sconvolt::check_if_game_finished(), It must be used in the main menu because it terminates the game

//Another way to use it is to return a value;
//returns 1 IF WHITE IS CHECKMATED
// returns 2 IF BLACK IS CHECKMATED
// returns -99 IF NO-ONE IS CHECKMATED

int check_if_game_finished(int t1bb[9][8])
{

    vector<movement> t5;
    t5.clear();







int solutions = 0;
    //If the king is in check, try all the possible moves, if in all of them the king is in check, then it's checkmte
    if (would_king_be_on_check(99, 99, 99, 99, t1bb, 1)){
        //cout<<"CHECK"<<endl;
    //if (check_king_possible_moves(1) < 1)
    //cout<<"Now analyzing possible moves:" << endl;
    {

    vector<movement> t5;
    t5.clear();


    //check all possible moves for whites
    for (int i = 0; i<=7 ; i++){
        for (int j = 0 ;j<= 7 ; j++){
            if (t1bb[i][j]>0 ){

            returnMoves(t5, j, i, t1bb, 1);

                            }
                        }
                    }



    //cout<<"White's possible moves:" << t5.size() << endl;

    //Try each move
    for (int k = 0; k< t5.size() ; k++)
    {
    //cout<<k << ": Considering move: " << t5[k].startx << ", " << t5[k].starty << " (" << bb[t5[k].startx][t5[k].starty] << "), " << t5[k].tox << ", " << t5[k].toy << " :";

            //cout<<"Now checking if the King would be in check: " ;
        //If you find a move that results in the king NOT being in check, then it's not checkmate
            if ((would_king_be_on_check(t5[k].starty, t5[k].startx, t5[k].toy ,t5[k].tox, t1bb, 1)))
            {

                //cout<<"Yes, " << endl;
                //cout<<"....." << endl;
            } else {/*cout<<k << ": Considering move: " << t5[k].startx << ", " << t5[k].starty << " (" << t1bb[t5[k].startx][t5[k].starty] << "), " << t5[k].tox << ", " << t5[k].toy << " :"; cout<< "NO, That's a SOLUTION!"<<endl;*/ solutions++;}

    //cout<< endl;
    }

//cout<<"SOLUTIONS FOUND:" << solutions << endl;

        if (solutions == 0)
        {
            //cout<<"Couldn't find a solution for your king after check, it's CHECKMATE " <<endl;

            //game_terminated = true;
            /*
            if (this-> user_side == 1) {who_won = 0; return 1;}
            if (this-> user_side == 0) {who_won = 1; return 2;}*/

            return 1;   //Return 2 = White is checkmated
        }

    }
}







solutions = 0;






//cout<<"_______________________________________________"<<endl;
//Check IF the CPU is checkmated
    //If the king is in check, try all the possible moves, if in all of them the king is in check, then it's checkmte
    if (would_king_be_on_check(99, 99, 99, 99, t1bb, 0)){
        //cout<<"CHECK"<<endl;
    //if (check_king_possible_moves(1) < 1)
    //cout<<"Now analyzing possible moves FOR OPPONENT:" << endl;
    {

    vector<movement> t5;
    t5.clear();


    //if (this->user_side == swi)
    //check all possible moves
    //check all possible moves
    for (int i = 0; i<=7 ; i++){
        for (int j = 0 ;j<= 7 ; j++){
            if (t1bb[i][j]<0 ){

            returnMoves(t5, j, i, t1bb, 0);

                            }
                        }
                    }


   // cout<<"OPPONENT's possible moves:" << t5.size() << endl;

    //Try each move
    for (int k = 0; k< t5.size() ; k++)
    {
    //cout<<k << ": Considering move: " << t5[k].startx << ", " << t5[k].starty << " (" << bb[t5[k].startx][t5[k].starty] << "), " << t5[k].tox << ", " << t5[k].toy << " :";

            //cout<<"Now checking if the King would be in check: " ;
        //If you find a move that results in the king NOT being in check, then it's not checkmate
            if ((would_king_be_on_check(t5[k].starty, t5[k].startx, t5[k].toy ,t5[k].tox, t1bb, 0)))
            {

                //cout<<"Yes, " << endl;
                //cout<<"....." << endl;
            } else {/*cout<<k << ": Considering move: " << t5[k].startx << ", " << t5[k].starty << " (" << t1bb[t5[k].startx][t5[k].starty] << "), " << t5[k].tox << ", " << t5[k].toy << " :"; cout<< "NO, That's a SOLUTION!"<<endl;*/ solutions++;}

    //cout<< endl;
    }

//cout<<"SOLUTIONS FOUND:" << solutions << endl;

        if (solutions == 0)
        {
            //cout<<"Couldn't find a solution for OPPONENT's king after check, it's CHECKMATE " <<endl;

            return 2; //Return 2 = Black is checkmated

        }

    }
}









//Check if draw, draw happens when there are no legal moves and the king is not in check
//if (side==0){
                for (int i = 0; i<=7 ; i++){
                    for (int j = 0 ;j<= 7 ; j++){
                    if (t1bb[i][j]<0){

                    returnMoves(t5, j, i, t1bb, 0);


                            }
                        }
                    }
           // }
//cout<<"_______________"<<endl;
//cout<<"Black possible moves:" << t5.size()<<endl;

if (t5.size()<1)
    //if (!(would_king_be_on_check(99, 99, 99 ,99, t1bb, 0)))
        {
            cout<<"RETURNING DRAW BECAUSE BLACK CAN'T MOVE AND IS NOT IN CHECK " << endl;
            return 3; //return 3 is draw
        }
//***************************************************
t5.clear();
//if (side==1){
                //Look for white king
                for (int i = 0; i<=7 ; i++){
                    for (int j = 0 ;j<= 7 ; j++){
                    if (t1bb[i][j]>0){

                    returnMoves(t5, j, i, t1bb, 1);


                            }
                        }
                    }
           // }

           //cout<<"White possible moves:" << t5.size()<<endl;

           //cout<<"_______________"<<endl;

if (t5.size() < 1)
    //if (!(would_king_be_on_check(99, 99, 99 ,99, t1bb, 1)))
    {
        cout<<"RETURNING DRAW BECAUSE WHITE CAN'T MOVE AND IS NOT IN CHECK " << endl;
        return 3; //return 3 is draw

    }
//*************************************************





return -99;


}



bool Sconvolt::can_GameStart()
{
bool found_white_king; found_white_king = false;
bool found_black_king; found_black_king = false;


                for (int i = 0; i<=7 ; i++){
                for (int j = 0; j<= 7 ; j++){
                if (bb[i][j]== 6)  found_white_king = true;
                if (bb[i][j]== -6) found_black_king = true;
                }
            }

if ((found_white_king == true) && (found_black_king == true) )

return true;

else

return false;


}



bool is_inside_button(int mouse_x, int mouse_y, int x, int y, int tox, int toy)
{
if (
    ((mouse_x >= x) && (mouse_x <= tox))
        &&
        ((mouse_y >= y) && (mouse_y <= toy))
            ) return true;


return false;
}





//To check if the king is in check, pretent the king is is the rook, the knight, the queen, and see if it can be reached from one of them

bool Sconvolt::is_white_king_on_check()
{




return false;
}


//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

//If first parameter is 99, check if the king is in check, without any hypothetical moves
bool would_king_be_on_check(int x1, int  y1, int x2, int y2, int t_bb[9][8], int sidee)
{

int k_x1=0;
int k_y1=0;

int tem_bb[8][8];




                for (int i = 0; i<=7 ; i++)
                for (int j = 0; j<= 7 ; j++)
                    tem_bb[i][j] = t_bb[i][j];



//If first parameter is 99, check if the king is in check, without any hypothetical moves
//Note, it doesn't make any move if the first parameter is 99
if (x1 != 99){
    //make temporary move
    tem_bb[y2][x2]= tem_bb[y1][x1];
    tem_bb[y1][x1] = 0;
    }



//int x1, y1;

if (sidee==1){
                //Look for white king
                for (int i = 0; i<=7 ; i++){
                    for (int j = 0 ;j<= 7 ; j++){
                    if (tem_bb[i][j]==6){
                    k_x1 = j;
                    k_y1 = i;

                    }

                    }
                }
}



if (sidee==0){
                //Look for black king
                for (int i = 0; i<=7 ; i++){
                    for (int j = 0 ;j<= 7 ; j++){
                    if (tem_bb[i][j]== -6){
                    k_x1 = j;
                    k_y1 = i;

                    }

                    }
                }
}





if (sidee == 1){
        //Move like white Rook
        for (int x = k_y1, y = k_x1, co = 0; inside_board(x,y);  x--, co++ ){
        if (tem_bb[x][y] == -4 || tem_bb[x][y] == -5) {return true;}
        if (tem_bb[x][y] != 0 && co>0) break;
        }
        for (int x = k_y1, y = k_x1, co = 0; inside_board(x,y) ; x++, co++ ){
        if (tem_bb[x][y] == -4 || tem_bb[x][y] == -5) {return true;}
        if (tem_bb[x][y] != 0 && co>0) break;
        }
        for (int x = k_y1, y = k_x1, co = 0; inside_board(x,y) ; y--, co++ ){
        if (tem_bb[x][y] == -4 || tem_bb[x][y] == -5) {return true;}
        if (tem_bb[x][y] != 0 && co>0) break;
        }
        for (int x = k_y1, y = k_x1, co = 0; inside_board(x,y) ; y++, co++ ){
        if (tem_bb[x][y] == -4 || tem_bb[x][y] == -5) {return true;}
        if (tem_bb[x][y] != 0 && co>0) break;
        }





        //Move like white Bishop
        for (int x = k_y1, y = k_x1, co = 0; inside_board(x,y);  x--, y--,  co++ ){
        if (tem_bb[x][y] == -2 || tem_bb[x][y] == -5) {return true;}
        if (tem_bb[x][y] != 0 && co>0) break;
        }
        for (int x = k_y1, y = k_x1, co = 0; inside_board(x,y) ; x++, y++, co++ ){
        if (tem_bb[x][y] == -2 || tem_bb[x][y] == -5) {return true;}
        if (tem_bb[x][y] != 0 && co>0) break;
        }
        for (int x = k_y1, y = k_x1, co = 0; inside_board(x,y) ; x--, y++, co++ ){
        if (tem_bb[x][y] == -2 || tem_bb[x][y] == -5){return true;}
        if (tem_bb[x][y] != 0 && co>0) break;
        }
        for (int x = k_y1, y = k_x1, co = 0; inside_board(x,y) ; x++, y--, co++ ){
        if (tem_bb[x][y] == -2 || tem_bb[x][y] == -5) {return true;}
        if (tem_bb[x][y] != 0 && co>0) break;
        }


        //Move like white horse
        if (inside_board(k_y1-2, k_x1+1)) if (tem_bb[k_y1-2][k_x1+1] == -3  ) {return true;}
        if (inside_board(k_y1-2, k_x1-1)) if (tem_bb[k_y1-2][k_x1-1] == -3  ) {return true;}
        if (inside_board(k_y1+2, k_x1+1)) if (tem_bb[k_y1+2][k_x1+1] == -3  ) {return true;}
        if (inside_board(k_y1+2, k_x1-1)) if (tem_bb[k_y1+2][k_x1-1] == -3  ) {return true;}

        if (inside_board(k_y1-1, k_x1+2)) if (tem_bb[k_y1-1][k_x1+2] == -3  ) {return true;}
        if (inside_board(k_y1-1, k_x1-2)) if (tem_bb[k_y1-1][k_x1-2] == -3  ) {return true;}
        if (inside_board(k_y1+1, k_x1-2)) if (tem_bb[k_y1+1][k_x1-2] == -3  ) {return true;}
        if (inside_board(k_y1+1, k_x1+2)) if (tem_bb[k_y1+1][k_x1+2] == -3  ) {return true;}

        //Pawn
        if (inside_board(k_y1-1, k_x1+1)) if (tem_bb[k_y1-1][k_x1+1] == -1) {return true;}
        if (inside_board(k_y1-1, k_x1-1)) if (tem_bb[k_y1-1][k_x1-1] == -1) {return true;}




        //King
        if (inside_board(k_y1-1, k_x1+1)) if (tem_bb[k_y1-1][k_x1+1] == -6 ) {return true;}
        if (inside_board(k_y1-1, k_x1-1)) if (tem_bb[k_y1-1][k_x1-1] == -6  ) {return true;}
        if (inside_board(k_y1-1, k_x1))   if (tem_bb[k_y1-1][k_x1] == -6  ) {return true;}
        if (inside_board(k_y1, k_x1+1))   if (tem_bb[k_y1][k_x1+1] == -6  ) {return true;}
        if (inside_board(k_y1, k_x1-1))   if (tem_bb[k_y1][k_x1-1] == -6 ) {return true;}
        if (inside_board(k_y1+1, k_x1))   if (tem_bb[k_y1+1][k_x1] == -6  ) {return true;}
        if (inside_board(k_y1+1, k_x1-1))   if (tem_bb[k_y1+1][k_x1-1] == -6  ) {return true;}
        if (inside_board(k_y1+1, k_x1+1))   if (tem_bb[k_y1+1][k_x1+1] == -6  ) {return true;}



/*
        if ( (tem_bb[k_y1-1][k_x1] == -6 )) {cout<<"UP:would be on check, yes,  temp["<<k_y1-1<<"]["<<k_x1<<"] = "<<tem_bb[k_y1-1][k_x1]<<"     "  ; return true;}
        if (tem_bb[k_y1+1][k_x1] == -6  ) {cout<<"DOWN: would be on check, yes,  temp["<<k_y1+1<<"]["<<k_x1<<"] = "<<tem_bb[k_y1+1][k_x1]<<"     " ;return true;}
        if (tem_bb[k_y1][k_x1+1] == -6 ) {cout<<"RIGHT: would be on check, yes,  temp["<<k_y1<<"]["<<k_x1+1<<"] = "<<tem_bb[k_y1][k_x1+1]<<"     "  ;return true;}
        if (tem_bb[k_y1][k_x1-1] == -6 && k_x1 >=0 && k_y1 >=0 ) {cout<<"LEFT, would be on check, yes, temp["<<k_y1<<"]["<<k_x1-1<<"] = "<<tem_bb[k_y1][k_x1-1]<<"     ";return true;}
        if (tem_bb[k_y1+1][k_x1-1] == -6  ) {cout<<"would be on check, yes,   ";return true;}
        if (tem_bb[k_y1-1][k_x1-1] == -6  ) {cout<<"would be on check, yes,   ";return true;}
        if (tem_bb[k_y1+1][k_x1+1] == -6  ) {cout<<"would be on check, yes,   ";return true;}
        if (tem_bb[k_y1-1][k_x1+1] == -6  ) {cout<<"would be on check, yes,   ";return true;}
*/



        return false;
} //end of "if side==1" bracket






//If side == 0, 0 is black
if (sidee == 0){
        //Move like black Rook
        for (int x = k_y1, y = k_x1, co = 0; inside_board(x,y);  x--, co++ ){
        if (tem_bb[x][y] == 4 || tem_bb[x][y] == 5) {return true;}
        if (tem_bb[x][y] != 0 && co>0) break;
        }
        for (int x = k_y1, y = k_x1, co = 0; inside_board(x,y) ; x++, co++ ){
        if (tem_bb[x][y] == 4 || tem_bb[x][y] == 5) {return true;}
        if (tem_bb[x][y] != 0 && co>0) break;
        }
        for (int x = k_y1, y = k_x1, co = 0; inside_board(x,y) ; y--, co++ ){
        if (tem_bb[x][y] == 4 || tem_bb[x][y] == 5) {return true;}
        if (tem_bb[x][y] != 0 && co>0) break;
        }
        for (int x = k_y1, y = k_x1, co = 0; inside_board(x,y) ; y++, co++ ){
        if (tem_bb[x][y] == 4 || tem_bb[x][y] == 5) {return true;}
        if (tem_bb[x][y] != 0 && co>0) break;
        }





        //Move like black Bishop
        for (int x = k_y1, y = k_x1, co = 0; inside_board(x,y);  x--, y--,  co++ ){
        if (tem_bb[x][y] == 2 || tem_bb[x][y] == 5) {return true;}
        if (tem_bb[x][y] != 0 && co>0) break;
        }
        for (int x = k_y1, y = k_x1, co = 0; inside_board(x,y) ; x++, y++, co++ ){
        if (tem_bb[x][y] == 2 || tem_bb[x][y] == 5) {return true;}
        if (tem_bb[x][y] != 0 && co>0) break;
        }
        for (int x = k_y1, y = k_x1, co = 0; inside_board(x,y) ; x--, y++, co++ ){
        if (tem_bb[x][y] == 2 || tem_bb[x][y] == 5){return true;}
        if (tem_bb[x][y] != 0 && co>0) break;
        }
        for (int x = k_y1, y = k_x1, co = 0; inside_board(x,y) ; x++, y--, co++ ){
        if (tem_bb[x][y] == 2 || tem_bb[x][y] == 5) {return true;}
        if (tem_bb[x][y] != 0 && co>0) break;
        }


        //Move like black horse
        if (inside_board(k_y1-2, k_x1+1)) if (tem_bb[k_y1-2][k_x1+1] == 3  ) {return true;}
        if (inside_board(k_y1-2, k_x1-1)) if (tem_bb[k_y1-2][k_x1-1] == 3  ) {return true;}
        if (inside_board(k_y1+2, k_x1+1)) if (tem_bb[k_y1+2][k_x1+1] == 3  ) {return true;}
        if (inside_board(k_y1+2, k_x1-1)) if (tem_bb[k_y1+2][k_x1-1] == 3  ) {return true;}

        if (inside_board(k_y1-1, k_x1+2)) if (tem_bb[k_y1-1][k_x1+2] == 3  ) {return true;}
        if (inside_board(k_y1-1, k_x1-2)) if (tem_bb[k_y1-1][k_x1-2] == 3  ) {return true;}
        if (inside_board(k_y1+1, k_x1-2)) if (tem_bb[k_y1+1][k_x1-2] == 3  ) {return true;}
        if (inside_board(k_y1+1, k_x1+2)) if (tem_bb[k_y1+1][k_x1+2] == 3  ) {return true;}

        //Move like black Pawn
        if (inside_board(k_y1+1, k_x1+1)) if (tem_bb[k_y1+1][k_x1+1] == 1) {return true;}
        if (inside_board(k_y1+1, k_x1-1)) if (tem_bb[k_y1+1][k_x1-1] == 1) {return true;}


        //black King
        if (inside_board(k_y1-1, k_x1+1)) if (tem_bb[k_y1-1][k_x1+1] == 6 ) {return true;}
        if (inside_board(k_y1-1, k_x1-1)) if (tem_bb[k_y1-1][k_x1-1] == 6  ) {return true;}
        if (inside_board(k_y1-1, k_x1))   if (tem_bb[k_y1-1][k_x1] == 6  ) {return true;}
        if (inside_board(k_y1, k_x1+1))   if (tem_bb[k_y1][k_x1+1] == 6  ) {return true;}
        if (inside_board(k_y1, k_x1-1))   if (tem_bb[k_y1][k_x1-1] == 6 ) {return true;}
        if (inside_board(k_y1+1, k_x1))   if (tem_bb[k_y1+1][k_x1] == 6  ) {return true;}
        if (inside_board(k_y1+1, k_x1-1))   if (tem_bb[k_y1+1][k_x1-1] == 6  ) {return true;}
        if (inside_board(k_y1+1, k_x1+1))   if (tem_bb[k_y1+1][k_x1+1] == 6  ) {return true;}

        return false;
} //end of "if side==0" bracket



return false;
}





bool is_checkmate(int t_bb[][8], int sidee)
{

    vector<movement> t5;
    t5.clear();

    //check all possible moves
    for (int i = 0; i<=7 ; i++){
        for (int j = 0 ;j<= 7 ; j++){
            if (t_bb[i][j]>0){

                returnMoves(t5, i, j, t_bb, true);

                            }
                        }
                    }

    //try each move
    for (int k = 0; k< t5.size() /*&& t5.size()>0*/; k++)
    {
        if (would_king_be_on_check(t5[k].startx, t5[k].starty, t5[k].tox ,t5[k].toy, t_bb, sidee))
        cout<<"King would be on check"<<endl;

    }





return false;
}




