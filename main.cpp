#include <iostream>
#include <string>
#include <vector>

typedef unsigned int uint;

bool is_tile_safe(std::vector<uint>& positions, uint row, uint col)
{
    for (uint x = 0; x < row; x++)
        if (positions[x] == col || positions[x] == col + (x - row) || 
            positions[x] == col - (x - row))
            return false;

    return true;
}

std::vector<std::vector<uint>> get_possibilities(
    std::vector<uint> positions, uint rows, uint cols)
{
    uint cur_row = positions.size();
    
    std::vector<std::vector<uint>> solutions;

    for (uint col = 0; col < cols; col++)
    {
        if (is_tile_safe(positions, cur_row, col))
        {
            std::vector<uint> temp = positions;
            temp.push_back(col);

            if ((uint) temp.size() == rows)
                solutions.push_back(temp);

            else
            {
                std::vector<std::vector<uint>> possibilites = 
                    get_possibilities(temp, rows, cols);
                solutions.insert(
                    solutions.end(), possibilites.begin(), possibilites.end());
            }
        }
    }

    return solutions;
}

std::vector<std::vector<uint>> solve_problem(uint rows, uint cols)
{
    std::vector<std::vector<uint>> solutions;

    for (uint col = 0; col < cols; col++)
    {
        std::vector<uint> positions { col };

        if (rows == 1)
            solutions.push_back(positions);
        else
        {
            std::vector<std::vector<uint>> possibilites = 
                get_possibilities(positions, rows, cols);
            solutions.insert(
                solutions.end(), possibilites.begin(), possibilites.end());
        }
    }

    return solutions;
}

int main(int argc, char* argv[])
{
    uint n = 8;

    if (argc > 1)
    {
        if (std::string(argv[1]) == "-h")
        {
            std::cout 
            << "Usage: nqp <queens>\n"
            << "queens - number of queens, rows and columns" << std::endl;
            return EXIT_SUCCESS;
        }

        else
            n = (uint) std::atoi(argv[1]);
    }

    std::vector<std::vector<uint>> solutions = solve_problem(n, n);

    for (std::size_t i = 0; i < solutions.size(); i++)
    {
        std::cout << i << ": { ";
        
        for (auto position : solutions[i])
            std::cout << position << ",";

        std::cout << "\b \b }" << std::endl;
    }

    std::cout << solutions.size() << " solutions" << std::endl;

    return EXIT_SUCCESS;
}
