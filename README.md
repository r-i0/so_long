# so_long
This project is to create a small 2D game with C.  
Using [minilinX](https://github.com/42Paris/minilibx-linux) to put image to window.
It only works on Linux 

## game rule
- The player is a slime.
- The goal is to escape the stage with fewer steps.
- Slime have to collect all collectibles on the map before escaping.

## Description
### *map*
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

  
### *Mandatory part*
The number of movements and collectibles will be displayed in the shell.
![Y3Ii4COu5JUgFg03B7ac1628086711-1628086959](https://user-images.githubusercontent.com/76856052/128198934-6723bbf9-6ead-466c-8091-55db20cb8f06.gif)


### *Bonus part*
Sprite animation is used in the player.  
Movements count is directly displayed on the screen.  
  
![so_long_bonus_600](https://user-images.githubusercontent.com/76856052/128201807-4f2291e9-7726-470a-b952-3e4d72c2e499.gif)

# Usage
```bash
$ make
$ ./so_long ./maps/sample1.ber
```
