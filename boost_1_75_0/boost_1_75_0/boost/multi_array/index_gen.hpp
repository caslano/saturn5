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
Bgy8831mG3RxVEszxbovzVj32UyrPloIJw616iuPozm4U07GMOiAlme9ssKFZvEdRlkkWwdj2bK/s1WXDjvxsLqFggaaOqax1iIjDO8xwMuf68weUwKKZ4rC64OqSecAdGEwQqXo118NGOU2AqOb2tcvkgkwenELw4gMUHlDBYxyGoSRjG1aX2fV08LsHGYNiaVY1dqJTRejRJfx3KrV0JDpQlZTuhreua/HsOlCNi3EY+u4ilC3j3sNX2k6P9HF6KEwxiqcTQZSHCVFZRORwAcRziKGNoCzWYbqMqydwFmsGhdjfFdn/TBHbROjo0+W69hdTehLI/T92ElHHyUCG3B3XZfLeEpKpU4/gwisV1unnNWWXkeMpeRaSdR5BOWF0hCAkjbJZZq2jl9rsmhV8LR102aato6V07R1wdO6ReuxLMOi1cll0GjfTjxthaye/dqaxVShctoTuCDOta6N/2SUa1FfmC6K+qHUeiZCRPWt1A9aWMWBRAcOV+lgNCmctLpKi6BN1U+UXnSUk80kka0wbW7K2LhiVyml7dMzAJr28S51c1bqeyN4e01Pb59HOT+4HSfg5USGN0fobiCgvXTxOsXqrzSH0m3D3K987sFbneAWhoJDT7Bewln0eFEPupPhRULZJQjluCt7F5lG4PmMQN+486UsLKZ8K4pD0osY4J2q2XC+oAqTPbtK2+qgwQDiBVVHe+BFTM5L
*/