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
W1YSJWUoVON89ow8ujSDMhizgNnAFU6ZW7Ih2ZXQdD1rwykjTG8PHWuerPd1dVwWsg+9Z5jhsGJH7CccU3v5GNt11MTU+VPEuxspjtvNqPvoJoqrlT2eMdi6mWJgFJRH/TcyDm5XA45+esSxpfTTH78JxdUAi7LPvCnFcN7AvfBTr9qK36C7F6/HazQ0jDG+X85lTc8U7ve+lPNMT1eu2/lpfpchs6PEcZN19ze6djuAfZy51pBzeBg45jixNks5BzZwDhaQxoUdYZzBBlQ26MttH71+uS5ZVxz94yaw6dQSzgLPyy1/6Ja4xx+oucxzwOxSnaJNzKxRHcLXHCSowyxax/k2Hfq8i9YRax8GpK8+5RexfTyVYVKDzqukrfZ9SpcixpubfG7HJGMbOXiafyf6peVGlrvu/bpbSz/tu6SfduNQ6YzLpPX5oxdW54+kO1f5f1lbespwqzmRs2sYOcxc7GyK4hBCHRDtAXhOusYHmwLXr79gXL63d24TwUwVNE6/PjvBOOB/UNHQ0O4XP877ZhjlmWcX6/a34xqK1qMbidSy4zLMHQHvuK/ACXS8cSq/4JQv5HH74VgduKmqvx0SYDdSP08d1qfE2jcX74nfDJwLrqC6ntC25zkHtl8RmxthGEw0iF3hGLQQxI6OMkyliD7djQyTm1G7cDYEHGP3tfAOaTcLfdNuU5MHB2IoZ7WF05MfwTS9iw2OOjeowtvRtv/MzQ0eZh/3PLcwDm6i1kMi8s4M5nVp3o7epJ2HcfFq3pabMh7bkEV/XpODvYCWc/RmJg/Nint4b2twcNtyqb52OSFv3y1SvXffasqoqphY6Cz1/fmM0z444LfCzRm3cu5OLM+yd+44BwYilN93C4aRs1TkTgPnmFlB3vgtGa9ntiF8d6nBa28fJ7aZvPb20b1VO8+MY3mlwcMuxer19K1N3uB6Rf/EbbhMXa9o5/Mal/4eMy4o9q3thNPjHHwnQ3Hw5KxUpb3hq9JjSMau2wIP1xvq5CLuPd2OYa3j4qcZh4+LM7dnGBsXL3MMjqsgdnwHw9iY+eg7MEzl5gbd/hh2zSMpWI8n7sjk+MY/X6ehzEvvdH0yXVL3B+7MZKqjGLTdcdw8htF/8/MuJg+PYCDn0XelHLbvj5wLjNM+Jhy4G+eskXoq784wGC+wLs4x7JrHCdCuZ+7B5a6nLo7f8/pkuvSd/3sxGfMwBdpo+07K4wcocG3AOcpIGEv63hVmLgAfoOvpPoBf5agqfVNEc9uXZriO33YX9Fvpg6Lq+xBjJn2cx3jJQ8+OrKDs30mpxhYjiMAw+pbZ2i8RgR+lhRfY6137wV0oOKdfKn0gQHJcJa04b3yI/F5X/iF9cYtwSP+6Uf55mrS1GzJXGHkXEHB2K4DcDcW3HEwOdG6mEN/na+fiXh7yRlp5+GVP4jC38bSLFHnuxlYefs2jz7rJU50Uy7qpifcGlHVocyu3WdZ2XrOsW1p5zbLepJXXLCvl1e2Y6bkpwckbnnU7Qz0nOa+B3/lmBJfGrHFM50sU7w1O59FbGQ/xXMcL+Rj/vnJC1/aybN1+ea1vG+2zri/SMLbcIGn/vOpMy+qqPqrIl5Zg8cbh21Tnf3pyqa44xO8+THA8n87iqCJeryzw7bI74l4B4cDqgWDbRggGKwSCHSGYGe995yjB+Ll8zPsJzoEvKrAC1vGOjSbe/p7REZPHzvSzbzPGU+vHauWInK7BAR9vbTHM93mDY+LpZoLLPIBfi9rtEsHxfa8aC7dwTN6gpotnTOMc5YGHTabD/PA3oTjen+jb9qYEb3xBkHfyGU/qgMIQXNzMwGsHHa6zKc6/QJAzs5VxWuvlIufwesE=
*/