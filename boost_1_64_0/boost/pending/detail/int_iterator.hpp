//  (C) Copyright Jeremy Siek 1999.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_INT_ITERATOR_H
#define BOOST_INT_ITERATOR_H

#if !defined BOOST_MSVC
#include <boost/operators.hpp>
#endif
#include <iostream>
#include <iterator>
#include <cstddef>
//using namespace std;

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
namespace boost {
namespace iterators {
#endif

// this should use random_access_iterator_helper but I've had
// VC++ portablility problems with that. -JGS
template <class IntT>
class int_iterator
{
  typedef int_iterator self;
public:
  typedef std::random_access_iterator_tag iterator_category;
  typedef IntT value_type;
  typedef IntT& reference;
  typedef IntT* pointer;
  typedef std::ptrdiff_t difference_type;

  inline int_iterator() : _i(0) { }
  inline int_iterator(IntT i) : _i(i) { }
  inline int_iterator(const self& x) : _i(x._i) { }
  inline self& operator=(const self& x) { _i = x._i; return *this; }
  inline IntT operator*() { return _i; }
  inline IntT operator[](IntT n) { return _i + n; }
  inline self& operator++() { ++_i; return *this; }
  inline self operator++(int) { self t = *this; ++_i; return t; }
  inline self& operator+=(IntT n) { _i += n; return *this; }
  inline self operator+(IntT n) { self t = *this; t += n; return t; }
  inline self& operator--() { --_i; return *this; }
  inline self operator--(int) { self t = *this; --_i; return t; }
  inline self& operator-=(IntT n) { _i -= n; return *this; }
  inline IntT operator-(const self& x) const { return _i - x._i; }
  inline bool operator==(const self& x) const { return _i == x._i; }
  // vc++ had a problem finding != in random_access_iterator_helper
  // need to look into this... for now implementing everything here -JGS
  inline bool operator!=(const self& x) const { return _i != x._i; }
  inline bool operator<(const self& x) const { return _i < x._i; }
  inline bool operator<=(const self& x) const { return _i <= x._i; }
  inline bool operator>(const self& x) const { return _i > x._i; }
  inline bool operator>=(const self& x) const { return _i >= x._i; }
protected:
  IntT _i;
};

template <class IntT>
inline int_iterator<IntT>
operator+(IntT n, int_iterator<IntT> t) { t += n; return t; }

#ifndef BOOST_NO_OPERATORS_IN_NAMESPACE
} /* namespace iterators */

using iterators::int_iterator;

} /* namespace boost */
#endif

#ifdef BOOST_NO_OPERATORS_IN_NAMESPACE
namespace boost {
using ::int_iterator;
namespace iterators {
using ::int_iterator;
}}
#endif


#endif /* BOOST_INT_ITERATOR_H */

/* int_iterator.hpp
L+q43vmweh3+PivKeKJe//Yd9ePmgM/HlcdU41vHffLXnS8u1o9caT+nqhfrtMN3289Jnn9APXNdUfZ705X6JfVn1rB6PE1/ab0varfzmh3HKOOYayx3vOddF+4y3+7nlMPlzisVxtPay+ZL7fdk9djybsvU/nY5H0xyXdChXsa4LniL+mW+nc1e/7t+6jT9qOv01Y36i2e1w/B77Hsd7ynqywWOa/j7/j9a36e0zzLL61FPrbfwO/Zffzav2Hix3LhVfb/uG85L55nvkOU9YRwacP324yj9g/rifP9g+Ls927fJeie+Qzn4fLPww5ajfO4Oz6drHHfX4TN6wut85XWt7dRvznJdsTXaecX3oDPqlYvro7u2qOefcfw+4vyVYD0TjEOMu56eazv0l+tqva9Pv+84bPiC8mnWT4Xn9185T7hene16bYXyLnQ98kC9fvRbyu83yiP0PBO0o4/avrC+adeIO+Tvvm/7vql+7dPPrTZ+dV07LvzeVj+65Zvq25n6z/XK+fXGqa7PZ3e7Pm5wfijw+cNM44hbTc9U7vfZrwz91BrjvQLrLbN/+s/cnda313WrfnT8E/bvc9r5esd7vP6nzfdYh5SL473pNPXjh8rNdXHZH03nOG7fs3+XGccUhr/rMZ56RLsL+wnnt0VLHeetxnv6rQfCz9djtJ8/q6+7le+Q8UH4vUP4Pcg37c9E5xmf+8zUj/Caye/vXV80Kr9W5d5m3BR+/xZe1+/Q3z5jPZa7+E3afYH6vMP4SHle3+N4GW/tst49r1N+D9rfN2pXjseR2T7XWqkf3mQ8YP4NF+qHLrF9zgcr1KPD42zvSuWx2fh5g/Hv1+z/fcpRue6+wvFznXL4ZuPe7a6nxukf79Bunndc3ul64gX151L1Tz3a57y+Xj98l3HYhj3KxXkt/wfeZ3wYpX7t9Ln86ou1M9dbhd3ah3pynno4/ukox1s5j7HdQ8bfG43bbjHfRsf1DJ83Nzof/0a/m+86TLmfV6p+zVNPP6Q9/Vn/43x66EuWO8txPazcNltujPHS+cqvRD2YrTzMd7XX517u/S2uZ7SDXN8nHTLd0WK/rf+6813/6U+WPqBdTTZ+mW48O6g+meYvVa/Up9ts1+zV4XjdcdK+pu41f7txXUC/4Pjt+Lv9UI5P67fuOWI//mw9Yx0n23FI/3r9DNd3nfoT/ffMVPXhDOebPfbT50pT3+w8rj+cFX5Oop8va9DP63e3uN6/w/5t+pXjtMd1kvK/a4P2We6xz2cmbnfcxhpfOX57Lrdd9zuOM8LrQvW6W7mG2z9Z/RlRLxKdH+OU4/XO088YB4yx3Fb7/aLzhHHa9F0+DzN+WNRr+drrRW9T3p9RPh8zngp/36F/2e54P39Qf/NJ41btJX+s66ax4fWY/Vvl/NNr+TMdx3jjHNt/5zz9qOu9q++336cH/F2ievUVz+/QX4fX20X6O/30Btc3hRPUd5/bzPiR5eg/F79fOfZoz9rF9mGvK8cZ+qlHlceRs5xfZgdTsJ35xkdPO59tbNPfPaMcdztfu/7ATYbybVNOD1uu7Vjg+mHr99XXKtv1Vuu9QP+z2fMLrdd11vVj1bde7+9XL3v12wna3ReVT7R2u9P4w3huvOvW9WE/+pD28lnjhOu0s1n2M8150nXqxK3G3+HnNxmuE37qPHGJ+hv+PvxD9ueZ8HeCjrPjd4/+7cC9zuOxxh3h75bneH+retpvvKE/np/ie80DT33vI99sfNvLn83++ne/OvHBpVfcdePLV72wYfpPbrjwibOfKrzt5R9uuGn+Fz618uLW5Rdc85e0t3T/ZWbX+b/v/eT3l/z8Kxe+HPvOTz976aY=
*/