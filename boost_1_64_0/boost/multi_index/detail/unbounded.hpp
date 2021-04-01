/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_UNBOUNDED_HPP
#define BOOST_MULTI_INDEX_DETAIL_UNBOUNDED_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/workaround.hpp>

namespace boost{

namespace multi_index{

/* dummy type and variable for use in ordered_index::range() */

/* ODR-abiding technique shown at the example attached to
 * http://lists.boost.org/Archives/boost/2006/07/108355.php
 */

namespace detail{class unbounded_helper;}

detail::unbounded_helper unbounded(detail::unbounded_helper);

namespace detail{

class unbounded_helper
{
  unbounded_helper(){}
  unbounded_helper(const unbounded_helper&){}
  friend unbounded_helper multi_index::unbounded(unbounded_helper);
};

typedef unbounded_helper (*unbounded_type)(unbounded_helper);

} /* namespace multi_index::detail */

inline detail::unbounded_helper unbounded(detail::unbounded_helper)
{
  return detail::unbounded_helper();
}

/* tags used in the implementation of range */

namespace detail{

struct none_unbounded_tag{};
struct lower_unbounded_tag{};
struct upper_unbounded_tag{};
struct both_unbounded_tag{};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* unbounded.hpp
AvQ50MuUVEKYvdHmif3tvwO+sWgIoxmxGrpfjJ1WG2y6qDilXFz0h9hBwVQJNr5P0mqcbK0ybgqUSMSRdIy/LLGm9kFNOMgnpP0VraSAPPez/YzHdQWkh/3WBrMNz+7Ay5h4EoFKcXv1Lj7aM739QJRmBdlYCDWiMclIjXOJzApWC1MtR60ohVvpRGd9f+SXOHyXAIDfFTQFL6Ea3jNiPuMkCAasGxC8N9pmwBSgxXI1fLOX8Q7UZol/94dP7Wdki7FAojnwN/ON+yYHEL3f0yUxQ4e7uHxezGy9ilZGYwQsxmaU3g+Hu4LECW+pZ5hHxYE3QcTI4kbiGpNynqbML1ff3btEKXqHxokcmguuuN6Wa55FKq1h/MWFGfz1WwGF1M2TKZ0fD7T5mXGv2Hi70rjm6ZFivsasU2Ty8i/Pya+Lb+VFDcu/WWQ+GG8kuvOLIm1wcq1xr+GLmYVMtN5ARQuktRuFDU2vy2nDhD7qNlsn8yPRvo7Tt4R0v8JWTHvOJQNXqZKaIwl7Yi6tkQ94C32JNqB7x1H/YUbNNSp4tGi1Xap9ki3kJlEzOA==
*/