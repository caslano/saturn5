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
B+EIJLVLDma4ZE7kU4L5U0ri4ikxBhJ9ppIRGSJ6zZ2aaMdVrMtVtkniDRL28M2IZFvDGn09dhvAHbcQMiLLtoPi7k+e4CpT4CYJdeUc2lyuC463pAdnXAHSxaa5U64iNroEH+ErnfhKB7yCutyEoiiQ+31tvsHVdrxmO4fzfmpxbcl7oL99Qd9UkUS7LJ1ov3UudeB6GK33B4U/Qbsr7VLpAZ8tXTlHYPvqagZHpLrnahSglUCy5eQMCKR58YM8Da5qag3eiG3qS9rV9wKatmcqg2IGBu2WNZG+7nLQ4yR7X8qg6JnRaBDCBS+2yFSGwmNDYQqx79TQXtoTtKVpmhwYFAOXndcF+zvR2YBshTWyv/9RyddxA9nVxqMsgSZywH6UfpXWR/2/4DolgkxM+QH7LFkbFCuMTvXtTUKD/BJHi1DqAGPE18by8tBXI1+IQ5gdXd1FVgY5ZW03vKCWnCXZrrfxsTNoW/F9Ry8nrVcZHo32QPVpvKW0onayvyf8mxSNf5wSDwaVvap7HsP9/jp+ESNC1eiPcn5CxRsNXcuujL0y8HpClew/a5keIftPOe/uKq/X+D9QK96XU9933UubWrZ91Z9kKnNjjNs9vFt+t8mpe1yLztKc1fozifZxTkowvukt1TnPoGGzppq8RyPVCJBM1b/TwnCwMzsYd5ZaK+Ojhwb795W3/GCDefe6YIdYOeErUJ8zlQp1
*/