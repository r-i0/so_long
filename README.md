# so_long
This project is to create a small 2D game with C.  
I use minilinX to put image to window.
It only works on Linux 

## geme rule
- The player is a slime.
- The goal is to escape the stage with fewer steps.
- Slime have to collect all collectibles on the map before escaping.

## Description
`so_long` takes as a first argument a map description file with the `.ber` extension.  
The map must be composed of only 5 possible characters:  
- 0 for an empty space 
- 1 for a wall
- C for a collectible
- E for map exit
- P for the player’s starting position

This is an example.
```
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```

The number of movements will be displayed in the shell in Mandatory part.
