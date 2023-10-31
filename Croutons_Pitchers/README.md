<p align="center">
  <img align="center" src="../assets/professor-layton-curious-village.png" />
</p>

<h1 align="center">
  Professor Layton and the Curious Village
</h1>
<h1 align="center">
  Crouton's Pitchers
</h1>

Project for my Combinatorics class at Tsinghua University

These puzzles were proposed by Crouton, the owner of the restaurant.

Since the program can take the capacity of each pitcher and the final state, you can create every variation of this puzzle **that you want!** (but the maximum capacity has to be hold in 8 bits for optimisation reasons)

# Puzzles

- 023 Juice Pitchers
- 024 Milk Pitchers
- 078 Water Pitchers

<p align="center">
  <img align="center" src="../assets/IMG-4067.PNG" />
</p>

# Video

If you want to see the demo of this game, you can watch it here:

https://www.youtube.com/watch?v=oEaVHxA4m3U

# Build

This project was made in c++ with cmake, so you will need g++ and cmake

You can build the project like so:
```
rm -rf build
mkdir build
cd build
cmake ..
cmake --build .
```
Or you can use the script "build.sh" to build the project.

After that, you can find the binary in the "build" folder

# Usage

```
./Croutons_pitchers x0 x1 x2 y0 y1 y2
```

The binary takes 6 arguments:

- x0 x1 x2 are integers representing the capacity in litres of pitcher 0, 1 and 2
- y0 y1 y2 are integers representing the amount of litres wanted at the end in pitcher 0, 1 and 2


# Example

Here's an exemple to solve "Water Pitchers"
```
./Croutons_pitchers 16 9 7 8 8 0
```

```
The steps are:
0 > 1
1 > 2
2 > 0
1 > 2
0 > 1
1 > 2
2 > 0
1 > 2
0 > 1
1 > 2
2 > 0
1 > 2
0 > 1
1 > 2
2 > 0
```

# Algorithm

I choose to store the quantity of liquid of each pitcher in an array of 3 unsigned char.

This array share his memory with another int inside an union called state.

```c++
typedef union {
    int id = 0;
    unsigned char pitchers[3];
} state_u;
```
The advantage is that now I can fill the array and have an unique indentifier that represents it.

Thanks to this, I can easily create a set to keep track of all different states that we had during the game.

here's a little pseudo code
```
set   seen_states;
queue states;

...
... variable initialization, adding first state to the queue and creating goal_state
...

while (states not empty):
    actual_state = states.pop()

    if actual_state == goal_state:
      return

    seen_states.add(actual_state)
    ...
    ... create new states from the one gotten from the queue and add them to the queue
    ...



```

