# AAD-project
All I know is that for now I should implement Bellman-Ford-Moore

## Contributor(s)
1. Emmett Kogan

## Build Instructions
The Makefile has 3 rules, `debug` which compiles both the bfm object file and aqueduct with `DEBUG` defined. This may have leftover unwanted prints/additional information about how the program is being run outputted on `stdout` and `stderr`. Furthermore, `DEBUG` changes the way the program looks for `grid.txt`. Instead of assuming it is in `./grid.txt` it takes a command line arguement that is a relative path to the desired input file (this was just done for easier testing). 

There is also the `big` rule which does all of what `debug` does, but also changes the order in which rows and columns are inputted into the program so that it could work with the large randomly genrated testcases someone posted on discord.

As specified, the `default` rule builds a program that fits the specifications as far as input file, output file and I *think* all debug statements are inside ifdefs (this is also the first rule so just running `make` runs this one).

## Report
There are three main steps in my solution:
1. Parse input file and convert 2D array of integers `heights` to a graph (edge list)
2. Perform Bellman-Ford on the graph where the starting node is src and for each node in B
3. Find the best permutation of traversing to each node to minimize cost (brute force)

To be more specific, I based my Bellman-Ford implementation off of a GeeksForGeeks post, and after that it seemed like the easiest way to represent the graph while doing this problem would be an edge list, as relaxation is a bit easier. Granted this approach uses `sizeof(Edge)*2*(2*rows*cols-rows-cols)` bytes of memory, which in the worst case is like, 237.6KB (call me Google Chrome). In my Bellman Ford implementation, it performs relaxation on each edge, `rows*cols-1` times as that is the maximum length of any path from a src node to any other path in the grid. This is technically dynammic programming, as an array is used to store the path to each node, and the related equation would be `Cost of path to node = when path to src is known = MIN(cost of path to src of edge + cost of edge, current cost of path to dest node), otherwise do not update`. The BellmanFord function I wrote returns a pointer to some heap allocated array of these distances, This is used to construct a 2D array of paths to each other node in {src, {B}} for each node also in that set. Essentially what has happened is that I constructed a new graph where each node is just {src, {B}} and the edges are now the cost of the paths to each other in the original graph. The next step is basically TSP on this new graph, but, since the size is always 1+|B|, and |B| <= 8, at worst I'm chceking 8! permutations (as src is always first). And I just brute forced this part, I honestly figured I'd have an issue with how long this would take for the worst case, so before testing with the largest possible input I actually multithreaded the Bellman-Ford calls, and I left this in, but this would've run just fine.

As far as a discussion of time complexity, I'll go by each part of the solution, and then produce a final time complexity for the entire program. The first part parses row\*col+1+|B| input rows, as 1 and |B| are essentially constants or small, this part is just O(rows\*cols). The following Bellman-Ford calls to produce the paths between each node in {src, {B}} happen 1+|B| times, but as previosuly discussed this is always <10 so I'm treating it as a constant. My Bellman-Ford implementation runs in O(V*E), but, `V = rows*cols` and `E = 2*(2*rows*cols-rows*cols)`, so this is effectivley `O(rows<sup>2</sup>cols<sup>2</sup>)`. This would typically be multiplied by `1+|B|` but this is small, and since I multithreaded these calls they all happen in parallel with no commmunication or parallelization overhead, so I dropped the constant (and felt good about it :smile;). The final part, finding the best order to traverse B in starting at src, would also typically be `O(|B|!)`, but, again, `|B| <= 8`, so... we could say that, or say this is a really big constant as it doesn't scale. So, the final time complexity, where `|B| <= 8` would be something like `O(rows<sup>2</sup>cols<sup>2</sup> + rows*cols + |B|)`, which simplifies to `O(rows<sup>2</sup>cols<sup>2</sup>)`.