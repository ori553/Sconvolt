#include <iostream> //c-c++ standard
#include <vector>

//Functions needed to use the Sconvolt chess engine
#include "move.h"
#include "SconvoltClass.h"
#include "engine3.h"


using namespace std;


	int main()
	{

		cout<<"test"<<endl;
		int jx;


		Sconvolt game1;
		game1.showBoard();

		do {
		cout<<"press a number representing the ply" <<endl;
		cin>>jx;

		game1.AlphaBetaMin(-30000, 30000, jx, false);
		game1.makeMove();
		game1.showBoard();

		cout<<game1.j1<<","<<game1.j2<<","<<game1.j3<<","<<game1.j4<<endl;

		} while (jx != 0);

	return 0;


}
