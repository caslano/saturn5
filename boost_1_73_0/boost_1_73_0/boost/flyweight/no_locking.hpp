/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_NO_LOCKING_HPP
#define BOOST_FLYWEIGHT_NO_LOCKING_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/no_locking_fwd.hpp>
#include <boost/flyweight/locking_tag.hpp>

/* null locking policy */

namespace boost{

namespace flyweights{

struct no_locking:locking_marker
{
  struct             mutex_type{};
  typedef mutex_type lock_type;
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* no_locking.hpp
Bgi8Hs8mAm/BvB0FXo762wRujnUYJXBrxDECFyDuJfCPiHsL/DPVucAXEMcLrOCzmCCwD+JRAh/B+rlP4Bx8Du4XeJIv+TQcVyDeIPCLOC7sE7iFBeBPvLed2O4hu94fj/OfjaflFmTlTc6WdFphltMROfHm8jgzxuc4SzKyJmHGrLvSHMWFE4oz8q304zGnNWJqj24d00pzC7ILS53WSbklzrQomywiyhZpi4yKs3WLibSlTcZhMs1Zkp1beDs=
*/