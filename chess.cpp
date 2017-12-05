#include <iostream>

using namespace std;

typedef unsigned int uint;
typedef std::vector<uint> vuint; 

enum EPiece { EM = 0, 
              WP = 1, WR = 2, WN = 3, WB = 4, WQ = 5, WK = 6,  
              BP =-1, BR =-2, BN =-3, BB =-4, BQ =-5, BK =-6  
};


enum EDirections
{
    N = 8, S = -8, E = -1, W = 1,
    NN = 16, SS = -16,
    NW = 7, NE = 9//, SW = -9,  SE = -11,
    //NNW = 21, NNE = 19, NWW = 12, NEE = 8,
    //SSW = -19, SSE = -21, SWW = -8, SEE = -12
};



class CBoard
{
public:
    CBoard() { init(); } 

    void print() 
    {
        static const char pieces[] = "kqbnrp.PRNBQK";  //b.w
        for(int w=0; w<8; w++) {
            for(int h=0; h<8; h++) {
                cout << pieces[board[w*8+h]+6];
            }
            cout << endl;
        }
    }

    int at(int w, int h) 
    {
        return board[8*w+h];
    }

    int set(int w, int h, int v) 
    {
        board[8*w+h] = v;
    }

     
    void clone(int (&a)[64])
    {
        for(int i=0; i<64; i++)
            a[i] = board[i];
    }      

    void move(char* s) 
    {
        int m[4];
        m[0] = s[0]-'a';
        m[1] = s[1]-'0' - 1;
        m[2] = s[2]-'a';
        m[3] = s[3]-'0' - 1;

        int f = at(m[1], m[0]);

        set(m[1], m[0], EM);
        set(m[3], m[2], f);
    }

    vuint get_moves(int side) 
    {
        vuint mv;

        if (side >= 0)  //white
        {
            for(uint i=0; i<64; i++)
            {
                switch(board[i]) 
                {
                   case EM:
                   break;

                   case WP:
                       uint d = i + N;
                       if(d < 64 && board[d] <= 0 && board[d] != BK) { 
                           mv.push_back(i || d<<8);
                       }
                } 
           }             
        } 
        else  //black
        {

        }

        return mv;
    }


private:
    void init() {
        const int initial[64] = {
            WR, WN, WB, WQ, WK, WB, WN, WR,
            WP, WP, WP, WP, WP, WP, WP, WP,
            EM, EM, EM, EM, EM, EM, EM, EM,
            EM, EM, EM, EM, EM, EM, EM, EM,
            EM, EM, EM, EM, EM, EM, EM, EM,
            EM, EM, EM, EM, EM, EM, EM, EM,
            BP, BP, BP, BP, BP, BP, BP, BP,
            BR, BN, BB, BQ, BK, BB, BN, BR
        };

        for(int i=0; i<64; i++)
            board[i] = initial[i];        
    }
 

private:
    int board[64];
};


int main(int argc, char** argv)
{
    CBoard board;
    //int b[64];
    //board.clone(b);
    board.print();

    board.move("e2e4");
    board.print();

    board.move("g8f6");
    board.print();

    vuint mv = get_moves(1);
    cout << mv << endl;

    return 0;
}
