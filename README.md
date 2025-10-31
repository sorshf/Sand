# 🏖️Falling Sand Simulation

Falling sand simulation built using **C++** and **SDL3**.

## Features

- 🏖️ Drop sands with random color
- 🪵 Add woods to support sands
- 🔥 Burn woods to create flame and smoke
- 🏞️ Built-in screenshot capture
![Screenshot of the app showing flamable wood, fire, and smoke.](/assets/screenshots/World_tree.png)

## Control Keys

Add material or apply a function by pressing left or right mouse button.

Change the material or function type by entering the following keys (no need to hold the keys):

- Sand: `S`
- Wood: `W`
- Burn: `F`
- Screenshot: `D` 


## Dependencies

- [SDL3](https://www.libsdl.org) – Window rendering
- C++17 or later

## Build

```bash
git clone https://github.com/sorshf/Sand.git
cd Sand
mkdir build && cd build
cmake ..
make
./bin/Sand
```