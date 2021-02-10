// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.

#ifndef BOOST_MULTI_ARRAY_COPY_ARRAY_HPP
#define BOOST_MULTI_ARRAY_COPY_ARRAY_HPP

//
// copy_array.hpp - generic code for copying the contents of one
// Basic_MultiArray to another.  We assume that they are of the same
// shape
//
#include "boost/type.hpp"
#include "boost/assert.hpp"

namespace boost {
namespace detail {
namespace multi_array {

template <typename Element>
class copy_dispatch {
public:
  template <typename SourceIterator, typename DestIterator>
  static void copy_array (SourceIterator first, SourceIterator last,
                   DestIterator result) {
    while (first != last) {
      copy_array(*first++,*result++);
    }
  }
private:
  // Array2 has to be passed by VALUE here because subarray
  // pseudo-references are temporaries created by iterator::operator*()
  template <typename Array1, typename Array2>
  static void copy_array (const Array1& source, Array2 dest) {
    copy_array(source.begin(),source.end(),dest.begin());
  }

  static void copy_array (const Element& source, Element& dest) {
    dest = source;
  }

};


template <typename Array1, typename Array2>
void copy_array (Array1& source, Array2& dest) {
  BOOST_ASSERT(std::equal(source.shape(),source.shape()+source.num_dimensions(),
                          dest.shape()));
  // Dispatch to the proper function
  typedef typename Array1::element element_type;
  copy_dispatch<element_type>::
    copy_array(source.begin(),source.end(),dest.begin());
}


} // namespace multi_array
} // namespace detail
} // namespace boost

#endif

/* copy_array.hpp
ZWijQFyaJkomGVWvLIcOLXkxq47l2E+qjuEwVQ0Od5NNzEub4+F4g2ZQtQL5ksPGnvtC330HZQfsbu8n2u+f5sK8ZtO5LL8cxfffLxk9FFk22tTtukVNw3eFM6vduPmp93G/6aF6fypxX7/2Gi44DevCJjXLFJ+hYO5ijli33nYeyy8U0lg0zEeLN9qHfl3o18Vdv4qHfhVP/eonvu0R7puetyp3EfM7XyHeQQrkdAFN3B83T9aWmgVWHtg3Dpl/3au3vQ1LGSi/Md+HriErL3koPcW+zjaFpoYkzngTFiilwKsLMKwXid0nZr5OnmQAEvJhQSZivTGoxZD2vRwu/d46YLYp5DgfP8KZVduKwoODVc4PxRrgMqxcBpYVbHd6PuNNc1N65m9uTYUsvkEtKj7GgO2m7Mxt4O9FmH6DhHROzrn2utRe97Ix/ob6vY/r3EG9IGbadcxPpjqyzmottoN1RZbKOMm2+po64By5MaNqXGbF2HYWDsHpVJGlcRtHaAC8njeOcftLlOJYfrZGPm90B7uVYYY7NfkPA3m8NV0+J5TH/10ot+bfZl03gG5ZNL4IdGZju7p+eXZ5if3NdTcdk1KddoeEUqnq0Fhqza3IqXVMjzJ/RLcC2Sj4nVOgZ3bRVRHGD2hxGlUs
*/