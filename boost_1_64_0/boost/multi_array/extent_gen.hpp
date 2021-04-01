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
5oybRUG0JKCI7noIiqsCMm6gMnLmeUBOJtVDT2iLjLb1ONgTRF8J4AV9WM1JvN7mQlEDyXjb5/ZsOd8yUNodXba7nhAEs60fhn3YMDFt76WgFa1G4o7UiA0v4RBoNM01gPH4qWpof2nDAsTmXHLtpUT1lvmDvHN6S22nhbKx9403IwiNCCD0SEzpq3GvKLIWt9cYi4M+dsjgOuO4KrcwfsZZAB59D+HcMQ+BSHqLobWCIOiioNoZ3HL3xnyuhFr5Nx6X2FFeXF9krK0BiZy2QxIQIzSUyhFS4tIP5Nfk9jobUZ/fDP+qySA6wbyKoNhqT1TqJpDsRtq6obFWdhtX6StSWa8aP/vnEHRuZoD8z1MoUW6KNkbl30gwdVCDKiUcjrSvwlHiibU76rj/tiEiutx0it/N1fONjbtT/+pL4KLrYNQ0eNkh6BTHbx1+GGMNJbB6FGyClHHfptHJiA2li+4b1ru/rHsPzj867lnJJmi/nLxYmT5kQ1aT4vRlnFuLnYOVN+CpnOhElcd/GZCY9VSTXqpFoHXNTZ72krYGVu9d5msqeJ3BvWokbg==
*/