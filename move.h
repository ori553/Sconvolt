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

bool would_king_be_on_check(int x1, int  y1, int x2, int y2, int tem_bb[9][8], int side);

using namespace std;

class movement{
public:
int startx;
int starty;
int tox;
int toy;


};

bool inside_board(int endx, int endy){
if (   (endx >= 0 && endx <= 7 ) && (endy >= 0 && endy <= 7 )    )
            return true;
                else {return false;}
}


void returnMoves(vector<movement>& moves, int startx, int starty, int bb[9][8], int side){


movement adding;


if ((inside_board(startx, starty)) == false) exit;

        int x1 = startx;
        int y1 = starty;
        //int x2 = toy+1;
        //int y2 = tox+1;

        adding.startx = starty;
        adding.starty = startx;

//if (side==1){
    //Check in case of white pawn
    if (bb[y1][x1]==1){
        if (bb[y1-1][x1] == 0 && inside_board(y1-1, x1 )) {adding.toy = x1; adding.tox = y1-1; moves.push_back(adding);}
        if (bb[y1-1][x1+1] <0 && inside_board(y1-1, x1+1) ) {adding.toy = x1+1; adding.tox = y1-1; moves.push_back(adding);}
        if (bb[y1-1][x1-1] <0 && inside_board(y1-1, x1-1) ) {adding.toy = x1-1; adding.tox = y1-1; moves.push_back(adding);}
        if (inside_board(y1-2, x1)) if (y1 == 6 && bb[y1-2][x1] <= 0 && bb[y1-2][x1]==0 && bb[y1-1][x1]==0) {adding.toy = x1; adding.tox = y1-2; moves.push_back(adding);}

/*
        //En passant on the left
        if (bb[8][6]==1 && bb[y1][x1-1] == -1 && bb[8][7] == 0) {adding.toy = x1-1; adding.tox = y1-1; moves.push_back(adding);}

        //En passant on the right
        if (bb[8][6]==1 && bb[y1][x1+1] == -1 && bb[8][7] == 0) {adding.toy = x1+1; adding.tox = y1+1; moves.push_back(adding);}
*/

    }


    //Check in case of white bishop
    if (bb[y1][x1]==2){
        for (int x = x1, y = y1; inside_board(x,y) ; x--,y-- ){
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] < 0 ) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        if (bb[y][x] > 0 && x !=startx && y!= starty ) { break; }

        }
        for (int x = x1, y = y1; inside_board(x,y) ; x++,y++ ){
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] < 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        if (bb[y][x] > 0 && x !=startx && y!= starty ) { break; }
        }
        for (int x = x1, y = y1; inside_board(x,y) ; x--,y++ ){
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] < 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        if (bb[y][x] > 0 && x !=startx && y!= starty ) { break; }
        }
        for (int x = x1, y = y1; inside_board(x,y) ; x++,y-- ){
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] < 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        if (bb[y][x] > 0 && x !=startx && y!= starty ) { break; }
        }

    }


    //Check in case of white Knight
    if (bb[y1][x1]==4){
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; x--, co++ ){
        if (bb[y][x] > 0  && co>0) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] < 0 ) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; x++, co++ ){
        if (bb[y][x] > 0 && co>0 ) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] < 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; y--, co++ ){
        if (bb[y][x] > 0 && co>0 ) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] < 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; y++, co++ ){
        if (bb[y][x] > 0 && co>0) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] < 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }


    }

    //In case of White horse
    if (bb[y1][x1]==3){
        if (inside_board(y1-2, x1+1)) if (bb[y1-2][x1+1] <=0  ) {adding.toy = x1+1; adding.tox = y1-2; moves.push_back(adding);}
        if (inside_board(y1-2, x1-1)) if (bb[y1-2][x1-1] <=0  ) {adding.toy = x1-1; adding.tox = y1-2; moves.push_back(adding);}
        if (inside_board(y1+2, x1+1)) if (bb[y1+2][x1+1] <=0  ) {adding.toy = x1+1; adding.tox = y1+2; moves.push_back(adding);}
        if (inside_board(y1+2, x1-1)) if (bb[y1+2][x1-1] <=0  ) {adding.toy = x1-1; adding.tox = y1+2; moves.push_back(adding);}

        if (inside_board(y1-1, x1+2)) if (bb[y1-1][x1+2] <=0  ) {adding.toy = x1+2; adding.tox = y1-1; moves.push_back(adding);}
        if (inside_board(y1-1, x1-2)) if (bb[y1-1][x1-2] <=0  ) {adding.toy = x1-2; adding.tox = y1-1; moves.push_back(adding);}
        if (inside_board(y1+1, x1-2)) if (bb[y1+1][x1-2] <=0  ) {adding.toy = x1-2; adding.tox = y1+1; moves.push_back(adding);}
        if (inside_board(y1+1, x1+2)) if (bb[y1+1][x1+2] <=0  ) {adding.toy = x1+2; adding.tox = y1+1; moves.push_back(adding);}

    }




    //Check in case of white Queen
    if (bb[y1][x1]==5){
        //Knight part for white queen
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; x--, co++ ){
        if (bb[y][x] > 0  && co>0) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] < 0 ) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; x++, co++ ){
        if (bb[y][x] > 0 && co>0 ) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] < 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; y--, co++ ){
        if (bb[y][x] > 0 && co>0 ) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] < 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; y++, co++ ){
        if (bb[y][x] > 0 && co>0) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] < 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }

        //Bishop Part for white queen
        //----------------------
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; x--, y--, co++ ){
        if (bb[y][x] > 0  && co>0) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] < 0 ) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; x++, y++, co++ ){
        if (bb[y][x] > 0 && co>0 ) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] < 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; x++, y--, co++ ){
        if (bb[y][x] > 0 && co>0 ) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] < 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; x--, y++, co++ ){
        if (bb[y][x] > 0 && co>0) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] < 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }

    }



    //White King
    if (bb[y1][x1]==6){

        //Check castling Down-RIGHT bb[8][0]
        if (bb[8][0]==true)
            {
                if (bb[y1][x1+2] <=0 && bb[7][7]== 4 && bb[7][6]== 0 && bb[7][5]== 0 && bb[7][4]== 6) {
                if ((would_king_be_on_check(x1, y1, x1+2 ,y1, bb, side) == false))
                if ((would_king_be_on_check(99, 99, 99 ,99, bb, side) == false))
                {adding.toy = x1+2; adding.tox = y1; moves.push_back(adding);}
                }
            }

        //Check castling Down-LEFT bb[8][1]
        if (bb[8][1]==true)
            {
                if (bb[y1][x1-2] <=0 && bb[7][0]== 4 && bb[7][3]== 0 && bb[7][2]== 0 && bb[7][1]== 0 && bb[7][4]== 6) {
                if ((would_king_be_on_check(x1, y1, x1-2 ,y1, bb, side) == false))
                if ((would_king_be_on_check(99, 99, 99 ,99, bb, side) == false))
                {adding.toy = x1-2; adding.tox = y1; moves.push_back(adding);}
                }
            }

//adding.toy = x1+2; adding.tox = y1; moves.push_back(adding);






        if (inside_board(y1-1, x1+1))
        if (bb[y1-1][x1+1] <=0 ) {
        if ((would_king_be_on_check(x1, y1, x1+1 ,y1-1, bb, side) == false))
        {adding.toy = x1+1; adding.tox = y1-1; moves.push_back(adding);}
        }

        if (inside_board(y1-1, x1-1))
        if (bb[y1-1][x1-1] <=0 ) {
        if ((would_king_be_on_check(x1, y1, x1-1 ,y1-1, bb, side) == false))
        {adding.toy = x1-1; adding.tox = y1-1; moves.push_back(adding);}
        }

        if (inside_board(y1-1, x1))
        if (bb[y1-1][x1] <=0 ) {
        if ((would_king_be_on_check(x1, y1, x1 ,y1-1, bb, side) == false))
        {adding.toy = x1; adding.tox = y1-1; moves.push_back(adding);}
        }

        if (inside_board(y1, x1+1))
        if (bb[y1][x1+1] <=0 ) {
        if ((would_king_be_on_check(x1, y1, x1+1 ,y1, bb, side) == false))
        {adding.toy = x1+1; adding.tox = y1; moves.push_back(adding);}
        }

        if (inside_board(y1, x1-1))
        if (bb[y1][x1-1] <=0 ) {
        if ((would_king_be_on_check(x1, y1, x1-1 ,y1, bb, side) == false))
        {adding.toy = x1-1; adding.tox = y1; moves.push_back(adding);}
        }

        if (inside_board(y1+1, x1))
        if (bb[y1+1][x1] <=0 ) {
        if ((would_king_be_on_check(x1, y1, x1 ,y1+1, bb, side) == false))
        {adding.toy = x1; adding.tox = y1+1; moves.push_back(adding);}
        }

        if (inside_board(y1+1, x1-1))
        if (bb[y1+1][x1-1] <=0 ) {
        if ((would_king_be_on_check(x1, y1, x1-1 ,y1+1, bb, side) == false))
        {adding.toy = x1-1; adding.tox = y1+1; moves.push_back(adding);}
        }

        if (inside_board(y1+1, x1+1))
        if (bb[y1+1][x1+1] <=0 ) {
        if ((would_king_be_on_check(x1, y1, x1+1 ,y1+1, bb, side) == false))
        {adding.toy = x1+1; adding.tox = y1+1; moves.push_back(adding);}
        }

    }
