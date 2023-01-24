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
92dWzLQx/gXo+zLu7gsiJsoCNM+T/4SZesH+zJuUgHp8uagG7ZZT2EOsmMqjXQzPyrmJxercMjHiCH6YCGNNxrECD/jOLBr7R2V8VI8vhOf58LwAb3LhJhNuJLxJdS0xww8c1DmLueW5IqfixdS5s9C5ufZnXqKU1OMXiGrQuQXouJGLFY+TqSXsopz5gFIWoGThIo8MR2T2fJixO28jyyOXCqg3Z35pudsuUVVorYw/WKbOzRM+7K9HGhQB+UKkTrF0XniGBBL4CbOAsnzxEhrSMQBnwEv20i8Isd6TVGAveZ+1R8/eyquWrkxzIDu3QdjAEyci55SpjtJnLGLh0lVHAtz4zpgB9gM58XVrSRXhuFO0kalc3bCNTG7DpbcBpOi3gVAbheRlC230Em1IyrFODdqQuI1zAa0NSXXMFW1EQRu5wZswX+EwLd3n4oYN5HIDX+kN5KqOoaIBIOVyyCSpQImFXRG8DZr6cJgGyeMbNpXKTU3SmwJgjhRNJcCrxcMiNEn4Ptyb5S77C+vFOv05h9cJ3t82R1syY6IEOWeBQWykVjlnzJ3hrFsgbNCghc9CLTzbihY8GeMTWSHhySCwt5eU0M34/KKZ8G9mUfFyJOmUu4/hIVArwn9kpwohZU4uACpA2Qjcwor5CJ2dSCOMiFdejiKJ+OBMTJKp+OEuq2wygOXoBW75DmB/74jHYEEXrEDgc5vvAIIN
*/