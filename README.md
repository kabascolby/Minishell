# Minishell

Shell is beautiful! Isn’t there a famous saying? _“As beautiful as Shell?”_.

## About

The objective of this project was to implement a basic shell that allow users
to create, access, change and display environement variables, also to execute
Internal (builtins) and external (executables) commands.
it's will be the fondation for future advanced projects like 21sh and 42sh.
I wrote this project to be flexible and expandable with less dependancy.
I avoid to use some advanced feature because they will be fully implemented
in 21sh and 42sh.

## Getting Started

### Prerequisites

Need a terminal to run on mac or linux.

```text
Iterm, terminal (mac and linux), WSL (windows)...
```

### Running the program

run the Makefile to create an executable.

```bash
git clone https://github.com/kabascolby/Minishell.git

cd Minishell

make or make re
```

After the compilation, run the executable.

```bash
./minishell
```

## Implementions

Based on the restrictions to implement this project
and the coding style imposed by 42.

### Mandatory

the instruction was to implement a serie's of builtins commands
with their basic functionality also to be able to run some
externals commands(with binary files) specified in the PATH environement.

- Builtins commands: echo, cd, setenv, unsetenv, env, exit

```
Give an example
```

Explain what these tests test and why

### Bonuses

- Raw mode also called Non Canonical mode.
- Auto completion (with tab keypad).
- Cursor Mouvement and line edition feature.
  - Cursor positionning (keypad Left and Right);
  - History (keypad Up and Down).
- Signal management:
  - `Ctrl + C`;
  - `Ctrl + Z` (I turned it off. Will be updated in 21sh);
  - `Ctrl + D`.
- User right execution management (error handling).
- Multiple commands (semi colons).
- Custom Prompt:
  - Display current directory name;
  - Changing prompt color depending on the exit Status.
- Some specials characteres handling (with `$`, `$$`, and `#`...)
  - Single quotes or strong quotes keep the string unchanged
  - Double quotes expand the string based on the value of `$variable` and `$$`
- Hash `#` (comment inside the terminal)
- etc;

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

- C programing language
- Makefile to genrate the executable

## Authors

- **Lamine kaba** - _Initial work_ - [kabascolby](https://github.com/kabascolby)

## License

open source

## Acknowledgments

- Hat tip to anyone whose code was used
- Inspiration
- etc
