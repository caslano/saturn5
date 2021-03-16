#ifndef BOOST_MOVE_DETAIL_PLACEMENT_NEW_HPP
#define BOOST_MOVE_DETAIL_PLACEMENT_NEW_HPP
///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

struct boost_move_new_t{};

//avoid including <new>
inline void *operator new(std::size_t, void *p, boost_move_new_t)
{  return p;  }

inline void operator delete(void *, void *, boost_move_new_t)
{}

#endif   //BOOST_MOVE_DETAIL_PLACEMENT_NEW_HPP

/* placement_new.hpp
QPU/r4f1QKvFyt0teVdKq70qwPvgVwf4/vSoAB8OGh3g+9NjAnx4YCxQ3KUpCvBhgXEBXkMVA8U7UxOAfg30GqCHgU4EClGWmAQUD4BMBpoFdApQ1EeptObdypp3O+7cybxFilfv9oBl12w90IdV5zevEp1Wz6xtLnu5Ev3vkYoUGUb7jevSugxi44KrVyi24iR8lj6UhzbfAKJzrjr3kytNN6sqv7kOdLQV6XX9MOF6w5uFaztLhHfzCEewdzc=
*/