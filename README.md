Go Utilities
============

* Go is an aicent board game invented at least 4000 years ago in China. 
* Utilities are made to help you download, transform and query games stored in sgf format. 
* Main usecase of this utilities is analysys of effectivness of different openings on a 9x9 board. Simple example is `ananisis/wins-per-first-move` script, that calculates winning percentage for every starting move in passed games.

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

download
--------
Different scripts that help you download your games from www.online-go.com website (as of now the website doesn't enable you to download all of your games at once, so you have to go to your games list, inspect the element with your browse, copy the raw html, save it to the file and pass the filename to the script, which then downloads the games. Since most games that can be shown per page is 50, you have to repeat the procedure 50 games at the time)

normalization
-------------
Main program called normalize-game, 'normalizes' your game using rotation and mirroring of the board using predefined criteria defining on which part of the board should the first moves be played. This way the games that start with identical opening, but with rotated or mirrored orientation will now have the same rotation and mirroring, thus will have the same opening moves. (Useful for analysis of openings, your winning percentage for every move, and so on..)

Definition of normalized game:
As many consecutive moves as possible from the start of the game should satisfy the following rules:
	1. x >= 0
	2. y >= 0
	3. x >= y


