# Zuma Deluxe Linux Port

Based on reverse engineering of Mac and Windows executables distributed on PopCap.com that was done by [Alula](https://github.com/alula/) at [CircleShootApp](https://github.com/alula/CircleShootApp/) repository, but rebased on SexyAppFramework ported to OpenGL/Linux at [re-plants-vs-zombies](https://github.com/headshot2017/re-plants-vs-zombies/) by [headshot2017](https://github.com/headshot2017) and [patoke](https://github.com/patoke). This port also uses [pevents](https://github.com/neosmart/pevents) by [neosmart](https://github.com/neosmart).
Replacing Windows-specific code with Linux-compatible in the game logic code, as well as implementing some missing features was done by me :)

Status: Fully playable, but potential bugs and inaccuracies are expected.

### Dependencies:
- libjpeg
- libpng
- libsdl2
- libglew2
- libogg
- libvorbis
- libvorbisfile

### Building:
Ensure you have all the neccesseray dependencies listed above installed, including their devel packages as well as building tools like make,cmake and gcc.
In the root of this repo run:
```
mkdir build && cd build
cmake ..
make 
```
If everything is right this should produce a binary called zuma-deluxe in the "build" folder which can be used to run the game, scroll further down to see how to setup.

### Differencies / accuracy notes:
- The most noticeable difference is that this project is based on open-source release of SexyAppFramework (1.3) that has been modified to work on Linux.
- Uses OpenGL instead of DirectX.
- None of the DRM stuff has been implemented and it won't be.
- Using software rendering or custom cursors is not supported. 
- Since the highscore reading/loading was not decompiled, I made a it from scratch, it is differently programmed from the original but functions the same.
- Game does not support savefiles from Windows.

### How to setup
Copy these folders from your original copy of the Zuma game to folder where you will store the executable:
```
fonts/
images/
levels/
music/
properties/
sounds/
```

### Potential bugs and how to fix them
#### Game crashing because the sounds are not loading properly:
For some reason, the game is unable to load all original .ogg sounds, temporary fix is to convert them all to .wav with ffmpeg. You can do that by running this command in terminal in the copied sounds/ folder:
```
for file in *; do ffmpeg -i "$file" "${file%.*}.wav"; done
```
after that you can delete .ogg files (be sure to do it with copied files in case something goes wrong). This is a temporary fix until I get araund to properly addressing the issue.

#### Levels blackswirley and grovefest not loading and crashing the game:
This is because in levels/levels.xml files for these levels are named as "Blackswirley" with an uppercase, but actual filenase are like "blackswirley". This is not a problem on Windows as it is case-insensitive, on Linux we have to fix that. 
Rename the "Blackswirley" to "blackswirley" inside of the levels/ folder, do the same for all files inside that blackswirley folder, everything should be lowercase.
Do the same for "grovefest" levels.
If there are any other levels causing the game to crash you might have to do this for them as well.

#### Font shadows not displaying correctly:
This is a known not game-breaking issue. Can be mitigated for now by editing Cancun8.txt, Cancun10.txt, Cancun12.txt files inside fonts/ directory. Will have to write up on that some other time. Game is fully playable without doing that, fonts might just look a little weird depending on the version of Zuma Deluxe that you got.

### Legal notes:
- The source code of game itself (everything in `/CircleShootApp/`) is provided as-is.
- Any modifications are licensed under MIT.
- The main focus of the project is porting and is done in a good faith - we don't condone piracy, we just essentially want to give the game a "second life".
- The decompilation project does not include any assets, you need to get them from your own copy of the game. If you don't own it, Steam version is easily available [here](https://store.steampowered.com/app/3330/Zuma_Deluxe/).
