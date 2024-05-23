#include <vector>

using namespace std;

struct mine_field {
    bool place_exists(const int r, const int c) const;

    int getMines() const;

    mine_field();

    mine_field(const int side_size, int m);

    ~mine_field();

    bool played(const int row, const int col);

    bool end_game() const;

    void print() const;

    void end_print() const;


private:
    int s;
    int mines;
    vector <vector<int>> field;
};