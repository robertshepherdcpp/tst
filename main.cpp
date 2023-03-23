// This is a project for testing things.
/*
#include"meta.hpp"

#include<iostream> // std::cout

struct xyz_x
{
	int xyz{};
	int xyz_() {}
	int a{};
	int b{};
};

int main()
{
	meta::invoke_wrapper < []() constexpr {return []() constexpr {return 56; }; } > x{};
	static_assert(x.invoke().final_invoke() == 56);

	template<auto T>
	using rust_trait = meta::trait < T, meta::trait_module < [](auto X) {X.xyz; x.xyz_(); } > {},
		                             meta::trait_module < [](auto X) {X.a + X.b; } > {} > ;

	std::cout << rust_trait < xyz_x{} > ::value;

}

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Compiler {
private:
    vector<string> assembly;

public:
    void compile(const string& input_program) {
        // Tokenize the input program
        stringstream ss(input_program);
        string line;
        while (getline(ss, line)) {
            stringstream line_ss(line);
            string token;
            vector<string> tokens;
            while (line_ss >> token) {
                tokens.push_back(token);
            }

            // Generate assembly code for the tokenized line
            if (tokens.size() == 3) {
                string var_name = tokens[0];
                string op = tokens[1];
                int value = stoi(tokens[2]);
                if (op == "=") {
                    assembly.push_back("mov DWORD PTR [rbp-" + var_name + "], " + to_string(value));
                }
                else if (op == "+=") {
                    assembly.push_back("add DWORD PTR [rbp-" + var_name + "], " + to_string(value));
                }
                else if (op == "-=") {
                    assembly.push_back("sub DWORD PTR [rbp-" + var_name + "], " + to_string(value));
                }
            }
        }
    }

    void output() {
        // Write the generated assembly code to stdout
        cout << "global _start\n\n";
        cout << "_start:\n";
        cout << "    mov rbp, rsp\n";
        for (string line : assembly) {
            cout << "    " << line << "\n";
        }
        cout << "    mov rax, 60\n";
        cout << "    xor rdi, rdi\n";
        cout << "    syscall\n";
    }
};

int main() {
    string input_program = "";
    string line;
    while (getline(cin, line)) {
        if (line == "quit") {
            break;
        }
        input_program += line + "\n";
    }

    // Compile the input program and output the generated assembly code
    Compiler compiler;
    compiler.compile(input_program);
    compiler.output();

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

// define the size of the grid and the range of possible numbers
const int GRID_SIZE = 5;
vector<int> NUM_RANGE = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

// generate a random grid with target numbers
vector<vector<int>> generateGrid() {
    vector<vector<int>> grid(GRID_SIZE + 1, vector<int>(GRID_SIZE + 1));
    shuffle(NUM_RANGE.begin(), NUM_RANGE.end(), default_random_engine());
    for (int i = 0; i < GRID_SIZE; i++) {
        int rowSum = 0;
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = NUM_RANGE[i * GRID_SIZE + j];
            rowSum += grid[i][j];
            grid[GRID_SIZE][j] += grid[i][j];
        }
        grid[i][GRID_SIZE] = rowSum;
        grid[GRID_SIZE][GRID_SIZE] += rowSum;
    }
    shuffle(NUM_RANGE.begin(), NUM_RANGE.end(), default_random_engine());
    for (int j = 0; j < GRID_SIZE; j++) {
        grid[GRID_SIZE][j] = NUM_RANGE[j];
        grid[j][GRID_SIZE] = NUM_RANGE[j + GRID_SIZE];
    }
    return grid;
}

// print the grid with target numbers
void printGrid(vector<vector<int>> grid) {
    for (int i = 0; i <= GRID_SIZE; i++) {
        for (int j = 0; j <= GRID_SIZE; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// delete a number from the grid and update the targets
void deleteNumber(vector<vector<int>>& grid, vector<int>& rowTargets, vector<int>& colTargets, int row, int col) {
    int num = grid[row - 1][col - 1];
    grid[row - 1][col - 1] = 0;
    rowTargets[row - 1] -= num;
    colTargets[col - 1] -= num;
    colTargets[GRID_SIZE] -= num;
}

int main() {
    // generate the grid and print it out
    auto grid = generateGrid();
    printGrid(grid);

    // loop until the puzzle is solved or the user quits
    while (true) {
        // ask the user to enter the coordinates of a number to delete
        int row, col;
        cout << "Enter row number to delete (or 0 to quit): ";
        cin >> row;
        if (row == 0) break;
        cout << "Enter column number to delete (or 0 to quit): ";
        cin >> col;
        if (col == 0) break;
        if (row < 1 || row > GRID_SIZE || col < 1 || col > GRID_SIZE) {
            cout << "Invalid input!" << endl;
            continue;
        }
        if (grid[row - 1][col - 1] == 0) {
            cout << "That cell is already empty!" << endl;
            continue;
        }
        deleteNumber(grid, grid[GRID_SIZE], grid[GRID_SIZE], row, col);
        deleteNumber(grid, grid[row - 1], grid[col - 1], col, row);
        printGrid(grid);

            bool solved = true;
            for (int i = 0; i < GRID_SIZE; i++) {
                if (grid[i][GRID_SIZE] != 0 && grid[i][GRID_SIZE] != grid[GRID_SIZE][GRID_SIZE]) {
                    solved = false;
                        break;
                }
                if (grid[GRID_SIZE][i] != 0 && grid[GRID_SIZE][i] != grid[GRID_SIZE][GRID_SIZE]) {
                    solved = false;
                        break;
                }
            }
        if (solved) {
            for (int i = 0; i < GRID_SIZE; i++) {
                if (grid[i][GRID_SIZE] == 0 || grid[GRID_SIZE][i] == 0) {
                    solved = false;
                    break;
                }
            }
        }
        if (solved) {
            cout << "Congratulations, you solved the puzzle!" << endl;
            break;
        }
    }
    cout << "Goodbye!" << endl;
    return 0;
}
*/

