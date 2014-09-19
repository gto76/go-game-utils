Go Utilities
============

Utilites for ancient board game of Go.

download-scripts
----------------
Different scripts that help you download your games from www.online-go.com website (as of now the website doesent enable you to download all of your games at once, so you have to go to your games list, inspect the element with your browse, copy the raw html, save it to the file and pass the filename to the script, which then downloads the games. Since most games that can be shown per page is 50, you have to repeat the procedure 50 games at the time)

normalization-scripts
---------------------
Main script will 'normalize' your game using rotation and mirroring of the board using predefined criteria defining on which part of the board should the first moves be played. This way the games that start with identical opening, but with rotated or mirrored orientation will now have the same rotation and mirroring, thus will have the same opening moves. (Useful for analysis of openings, your winnig percentage for every move, and so on..)

Definition of normalized game:
As many consecutive moves as posible from the start of the game should satisfy the folloving rules:
	1. x >= 0
	2. y >= 0
	3. x >= y


