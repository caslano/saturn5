// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.

#ifndef BOOST_MULTI_ARRAY_RANGE_LIST_HPP
#define BOOST_MULTI_ARRAY_RANGE_LIST_HPP
//
// range_list.hpp - helper to build boost::arrays for *_set types
//

#include "boost/array.hpp"

namespace boost {
namespace detail {
namespace multi_array {

/////////////////////////////////////////////////////////////////////////
// choose range list begins
//

struct choose_range_list_n {
  template <typename T, std::size_t NumRanges>
  struct bind {
    typedef boost::array<T,NumRanges> type;
  };
};

struct choose_range_list_zero {
  template <typename T, std::size_t NumRanges>
  struct bind {
    typedef boost::array<T,1> type;
  };
};


template <std::size_t NumRanges>
struct range_list_gen_helper {
  typedef choose_range_list_n choice;
};

template <>
struct range_list_gen_helper<0> {
  typedef choose_range_list_zero choice;
};

template <typename T, std::size_t NumRanges>
struct range_list_generator {
private:
  typedef typename range_list_gen_helper<NumRanges>::choice Choice;
public:
  typedef typename Choice::template bind<T,NumRanges>::type type;
};

//
// choose range list ends
/////////////////////////////////////////////////////////////////////////

} // namespace multi_array
} // namespace detail
} // namespace boost

#endif

/* range_list.hpp
4gG2ET/lKHsAu12drFuoVcdeB2bo34hM8/kc2WnplGMSHMCnvb2V9LdcYBKi3CzIE6mlckbvJ4KHt0QWUgkPA5UsSnGaBCEGKyaowNRG1XCJADAArYCmS5Yv0NAHg0cFVj/0LgApC6UK407llfWCAUYG17G4CrAiikVAyIAhCZSeWmiaceR2AK4SdLsKqqdCnujwruJFSoJbYWDmSAp7GkYjnQQrj9UEcF050Vgu5ewZVvXgVLkecsaw7lfX0RXI2C6oIfrk+LzfPz0eaYiJxK4ez3mqEkedsjn3WRLMBeCE4xiJNJAxqAm37XYLSojHGbPWdn2cwbUGlsuENA+PBmdXLZshmAbb6vuv3a9AvoO7s2Md4xYSNanO1+q0egpHKnNWpFsTEDGdSdBGy4WnRvlLEvECC+v+9WlYwIZ52ONdm4aV3zALW5vWJWHEN8wBc/tDjUE129cAf3wF/PFNsCpLO6bKvKLDVSJudy3nVIrchj1kcrVOcZW/nTe3qSL4tSOGg3/A/7s5jn5tbfsvxr7aS2cTu7B1ae1gK+rYhqMt+n+uKC6S7Y7GdOAL7LY2Qcjet/XTLS/h58dLKmJpRpmE4ejkdDAAZ8yuTduwb7pLfTO10wTbs1vG75hqWLEhwBZtHwoOY+ZU9dd2
*/