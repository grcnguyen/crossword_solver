#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

struct Solution{
    string word;
    string start;
    string end;

    Solution (string s = string(), string st = string(), string e = string()){
        word = s;
        start = st;
        end = e;
    }
};

template <class T>
void selection_sort (T a[], std::size_t n)
{
    for (int s = n; s > 1; --s)
    {
        int index_of_largest = 0;
        for (int i = 1; i < s; ++i)
            if (a[index_of_largest].word < a[i].word)
                index_of_largest = i;
        swap(a[index_of_largest], a[s-1]);
    }
}

int main()
{
    ifstream puzz, dictionary;
    string token;
    string s;
    int row_count (0), column_count (0);
    int row_cap(1), col_cap(1);
    string ** puzzle;

    puzz.open("puzzle.txt");
    if (puzz.fail())
    {
        cout<<"Puzzle failed to open"<<endl;
        return 1;
    }

    dictionary.open("words.txt");
    if (dictionary.fail())
    {
        cout<<"Dictionary failed to open"<<endl;
        return 2;
    }

/*********************************READ IN PUZZLE****************************************/

    puzzle = new string * [row_cap];    //creates array of pointers of size 10 (row_cap)

    while (!puzz.eof())
    {
        getline (puzz, s);
        istringstream line (s);
        if (row_count >= row_cap) //if number of rows exceeds capacity, create new block
        {
            row_cap += 20;
            string **newdata = new string * [row_cap];
            std::copy(puzzle, puzzle + row_count, newdata);
            delete [] puzzle;
            puzzle = newdata;
        }
        puzzle[row_count] = new string[col_cap]; //creates an array of size column_count for each element in the array of pointers
        column_count = 0;
        while (line >> token)
        {
            if (column_count >= col_cap)
            {
                col_cap += 20;
                string *newcoldata = new string [col_cap];
                std::copy(puzzle[row_count], puzzle[row_count] + column_count, newcoldata);
                delete [] puzzle[row_count];
                puzzle[row_count] = newcoldata;
            }
            puzzle[row_count][column_count] = token;
            ++column_count;
        }
        ++row_count;
    }

    puzz.close();

/*********************************READ IN DICTIONARY****************************************/

    unordered_map<string, bool> dict;
    int min_size = 6, max_size = 40; //minimum and maximum word sizes

    while (dictionary >> token)
    {
        if (token.size() >= min_size)
            dict[token]=true;
    }

    dictionary.close();

/*********************************SOLVE PUZZLE****************************************/

    string word = "";
    bool is_word = false;
    Solution* results;
    int results_size = 0, rcap=1;

    results = new Solution[rcap];

    for (int row = 0; row < row_count; ++row)   //index of row
    {
        for (int col = 0; col < column_count; ++col)    //index of column
        {
            int i = 0, j = 0;
            while (col+j < column_count && word.size() <= max_size) //check forwards
            {
                is_word = false;
                word += puzzle[row][col+j];
                if (word.size() >= min_size)
                    is_word = dict[word];
                if (is_word)
                {
                    if (results_size >= rcap)
                    {
                        rcap += 20;
                        Solution *newdata = new Solution [rcap];
                        std::copy(results, results + results_size, newdata);
                        delete [] results;
                        results = newdata;
                    }
                    results[results_size].word = word;
                    results[results_size].start = '(' + to_string(row) + ", " + to_string(col) + ')';
                    results[results_size].end = '('+to_string(row)+", "+ to_string(col+j) +')';
                    results_size++;
                }
                ++j;
            }

            word = "";
            j=0;
            while (col-j >= 0 && word.size() <= max_size) //check backwards
            {
                is_word = false;
                word += puzzle[row][col-j];
                if (word.size() >= min_size)
                    is_word = dict[word];
                if (is_word)
                {
                    if (results_size >= rcap)
                    {
                        rcap += 20;
                        Solution *newdata = new Solution [rcap];
                        std::copy(results, results + results_size, newdata);
                        delete [] results;
                        results = newdata;
                    }
                    results[results_size].word = word;
                    results[results_size].start = '(' + to_string(row) + ", " + to_string(col) + ')';
                    results[results_size].end = '('+to_string(row)+", "+ to_string(col-j) +')';
                    results_size++;
                }
                ++j;
            }

            word = "";
            i=0;
            while (row+i < row_count && word.size() <= max_size) //check down
            {
                is_word = false;
                word += puzzle[row+i][col];
                if (word.size() >= min_size)
                    is_word = dict[word];
                if (is_word)
                {
                    if (results_size >= rcap)
                    {
                        rcap += 20;
                        Solution *newdata = new Solution [rcap];
                        std::copy(results, results + results_size, newdata);
                        delete [] results;
                        results = newdata;
                    }
                    results[results_size].word = word;
                    results[results_size].start = '(' + to_string(row) + ", " + to_string(col) + ')';
                    results[results_size].end = '('+to_string(row+i)+", "+ to_string(col) +')';;
                    results_size++;
                }
                ++i;
            }

            word = "";
            i=0;
            while (row-i >= 0 && word.size() <= max_size) //check up
            {
                is_word = false;
                word += puzzle[row-i][col];
                if (word.size() >= min_size)
                    is_word = dict[word];
                if (is_word)
                {
                    if (results_size >= rcap)
                    {
                        rcap += 20;
                        Solution *newdata = new Solution [rcap];
                        std::copy(results, results + results_size, newdata);
                        delete [] results;
                        results = newdata;
                    }
                    results[results_size].word = word;
                    results[results_size].start = '(' + to_string(row) + ", " + to_string(col) + ')';
                    results[results_size].end = '('+to_string(row-i)+", "+ to_string(col) +')';
                    results_size++;
                }
                ++i;
            }

            word = "";
            i=0;
            j=0;
            while (row-i >= 0 && col-j >= 0 && word.size() <= max_size) //check diagonally up left
            {
                is_word = false;
                word += puzzle[row-i][col-j];
                if (word.size() >= min_size)
                    is_word = dict[word];
                if (is_word)
                {
                    if (results_size >= rcap)
                    {
                        rcap += 20;
                        Solution *newdata = new Solution [rcap];
                        std::copy(results, results + results_size, newdata);
                        delete [] results;
                        results = newdata;
                    }
                    results[results_size].word = word;
                    results[results_size].start = '(' + to_string(row) + ", " + to_string(col) + ')';
                    results[results_size].end = '('+to_string(row-i)+", "+ to_string(col-j) +')';
                    results_size++;
                }
                ++i;
                ++j;
            }

            word = "";
            i=0;
            j=0;
            while (row-i >= 0 && col+j < column_count && word.size() <= max_size) //check diagonally up right
            {
                is_word = false;
                word += puzzle[row-i][col+j];
                if (word.size() >= min_size)
                    is_word = dict[word];
                if (is_word)
                {
                    if (results_size >= rcap)
                    {
                        rcap += 20;
                        Solution *newdata = new Solution [rcap];
                        std::copy(results, results + results_size, newdata);
                        delete [] results;
                        results = newdata;
                    }
                    results[results_size].word = word;
                    results[results_size].start = '(' + to_string(row) + ", " + to_string(col) + ')';
                    results[results_size].end = '('+to_string(row-i)+", "+ to_string(col+j) +')';
                    results_size++;
                }
                ++i;
                ++j;
            }

            word = "";
            i=0;
            j=0;
            while (row+i < row_count && col-j >= 0 && word.size() <= max_size) //check diagonally down left
            {
                is_word = false;
                word += puzzle[row+i][col-j];
                if (word.size() >= min_size)
                    is_word = dict[word];
                if (is_word)
                {
                    if (results_size >= rcap)
                    {
                        rcap += 20;
                        Solution *newdata = new Solution [rcap];
                        std::copy(results, results + results_size, newdata);
                        delete [] results;
                        results = newdata;
                    }
                    results[results_size].word = word;
                    results[results_size].start = '(' + to_string(row) + ", " + to_string(col) + ')';
                    results[results_size].end = '('+to_string(row+i)+", "+ to_string(col-j) +')';
                    results_size++;
                }
                ++i;
                ++j;
            }

            word = "";
            i=0;
            j=0;
            while (row+i < row_count && col+j < column_count && word.size() <= max_size) //check diagonally down right
            {
                is_word = false;
                word += puzzle[row+i][col+j];
                if (word.size() >= min_size)
                    is_word = dict[word];
                if (is_word)
                {
                    if (results_size >= rcap)
                    {
                        rcap += 20;
                        Solution *newdata = new Solution [rcap];
                        std::copy(results, results + results_size, newdata);
                        delete [] results;
                        results = newdata;
                    }
                    results[results_size].word = word;
                    results[results_size].start = '(' + to_string(row) + ", " + to_string(col) + ')';
                    results[results_size].end = '('+to_string(row+i)+", "+ to_string(col+j) +')';
                    results_size++;
                }
                ++i;
                ++j;
            }
        }
    }

/*********************************SORT RESULTS****************************************/

    selection_sort(results, results_size);

/********************************PRINT RESULTS****************************************/

    for (int i = 0; i < results_size; ++i)
        cout<<results[i].word<<": "<<results[i].start<<" "<<results[i].end<<endl;

    return 0;
}
