/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_SIMPLE_LOCKING_HPP
#define BOOST_FLYWEIGHT_SIMPLE_LOCKING_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/detail/recursive_lw_mutex.hpp>
#include <boost/flyweight/simple_locking_fwd.hpp>
#include <boost/flyweight/locking_tag.hpp>

/* simple locking policy based on native recursive mutexes */

namespace boost{

namespace flyweights{

struct simple_locking:locking_marker
{
  typedef detail::recursive_lightweight_mutex mutex_type;
  typedef mutex_type::scoped_lock             lock_type;
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* simple_locking.hpp
McG/KF2vJdQwnL4YXuRRSxhDCQLmDqLUs78JmBXPs3kmi6++u67yfOuAue147HKP2IGumTRQJZpTQxKrUkNUdQSN6ia208cYhlTP9GOq78XhTa1bzvvXxye5MNd2YtBdouob/yT8Xx6hoaGKwejl7ePr18Bk9g9tGMqORgGWwKDGhJo0bRZ6taN5fWTwHfWxoaEtWoa0cg/UNBR1Y4g2GuIYoi2BSDlkb/GhLqAI0VaGLiP6nA3jY/Aps7EcxRI=
*/