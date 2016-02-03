#include <iostream>
#include <stack>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

void leaveBreadCrumb(stack<Coord>& p_stack, string maze[],  int r, int c);

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X........X",
        "XX.X.XXXXX",
        "X..X.X...X",
        "X..X...X.X",
        "XXXX.XXX.X",
        "X.X....XXX",
        "X..XX.XX.X",
        "X...X....X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10, 10, 6, 4, 1, 1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}

void leaveBreadCrumb(stack<Coord>& p_stack, string maze[], int r, int c)
{
    if(maze[r][c] == '.')
    {
        p_stack.push(Coord(r, c));
        maze[r][c] = '?';
    }
}

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    
    stack<Coord> m_stack;
    Coord end_coord(er, ec);

    leaveBreadCrumb(m_stack, maze, sr, sc);
    

    while(!m_stack.empty())
    {
        Coord current_coord(m_stack.top());
        //cout << "(" << current_coord.r() << "," << current_coord.c() << ")" << endl;
        m_stack.pop();
        if(current_coord.r() == end_coord.r() && current_coord.c() == end_coord.c())
            return true;
        leaveBreadCrumb(m_stack, maze, current_coord.r() - 1, current_coord.c());
        leaveBreadCrumb(m_stack, maze, current_coord.r(), current_coord.c() + 1);
        leaveBreadCrumb(m_stack, maze, current_coord.r() + 1, current_coord.c());
        leaveBreadCrumb(m_stack, maze, current_coord.r(), current_coord.c() - 1);
    }
    return false;
 
 //Stack-based algorithm
 // Push the starting coordinate (sr,sc) onto the coordinate stack and
 // update maze[sr][sc] to indicate that the algorithm has encountered
 // it (i.e., set maze[sr][sc] to have a value other than '.').
 // While the stack is not empty,
 // {   Pop the top coordinate off the stack. This gives you the current
 // (r,c) location that your algorithm is exploring.
 // If the current (r,c) coordinate is equal to the ending coordinate,
 // then we've solved the maze so return true!
 // Check each place you can move from the current cell as follows:
 // If you can move NORTH and haven't encountered that cell yet,
 // then push the coordinate (r-1,c) onto the stack and update
 // maze[r-1][c] to indicate the algorithm has encountered it.
 // If you can move EAST and haven't encountered that cell yet,
 // then push the coordinate (r,c+1) onto the stack and update
 // maze[r][c+1] to indicate the algorithm has encountered it.
 // If you can move SOUTH and haven't encountered that cell yet,
 // then push the coordinate (r+1,c) onto the stack and update
 // maze[r+1][c] to indicate the algorithm has encountered it.
 // If you can move WEST and haven't encountered that cell yet,
 // then push the coordinate (r,c-1) onto the stack and update
 // maze[r][c-1] to indicate the algorithm has encountered it.
 // }
 // There was no solution, so return false
 
}