//} //if side==1 bracked









//BLACK PIECES
//--------------------------------------------------------------------
//--------------------------------------------------------------------

//if (side==0){
    //Check in case of black pawn
    if (bb[y1][x1]== -1){
        if (inside_board(y1+1, x1))   if (bb[y1+1][x1] == 0 ) {adding.toy = x1; adding.tox = y1+1; moves.push_back(adding);}
        if (inside_board(y1+1, x1+1)) if (bb[y1+1][x1+1] >0 ) {adding.toy = x1+1; adding.tox = y1+1; moves.push_back(adding);}
        if (inside_board(y1+1, x1-1)) if (bb[y1+1][x1-1] >0 ) {adding.toy = x1-1; adding.tox = y1+1; moves.push_back(adding);}
        if (inside_board(y1+2, x1))   if (y1 == 1 && bb[y1+2][x1] >= 0 && bb[y1+2][x1] == 0 && bb[y1+1][x1] == 0) {adding.toy = x1; adding.tox = y1+2; moves.push_back(adding);}
    }


 //Check in case of black bishop
    if (bb[y1][x1]==-2){
        for (int x = x1, y = y1; inside_board(x,y) ; x--,y-- ){
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] > 0 ) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        if (bb[y][x] < 0 && x !=startx && y!= starty ) { break; }

        }
        for (int x = x1, y = y1; inside_board(x,y) ; x++,y++ ){
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] > 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        if (bb[y][x] < 0 && x !=startx && y!= starty ) { break; }
        }
        for (int x = x1, y = y1; inside_board(x,y) ; x--,y++ ){
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] > 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        if (bb[y][x] < 0 && x !=startx && y!= starty ) { break; }
        }
        for (int x = x1, y = y1; inside_board(x,y) ; x++,y-- ){
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] > 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        if (bb[y][x] < 0 && x !=startx && y!= starty ) { break; }
        }

    }





        //Check in case of black rook
    if (bb[y1][x1]==-4){
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; x--, co++ ){
        if (bb[y][x] < 0  && co>0) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] > 0 ) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; x++, co++ ){
        if (bb[y][x] < 0 && co>0 ) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] > 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; y--, co++ ){
        if (bb[y][x] < 0 && co>0 ) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] > 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; y++, co++ ){
        if (bb[y][x] < 0 && co>0) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] > 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }

    }








