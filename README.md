# AAD-project
All I know is that for now I should implement Bellman-Ford-Moore

## Contributor(s)
1. Emmett Kogan

## Build Instructions
1. Use the makefile

## Notes
There are currently some issues with the assignment doc where the example they gave is being updated soon and the bounds of station coordinates should be adjusted as they should be [0, M) for rows and [0, N) for columns, not inclusive like the document currently states.

For final submission, I need to change the way the input file is passed in so that it's hardcoded to `grid.txt` and not a cmdline arg

And need to do make not make debug

## Explanation

So I'm going to multithread the Bellman Ford calls so that all 1+|B| calls happen at the same time. Fortunatley they all take pretty much the exact same args, AND, don't share any data. So there's no mutual exclusion that I need to do either fortunatley. I think I'm going to write a small wrapper for BellmanFord that deals with setting up the args correctly and just sending that.