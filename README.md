This is my latest attempt at writing an n-body physics simulator, after the 'failures' that were ParSi and Unisim a few years ago.

To use, compile as;

```gcc main.c -lm -o nb -g```

Then (using the model given in 'model') run as

```./nb model t```

Where 't' is prepended to the output csvs. This runs, and accepts keyboard input. On each input (enter text and hit enter) it will run another STEPS iterations, with timestep DT, outputing every PRINT. Once finished, type "exit" to close nicely.

 This outputs as many csv files as there are objects, with each file representing the motion of that object. The columns in the csv files are;

```time, x, y, z```

And so using gnuplot the position of an atom can be plotted in 3D as 

```splot 'file-0.csv' using 2:3:4 with lines```

Or with time in the 4th dimension as colour;

```splot 'file-0.csv' using 2:3:4:1 with lines palette```

The input files are given as

```STEPS:PRINT:DT
X,Y,Z,XV,YV,ZV,M```

Where X, Y, Z are the position, XV, YV and ZV are the initial velocities, and M is the mass. 
