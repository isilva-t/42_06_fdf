# FDF - Wireframe Model Renderer

![sample](./assets/01.png)

## Project Overview

FDF (Fil de Fer, French for "wireframe") is a 3D wireframe renderer created as part of the curriculum at 42 School. This program renders simple 3D landscapes from elevation maps, connecting the points with line segments to create a wireframe visualization.

## Features

- Reads a map file (.fdf) with elevation data
- Renders a 3D wireframe model in isometric projection
- Color gradients based on elevation (z-axis values)
- Efficient line drawing using the Bresenham algorithm

## Compilation

```
make
```

## Quick Demo

To quickly test the program with a sample map, simply run:

```
make demo
```
![sample](./assets/022.png)

## Usage

```
./fdf [map_file.fdf]
```

## Implementation Details

This project was my first introduction to computer graphics programming. Some of the key technical components include:

- **MiniLibX**: Uses the school's graphical library for window management and pixel drawing
- **Bresenham's Line Algorithm**: Implements this classic algorithm for efficient line rendering
- **Color Gradients**: Implements smooth color transitions based on elevation changes
- **Map Parser**: Reads and interprets .fdf files with proper error handling

## Personal Notes

I chose this project to explore how CAD programs draw lines on screen. Learning the Bresenham algorithm and implementing it was particularly enlightening. The most enjoyable part was creating the gradient color effect in the line drawing, which made the wireframes more visually appealing and helped emphasize the elevation changes.

![sample](./assets/04.png)

## Examples

The project includes several example maps that demonstrate various terrain features, from simple shapes to complex landscapes.

![sample](./assets/033.png)
