
Go Utilities
============
 
* Go is an ancient board game invented at least 2500 years ago in China. 
* Utilities are made to help you download, transform and query games stored in sgf format. 
* Main use-case of this utilities is statistical analysis of effectiveness of different openings on a 9x9 board. Simple example is [**`wins-per-first-move`**](analysis/wins-per-first-move) script, that calculates winning percentage for every starting move in passed games.
 
How to run:
-----------
### Windows
* Download and install [wget](http://sourceforge.net/projects/gnuwin32/files/wget/1.11.4-1/wget-1.11.4-1-setup.exe/download)
* Open command prompt
* Go to the directory where you want Cygwin installed
* Install and start Cygwin:

>```bat
setx PATH "%PATH%;C:\Program Files (x86)\GnuWin32\bin"
wget --no-check-certificate https://cygwin.com/setup-x86_64.exe
mkdir cygwin
setup-x86_64.exe --quiet-mode --no-shortcuts --site http://cygwin.mirror.constant.com --root %cd%\cygwin -P git -P wget -P gcc-core -P libgcc1 -P libclang-devel -P make -P bc -B
cygwin\Cygwin.bat
```

* Once in Cygwin, run the UNIX commands to start the game

### UNIX
```bash
git clone https://github.com/gto76/go-game-utils.git
cd go-game-utils 
make
export PATH="$PATH:`pwd`/bin" 
download-games {10234..10244}
cd games
delete-unneeded-games *
wins-per-first-move * > tmp
visualize-percentages tmp
```
The end result of this sequence of commands is a diagram of 9x9 go board, showing winning percentages of different starting moves, and it should look something like that:
```
    a   b   c   d   e   f   g   h   i
a   -   -   -   -   -   -   -   -   -
b   -   -   -   -   -   -   -   -   -
c   -   -   *   -   *   -  36   0   -
d   -   -   -   -   -  46  51   -   -
e   -   -   *   -  41  45  14 100   -
f   -   -   -   -   -   -   -   -   -
g   -   -   *   -   *   -   *   -   -
h   -   -   -   -   -   -   -   -   -
i   -   -   -   -   -   -   -   -   -
```
So we can see that in the observed games, 41% of players that started the game in the center of the board won the game. Also we can observe that percentages get unreliable at the edge of the board due to the small sample size.
  
Utilities consist of bash scripts and c programs that are grouped by functionality and reside in following folders: 
  
download
--------
Different scripts that help you download your games from www.online-go.com website (as of now the website doesn't enable you to download all of your games at once, so you have to go to your games list, inspect the element with your browse, copy the raw html, save it to the file and pass the filename to the script, which then downloads the games. Since most games that can be shown per page is 50, you have to repeat the procedure 50 games at the time)
 
##### [**`download-games`**](download/download-games)
* Usage: `download-games [GAME ID]...`

* Downloads specified games from www.online-go.com, saves them in games directory.

##### [**`download-games-on-list`**](download/download-games-on-list)
* Usage: `download-games-on-list [FILE CONTAINING GAME ID-S]`

* Downloads from www.online-go.com all games with id specified in file passed as first argument, saves them in games directory.

##### [**`get-game-ids-from-html`**](download/get-game-ids-from-html)
* Usage: `get-game-ids-from-html [HTML FILE WITH LINKS TO GAMES]`

* Pass this script filename of html file with list of games and it will return this games urls, one per line.

normalization
-------------
Main program called normalize-game, 'normalizes' your game using rotation and mirroring of the board using predefined criteria defining on which part of the board should the first moves be played. This way the games that start with identical opening, but with rotated or mirrored orientation will now have the same rotation and mirroring, thus will have the same opening moves. (Useful for analysis of openings, your winning percentage for every move, and so on..)
 
Definition of normalized game:
As many consecutive moves as possible from the start of the game should satisfy the following rules:
	1. x >= 0
	2. y >= 0
	3. x >= y
 
##### [**`normalize-games`**](normalization/normalize-games)
* Usage: `normalize-games [SGF FILE]...`

* Normalizes all passed games. Overwrites existing file with normalized version.

query
-----
Just a basic scripts that search through passed game-file and print requested information, like the winner of the game or board size...
 
##### [**`board-size`**](query/board-size)
* Usage: `board-size [SGF FILE]`

* Prints board size of the passed game.

##### [**`delete-unneeded-games`**](query/delete-unneeded-games)
* Usage: `delete-unneeded-games [SGF FILE]...`

* Deletes games with less then four moves, and games that were not played on 9x9 board.

##### [**`first-move`**](query/first-move)
* Usage: `first-move [SGF FILE]`

* Prints first move of the passed game.

##### [**`first-moves`**](query/first-moves)
* Usage: `first-moves [NO OF MOVES] [SGF FILE]`

* Prints first move of the passed game.

##### [**`number-of-moves`**](query/number-of-moves)
* Usage: `number-of-moves [SGF FILE]`

* Prints number of moves in passed game.

##### [**`query-game-for`**](query/query-game-for)
* Usage: `query-game-for [SGF FILE] [FIELD]`

* Queries game for content of field.

##### [**`winner`**](query/winner)
* Usage: `winner [SGF FILE]`

* Prints winner of the passed game.

analysis
--------
This scripts are the reason for all the others.
 
##### [**`visualize-percentages`**](analysis/visualize-percentages)
* Usage: `visualize-percentages [FILE CONTAINING OUTPUT FROM wins-per-first-move OR SIMILAR SCRIPT]`

* Prints a go board with win percentages in fields that got entries in the passed file. If '-' is passed instead of a filename, then it reads from pipe. Works correctly only with 9x9 games.

##### [**`wins-per-first-move`**](analysis/wins-per-first-move)
* Usage: `wins-per-first-move [SGF FILE]...`

* Prints number of wins and loses for every starting move among the passed games. Only analyzes 9x9 games.

##### [**`wins-per-first-moves`**](analysis/wins-per-first-moves)
* Usage: `wins-per-first-moves [MOVE]:... [SGF FILE]...`

* Prints number of wins and loses for every move after the MOVEs among the passed games. Only analyzes 9x9 games.

