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
zcKMhtd1gHpg2Q169I3ECRR5aooUvdXCH8uvXXgyUlqOugGFS5EXRbpSkbSPu1g5irowPf03C4NafIbyMe9C0TwOD/QJe8BhocBUuNc17N5vJBx2q4FOuLgCvumKmwE7oMUBV/YOXQMwslvf241DVAuZ5e4e5TRVUAhlqDaVT0CKRe5ZPpddkHNakQsykrZh22He2Qj41Ny5XevvRqjPROpF+x6J1BktaBz5I438pMXGxbsiiQ+nwI86ERuoY/HwRvxzA/7JiqwfAxurl1nCvVTriUgj2jlDqcHpHjT49C6mkOcvrjPXbeMJP/UjmvDjdtCEf/ZFXSmcnWsohbWdQ/WvL6qfIKHrBeZij2nKMU/KBODgXDbnT9bfmIE2NnfEDtF9mVYU7//dUtTFr1ng7aOy7ZIPI1v+gtGoEry6uiOcnYCz6ho42ISXq24EoGCSBCQ6mcOlmeAuHUE0QhOESYIfJDKg0Lr0OhHTkbDc7M5xz28OZ/IKPfWqpMdErwq794iks8kSuOcJPF1KVvhQk+I5xrKkZVemO5np7vRwpw7EPbFWc5R0Wj3xLaKk25WEvBMwJFN4JozX1y7XOJBGkuGvmoR/euOfyxwmGtFrd7IUcnz3p0EgQPl/gDbI69ccmiJxyMO6mJNd5Ii08Q/gNEsrVFfpco5Yz0UU5DIKNPeaGxpSwwtZoo7tLtEjtyDm8rn6ASU/Sedt+jwh
*/