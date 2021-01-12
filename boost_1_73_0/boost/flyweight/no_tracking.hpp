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
XAbza+YkDnlv+pw7e366/oxXPjmxft3cTfwaW8knMOizxnZBiql2eREMwIvhvrg7V92dr+4ugEbWhP46OW931AhUOUrlrshcY7LWdSivjDUX5SdXnYXamyw1Xo7aBRWVm05FVaP8ZaX+ctJq5KMr6mSkdVfdVXfVXXVX3VV31V1116+8/t3j/5rh/69f978uJzb+76775DcLMmaAjflpUUA/+YnY2vCS0tLiMdMrqyomF9cM
*/