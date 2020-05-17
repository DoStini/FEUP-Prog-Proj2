Scrabble junior and Board builder is a project made for Curricular Unit "Programação", 1st year, 2nd semester.

This program only works for Windows, as it uses Windows.h library to accomodate our needs to improve visual environment.

Developed by André Moreira and Nuno Alves

Accomplishments:

	A lot of effort was made in order to make the program more visually pleasant to the user. We used ascii art provided by http://patorjk.com/software/taag/ in the title and subtitles.
	The title of the game drops its tiles at the startup of the program (can be skipped by pressing enter).
	The text was centered manually with help from values defined in graphical.h
	The board is centered automatically according to its horizontal size.
	An attempt of adding sound was made, but issues relating to compatibility forced us to not implement it. 	

BOARD BUILDER:

    Player can select the size of the board. The minimum board size allowed by our program is 20 squares (a 3*3 board has 9 squares while a 3*10 board has 30 squares) to allow at least 2 players to play it (14 tiles).
    Words.txt was used by initially reading the file and storing it in memory to make for a faster execution.
    Players can select any word present in the words.txt file and its position and orientation on the board.
    Every rule was followed in terms of placing words:
    * Word must exist in the WORDS.TXT file.
    * Word can't be placed out of bounds.
    * Word can't touch/intersect with other words in the same column/row.
    * Word can't touch edges with other words.
    * Word can't intersect with another word with a different orientation, unless the letter that intersects is the same on both words.
    The file is saved on the Board Builder folder and needs to be later moved by the user to the Scrabble Junior folder to be able to be played with.
    One possible solution for this was to have an Assets folder, alongside with Scrabble Junior and Board builder folder, being saved there, and use relative pathing to save and load from that folder.
    The file version where the board is shown at the end of the file was implemented, separating data and visual parts by one line of ####.

SCRABBLE JUNIOR:

    Players need to select between 2 and 4 players.
    If an excessive amount of players over the number of tiles of the board (tiles < 7 * players), the game will prompt a message forbidding that game, returning to the main menu.
    The program structure was separated adequately in different files, according to their objectives.
    There are several menus like rules, credits, scoreboard and the game itself.
    The game board was drawn dynamically, allowing to change the parameters defined in graphical.h like vertical spacing and menu start to allow the programmer to change easily the aspect of the board.	The board also has an outline with the position identifiers (A or a).
    Placing players in the console is also partially automatic according to values defined in graphical.h.
    The input during the game will be of type Aa or Bb, and will detect any bad inputs like integers. If ctrl-z is pressed, the user will be prompted to confirm that he wants to end the game.
	
About our algorithm:

		In terms of checking possible valid moves and completed words, we thought a good way of doing this was to have a 2d vector of objects Word.
		Every element of the first vector would contain vectors of words according to the vertical/horizontal position that the vertical/horizontal word occupied.
		This way, having the input of the player, the row/column of that position can be quickly accessed to find possible words.
			An example on how to find a word:
				If the input given was Cd, position in integer values would be [2, 3].
				If we're looking for a vertical word, we should access vWords in index 3. Index 3 contains all the words in that column.
				After that we can loop through that vector, checking if a word contains that position, index 2 (start <= 2 <= end).
				This way we can quickly check a move validity and if so, change the status of a tile in both horizontal and vertical words (by looking through vWords and hWords). 
		Class word: 
			Has a start and end positions variable. Given a certain input, we can check if the tile in question belongs to the word (start <= input <= end : tile is within word).
			A vector of char containing the tiles.
			A vector of bool, corresponding each tile to a boolean, indicating if it's covered or not.
		We think we should've used a single vector instead of two different ones (hWords and vWords) to prevent code repetition in some cases, although this way is more readable.
	
	All inputs prevent bad entries and sometimes prompts the user to re-enter in a red warning message.
	The board is only written once in the board. When a valid move is made, the program replaces graphicly the tile played by a colored one (automatically done with graphical variables defined in graphical.h)
	Also added an extra feature, a scoreboard menu, that shows the best 5 players (if existing), saving the file in scoreboard.win (saving structs directly into the file).
			 
