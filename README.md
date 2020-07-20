# mesh_editor_stl_format

TASK

Lab 0
Overview
In this Lab, you will learn how to create a simple console application that processes inputs and outputs
ASCII STL files. The commands to be implemented are Cube, Sphere, and Split.
Objective
The objective of this Lab is to implement the following classes:
 Application that takes input arguments and registers the Cube, Sphere, and Split
commands
 STLParser that reads and writes ASCII STL files
 Cube that creates a tessellated cube and outputs it to an ASCII STL file
 Sphere that creates a tessellated sphere and outputs it to an ASCII STL file
 Split that splits a tessellated input mesh into two and outputs them to ASCII STL files

An example:
Cube L = 10.0, origin = (4.5,3.4,2.1), filepath = &quot;D:\cube.stl&quot;
A tessellated cube is created with the side length 10.0 at the point (4.5,3.4,2.1), and is written to
an ASCII STL file with the full path D:\cube.stl.

Split input = &quot;D:\Bunny.STL&quot;, origin = (1,2,3), direction = (0,0,1), output1 = &quot;D:\A.STL&quot;, output2 =
&quot;D:\B.STL&quot;
Two meshes are written to the D:\A.STL and D:\B.STL STL ASCII files as the output of splitting the original
mesh contained in the D:\Bunny.STL file by the plane defined by a normal from (0,0,1) in the (0,0,1)
direction.
