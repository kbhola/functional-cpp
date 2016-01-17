#include <memory>
#include <algorithm>
#include <iostream>
#include <vector>


// this is a generic map function for vectors
template<typename S, typename T>
std::vector<T> map(T (*f)(S), std::vector<S> v) {

  size_t num_elems = v.size();

  std::vector<T> w(num_elems);

  for(int i = 0; i < num_elems; ++i) {
    w[i] = f(v[i]);
  }  
  return w; // counting on automatic move semantics here
}


template<typename S>
S reduce(S (*f)(const S, const S), std::vector<S> v) {
  // to ensure this works on vectors of size 0 and 1, we will require
  // that type S have an empty constructor.  Preferably, f(S(),x) = a for any x.  
  S val{};
  for(const auto & x : v) {
    val = f(val, x);
  }
  return val;
}


template<typename S>
S reduce(S (*f)(const S &, const S &), std::vector<S> v) {
  S val{};
  for(size_t i = 0; i < v.size(); ++i) {
    val = f(val, v[i]);    
  }
  return val;
}

/** I'd like to make a template reduce that takes in, e.g., operator+
    but overloaded operators can't be static, and you can't have a function
    pointer to a member function (easily; can with boost::bind, etc)

    template<typename S>
    S reduce(S (*f)(
 **/



template<typename S>
void print_vec(const std::vector<S> & v) {
  for(const auto & x : v) {
    std::cout << x << "\n";
  }
}


template<typename S>
S add(const S s1, const S s2) {return s1 + s2;}

double add_half(int x) { return x + 0.5;}

template<typename S>
std::vector<S> filter(bool (*f)(S), std::vector<S> v) {
  std::vector<S> w;
  w.reserve(v.size());
  for(const auto & x: v) {
    if (f(x)) {
      w.push_back(x);
    }
  }
  return w;
}


template<typename S>
std::vector<S> hadamard(std::vector<S> v, std::vector<S> w) {
  size_t sz = std::min(v.size(), w.size());
  std::vector<S> res(sz);
  for(int i = 0; i < sz; ++i) {
    res[i] = v[i]*w[i];
  }
  return res;
}


template<typename S>
S sum_vec(std::vector<S> v) {
  S val{};
  for(const auto & x : v) {
    val = val + x;
  }
  return val;
}


template<typename S>
S sum_vec2(std::vector<S> v) {
  return reduce(S::operator+, v);
}


struct myInt {
  myInt() : val(0) {}
  myInt(int v) : val(v) {}
  int val;

  myInt operator+(const myInt & i1) const
  {
    return myInt(i1.val + val);
  }


  friend std::ostream& operator<<(std::ostream& o, const myInt& i1);
};

std::ostream& operator<<(std::ostream& o, const myInt & i1)
{
  return (o << i1.val);
}

myInt factory(int v) { return myInt(v); }


template<typename T>
T dot_prod(std::vector<T> v, std::vector<T> w) {
  return sum_vec(hadamard(v,w));
}
  
bool is_even(int x) { return x%2 == 0; }

int main() {
  std::vector<int> vec1{1,2,3,4,5,6};
  auto vec2 = map(add_half, vec1);

  auto red_val(reduce(add<int>, vec1));
  print_vec(vec2);
  std::cout << red_val << "\n";

  auto vec3 = filter(is_even, vec1);
  print_vec(vec3);

  std::cout << "\nHadamard\n";
  std::vector<int> vec4{2,3,400};
  print_vec(hadamard(vec4, vec1));
  std::cout<< "\ndotprod\n";
  std::cout << (dot_prod(vec4, vec1));


  auto test = factory(vec1[0]);

  std::vector<myInt> v4 = map(factory, vec1);
  std::cout << "\n";
  //    print_vec(v4);
    std::cout << sum_vec(map(factory,vec1));
    std::cout << "\n";
  return 0;
}
