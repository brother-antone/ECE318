#ifndef BASE28_H
#define BASE28_H

#include <string>

using namespace std;

string deflate(string s);
string reflate(string s);
void set_string_length(string & s, int newlen);

typedef unsigned char tdigit;

class big {
protected:
    tdigit* digits;
    int size, cap, base;
    string all_digits;

    void construct();

public:

    big();
    ~big();
    big(const big& other);
    big& operator=(const big& other);
    void set_digits(string s);
    int decode(char c) const;
    char recode(int d) const;
    void grow();
    void grow_to(int mincap);
    void print_digits() const;
    int get_digit(int p) const;
    void set_digit(int p, int v);
    void zero();
    void add(unsigned int n);
    void mul(unsigned int n);
    int divmod(int n);
    void from_string(string s);
    big(string s);
    void from_bytes(char* b, int num);
    big(char* b, int num);
    void to_bytes(char* b, int num) const;
    string to_string() const;
    int compare(const big& other) const;
};

#endif

