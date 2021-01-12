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
UPy3/mUb617SeWypt2xsWWWfKW3Bl6Lf6Petlc1bh8szVzvdTWfWyCc6UberxXywkxqLe/v+8+TeQehz7fveJmYhT/hKyqs0I0XjaLnYiag+6iaAG2/+k+9y7LPWi52DSV/qZQ3zFjFr48TcucVG3Nk6fp3Y6eosZsf7/ZyC+HjU82Bj30q9nUNbDQ9DdVd1I6oENXQfvp/SOlTrS+osNUv2adddf3ISMIurP5pwL9POTfnW
*/