
#include <iostream>
#include <queue>
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

void leaveBreadCrumb(queue<Coord>& p_queue, string maze[], int r, int c);

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

void leaveBreadCrumb(queue<Coord>& p_queue, string maze[], int r, int c)
{
    if(maze[r][c] == '.')
    {
        p_queue.push(Coord(r, c));
        maze[r][c] = '?';
    }
}

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    
    queue<Coord> m_queue;
    Coord end_coord(er, ec);
    
    leaveBreadCrumb(m_queue, maze, sr, sc);
    while(!m_queue.empty())
    {
        Coord current_coord(m_queue.front());
        //cout << "(" << current_coord.r() << "," << current_coord.c() << ")" << endl;
        m_queue.pop();
        if(current_coord.r() == end_coord.r() && current_coord.c() == end_coord.c())
            return true;
        leaveBreadCrumb(m_queue, maze, current_coord.r(), current_coord.c() - 1); //Look east
        leaveBreadCrumb(m_queue, maze, current_coord.r(), current_coord.c() + 1); //Look west
        leaveBreadCrumb(m_queue, maze, current_coord.r() - 1, current_coord.c()); //Look north
        leaveBreadCrumb(m_queue, maze, current_coord.r() + 1, current_coord.c()); //Look south
    }
    return false;
    
// Queue-based algorithm
//     1.   Insert starting point onto the queue.
//     2.  Mark the starting point as “discovered.”
//     3.  If the queue is empty, there is NO SOLUTION and we’re done!
//     4.  ReleaveBreadCrumb the top point from the queue.
//     5.  If we’re at the endpoint, DONE!  Otherwise…
//     6.  If slot to the WEST is open & is undiscovered
//     Mark (curx-1,cury) as “discovered”
//     INSERT (curx-1,cury) on queue.
//     7.  If slot to the EAST is open & is undiscovered
//     Mark (curx+1,cury) as “discovered”
//     INSERT (curx+1,cury) on queue.
//     8.  If slot to the NORTH is open & is undiscovered
//     Mark (curx,cury-1) as “discovered”
//     INSERT (curx,cury-1) on queue.
//     9.  If slot to the SOUTH is open & is undiscovered
//     Mark (curx,cury+1) as “discovered”
//    INSERT (curx,cury+1) on queue.
//     10. GOTO step #3
    
}