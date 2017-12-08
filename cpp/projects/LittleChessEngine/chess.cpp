#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int uint;
typedef std::vector<uint> vuint;

enum EPiece { EM = 0, IV = 1,
    WP = 2, WR = 3, WN = 4, WB = 5, WQ = 6, WK = 7,
    BP =-2, BR =-3, BN =-4, BB =-5, BQ =-6, BK =-7
};


enum EDirections
{
    N = 10, S = -10, E = -1, W = 1,
    NN = 20, SS = -20,
    NE = 11, NW = 9, SW = -11, SE = -9,
    NNW = 19, NNE = 21, NWW = 8, NEE = 12,
    SSW = -21, SSE = -19, SWW = -12, SEE = -9
};


class CBoard
{
public:
    CBoard() { init(); }

    void print() {
        static const char pW[] = "  PRNBQK";
        static const char pB[] = "  prnbok";

        cout << endl << " +-+-+-+-+-+-+-+-+" << endl;

        for (int w = 7; w >= 0; --w) {
            cout << w + 1 << "|";
            for (int h = 1; h < 9; h++) {
                int p = board[w * 10 + h];
                char c = p > 0 ? pW[p] : pB[-p];
                cout << c << "|";
            }
            cout << endl << " +-+-+-+-+-+-+-+-+" << endl;
        }
        cout << "  a b c d e f g h" << endl;
    }

    void print_history() {
        for (int i = 0; i < move_hist.size(); i++) {
            char s[5];
            uint m = move_hist[i];
            decode_move(m, s);
            cout << "i=" << i << "  " << s << endl;
        }
    }

    int wh_to_n(int w, int h) {
        return 10 * w + h + 1;
    }

    int at(int w, int h) {
        return board[wh_to_n(w, h)];
    }

    int set(int w, int h, int v) {
        board[wh_to_n(w, h)] = v;
    }

    void decode_move(uint m, char *s) {
        uint from = m & 255;
        uint to = (m >> 8) & 255;

        s[0] = from / 10 + 'a';
        s[1] = from % 10 + '0';
        s[2] = to / 10 + 'a';
        s[3] = to % 10 + '0';
        s[5] = 0;
    }

    void clone(int (&a)[80]) {
        for (int i = 0; i < 80; i++)
            a[i] = board[i];
    }

    void move(const char *s) {
        int fw = s[0] - 'a';
        int fh = s[1] - '0' - 1;
        int tw = s[2] - 'a';
        int th = s[3] - '0' - 1;

        int f = at(fh, fw);

        set(fh, fw, EM);
        set(th, tw, f);

        uint fm = wh_to_n(fw, fh);
        uint tm = wh_to_n(tw, th);
        move_hist.push_back(fm | tm << 8);
    }

