
Go Utilities
============
 
* Go is an ancient board game invented at least 4000 years ago in China. 
* Utilities are made to help you download, transform and query games stored in sgf format. 
* Main use-case of this utilities is statistical analysis of effectiveness of different openings on a 9x9 board. Simple example is `analisis/wins-per-first-move` script, that calculates winning percentage for every starting move in passed games.
 
How to run:
-----------
```bash
$ git clone https://github.com/gto76/go-utilities.git
$ cd go-utilities
$ make
$ export PATH="$PATH:`pwd`/bin" 
$ download-games {1000-1010}
$ cd games
$ wins-per-first-move *
```
 
Utilities consist of bash scripts and c programs that are grouped by functionality and reside in following folders: 
  
download
--------
Different scripts that help you download your games from www.online-go.com website (as of now the website doesn't enable you to download all of your games at once, so you have to go to your games list, inspect the element with your browse, copy the raw html, save it to the file and pass the filename to the script, which then downloads the games. Since most games that can be shown per page is 50, you have to repeat the procedure 50 games at the time)
 
### [**`download-games`**](download/download-games)
Usage: `download-games [GAME ID]...`
Downloads specified games from www.online-go.com, saves them in games directory

### [**`download-games-on-list`**](download/download-games-on-list)
Usage: `download-games-on-list [FILE CONTAINING GAME ID-S]`
Downloads from www.online-go.com all games with id specified in file passed as first argument, saves them in games directory

### [**`get-game-ids-from-html`**](download/get-game-ids-from-html)
Usage: `get-game-ids-from-html [HTML FILE WITH LINKS TO GAMES]`
Pass this script filename of html file with list of games and it will return this games urls, one per line.

normalization
-------------
Main program called normalize-game, 'normalizes' your game using rotation and mirroring of the board using predefined criteria defining on which part of the board should the first moves be played. This way the games that start with identical opening, but with rotated or mirrored orientation will now have the same rotation and mirroring, thus will have the same opening moves. (Useful for analysis of openings, your winning percentage for every move, and so on..)
 
Definition of normalized game:
As many consecutive moves as possible from the start of the game should satisfy the following rules:
	1. x >= 0
	2. y >= 0
	3. x >= y
 
### [**`normalize-games`**](normalization/normalize-games)
Usage: `normalize-games [SGF FILE]...`
Normalizes all passed games. Overwrites existing file with normalized version.

query
-----
Just a basic scripts that search through passed game-file and print requested information, like the winner of the game or board size...
 
### [**`board-size`**](query/board-size)
Usage: `board-size [SGF FILE]`
Prints board size of the passed game.

### [**`first-move`**](query/first-move)
Usage: `first-move [SGF FILE]`
Prints first move of the passed game.

### [**`query-game-for`**](query/query-game-for)
Usage: `query-game-for [SGF FILE] [FIELD]`
Queries game for content of field.

### [**`winner`**](query/winner)
Usage: `winner [SGF FILE]`
Prints winner of the passed game.

analysis
--------
This scripts are the reason for all the others.
 
### [**`wins-per-first-move`**](analysis/wins-per-first-move)
Usage: `wins-per-first-move [SGF FILE]...`
Prints number of wins and loses for every starting move among the passed games. Only analyzes 9x9 games.

