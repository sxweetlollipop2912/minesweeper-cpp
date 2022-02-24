# minesweeper-cpp
A game that is both explosive and mind-blowing.

## Dependencies:
- SFML v2.5 or above.
- Boost serialization v1.78 or above.
<br>

This repo is a solution from Visual Studio (2019 in particular). Boost is set to be installed through NuGet, and SFML is already configured.
## Installing SFML:
If you're not on Visual Studio, see [SFML Tutorials](https://www.sfml-dev.org/tutorials/2.5/).
<br>
If you're on Visual Studio:
1. Download SFML binaries matching your Visual Studio version [here](https://www.sfml-dev.org/download/sfml/2.5.1/).
2. Unzip and move 2 folders `include` and `lib` to `minesweeper/SFML`.
<br>

Note: current configuration of the library in Visual Studio is:
- `SFML_STATIC` (requires no `.dll`)
- `release`
<br>

Refer to [SFML instruction for VS](https://www.sfml-dev.org/tutorials/2.5/start-vc.php) for more details or if you want to make any change on Visual Studio.
## Images
- Menu:<br>![Menu](https://github.com/sxweetlollipop2912/minesweeper-cpp/blob/main/game_release/images/menu.jpg?raw=true)
- Selecting difficulty:<br>![Difficulty](https://github.com/sxweetlollipop2912/minesweeper-cpp/blob/main/game_release/images/difficulty.jpg?raw=true)
- In-game:<br>![In-game](https://github.com/sxweetlollipop2912/minesweeper-cpp/blob/main/game_release/images/ingame.jpg?raw=true)