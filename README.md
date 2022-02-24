# minesweeper-cpp
A game that is both explosive and mind-blowing.

## Dependencies:
- SFML v2.5 or above.
- Boost serialization v1.78 or above.
- [Repo](https://github.com/phatalways-sleeping/firstgame_Minesweeper) that saw the development of this game's functional part.
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

## Features
Minesweeper should be too familiar a game for everyone. This section only mentions uncommon/need to be mentioned features in this particular game:
- If all bombs surrounding a cell has been flagged, `double left click` on that cell to reveal the rest of surrounding cells.
- There are 2 ways to win: open all non-bomb cells or flag all bomb cells.
- When playing custom-sized board, number of bombs is 20% of total number of cells.

## Images
- Menu:<br><img src="https://github.com/sxweetlollipop2912/minesweeper-cpp/blob/main/game_release/images/menu.png" alt="menu" width="400"/>
- Selecting difficulty:<br><img src="https://github.com/sxweetlollipop2912/minesweeper-cpp/blob/main/game_release/images/difficulty.png" alt="difficulty" width="400"/>
- In-game:<br><img src="https://github.com/sxweetlollipop2912/minesweeper-cpp/blob/main/game_release/images/ingame.png" alt="in-game" width="400"/>
