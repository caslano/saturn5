// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.

#ifndef BOOST_MULTI_ARRAY_EXTENT_GEN_HPP
#define BOOST_MULTI_ARRAY_EXTENT_GEN_HPP

#include "boost/multi_array/extent_range.hpp"
#include "boost/multi_array/range_list.hpp"
#include "boost/multi_array/types.hpp"
#include "boost/array.hpp"
#include <algorithm>

namespace boost {
namespace detail {
namespace multi_array {


template <std::size_t NumRanges>
class extent_gen {
public:
  typedef boost::detail::multi_array::index index;
  typedef boost::detail::multi_array::size_type size_type;
  typedef extent_range<index,size_type> range;
private:
  typedef typename range_list_generator<range,NumRanges>::type range_list;
public:
  template <std::size_t Ranges>
  struct gen_type {
    typedef extent_gen<Ranges> type;
  };

  range_list ranges_;

  extent_gen() { }

  // Used by operator[] to expand extent_gens
  extent_gen(const extent_gen<NumRanges-1>& rhs,
            const range& a_range)
  {
    std::copy(rhs.ranges_.begin(),rhs.ranges_.end(),ranges_.begin());
    *ranges_.rbegin() = a_range;
  }

  extent_gen<NumRanges+1>
  operator[](const range& a_range)
  {
    return extent_gen<NumRanges+1>(*this,a_range);    
  }

  extent_gen<NumRanges+1>
  operator[](index idx)
  {
    return extent_gen<NumRanges+1>(*this,range(0,idx));    
  }    

  static extent_gen<0> extents() {
    return extent_gen<0>();
  }
};

} // namespace multi_array
} // namespace detail
} // namespace boost


#endif

/* extent_gen.hpp
H6MfNjy5F8/FVZu7XMRGmMaKTTfMHjcEA1Zepg4n4+We74BpyxoQFvqZv7em9bp81+exBntfWQXOgPnn6GCTcHMm2b7S9E7o5XnsUAqDhIuQlcX6y2xvjdqU1G028cUl2AoIEUbXwlptgMQNWzJfDNEF2fqSh8crCfL892Ks6Y2/gaVuey3skOU1zhOlWlVWe1ulKW7iuxOolncwnsFlxAMzsoLQkK+2ODyI2EItwlaBgVtmxmo7kukV0sPF6q+Rp0uzdublimVhCrXYBHGPSZTHR7Y1Sa25MwyXKUzGWGpVX2dz8j8wdKUalLowBxPXhTGdsUR/biOW46hLRzu6qW/XPHHvS1tb1F07rnNA+4TBZmz+Uim7dksn5YillMGyqzfetBwhqtGl/Y7BV6IshWlghmA+TYoN/obEm6zOW2o/jp0+ebjNmYOLdpz6IQbkUtPNMCxE2EzfjsqExO2uXJ3ckYWLbzoRSeOfb163qHpatxtw0Re3MhlzgcUKtg0goUD5E3+EwXyu0bKh1vD5Btb5ar4gs+PfKah6m6sU9NlUpPgK4lQLVqlZxD0iKkr5PPRlPFWiiNW8BKyJLKWf8YMxlWZ8wsfzGXuhvO8u9VkAblO885gMp3FciMlq2Go0UzIT7qxMmzaX70fy
*/