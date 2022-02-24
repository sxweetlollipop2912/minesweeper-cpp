# minesweeper-cpp
A game that is both explosive and mind-blowing.

## Dependencies:
- SFML v2.5 or above.
- Boost serialization v1.78 or above.
<br>

This repo is a solution from Visual Studio (2019 in particular). Boost is set to be installed through NuGet, and SFML is already configured.
## Install SFML:
If you're not on Visual Studio, see [SFML Tutorials](https://www.sfml-dev.org/tutorials/2.5/).
<br>
If you're on Visual Studio:
1. Download SFML binaries matching your Visual Studio version [here](https://www.sfml-dev.org/download/sfml/2.5.1/).
2. Unzip and move 2 folders `include` and `lib` to `minesweeper/SFML`.
<br>

Note: Current configuration of the library in Visual Studio is:
- `SFML_STATIC` (requires no `.dll`)
- `release`
<br>

Refer to [SFML instruction for VS](https://www.sfml-dev.org/tutorials/2.5/start-vc.php) for more details or if you want to make any change on Visual Studio.