    vuint getMoves(int side) {
        vuint mv;

        for (uint i = 1; i <= 78; i++) {
            if (side >= 0) { //white
                switch (board[i]) {
                    case EM:
                        break;

                    case IV:
                        break;

                    case WP: {
                        uint d = i + N;
                        if (d <= 78 && board[d] == EM) {
                            mv.push_back(i | d << 8);
                            d = i + NN;
                            if (i >= 11 && i <= 18 && board[d] == EM) {
                                mv.push_back(i | d << 8);
                            }
                        }

                        d = i + NW;
                        if (d <= 78 && board[d] <= BP && board[d] != BK) {
                            mv.push_back(i | d << 8);
                        }

                        d = i + NE;
                        if (d <= 78 && board[d] <= BP && board[d] != BK) {
                            mv.push_back(i | d << 8);
                        }
                    }
                        break;

                    case WK: {
                        int dirs[8] = {N, E, S, W, NE, SE, NW, SW};
                        for (int j = 0; j < 8; j++) {
                            uint d = i + dirs[j];
                            if (d >= 1 && d <= 78 && board[d] <= EM && board[d] != BK) {
                                mv.push_back(i | d << 8);
                            }
                        }
                    }
                        break;

                    case WN: {
                        int dirs[8] = {NNW, NNE, NWW, NEE, SSW, SSE, SWW, SEE};
                        for (int j = 0; j < 8; j++) {
                            uint d = i + dirs[j];
                            if (d >= 1 && d <= 78 && board[d] <= EM && board[d] != BK) {
                                mv.push_back(i | d << 8);
                            }
                        }
                    }
                        break;

                    case WR: {
                        int dirs[4] = {N, E, S, W};
                        for (int j = 0; j < 4; j++) {
                            uint d = i + dirs[j];
                            while (d >= 1 && d <= 78 && board[d] <= EM && board[d] != BK) {
                                mv.push_back(i | d << 8);
                                if (board[d] <= BP)
                                    break;
                                d += dirs[j];
                            }
                        }
                    }
                        break;


                    case WB: {
                        int dirs[4] = {NE, SE, NW, SW};
                        for (int j = 0; j < 4; j++) {
                            uint d = i + dirs[j];
                            while (d >= 1 && d <= 78 && board[d] <= EM && board[d] != BK) {
                                mv.push_back(i | d << 8);
                                if (board[d] <= BP)
                                    break;
                                d += dirs[j];
                            }
                        }
                    }
                        break;


                    case WQ: {
                        int dirs[8] = {N, E, S, W, NE, SE, NW, SW};
                        for (int j = 0; j < 8; j++) {
                            uint d = i + dirs[j];
                            while (d >= 1 && d <= 78 && board[d] <= EM && board[d] != BK) {
                                mv.push_back(i | d << 8);
                                if (board[d] <= BP)
                                    break;
                                d += dirs[j];
                            }
                        }
                    }
                        break;

                }
            } else { //black

                switch (board[i]) {
                    case EM:
                        break;

                    case IV:
                        break;

                    case BP: {
                        uint d = i + S;
                        if (d >= 1 && board[d] == EM) {
                            mv.push_back(i | d << 8);
                            d = i + SS;
                            if (i >= 61 && i <= 68 && board[d] == EM) {
                                mv.push_back(i | d << 8);
                            }
                        }

                        d = i + SW;
                        if (d >= 1 && board[d] >= WP && board[d] != WK) {
                            mv.push_back(i | d << 8);
                        }

                        d = i + SE;
                        if (d >= 1 && board[d] >= WP && board[d] != WK) {
                            mv.push_back(i | d << 8);
                        }
                    }
                        break;

                    case BK: {
                        int dirs[8] = {N, E, S, W, NE, SE, NW, SW};
                        for (int j = 0; j < 8; j++) {
                            uint d = i + dirs[j];
                            if (d >= 1 && d <= 78 && board[d] >= EM && board[d] != IV && board[d] != WK) {
                                mv.push_back(i | d << 8);
                            }

                        }
                    }
                        break;

                    case BN: {
                        int dirs[8] = {NNW, NNE, NWW, NEE, SSW, SSE, SWW, SEE};
                        for (int j = 0; j < 8; j++) {
                            uint d = i + dirs[j];
                            if (d >= 1 && d <= 78 && board[d] >= EM && board[d] != IV && board[d] != WK) {
                                mv.push_back(i | d << 8);
                            }
                        }
                    }
                        break;

                    case BR: {
                        int dirs[4] = {N, E, S, W};
                        for (int j = 0; j < 4; j++) {
                            uint d = i + dirs[j];
                            while (d >= 1 && d <= 78 && board[d] >= EM && board[d] != IV && board[d] != WK) {
                                mv.push_back(i | d << 8);
                                if (board[d] >= WP)
                                    break;
                                d += dirs[j];
                            }
                        }
                    }
                        break;


                    case BB: {
                        int dirs[4] = {NE, SE, NW, SW};
                        for (int j = 0; j < 4; j++) {
                            uint d = i + dirs[j];
                            while (d >= 1 && d <= 78 && board[d] >= EM && board[d] != IV && board[d] != WK) {
                                mv.push_back(i | d << 8);
                                if (board[d] >= WP)
                                    break;
                                d += dirs[j];
                            }
                        }
                    }
                        break;


                    case BQ: {
                        int dirs[8] = {N, E, S, W, NE, SE, NW, SW};
                        for (int j = 0; j < 8; j++) {
                            uint d = i + dirs[j];
                            while (d >= 1 && d <= 78 && board[d] >= EM && board[d] != IV && board[d] != WK) {
                                mv.push_back(i | d << 8);
                                if (board[d] >= WP)
                                    break;
                                d += dirs[j];
                            }
                        }
                    }
                        break;
                }

            }
        }


        return mv;
    }


private:
    void init() {

       const int initial[80] = {
                IV, WR, WN, WB, WQ, WK, WB, WN, WR, IV,
                IV, WP, WP, WP, WP, WP, WP, WP, WP, IV,
                IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
                IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
                IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
                IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
                IV, BP, BP, BP, BP, BP, BP, BP, BP, IV,
                IV, BR, BN, BB, BQ, BK, BB, BN, BR, IV
        };
/*
       const int initial[80] = {
                IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
                IV, WP, EM, EM, EM, EM, EM, EM, EM, IV,
                IV, EM, BP, EM, EM, EM, EM, EM, EM, IV,
                IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
                IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
                IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
                IV, EM, EM, EM, EM, EM, EM, EM, EM, IV,
                IV, EM, EM, EM, EM, EM, EM, EM, EM, IV
       };
*/
        for(int i=0; i<80; i++)
            board[i] = initial[i];
    }


private:
    int board[80];
    vuint move_hist;
};


int main(int argc, char** argv)
{
    CBoard board;
    //int b[64];
    //board.clone(b);
    //board.print();

    board.move("e2e4");
    board.print();

    board.move("g8f6");
    board.print();

    vuint mv = board.getMoves(-1);

    cout << mv.size() << endl;
    //cout << mv[0] << endl;
    //cout << mv[1] << endl;

    board.print_history();

    return 0;
}
