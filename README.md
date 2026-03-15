# Sprout Shell

A basic, simple shell built using C++ 🌱

## Features
* Command execution
* Program execution
* Piplines
* Redirection
* Basic session-based history
* Built-in commands

## 🔤 Commands
Sprout Shell has a few handy-dandy commands for use:

| Command | Usage                  | Description                         |
| ------- | ---------------------- | ----------------------------------- |
| cd      | ``cd <**directory**>`` | Navigates to given folder directory |
| history | ``history``            | Prints out command history          |
| exit    | ``exit``               | exits shell                         |

You can also check the version you are running:

```
sproutsh --version
```
*or*
```
sprout --version
```

> The commands `sprout` and `sproutsh` can be used interchangeably.

## Pipelines
Pipe symbols must be separated with a space:
```
ls -l | wc -l
```

## Redirection

Redirection symbols must have spaces before and after them

* Output: `ls > files.txt` (overwrites) or `ls >> files.txt` (appends)
* Input: `sort < names.txt`

## 📢 Signal Handling
Sprout Shell handles standard interrupts like `Ctrl+C`. It won't crash or exit when you interrupt a running process, keeping your session active.

## ⚙️ Building and Running
### Prerequisites
* C++ Compiler (supporting C++17 or later)
* CMake (version 3.10 or higher)

To compile in your terminal:
```
mkdir build
cd build
cmake ..
make
./sproutsh
```