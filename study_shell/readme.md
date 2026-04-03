# Mini Shell in C

A simple Unix-like shell implementation written in C.

## Features

* Command execution using `fork` and `execvp`
* Support for pipelines (`|`)
* Built-in commands:

  * `cd`
  * `exit`
* Multiple command pipelines:

  * `ls | grep c | wc -l`

## Example

```
myshell> echo hello world | tr a-z A-Z | wc -w
2
```

## How it works

* Input is parsed into commands and arguments
* Pipes are created for inter-process communication
* Each command is executed in a separate process using `fork`
* `dup2` is used to redirect stdin/stdout between processes

## Build

```
make
```

## Run

```
./shell
```