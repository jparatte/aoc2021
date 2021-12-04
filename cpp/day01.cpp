#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

const string WHITESPACE = " \n\r\t\f\v";
 
string ltrim(const string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
}
 
string rtrim(const string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}
 
string trim(const string &s) {
    return rtrim(ltrim(s));
}

vector<int> parse_input(string filepath) {
    ifstream inf{filepath};

    vector<int> numbers;

    while (inf)
    {
        string strInput;
        getline(inf, strInput);
        strInput = trim(strInput);
        if (strInput != "") 
        {
            int nb = stoi(strInput);
            numbers.push_back(nb);
        }
    }

    return numbers;
}

int solve_part_a(vector<int> & numbers) {
    vector<int>::const_iterator it;
    it = numbers.cbegin();

    int counter{0};
    int last_nb{numbers[0]};
    ++it;
    while (it != numbers.cend())
        {
            if (*it > last_nb) {
                counter++;
            }
            last_nb = *it;
            ++it;
        }

    return counter; 
}

int moving_avg(deque<int> & deq) {
    deque<int>::const_iterator it;
    it = deq.cbegin();

    int acc{0};
    while (it != deq.cend()) {
        acc += *it;
        ++it;
    }
    return acc;
}

int solve_part_b(vector<int> & numbers) {
    vector<int>::const_iterator it;
    it = numbers.cbegin();

    deque<int> deq;

    for (int i = 0; i<3; i++) {
        deq.push_back(*it);
        ++it;
    }

    int last_avg = moving_avg(deq);

    int counter{0};

    while (it != numbers.cend())
        {
            deq.pop_front();
            deq.push_back(*it);
            
            int new_avg{moving_avg(deq)};

            if (new_avg > last_avg) {
                counter++;
            }
            last_avg = new_avg;
            ++it;
        }

    return counter; 
}

int main()
{
    vector<int> numbers = parse_input("inputs/input01.txt");

    cout << "Part A: " << solve_part_a(numbers) << endl;

    cout << "Part B: " << solve_part_b(numbers) << endl;

    return 0;
}