// pack_remove.hpp
/*
#include <iostream>
#include <tuple>
#include <utility>

struct Not {
    constexpr auto operator==(Not) { return true; }
    constexpr auto operator==(auto) { return false; }
};

template <auto True, auto value> struct add_if {
    constexpr auto operator()() {
        if constexpr (True == true) {
            return value;
        }
        else {
            return Not{};
        }
    }
};

template<typename Tuple>
constexpr auto tuple_size(Tuple tuple)
{
    return[]<typename... Ts>(std::tuple<Ts...>&tup)
    {
        return (sizeof(Ts) + ... + 0);
    }(tuple);
}

template <auto lambda, auto... Ts> constexpr auto pack_remove() {
    return std::make_tuple(add_if<!lambda(Ts), Ts>{}()...);
}

template <auto ToGet, typename Tuple> constexpr auto special_get(Tuple tuple) {
    if constexpr (std::get<ToGet>(tuple) == Not{} &&
        tuple_size(tuple) < ToGet) {
        return special_get<ToGet + 1, decltype(tuple)>(tuple);
    }
    if constexpr (std::get<ToGet>(tuple) == Not{}) {
        return -1;
    }
    else {
        return std::get<ToGet>(tuple);
    }
}

int main() {
    std::cout
        << special_get < 0, decltype(pack_remove < [](auto x) { return x == 4; }, 4,
            'c', true, false, 4, 2 > ()) > (
                pack_remove < [](auto x) { return x == 4; }, 4, 'c', true, false,
                4, 2 > ());
}
*/

#include"constexpr_while.hpp"

#include<iostream>

int main()
{
    constexpr_while < 0, [](auto x) {return x < 10; }, [](auto x) {return x + 1; } > c_w{};
    c_w([]() {std::cout << "Hi\n"; });
}

