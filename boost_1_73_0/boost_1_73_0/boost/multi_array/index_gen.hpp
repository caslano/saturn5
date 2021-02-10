// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.

#ifndef BOOST_MULTI_ARRAY_INDEX_GEN_HPP
#define BOOST_MULTI_ARRAY_INDEX_GEN_HPP

#include "boost/array.hpp"
#include "boost/multi_array/index_range.hpp"
#include "boost/multi_array/range_list.hpp"
#include "boost/multi_array/types.hpp"
#include <algorithm> 
#include <cstddef>

namespace boost {
namespace detail {
namespace multi_array {


template <int NumRanges, int NumDims>
struct index_gen {
private:
  typedef ::boost::detail::multi_array::index index;
  typedef ::boost::detail::multi_array::size_type size_type;
  typedef index_range<index,size_type> range;
public:
  template <int Dims, int Ranges>
  struct gen_type {
    typedef index_gen<Ranges,Dims> type;
  };

  typedef typename range_list_generator<range,NumRanges>::type range_list;
  range_list ranges_;

  index_gen() { }

  template <int ND>
  explicit index_gen(const index_gen<NumRanges-1,ND>& rhs,
            const range& r)
  {
    std::copy(rhs.ranges_.begin(),rhs.ranges_.end(),ranges_.begin());
    *ranges_.rbegin() = r;
  }

  index_gen<NumRanges+1,NumDims+1>
  operator[](const range& r) const
  {
    index_gen<NumRanges+1,NumDims+1> tmp;
    std::copy(ranges_.begin(),ranges_.end(),tmp.ranges_.begin());
    *tmp.ranges_.rbegin() = r;
    return tmp;
  }

  index_gen<NumRanges+1,NumDims>
  operator[](index idx) const
  {
    index_gen<NumRanges+1,NumDims> tmp;
    std::copy(ranges_.begin(),ranges_.end(),tmp.ranges_.begin());
    *tmp.ranges_.rbegin() = range(idx);
    return tmp;
  }    

  static index_gen<0,0> indices() {
    return index_gen<0,0>();
  }
};

} // namespace multi_array
} // namespace detail
} // namespace boost


#endif

/* index_gen.hpp
1QXW7k2pXnTD6Zob3C7K30vb6MYc32DRllSnH0xgs1nqggt3CSUALuwMBu/DaeIOMiXKo854lkL4x+aPZiDjo5pU8e5RM+4BnZom9CSUw+ETBiIvbi0JIUFP46zoRX7LywmN9mSK6czWzyidmbcFL8bpKJR8+rur1NjFxoPtbtXReEEkgl8PRiIRykdaV09KC49XF4r7iZlnqltB2s5DY8G2qGSF4JhDysJfcfjiF3wo3VfezYvLj/nfaEqfEu/m9avSpyJs442vqyvDQSn6W0w4Lpuw9OTv0YY8Z3ga69LPBhoHUxc+F2467nmhuPMStGA/L7ukvTqIbo4+Fu0q8wl28rEalXII1CaDKiid/wZQSwMECgAAAAgALWdKUsftqzO2AwAA+wkAACEACQBjdXJsLW1hc3Rlci90ZXN0cy9odHRwMi1zZXJ2ZXIucGxVVAUAAbZIJGCtVftvIjcQ/p2/YrqJdMlplwWkPkKO06HkHlElEgHXKConZHYH1o3X3tpeAmrSv71js7zUq4gqFrE243l8/ubByQ9xaXQ84TJGOYcCtaidvD3eUzuBg8/Yf8f00OoM7rT6AxP7feXx+BlWHzIa0XogRAxbi+fxORy0eIYzbzGuYrxz+/H4QJiRA+ZesTMcjd2WJLUT
*/