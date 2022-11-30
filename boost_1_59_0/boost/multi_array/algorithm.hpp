#ifndef BOOST_MULTI_ARRAY_ALGORITHM_HPP
#define BOOST_MULTI_ARRAY_ALGORITHM_HPP

//
//
// Copyright (c) 1994
// Hewlett-Packard Company
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation.  Hewlett-Packard Company makes no
// representations about the suitability of this software for any
// purpose.  It is provided "as is" without express or implied warranty.
//
//
// Copyright (c) 1996-1998
// Silicon Graphics Computer Systems, Inc.
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation.  Silicon Graphics makes no
// representations about the suitability of this software for any
// purpose.  It is provided "as is" without express or implied warranty.
//

// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.


#include <iterator>

namespace boost {
namespace detail {
namespace multi_array {
//--------------------------------------------------
// copy_n (not part of the C++ standard)
#if 1

template <class InputIter, class Size, class OutputIter>
OutputIter copy_n(InputIter first, Size count,
                  OutputIter result) {
  for ( ; count > 0; --count) {
    *result = *first;
    ++first;
    ++result;
  }
  return result;
}
#else // !1

template <class InputIter, class Size, class OutputIter>
OutputIter copy_n__(InputIter first, Size count,
                                       OutputIter result,
                                       std::input_iterator_tag) {
  for ( ; count > 0; --count) {
    *result = *first;
    ++first;
    ++result;
  }
  return result;
}

template <class RAIter, class Size, class OutputIter>
inline OutputIter
copy_n__(RAIter first, Size count,
         OutputIter result,
         std::random_access_iterator_tag) {
  RAIter last = first + count;
  return std::copy(first, last, result);
}

template <class InputIter, class Size, class OutputIter>
inline OutputIter
copy_n__(InputIter first, Size count, OutputIter result) {
  typedef typename std::iterator_traits<InputIter>::iterator_category cat;
  return copy_n__(first, count, result, cat());
}

template <class InputIter, class Size, class OutputIter>
inline OutputIter
copy_n(InputIter first, Size count, OutputIter result) {
  return copy_n__(first, count, result);
}

#endif // 1
} // namespace multi_array
} // namespace detail
} // namespace boost

#endif

/* algorithm.hpp
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
*/