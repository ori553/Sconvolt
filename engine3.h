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





#include <iostream>
#include <vector>


using namespace std;


int AlphaBetaMin(int alpha, int beta, int depth, bool sid);






int evaluate (int pboard[9][8]){
    int score;
    score = 0;

    //srand (time(NULL));

    //int v1 = rand() % 2;

count_board_combinations++;

/*
            int test = check_if_game_finished(pboard);
            if (test!= -99)
            {

            if ( test == 1) score = -31000 ;
            //if (would_king_be_on_check(99, 99, 99 ,99, pboard, 0))
            if ( test == 2) score = 31000;

            if ( test == 3) score = 0;

            return score;
            }
*/

//else



/*
            int test = check_if_game_finished(pboard);
            if (test!= -99)
            {

            if ( test == 1) score = -31000 ;
            //if (would_king_be_on_check(99, 99, 99 ,99, pboard, 0))
            if ( test == 2) score = 31000;

            return score;
            }
*/



 for (int i = 0; i <=7; i++)
        for (int j = 0; j <=7; j++)
            if (pboard[i][j] != 0)
            {

            //Add points for whites
            if (pboard[i][j]== 1) score = score + 100;  //Pawn equals 100
            if (pboard[i][j]== 2) score = score + 325;  //Bishop equals 325
            if (pboard[i][j]== 3) score = score + 320;  //knight equals 320
            if (pboard[i][j]== 4) score = score + 500;  //Rook equals 500
            if (pboard[i][j]== 5) score = score + 975;  //Queen equals 975
            if (pboard[i][j]== 6) score = score + 20000;  //King as much as possible obviously


        //if (v1==1){

            //if (pboard[i][j]>0 && i<5) score+=3;
            //                              if (pboard[i][j]<0 && i>2) score-=3;

            //}


        //if (v1==0){
            if (pboard[i][j]>0 && i<6) score+=3;
            if (pboard[i][j]<0 && i>1) score-=3;
            //}






            //if (would_king_be_on_check(99, 99, 99 ,99, pboard, 1))


            //Subtract points for blacks
            if (pboard[i][j]== -1) score = score - 100;  //Pawn equals 100
            if (pboard[i][j]== -2) score = score - 325;  //Bishop equals 325
            if (pboard[i][j]== -3) score = score - 320;  //knight equals 320
            if (pboard[i][j]== -4) score = score - 500;  //Rook equals 500
            if (pboard[i][j]== -5) score = score - 975;  //Queen equals 975
            if (pboard[i][j]== -6) score = score - 20000;  //King as much as possible obviously
            }

/*
    //If black has castled
    if (pboard[8][5]==1) score = score - 120 ;
    //If white has castled
    if (pboard[8][4]==1) score = score + 120 ;
*/

//if (would_king_be_on_check(99, 99, 99, 99, pboard, 1)) score = score - 400 ;


//if (would_king_be_on_check(99, 99, 99 ,99, pboard, 0)) score = score + 900;
//if (would_king_be_on_check(99, 99, 99 ,99, pboard, 1)) score = score - 900;


return score;
}




