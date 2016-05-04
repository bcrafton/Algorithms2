// project 1B
// main.cpp
// the main file containing the main loop
// Brian Crafton and Oliver Scott.
#include <iostream>
#include "mastermind.h"
#include "d_except.h"
#include <stdlib.h>

using namespace std;


int main()
{
	cout << "please be patient if it is taking awhile it needs to make a lot of comparisons" << endl;
	try
	{
		Mastermind m;
		m.playGame2();
	}
	catch(baseException e)
	{
		cout << e.what() << endl;
		exit(0);
	}
}


