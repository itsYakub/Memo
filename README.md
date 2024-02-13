# Memo

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/P5P8U0T3I)


<i>Point and click, match the pairs in the shortest amount of time!</i>

## About❗️

<b>Memo</b> is the match-pair game in which you're challenged to find the pairs of numeric cards on 4x4, 6x6 od 8x8 grid.

## Prerequesites 📜
- <b>Valid operating system:</b> Currently <b>Memo</b> is available only on `Windows` and `Linux`.
- <b>Valid C/C++ compiler:</b> by default the project is built using `g++` compiler. 
- <b>Valid GNU Make instalation:</b> <b>Memo</b> uses `Makefile` as it's primary build system. Make sure that you've one installed on your machine.

## Instalation 🛠️
#### 1. Clone this repository
```bash
git clone https://github.com/itsYakub/Memo.git --depth=1
```
#### 2. Go to the project's directory:
```bash
cd Memo
```
#### 3. Check if every thing in the `Makefile` is set up correctly.
- Check if the <b>include paths</b> are correct in the `IXXFLAGS`;
- Check if <b>library paths</b> are correct in the `LDFLAGS`;
#### 4. Building the final executable:
- Default build command:
```bash
make all
```

- If you want to build in the `DEBUG` mode, use command:
```bash
make all MODE=debug
```

- If you want to build in the `RELEASE` mode, use command:
```bash
make all MODE=release
```

- If you want to target the `Windows` platform, use command:
```bash
make all PLATFORM=windows
```

- If you want to target the `Linux` platform, use command:
```bash
make all PLATFORM=linux
```

- If you want to combine all the parameters to get the build you want, use command:
```bash
make all PLATFORM={{Your Platform}} MODE={{Build Mode}}
```

The default parameters of the Makefile are:
- <b>PLATFORM:</b> windows;
- <b>MODE:</b> debug;

## Credits 📖
- [raysan5/raylib](https://github.com/raysan5/raylib) - raylib library;
- [raysan5/raygui](https://github.com/raysan5/raygui) - raygui library;
- [nlohmann/json](https://github.com/nlohmann/json) - json library;
- [Kenney/UI Audio](https://www.kenney.nl/assets/ui-audio) - UI Audio library;
- [emhuo/peaberry-pixel-font](https://emhuo.itch.io/peaberry-pixel-font?download) - Font;
- [Adigun A. Polack/aap64](https://lospec.com/palette-list/aap-64) - Color Palette;

## Licence ⚠️
This project is under the [MIT Licence](https://github.com/itsYakub/Memo/LICENCE)