//Check in case of Black Queen
    if (bb[y1][x1]==-5){
        //Knight part
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; x--, co++ ){
        if (bb[y][x] < 0  && co>0) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] > 0 ) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; x++, co++ ){
        if (bb[y][x] < 0 && co>0 ) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] > 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; y--, co++ ){
        if (bb[y][x] < 0 && co>0 ) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] > 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; y++, co++ ){
        if (bb[y][x] < 0 && co>0) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] > 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }

        //Bishop Part
        //----------------------
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; x--, y--, co++ ){
        if (bb[y][x] < 0  && co>0) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] > 0 ) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; x++, y++, co++ ){
        if (bb[y][x] < 0 && co>0 ) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] > 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; x++, y--, co++ ){
        if (bb[y][x] < 0 && co>0 ) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] > 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }
        for (int x = x1, y = y1, co = 0; inside_board(x,y)  ; x--, y++, co++ ){
        if (bb[y][x] < 0 && co>0) { break; }
        if (bb[y][x] == 0) {adding.toy = x; adding.tox = y; moves.push_back(adding);}
        if (bb[y][x] > 0) {adding.toy = x; adding.tox = y; moves.push_back(adding); break;}
        }

    }



        //In case of Black horse
    if (bb[y1][x1]==-3){
        if (inside_board(y1-2, x1+1)) if (bb[y1-2][x1+1] >=0  ) {adding.toy = x1+1; adding.tox = y1-2; moves.push_back(adding);}
        if (inside_board(y1-2, x1-1)) if (bb[y1-2][x1-1] >=0  ) {adding.toy = x1-1; adding.tox = y1-2; moves.push_back(adding);}
        if (inside_board(y1+2, x1+1)) if (bb[y1+2][x1+1] >=0  ) {adding.toy = x1+1; adding.tox = y1+2; moves.push_back(adding);}
        if (inside_board(y1+2, x1-1)) if (bb[y1+2][x1-1] >=0  ) {adding.toy = x1-1; adding.tox = y1+2; moves.push_back(adding);}

        if (inside_board(y1-1, x1+2)) if (bb[y1-1][x1+2] >=0  ) {adding.toy = x1+2; adding.tox = y1-1; moves.push_back(adding);}
        if (inside_board(y1-1, x1-2)) if (bb[y1-1][x1-2] >=0  ) {adding.toy = x1-2; adding.tox = y1-1; moves.push_back(adding);}
        if (inside_board(y1+1, x1-2)) if (bb[y1+1][x1-2] >=0  ) {adding.toy = x1-2; adding.tox = y1+1; moves.push_back(adding);}
        if (inside_board(y1+1, x1+2)) if (bb[y1+1][x1+2] >=0  ) {adding.toy = x1+2; adding.tox = y1+1; moves.push_back(adding);}

    }



        //Black king King
    if (bb[y1][x1]==-6){


//..................................................
            //Check castling UP-RIGHT bb[8][2]
        if (bb[8][2]==true)
            {
                if (bb[y1][x1+2] <=0 && bb[0][7]== -4 && bb[0][6]== 0 && bb[0][5]== 0  && bb[0][4]== -6)
                if ((would_king_be_on_check(x1, y1, x1+2 ,y1, bb, side) == false))
                if ((would_king_be_on_check(99, 99, 99 ,99, bb, side) == false))
                {adding.toy = x1+2; adding.tox = y1; moves.push_back(adding);}
            }


                        //Check castling UP-RIGHT bb[8][2]
        if (bb[8][3]==true)
            {
                if (bb[y1][x1-2] <=0 && bb[0][0]== -4 && bb[0][1]== 0 && bb[0][2]== 0 && bb[0][3]== 0 && bb[0][4]== -6)
                if ((would_king_be_on_check(x1, y1, x1-2 ,y1, bb, side) == false))
                if ((would_king_be_on_check(99, 99, 99 ,99, bb, side) == false))
                {adding.toy = x1-2; adding.tox = y1; moves.push_back(adding);}

            }
//.-----------------------------------------------------

        //if (bb[y1-1][x1] == 0 && inside_board(y1-1, x1 )) {adding.toy = x1; adding.tox = y1-1; moves.push_back(adding);cout<<"pushed back ";}
        if (inside_board(y1-1, x1+1)) if (bb[y1-1][x1+1] >=0 ) {
        if ((would_king_be_on_check(x1, y1, x1+1 ,y1-1, bb, side) == false))
        {adding.toy = x1+1; adding.tox = y1-1; moves.push_back(adding);}
        }

        if (inside_board(y1-1, x1-1)) if (bb[y1-1][x1-1] >=0 ) {
        if ((would_king_be_on_check(x1, y1, x1-1 ,y1-1, bb, side) == false))
        {adding.toy = x1-1; adding.tox = y1-1; moves.push_back(adding);}
        }

        if (inside_board(y1-1, x1))   if (bb[y1-1][x1] >=0 ) {
        if ((would_king_be_on_check(x1, y1, x1 ,y1-1, bb, side) == false))
        {adding.toy = x1; adding.tox = y1-1; moves.push_back(adding);}
        }

        if (inside_board(y1, x1+1))   if (bb[y1][x1+1] >=0 ) {
        if ((would_king_be_on_check(x1, y1, x1+1 ,y1, bb, side) == false))
        {adding.toy = x1+1; adding.tox = y1; moves.push_back(adding);}
        }

        if (inside_board(y1, x1-1))   if (bb[y1][x1-1] >=0 ) {
        if ((would_king_be_on_check(x1, y1, x1-1 ,y1, bb, side) == false))
        {adding.toy = x1-1; adding.tox = y1; moves.push_back(adding);}
        }


        if (inside_board(y1+1, x1))
        if (bb[y1+1][x1] >=0 ) {
        if ((would_king_be_on_check(x1, y1, x1 ,y1+1, bb, side) == false))
        {adding.toy = x1; adding.tox = y1+1; moves.push_back(adding);}
        }


        if (inside_board(y1+1, x1-1))   if (bb[y1+1][x1-1] >=0 ) {
        if ((would_king_be_on_check(x1, y1, x1-1 ,y1+1, bb, side) == false))
        {adding.toy = x1-1; adding.tox = y1+1; moves.push_back(adding);}
        }

        if (inside_board(y1+1, x1+1))   if (bb[y1+1][x1+1] >=0 ) {
        if ((would_king_be_on_check(x1, y1, x1+1 ,y1+1, bb, side) == false))
        {adding.toy = x1+1; adding.tox = y1+1; moves.push_back(adding);}
        }

    }

//}// if side==0 bracket

//return moves;
}








