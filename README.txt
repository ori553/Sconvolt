 ____                            _ _      ____ _                   
/ ___|  ___ ___  _ ____   _____ | | |_   / ___| |__   ___  ___ ___ 
\___ \ / __/ _ \| '_ \ \ / / _ \| | __| | |   | '_ \ / _ \/ __/ __|
 ___) | (_| (_) | | | \ V / (_) | | |_  | |___| | | |  __/\__ \__ \
|____/ \___\___/|_| |_|\_/ \___/|_|\__|  \____|_| |_|\___||___/___/


                                                                      
                                                                      
Sconvolt Chess, Version 0.99.8, by Orest Sota (Last modified: 1/03/2015 )


HOW TO RUN THE PROGRAM
//------------------------------------------------------------------------------------------------------

NOTE: The program is not finished and may contain some bugs, please email me if you encounter one or want to give me feedback, 
Orest.Sota.2008@live.rhul.ac.uk

-Instructions, HOW TO PLAY:

  - On WINDOWS, Just click on executable named Sconvolt.exe (in some windows 
versions you may be required to run as administrator, right-click on the file 
"Sconvolt.exe" and click "run as administrator, if it says that it's not safe run aniway, there are no viruses (the source code is included)"), 
remember to extract the downloaded archive first, enjoy

  - On LINUX, you have to run the file "startSconvoltLinux", so change the 
permissions of the files "Sconvolt" and "startSconvoltLinux" (so, from terminal,  
type "chmod u+x Sconvolt", "chmod u+x startSconvoltLinux") then start the program by typing
./startSconvoltLinux (it's a script that executes the file "Sconvolt" by automatically 
linking the required libraries). It should work fine, remember to extract the downloaded archive first, If you 
have trouble starting it, email me, I've tested it on Lubuntu 64 bit and in a 32 bit netbook with Ubuntu, enjoy


 - Click and keep the mouse pressed to move pieces in the board
 



HOW TO COMPILE THE PROGRAM FROM SOURCE CODE
//----------------------------------------------------------------------------------------------------------

-Instructions for compiling the program from source code

Feel free to email me if you have any questions, Orest.Sota.2008@live.rhul.ac.uk

  - Program Compiled under Lubuntu Linux, and Windows 7, Using "code::Blocks"
8.02 with GNU GCC Compiler and the Allegro 5 graphical libraries linked with 
the compiler.
  code::Blocks can be downloaded for both Windows(xp, vista, 7) and Linux.

  - The same main file (Sconvolt.cpp) can be compiled for Linux and Windows, (On a Mac too, I just don't own a mac to compile it)

Note: to compile this program from source code, you will need Allegro 5 
installed


	***** Compile from Linux

- Download Allegro 5 from http://www.allegro.cc/
- Follow instructions on how to compile a program with allegro 5
- The file to be compiled is Sconvolt.cpp


  - For further information about the allegro programming libraries, please go to http://www.allegro.cc/
  - For further information about code::Blocks please follow this link http://www.codeblocks.org/



	***** Compile from Windows
  - Program compiles on windows too, using the same IDE (code:Blocks) and linking it with the Allegro programming libraries
  for further information on how to set up the compiler for windows, this link 
can be followed:
  http://wiki.allegro.cc/index.php?title=Code::Blocks


//----------------------------------------------------------------------------------------------------
  - For further information about the allegro programming libraries, please go 
to http://www.allegro.cc/
  - For further information about code::Blocks please follow this link 
http://www.codeblocks.org/

  -The file to be compiled is "Sconvolt.cpp"

//---------------------------------------------------------------------------------------------------
//***************************************************************************************************
1/03/2015 Version 0.99.8, What's new
- Engine's behaviour
- Implemented draw
- Bux fixes

12/01/2015 Version 0.99.7, What's new
- Implemented Castling!
- Implemented Human vs Human play (In editor, in the section Choose your side, select No CPU)
- Implemented Who starts first option in Editor
- Chose Better looking chess pieces and board


11/01/2015 Version 0.99.5, What's new
 - Implemented Checkmate detection
 - Performance improvements, improved the engine's speed
 - Included licence, MIT Licence
 - Bug fixes

5/01/2015 Version 0.9.9.4, What's new
- Bug fixes
- Improved dialogs

3/01/2015 Version 0.9.9.3, What's new
- The program doesn't let you anymore make moves that bring the king in check
- Bug fixes

30/12/2014 Version 0.99, What's new:
- Drag/drop in editor mode more realistic, you can now see the piece actually moving to the board with the mouse cursor
- Pawns becoming queens when they reach the end (but, user should be able to choose, I'll implemented it soon)
- Bug fixes

28/12/2014,  Version 0.98, What's new:
- Rewrote the graphical interface from scratch for Allegro 5 (it was not retro-compatible with allegro 4)
- The Look of the interface is improved, it doesn't look anymore 80's style, now it looks 90's
- Improved the chess engine's speed, it's twice as fast now
- Editor Mode, the user can edit the board pieces and play
- Mouse is not freezing anymore when the CPU is thinking

TO DO:

- Implement draw
- Bug fixes

//***********************************************************************************************
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
 * The MIT License (MIT)
 * Copyright (c) 2015, Orest Sota
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

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
 //------------------------------------------------------------------------------------------------