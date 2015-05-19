# Corner table and CHE table generator

## Up and running

Just running 'make' should generate the 'opposites' binary executable.

With the binary built, it should receive a mandatory flag - '-corner' or '-che', informing which type of opposites
table you wish to build, followed by the input file.

```bash
	~/cfg $ make
	~/cfg $ ./opposites -che path/my_input.txt
	# A my_input.txt.output will be generated in the same folder as the input file
```

## Input File

The input file must obey the following convention, informing the vertices's as well as the geometry of a 3D mesh.
Examples of input files can be found at 'test/input'.

```
NumPoints NumTriangles
x y z
x y z # After the header, there should be numPoints lines with X,Y,Z coordinates each
x y z
......
id1 v1 v2 v3 # After the coordinates, there will be numTriangles lines containing four integer
id2 v1 v2 v3 #  values each. The first one is the triangle ID and should be ignored.
id3 v1 v2 v3 #  The following three values compose the triangles, referencing the previous vertex list
```

## Testing

To test the algorithm, you just have to place the input file to be tested inside the 'test/input'
path, followed by the result output file in the 'test/results' path. By convention, the result
file should be name 'che_' + result file or 'corner_' + result file. Finally, the name of the
input file should be added into the Test file (examples can be found in the 'test' folder). The
test should automatically build the table on top of the input file and compare the results with
the expected output file.

Running tests consist of one command per operation, and no parameters need to be informed:

```bash
	make corner-table-test
	make che-table-test
```
