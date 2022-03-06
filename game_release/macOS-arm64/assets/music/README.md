## In here, you can customize with your own music taste and visual choices.
Stuff worth mentioning:
- Allowed audio file extensions: `.flac`, `.ogg`, `.wav`. Due to licensing reasons, mp3 is not supported by SFML library.<br>
[This site](https://audio.online-convert.com/convert-to-ogg) can help converting files to .ogg (at `Select audio codec`, pick `vorbis`).
- There should be no space in filenames.
- By default, 15 songs are picked randomly at the start of the game (this is hard-coded, sorry).
## Add a song
To add a song into the game, simply drag its audio file into this folder.
<br>
To remove a song, simply move it elsewhere (or delete it).
## Add visuals
The hard part is to set up visuals. Visuals for a song is only optional, and is stored in a text file sharing the same name as the audio, with `.cfg` as its extension.
<br>
For example, say I've added an audio file named `Megalovania.ogg` into this folder. To set up visuals for it, I create a file named `Megalovania.cfg`. Inside, it should look something like this:
```
[0]
PrimaryColor: 125 127 129
SecondaryColor: 130 132 134
TransitionDuration: 10
BubbleSpeed: 250

[10]
SecondaryColor: 139 142 145
TransitionDuration: 10

[71]
PrimaryColor: 119 123 128
SecondaryColor: 131 135 139
TransitionDuration: 15
BubbleSpeed: 400

[82]
BubbleSpeed: 450
```
This is actually taken out of one of the config files. Here are some explanations:
- Numbers between `[]` brackets denotes a point in time, after certain seconds into the song.<br>`[10]` means after 10 seconds from the start of the song, visual changes in following lines will be applied.
- `PrimaryColor:` is for background color, in RGB.
- `SecondaryColor:` is for the color of the bubbles, in RGB.<br>
[This site](https://htmlcolors.com/html-color-picker) can help picking out color and its RGB code.
- `TransitionDuration:` denotes the duration for the transitions of `PrimaryColor` and `SecondaryColor`.<br>If you wish to have different durations for each type, set them up separately, say `[10]` for primary, then `[11]` for secondary.
- `BubbleSpeed:` is to set up the bubbles' speed. This happens instantly.<br>`200` is really slow, `300-400` is medium, and `600-650` is really fast.


And here are some important notes:
- Syntax is crucial. Capital letters matter. Do not mistype. Add `:` right after the name of a field, with no spacing in between. Fields must be on separate lines. See how I wrote up there?
- Changes must be sorted CHRONOLOGICALLY. `[]`s must be strictly greater than the preivous.
- Every color change should come with a `TransitionDuration`, even if it is 0 sec.
- You only need to set up stuff that actually changes. For instance, if you only wish to make change for `SecondaryColor`, then there's no need to add a `PrimaryColor` field also. See `[10]` and `[82]` from the example above.
- It is recommended to have the first `TransitionDuration` to be at least 10 seconds so it won't blind people's eyes.
- It's okay to have `TransitionDuration` exceeds the time of the next change. By the time of the next change, any ongoing previous change is simply stopped.

### That's all. Have fun listening!