int Sconvolt::AlphaBetaMax( int alpha, int beta, int depth, bool sid)
{

    int val = 0;
    int temp = 0;



        if (depth<=0) {/*cout << "reached surface" << endl;*/ return evaluate(bb);  }

            vector<movement> legalmoves;
            legalmoves.clear();





    //GenerateLegalMoves(); GENERATING LIST OF LEGAL MOVES
    //============================================
            for (int t1 = 0; t1<= 7; t1++){
                for (int t2 = 0; t2<=7; t2++){
                if (bb[t1][t2]>0){
                    //temp1.clear();
                    //temp1 = returnMoves(t2, t1, bb, 1);
                    returnMoves(legalmoves, t2, t1, bb, 1);
                    //cout<<"temp1: " << temp1.size() << endl;

                    //legalmoves.insert(legalmoves.end(), temp1.begin(), temp1.end());
                    }
                }
            }



    if (legalmoves.size()<1) return 0;

    //((evaluate(bb))-1);

    //return -30000;
    //return evaluate(bb); //if there are no possible positions at this point, return evaluate


    //For Each Move
    for (int k = 0; k < legalmoves.size() ; k++)
    {
            //Make move
            temp = bb  [legalmoves[k].tox] [legalmoves[k].toy];

            bb  [legalmoves[k].tox] [legalmoves[k].toy]  = bb  [legalmoves[k].startx] [legalmoves[k].starty] ;

            bb  [legalmoves[k].startx] [legalmoves[k].starty] = 0;

            /*
            if (sid==true) sid = false;
              else sid = true;
            */

        val = AlphaBetaMin(alpha, beta, depth - 1, sid);

            //UnmakeMove();
            bb  [legalmoves[k].startx] [legalmoves[k].starty]  =  bb  [legalmoves[k].tox] [legalmoves[k].toy] ;
            bb  [legalmoves[k].tox] [legalmoves[k].toy] = temp ;


        if (val >= beta) //if score >= beta then return beta
        {

            return beta; //beta cut off
        }

        if (val > alpha) //if score >= beta then return beta
        {

        alpha = val;

            if (depth == user_depth /*&& sid==true*/)
            {

                cout<<"New best board score for ALPHA: " << alpha << ", Move : "<<j1 << ", " << j2 << " -> " << j3 << ", " << j4 <<", Depth: "<<depth<<endl;

                j1 = legalmoves[k].startx;
                j2 = legalmoves[k].starty;
                j3 = legalmoves[k].tox;
                j4 = legalmoves[k].toy;
            }

        }

    }



return alpha;
}



//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

int Sconvolt::AlphaBetaMin( int alpha, int beta, int depth, bool sid)
{
int val = 0 ;
int temp = 0;



    if (depth<=0) { return (evaluate(bb));}

            vector<movement> legalmoves;
            legalmoves.clear();





    //GenerateLegalMoves(); GENERATING LIST OF LEGAL MOVES
    //============================================


            for (int t1 = 0; t1<= 7; t1++){
                for (int t2 = 0; t2<=7; t2++){
                if (bb[t1][t2]<0){

                    returnMoves(legalmoves, t2, t1, bb, 0);

                    }
                }
            }



    if (legalmoves.size()<1) return 0;
    //((evaluate(bb))+1);
    //return evaluate(bb); //if there are no possible positions at this point, return evaluate

    //For Each Move
    for (int k = 0; k < legalmoves.size() ; k++)
    {

            //bb[legalmoves[k].tox][legalmoves[k].toy] = [legalmoves[k].startx][legalmoves[k].starty];

            temp = bb  [legalmoves[k].tox] [legalmoves[k].toy];

            bb  [legalmoves[k].tox] [legalmoves[k].toy]  = bb  [legalmoves[k].startx] [legalmoves[k].starty] ;

            bb  [legalmoves[k].startx] [legalmoves[k].starty] = 0;

                        /*
                        if (sid==true) sid = false;
              else sid = true;
                */

        val = AlphaBetaMax(alpha, beta, depth - 1, sid);

                    //UnmakeMove();

            bb  [legalmoves[k].startx] [legalmoves[k].starty]  =  bb  [legalmoves[k].tox] [legalmoves[k].toy] ;
            bb  [legalmoves[k].tox] [legalmoves[k].toy] = temp ;


        if (val <= alpha) //if score <= alpha then return alpha
        {

            return alpha;
        }

        if (val < beta) //if score < beta then beta mbecomes the new score
        {

        beta = val;

            if (depth == user_depth /*&& sid==false*/)
            {


            //if (depth == user_depth){

            cout<<"New best board score for BETA: " << beta << ", Move : "<<j1 << ", " << j2 << " -> " << j3 << ", " << j4 <<", Depth: "<<depth<<endl;

            j1 = legalmoves[k].startx;
            j2 = legalmoves[k].starty;
            j3 = legalmoves[k].tox;
            j4 = legalmoves[k].toy;

            //}

            }

        }


    }


return beta;
}



/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////



