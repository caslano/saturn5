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
EFgJsFJg5cA8wHzAaoCtBVYLbD2wDcDqgNUDawDWCKzJEpyTtyh2WCr3B8V6gR0BdhQYsZqbHZgDmAtYFLAYYLHA4oDFA0sAlggsyRocv07FSqRyv1esFFg5MA8wH7AaYGuB1QJbD2wDsDpg9cAagDUCawLWDKwF2DZp3G9SbJ9Ubo9iB4AdBHYI2GFgvcCOADsKjNjMzQ7MAcwFLApYDLBYYHHA4oElAEsElgQsBVgasAxg
*/