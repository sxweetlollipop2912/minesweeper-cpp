# minesweeper-cpp
A game that is both explosive and mind-blowing.<br>
Here is the [link (v1.0 tag)](https://github.com/sxweetlollipop2912/minesweeper-cpp/releases/tag/v1.0) to download executable.

## To add your own music and visuals:
- Refer to [this README](https://github.com/sxweetlollipop2912/minesweeper-cpp/blob/main/game_release/windows/assets/music/README.md) for further instructions.

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
- `SFML_STATIC` (requires no `.dll`) (already set up)
- `release` (remember to run in `release` instead of `debug` mode)
<br>

Refer to [SFML instruction for VS](https://www.sfml-dev.org/tutorials/2.5/start-vc.php) for more details or if you want to make any change.

## Features
Minesweeper should be too familiar a game for everyone. This section only mentions uncommon/need to be mentioned features in this particular game:
- If all bombs surrounding a cell has been flagged, `double left click` on it to reveal the rest of surrounding cells.
- There are 2 ways to win: open all non-bomb cells or flag all bomb cells.
- When playing custom-sized board, number of bombs is 20% of total number of cells.

## Screenshots
<img src="https://github.com/sxweetlollipop2912/minesweeper-cpp/blob/main/game_release/screenshots/menu.png" alt="menu" width="600"/>
<img src="https://github.com/sxweetlollipop2912/minesweeper-cpp/blob/main/game_release/screenshots/difficulty.png" alt="difficulty" width="600"/>
<img src="https://github.com/sxweetlollipop2912/minesweeper-cpp/blob/main/game_release/screenshots/ingame.png" alt="in-game" width="600"/>
<img src="https://github.com/sxweetlollipop2912/minesweeper-cpp/blob/main/game_release/screenshots/leaderboard.png" alt="leaderboard" width="600"/>
