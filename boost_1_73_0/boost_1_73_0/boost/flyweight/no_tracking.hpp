/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_NO_TRACKING_HPP
#define BOOST_FLYWEIGHT_NO_TRACKING_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/no_tracking_fwd.hpp>
#include <boost/flyweight/tracking_tag.hpp>

/* Null tracking policy: elements are never erased from the factory.
 */

namespace boost{

namespace flyweights{

struct no_tracking:tracking_marker
{
  struct entry_type
  {
    template<typename Value,typename Key>
    struct apply{typedef Value type;};
  };

  struct handle_type
  {
    template<typename Handle,typename TrackingHelper>
    struct apply{typedef Handle type;};
  };
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* no_tracking.hpp
8T8sjZ5jZ3RJliPX8Q9LUvVyRuc6snPG32ppnsMJrZ/cjpLU3jU/Jz/LUZbuvNUyPe81M8OZU+LMvtnGRA1wSszN5mJrOTebica5m80zOfdWa+cqI7gw4h8gPoEGyYF/oK/zlYF/ssgMBwQyQTf00Roy7i6BTDAZUSPGlQlkAnTBoBiaNn1o666ur71SNHB12X97hA2uMBcZbu/3duTP4HKzIh3ZmaAeCvmTeC0Dni/imYIljRyZbOXlW63RcdY=
*/