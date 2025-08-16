# nixie

A terminal-based text editor because I'm tired of using vim...

## What it is right now

This is a little hobby project where I'm building a text editor from scratch. It's super early, but here's what works:

- Basic terminal UI using notcurses
- A simple widget system (right now just text widgets)
- You can position text on the screen with different alignments
- Basic keyboard input (press 'q' to quit)
- Clean terminal setup and cleanup

## How it's organized

Nothing fancy, just trying to keep things clean:

```
include/           # All the header files
├── events/        # Keyboard stuff
├── ui/            # Positioning logic
└── widgets/       # UI components

src/               # Implementation files
└── widgets/

main.cpp           # Where it all starts
```

## What's Next

My next goal is to add **panel management** - basically a way to split the terminal into different panels and organize them in grids. Think of it like having multiple panes that you can arrange however you want.

## What you need to build it

- notcurses (for the terminal stuff)
- CMake (3.10 or newer)
- pkg-config
- A C++17 compiler

## My setup

I'm using CLion and iTerm2 on macOS. If it doesn't work on your setup, I honestly don't know - but if you figure out how to fix it, send me a pull request!

## How to build it

First, get notcurses:

```bash
# macOS
brew install notcurses

# Ubuntu/Debian
sudo apt-get install libnotcurses-dev

# Arch Linux
sudo pacman -S notcurses
```

Then build:

```bash
git clone https://github.com/AmicioEspyy/nixie.git
cd nixie
cmake -S . -B build
cmake --build build
./build/nixie
```

## If you want to help

Only if you have time and actually want to!

If you do contribute:
- Use the `.clang-format` file (it's basically Google style)
- Follow [conventional commit rules](https://gist.github.com/qoomon/5dfcdf8eec66a051ecd85625518cfd13)
- Keep the file naming consistent

Things that might be fun to work on:
- Panel management (my next goal)
- More widget types
- Better keyboard handling
- Whatever else seems interesting

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

*"Sometimes you just need to build your own tools to get things done right."*
