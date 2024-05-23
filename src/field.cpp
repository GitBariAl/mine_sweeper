#include <iostream>
#include <random>
#include <assert.h>
#include "../headers/field.hpp"

bool mine_field::place_exists(const int r, const int c) const {
    return (r >= 0 && c >= 0 && r < s && c < s);
}

int mine_field::getMines() const {
    return mines;
}

mine_field::mine_field() {}

mine_field::mine_field(const int side_size, int m) {
    s = side_size;
    mines = m;
    assert(m <= side_size);//make sure there aren't too many mines

    //create field
    field.resize(side_size);
    for (int i = 0; i < s; i++) {
        field.at(i).resize(side_size);
        for (int j = 0; j < s; j++) {
            field.at(i).at(j) = 0;
        }
    }


    random_device rd;
    // Seed the mersenne twister engine (a good random number generator)
    mt19937 engine(rd());
    // Create a uniform distribution between 0 (inclusive) and n-1 (exclusive)
    int p = 0;
    int q = 0;
    do {
        uniform_int_distribution<int> dist(0, side_size - 1);
        p = dist(engine);
        uniform_int_distribution<int> secondD(0, side_size - 1);
        q = secondD(engine);
        if (m > 0 && field.at(q).at(p) != -1) {//cell available: mine placed
            field.at(q).at(p) = -1;
            --m;
        }

    } while (m > 0);//not done until all mines are placed (randomly of course)

    //set distance number around every mine
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            if (field.at(i).at(j) == -1) {
                //row on top
                if (place_exists(i - 1, j - 1) && field.at(i - 1).at(j - 1) != -1) {
                    field.at(i - 1).at(j - 1)++;
                }
                if (place_exists(i - 1, j) && field.at(i - 1).at(j) != -1) {
                    field.at(i - 1).at(j)++;
                }
                if (place_exists(i - 1, j + 1) && field.at(i - 1).at(j + 1) != -1) {
                    field.at(i - 1).at(j + 1)++;
                }
                //row underneath
                if (place_exists(i + 1, j - 1) && field.at(i + 1).at(j - 1) != -1) {
                    field.at(i + 1).at(j - 1)++;
                }
                if (place_exists(i + 1, j) && field.at(i + 1).at(j) != -1) {
                    field.at(i + 1).at(j)++;
                }
                if (place_exists(i + 1, j + 1) && field.at(i + 1).at(j + 1) != -1) {
                    field.at(i + 1).at(j + 1)++;
                }
                //left
                if (place_exists(i, j - 1) && field.at(i).at(j - 1) != -1) {
                    field.at(i).at(j - 1)++;
                }
                //right
                if (place_exists(i, j + 1) && field.at(i).at(j + 1) != -1) {
                    field.at(i).at(j + 1)++;
                }
            }
        }
    }


}

mine_field::~mine_field() {}

bool mine_field::played(const int row, const int col) {
    if (place_exists(row, col)) {
        if (field.at(row).at(col) == -1) {//MINE FOUND
            mines--;
            return false;
        } else if (field.at(row).at(col) > 9) {//cell already discovered
            return true;
        } else {
            field.at(row).at(col) += 10;//cell discovered
            if (field.at(row).at(col) == 10) {//it was a 0 value cell -> propagate
                if (place_exists(row - 1, col - 1) && field.at(row - 1).at(col - 1) != -1) {
                    played(row - 1, col - 1);
                }
                if (place_exists(row - 1, col) && field.at(row - 1).at(col) != -1) {
                    played(row - 1, col);
                }
                if (place_exists(row - 1, col + 1) && field.at(row - 1).at(col + 1) != -1) {
                    played(row - 1, col + 1);
                }
                //row underneath
                if (place_exists(row + 1, col - 1) && field.at(row + 1).at(col - 1) != -1) {
                    played(row + 1, col - 1);
                }
                if (place_exists(row + 1, col) && field.at(row + 1).at(col) != -1) {
                    played(row + 1, col);
                }
                if (place_exists(row + 1, col + 1) && field.at(row + 1).at(col + 1) != -1) {
                    played(row + 1, col + 1);
                }
                //left
                if (place_exists(row, col - 1) && field.at(row).at(col - 1) != -1) {
                    played(row, col - 1);
                }
                //right
                if (place_exists(row, col + 1) && field.at(row).at(col + 1) != -1) {
                    played(row, col + 1);
                }
            }
            return true;
        }
    }
    return true;//if the cell is out of bound, it doesn't affect the output at all (which is what I want for the recursive nature)
}

bool mine_field::end_game() const{
    bool res = true;
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            if(field.at(i).at(j)<9 && field.at(i).at(j)!=-1){//only uncovered cards (10-18 only with mines {-1} excluded)
                res = false;
            }
        }
    }
    return res;
}

void mine_field::print() const {
    //string tile;
    for (int i = 0; i < s; i++) {
        cout << " ";
        for (int j = 0; j < s; j++) {
            cout << ((field.at(i).at(j) > 9) ? to_string(field.at(i).at(j) % 10) : "#")
                 << "  ";
        }
        cout << endl;
    }
}

void mine_field::end_print() const {
    for (int i = 0; i < s; i++) {
        cout << " ";
        for (int j = 0; j < s; j++) {
            cout << ((field.at(i).at(j) > 9) ? to_string(field.at(i).at(j) % 10) : (field.at(i).at(j) != -1) ? "#"
                                                                                                             : "X")
                 << "  ";
        }
        cout << endl;
    }
}

