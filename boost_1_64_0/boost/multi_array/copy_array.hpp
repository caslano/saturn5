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
Q9f/cP2Di/4C07UasEvQlmV7SykneLewX2fVKa6pdpy1jf+mPBbitQEUFZ2SNTGmpYb9bUhn9xu+y42uyMaoKUj/RZkED6iHF+zXF2P9CR+eK9t/g7/y+fv//SAhfRElCTyYTrjF/SkCQw/RczpOTPN1l3tuaFb7nX802fRnRTbyXV/6ULayQJNXdSO4O/6DXKAd+2Hdcn4XfOrA2HJHRGNTMOZzSu0HejBtb0DmmzNFFTCoxfh6Yuui7iWFp8tGu8b/6sTkOUIU+U/GJ3e+ndimHFNc0BJTBnQQRig/zWhPl5Djw3bfihMlM+eMe5QCq/y4sHzx7vICwHncKKTXT7ajepAc4/vDFhX+blCkHqYj8lmu4ff/elS9r6Ie1/+a+A/Hw/gm42mS6zwBW3dcMM4hkImBjkFA+yfdJFq/fivlN3za1xr6YzMQf8pgo5G8Pi/a5g4DikmwmhvhUq0lj+Ua7bdBKMXCbVJUwNS0H1sW48sVDdQLdr/VP/SeHVGP5+EpR08A4S52KUfacJBKzvcsqT2AQbzEd0O2UbccbzGW8kxkaUuOeaRTAw==
*/