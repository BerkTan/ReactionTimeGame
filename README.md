# ReactionTimeGame
 Reaction time game created in CS 3420 using my own code and the FRDM-K64F NXP board
 
 This game involves two players pressing a physical button on the board to determine which player has the fastest reaction time.
 
 The light is first white, indicating player 1 must "ready up"
 When the button is pressed, the light turns red and a random time wait is set for player 1 (whose player color is blue), after which he must press the button when the light turns green (from red) to time his reaction.
 The board is then passed to the next player (while there is a yellow light indicating intermission)
 Player 2 (represented by the color red) then "readies up" by pressing the button, making the light turn red.
 The board then times player 2's reaction time when the light turns green
 To indicate the winner, blue is blinked rapdily for P1 victory, red for P2 victory, and alternate blue/red for a tie
