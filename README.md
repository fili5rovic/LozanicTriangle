# Lozanic Triangle Simulation

This C++ program simulates operations on a Lozanic Triangle, which is a variation of the Pascal Triangle with specific rules for its formation. The program allows users to generate a Lozanic Triangle, perform interpolation and ternary searches on the last row of the triangle, and measure the performance of these searches.

> This project was developed as the first university assignment for "Algorithms and Data Structures 2", University of Belgrade School of Electrical Engineering majoring Software Engineering. Please refer to the [instructions.pdf](instructions.pdf) file for detailed assignment instructions.
>
> Through the LozanicTriangle project, I appreciate gaining a practical understanding of Ternary and Interpolate searches, their significance and implementation in traversal, making my learning journey insightful and enjoyable.

## Features

- **Generate Lozanic Triangle**: Dynamically creates a Lozanic Triangle up to a user-specified size.
- **Interpolation Search**: Performs an interpolation search on the last row of the Lozanic Triangle.
- **Ternary Search**: Executes a ternary search on the last row of the Lozanic Triangle.
- **Performance Metrics**: Measures and outputs the number of iterations and time taken for each search algorithm.
- **Visual Output**: Displays the triangle and search results in a formatted table.
## Usage
Upon running the program, you will be prompted with a menu to start the simulation or exit. If you choose to start the simulation, you will then be asked to enter the size of the Lozanic Triangle. After the triangle is generated, you can input a key to search for in the last row of the triangle.

## Menu Options
Start Simulation: Begin the simulation process.
Exit Simulation: Terminate the program.
Search
After the triangle is generated, enter the key you wish to search for. The program will perform both interpolation and ternary searches and display the results.

## Output
The program outputs the Lozanic Triangle and the results of the searches in a well-formatted table, including:

* The number of iterations for each search.
* The time taken for each search in milliseconds.
* The success status of each search.
