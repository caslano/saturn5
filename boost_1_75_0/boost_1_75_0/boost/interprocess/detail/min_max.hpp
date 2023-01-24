//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_MIN_MAX_HPP
#define BOOST_INTERPROCESS_DETAIL_MIN_MAX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

namespace boost {
namespace interprocess {

template<class T>
const T &max_value(const T &a, const T &b)
{  return a > b ? a : b;   }

template<class T>
const T &min_value(const T &a, const T &b)
{  return a < b ? a : b;   }

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_MIN_MAX_HPP


/* min_max.hpp
qG+DFpGntrN5O438w+oZ5ZVORwVr33KqzsCMfXLN+dz+dkYG8DUHnXEhtXzdSYVVUORkW/s2eOQgshvxi7q5B8zyjFErL/IeUiX4xA3y0vEN9f3btuGXNSILn42NELCl/H/pjCGqXhMKyiHnqtAfyTy4hfXUXhvAGFBuewW/jnfRY5Bkgq7unPZ3iPmczFco7g3rc6z5rpbNPyjsdN0n9BBFJoQRS02zxH7xRsl4RcrXt+TTn+WtjnsjQhpXpz6LrTUBqtu6y+QZT1OzhwVzsqu5yJzKdx1qEZWG2zcEnoPVy+qbnQzf0EWWjunN/9QbvX/tYo32Y9nGJ8q1z0Xdl02dAWnoej5FtUrxZqiDaAlz9/0L69WScmq6hleizzcJICCa2++FYKIXa1TqbwODJrR2V6YahV76CaIWBxP+dsZrXvsYAf0J8CY023PICirhJhJui45kfUHqHZoAhaGHbtnsjNd4rIZIKZ3La+3JT7s63wPsCvM2gqVIOGtvoVGdTy2HuE6kv9tqmFTshF89iGgO3AldaIpoRTK0vnqVXc8YZD53eOoDXMp/tWU4E9pbS90KWxpa3zMyWXtrrN2BIiJAwne0Tq1MVbX/IMpPnR3s137IaEXSvjFvxXrWS2xbqRtqrvCmHGKGhXuxWdsuZNIBz4fj0ubdAtRJvH8Fg9nTsMvSOQ+G+9d+4x3HcrpgCpCejtjG9DQoxic9
*/