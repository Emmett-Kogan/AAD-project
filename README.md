# AAD-project
All I know is that for now I should implement Bellman-Ford-Moore

## Contributor(s)
1. Emmett Kogan

## Build Instructions
The Makefile has 3 rules, `debug` which compiles both the bfm object file and aqueduct with `DEBUG` defined. This may have leftover unwanted prints/additional information about how the program is being run outputted on `stdout` and `stderr`. Furthermore, `DEBUG` changes the way the program looks for `grid.txt`. Instead of assuming it is in `./grid.txt` it takes a command line arguement that is a relative path to the desired input file (this was just done for easier testing). 

There is also the `big` rule which does all of what `debug` does, but also changes the order in which rows and columns are inputted into the program so that it could work with the large randomly genrated testcases someone posted on discord.

As specified, the `default` rule builds a program that fits the specifications as far as input file, output file and I *think* all debug statements are inside ifdefs (this is also the first rule so just running `make` runs this one).

## Report

## Explanation

So I'm going to multithread the Bellman Ford calls so that all 1+|B| calls happen at the same time. Fortunatley they all take pretty much the exact same args, AND, don't share any data. So there's no mutual exclusion that I need to do either fortunatley. I think I'm going to write a small wrapper for BellmanFord that deals with setting up the args correctly and just sending that.