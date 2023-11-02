#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include "base28.h"

using namespace std;
        
void set_string_length(string & s, int newlen)
{ int len = s.length();
  if (len < newlen)
  { string a(newlen - len, ' ');
    s += a; }
  else if (len > newlen)
    s = s.substr(0, newlen); }

string deflate(string s)
{ string result = "";
  bool canspace = false;
  for (int i = 0; i < s.length(); i += 1)
  { char c = s[i];
    if (islower(c))
      c = toupper(c);
    else if (! isalpha(c))
      c = ' ';
    if (c == ' ')
    { if (canspace)
      { result += c;
        canspace = false; } }
    else
    { result += c;
      canspace = true; } }
  int len = result.length();
  if (len > 0 && result[len - 1] == ' ')
    result = result.substr(0, len - 1);
  return result; }

string reflate(string s)
{ bool needlittle = false;
  string result = "";
  for (int i = 0; i < s.length(); i += 1)
  { char c = s[i];
    if (c == ' ')
      needlittle = false;
    else if (needlittle)
      c = tolower(c);
    else
      needlittle = true;
    result += c; }
  return result; }

void big::construct()
{ size = 0;
  cap = 10;
  digits = new tdigit[cap];
  all_digits = " ABCDEFGHIJKLMNOPQRSTUVWXYZ'";
  base = all_digits.length(); }

big::big()
{ construct(); }

big::~big()
{ delete [] digits; }

big::big(const big & other)
{ size = other.size;
  cap = other.cap;
  all_digits = other.all_digits;
  base = other.base;
  digits = new tdigit[cap];
  for (int i = 0; i < size; i += 1)
    digits[i] = other.digits[i]; }

big & big::operator=(const big & other)
{ if (& other == this)
    return * this;
  size = other.size;
  cap = other.cap;
  all_digits = other.all_digits;
  base = other.base;
  delete [] digits;
  digits = new tdigit[cap];
  for (int i = 0; i < size; i += 1)
    digits[i] = other.digits[i];
  return * this; }

void big::set_digits(string s)
{ all_digits = s;
  base = s.length(); }

int big::decode(char c) const
{ for (int i = 0; i < base; i += 1)
    if (all_digits[i] == c)
      return i;
  return 0; }

char big::recode(int d) const
{ if (d < 0 || d >= base)
    return '?';
  return all_digits[d]; }

void big::grow()
{ int newcap = cap * 2;
  tdigit * newd = new tdigit[newcap];
  for (int i = 0; i < size; i += 1)
    newd[i] = digits[i];
  delete [] digits;
  digits = newd;
  cap = newcap; }

void big::grow_to(int mincap)
{ while (cap < mincap)
    grow(); }

void big::print_digits() const
{ cout << "[" << size << "]: ";
  for (int i = size - 1; i >= 0; i -= 1)
    cout << setw(3) << (int)digits[i] << " ";
  cout << "\n"; }

int big::get_digit(int p) const
{ if (p < 0 || p >= size)
    return 0;
  return digits[p]; }

void big::set_digit(int p, int v)
{ if (p < 0)
    return;
  if (p >= cap)
    grow_to(p + 1);
  if (p > size)
    for (int i = 0; i < p; i += 1)
      digits[i] = 0;
  digits[p] = v;
  if (p >= size)
    size = p + 1; }

void big::zero()
{ size = 0; }

void big::add(unsigned int n)
{ for (int i = 0; n > 0; i += 1)
  { n += get_digit(i);
    set_digit(i, n & 0xFF);
    n >>= 8; } }

void big::mul(unsigned int n)
{ int carry = 0;
  for (int i = 0; i < size || carry > 0; i += 1)
  { int v = get_digit(i) * n + carry;
    set_digit(i, v & 0xFF);
    carry = v >> 8; } }

int big::divmod(int n)
{ int carry = 0;
  for (int i = size - 1; i >= 0; i -= 1)
  { int v = get_digit(i) + (carry << 8);
    carry = v % n;
    set_digit(i, v / n); }
  while (size > 0 && digits[size - 1] == 0)
    size -= 1;
  return carry; }

void big::from_string(string s)
{ int len = s.length();
  s = deflate(s);
  set_string_length(s, len);
  bool canspace = false;
  zero();
  for (int i = 0; i < s.length(); i += 1)
  { int v = decode(s[i]);
    mul(base);
    add(v); } }

big::big(string s)
{ construct();
  from_string(s); }

void big::from_bytes(char * b, int num)
{ grow_to(num);
  for (int i = 0; i < num; i += 1)
    set_digit(i, (tdigit)b[i]);
  size = num;
  while (size > 0 && digits[size - 1] == 0)
    size -= 1; }

big::big(char * b, int num)
{ construct();
  from_bytes(b, num); }

void big::to_bytes(char * b, int num) const
{ for (int i = 0; i < size; i += 1)
    b[i] = (char)digits[i];
  for (int i = size; i < num; i += 1)
    b[i] = 0; }

string big::to_string() const
{ big val(* this);
  string result = "";
  while (val.size > 0)
  { int dig = val.divmod(base);
    result += recode(dig); }
  for (int i = result.length() - 1, j = 0; i > j; i -= 1, j += 1)
    swap(result[i], result[j]);
  return reflate(result); }

int big::compare(const big & other) const
{ if (size != other.size)
    return size - other.size;
  for (int i = size - 1; i >= 0; i -= 1)
    if (digits[i] != other.digits[i])
      return digits[i] - other.digits[i];
  return 0; }


