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

The Lab Structure
This Lab has a header files for you to implement. Your headers should be the same as in the Lab.
Note: All the code listings do not have header guards (#pragma once, or ifdef X_H/endif), and
you need to place them manually.
Your job is to complete the code under the TODO comments and to write the corresponding .cpp file.
Sometimes a part of the .cpp file is demonstrated to explain the task. Your implementation may differ
from that demonstration.
Commands:
The variable arguments in the commands:
 dbl_value is a double value that conforms to the IEEE754 standard
 string_value is a simple C ASCII style string
Cube
The syntax:
Cube L = dbl_value, origin = (dbl_value, dbl_value, dbl_value), filepath = &quot;string_value&quot;
where:
L is a length of a cube side
origin is a position of the cube in a scene where commas with or without white spaces
separate the coordinates
filepath is a full path to an output STL file including its name

The result:

A tessellated cube is written to an ASCII STL file.
The return values:
One of these values depending on a case described:
0 if succeeded
1 if L &lt;= 0
2 if the filepath is incorrect
3 if one or all arguments are not specified

An example:
Cube L = 10.0, origin = (4.5,3.4,2.1), filepath = &quot;D:\cube.stl&quot;
A tessellated cube is created with the side length 10.0 at the point (4.5,3.4,2.1), and is written to
an ASCII STL file with the full path D:\cube.stl.

Sphere
The syntax:
Sphere R = dbl_value, origin = (dbl_value, dbl_value, dbl_value), filepath = &quot;string_value&quot;
where:
R is a sphere radius
origin is a position of the sphere in a 3D scene where commas with or without white
spaces separate the coordinates
filepath is a full path to an output STL file including its name

The result:
A tessellated sphere is written to an ASCII STL file.
The return value:
One of these values depending on a case described:
0 if succeeded
1 if R &lt;= 0
2 if the filepath is incorrect
3 if one or all arguments are not specified

An example:
Sphere R = 10.0, origin = (4.5,3.4,2.1), filename = &quot;D:\sphere.stl&quot;

A tessellated sphere is created with a radius of 10.0 at the point (4.5,3.4,2.1), and is written to
an ASCII STL file with the full path D:\sphere.stl.

Split
Syntax:
Split input = &quot;string_value&quot;, origin = (dbl_value, dbl_value, dbl_value), direction = (dbl_value, dbl_value,

dbl_value), output1 = &quot;string_value&quot;, output2 = &quot;string_value&quot;

where:
input is a full path to an input STL file, including its name, containing an original
tessellated mesh
origin is a position of a normal vector start in a 3D scene where commas with or without
white spaces separate the coordinates
direction is a position of the normal vector direction in the 3D scene where commas
with or without white spaces separate the coordinates
output1 and output2 are full paths to output STL files including their names

The result:
Two tessellated meshes are written to the output1 and output2 STL ASCII files as the output of
splitting the original mesh contained in the input file by the plane defined by a normal vector
from the origin in the direction.
The return value:
One of these values depending on a case described:
0 if succeeded
1 if a normal length &lt;= 0
2 if input, output1, or output2 is incorrect
3 if one or all arguments are not specified
4 if the plane doesn’t intersect the original mesh which becomes the result

An example:
Split input = &quot;D:\Bunny.STL&quot;, origin = (1,2,3), direction = (0,0,1), output1 = &quot;D:\A.STL&quot;, output2 =
&quot;D:\B.STL&quot;
Two meshes are written to the D:\A.STL and D:\B.STL STL ASCII files as the output of splitting the original
mesh contained in the D:\Bunny.STL file by the plane defined by a normal from (0,0,1) in the (0,0,1)
direction.
Prerequisites

Before you begin to work with this Lab, it is recommended to read these materials:
 The STL File Format
Infrastructure
To set the infrastructure in your solution:
1. In Visual Studio 2017, create MeshEditor project written in C++17 as a command-line program
with main.cpp and empty main function.
Table 1 shows the final directory structure of this Lab.
Table 1. Final directory structure
. MeshEditor
MeshEditor
MeshEditor.sln

Application.h
Application.cpp
Command.h
Parser.h
Sphere.h
Sphere.cpp
Cube.h
Cube.cpp
Split.h
Split.cpp
STLParser.h
STLParser.cpp
main.cpp
MeshEditor.vcxproj

Dependencies
There are no dependencies.
Task 1
Before implementing our classes, let&#39;s examine the main function (see List. 1) where we create our
application and register all commands. The application is expandable for new functionality added by
registering custom types of commands. Each command takes input parameters and outputs an ASCII STL
file.
#include &quot;Application.h&quot;
#include &quot;Sphere.h&quot;
#include &quot;Cube.h&quot;
#include &quot;Split.h&quot;
int main(int argc, char *argv[])
{
Application app;
app.registerCommand(std::make_unique&lt;Sphere&gt;());
app.registerCommand(std::make_unique&lt;Cube&gt;());
app.registerCommand(std::make_unique&lt;Split&gt;());

return app.execute(argc, argv);
}

Code Listing 1. The main function

Start with the implementation of the Application class with parsing arguments (see List. 2).
Application.h MeshEditor
#include &quot;Command.h&quot;
#include &quot;Parser.h&quot;
class Application
{
public:
void registerCommand(std::unique_ptr&lt;Command&gt; command);
int execute(int argc, char *argv[]);
private:
// TODO
};

Code Listing 2. The Application class

There are two main methods:
1. registerCommand stores all commands inside the application to enable future extension
with new commands.
2. execute calls appropriate commands depending on the C arguments received from the main
function. Also, it converts the arguments from argc, argv to a dictionary understandable to
each command.
To store the commands for calling later, you must choose a container the best suiting your
implementation.
Now, let&#39;s look at the Code Listing 3 which shows the command interface.
Command.h MeshEditor
#include &lt;string&gt;
#include &lt;map&gt;
class Command
{
public:
virtual ~Command() {};
virtual const std::string&amp; getName() const = 0;
virtual int execute(const std::map&lt;std::string, std::string&gt;&amp; args) = 0;
};

Code Listing 3. The Command interface

Each command has:
1. A name returned by getName.

2. The execute method which input arguments are a dictionary of {argument name, value} string
pairs.
For example, the string Sphere R = 10.0, origin = (4.5,3.4,2.1), filename = &quot;D:\sphere.stl&quot;
becomes the args argument as the dictionary of string pairs:
std::map&lt;std::string, std::string&gt; args = {
{&quot;R&quot;, &quot;10.0&quot;},
{&quot;origin&quot;, &quot;(4.5,3.4,2.1)&quot;}
{&quot;filename&quot;, &quot;D:\sphere.stl&quot;}
};
Task 2
Using the normal calculation by hand inside write function, implement the STLParser class needed
for reading and writing STL files.
You can test the results, the output STL files, with Mixed Reality Viewer in Windows 10.
