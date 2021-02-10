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
WzC4rCvlFU1TrMAXTiyP9e2kmkMye0NzW8hhDvvY5VRZ4e6ciRtiTm1xAyjeMVkKxRWszgdcXzs5/MhVld/X5A9/fsItCD5glZwRw2J5VP+W3paFeqtK7VaxU2J2l+2/bsxplyDk+Zuk1r1yIgwX5XtIg4eZkTHZChcOVrbKGrOyAY8f28e05NyJkM51ne1R2mzN52YbF+Mi7a81vpC5dssmxBjd4KaEcHQ+0MfF2D1IXHmudrqQkiikNgbMvPXZXQONi8gbvvgeBCUaWHp/CiqDQeL5AFZutm8+mIX4DKSXQBhQRdtn88H/B1BLAwQKAAAAAAAtZ0pSAAAAAAAAAAAAAAAAFwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2Z1enovVVQFAAG2SCRgUEsDBAoAAAAIAC1nSlJizMjblAAAANQAAAAdAAkAY3VybC1tYXN0ZXIvdGVzdHMvZnV6ei9SRUFETUVVVAUAAbZIJGA9jjEOwjAMRXefwheg3SuxsrFxAbc4TSQaV47Tip4ehwqsLy9fev/d6nGgcbEC1/8BPCJj8Crl+WwxiOJU9YWRNsaROeMiGz/RBAkLr6RkjMqrlGSi7wEgmq1l6Ps5WaxjN8nSN8T3XRqeFeAuypiy8xeyJBk9UfbGndmwGKn5
*/