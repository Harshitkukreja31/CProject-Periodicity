# 🧪 Periodic Table Implementation in C

Welcome to the Periodic Elements Explorer - a powerful C-based tool for chemistry enthusiasts and students alike!



## Overview
This project is a comprehensive C implementation of a periodic table of elements. It provides an interactive interface for exploring element data, analyzing trends, and visualizing chemical properties. The application uses efficient data structures and algorithms to ensure fast lookups and responsive analysis.

## 🌟 Features
- **Fast Data Retrieval**: Utilizes a hash table for quick element lookups.
- **Multiple Search Options**: Search elements by name, symbol, or atomic number.
- **Full Periodic Table Display**: View the entire periodic table.
- **Trend Analysis**: Analyze trends for various properties including:
  - Electronegativity
  - Melting point
  - Boiling point
  - Ionization energy
  - Electron affinity
  - Atomic radius
- **Data Visualization**: Plot trends with options to display in a pop-up window or save as PNG.
- **Interactive Menu**: User-friendly command-line interface.

## How It Works
1. **Data Loading**: Element data is read from a CSV file and stored in a hash table for efficient access.
2. **User Interaction**: The program presents a menu-driven interface for users to choose various operations.
3. **Search Functionality**: Utilizes hash table lookups for fast element retrieval.
4. **Trend Analysis**: Implements algorithms to analyze and compare element properties across specified ranges.
5. **Visualization**: Uses plotting functions to create visual representations of analyzed trends.

## File Structure
```
project_root/
│
├── .vscode/
│   ├── launch.json
│   ├── settings.json
│   └── tasks.json
│
├── bin/
│   ├── data.csv
│   └── test_data.csv
│
├── include/
│   ├── csv_reader.h
│   ├── hashtable.h
│   ├── periodic_table.h
│   ├── plotFunctions.h
│   └── trends.h
│
├── src/
│   ├── csvReader.c
│   ├── hashtable.c
│   ├── main.c
│   ├── periodictable.c
│   ├── plotFunctions.c
│   └── trends.c
│
├── tests/
│   └── test_main.c
│
└── Makefile
```

### Directory and File Descriptions:
- `.vscode/`: Contains VS Code configuration files for the project.
- `bin/`: Stores binary and data files.
  - `data.csv`: Main data file for the periodic table.
  - `test_data.csv`: Test data for unit testing.
- `include/`: Contains header files for the project.
- `src/`: Contains the source code files.
- `tests/`: Contains unit tests for the project.
- `Makefile`: Automates the build process.

## Getting Started
1. Ensure you have a C compiler installed (e.g., GCC).
2. Clone the repository to your local machine.
3. Navigate to the project directory.
4. Build the project using the Makefile:
   ```
   make
   ```
5. Run the compiled program:
   ```
   ./bin/periodic_table
   ```

## Usage
1. Upon running the program, you'll be presented with a menu of options.
2. Choose an option by entering the corresponding number:
   - Print entire periodic table
   - Search by full symbol
   - Search by full name
   - Search by atomic number
   - Analyze specific trend
   - Analyze all trends
   - Plot specific trend
   - Quit
3. Follow the prompts to search for elements, analyze trends, or visualize data.
4. To exit the program, choose the "Quit" option from the menu.

## Performance
- **Element Lookups**: O(1) average time complexity due to hash table implementation.
- **Trend Analysis**: O(n) time complexity for analyzing trends, where n is the number of elements in the specified range.
- **Data Loading**: O(m) time complexity, where m is the total number of elements in the CSV file.

The use of a hash table ensures that individual element lookups remain fast even as the dataset grows, making this implementation scalable and efficient for various applications in chemistry education and research.



