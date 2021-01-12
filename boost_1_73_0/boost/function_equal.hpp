//  Copyright Douglas Gregor 2004.
//  Copyright 2005 Peter Dimov

//  Use, modification and distribution is subject to
//  the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org
#ifndef BOOST_FUNCTION_EQUAL_HPP
#define BOOST_FUNCTION_EQUAL_HPP

namespace boost {

template<typename F, typename G>
  bool function_equal_impl(const F& f, const G& g, long)
  { return f == g; }

// function_equal_impl needs to be unqualified to pick
// user overloads on two-phase compilers

template<typename F, typename G>
  bool function_equal(const F& f, const G& g)
  { return function_equal_impl(f, g, 0); }

} // end namespace boost

#endif // BOOST_FUNCTION_EQUAL_HPP

/* function_equal.hpp
HiHvLAFSDh1h8uhPfot5lc6EYlYZRr3oIDEqISV5+vkb3lLvIEVO/oTbp32jkjT88QiidJIfKMG+u4EDlI9uR065pG0PFYzbQkZARslX0E+Qfs7lKuGLKzor9pmn0h0Y/8d/UQj0pBaldlV71Wv3ajvY18C1BDNElfc6h4MS2EUwgy+OtI5Dpx4pVKQ6omQspFTRTWorMlxZh6SOHvQFr2c8EvJGwk5YUAV7+8AyPA1LIzyE
*/