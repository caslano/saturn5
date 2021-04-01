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
eZzJYe9k9/al4lQSeKCplg6D/bkHpM6aFnfab7NQKG7KDhH5knpt4sorzc/XDhZpNerfbffNi6X5wJQmf0HwM4coettqc6Vgd93mqQesgh29cFhmflR/+8hyZlgSDrb2NhEW7k9iVom+lrgnGZZzdV7mbB/cDzZh8ZKEItviIyeJkGFKrek/Pc4aB5KuqSJTBoFQCwNEQflzS07VZnuZJTB2e1PdYorpurGLzGDVX56DhiL2m1TdYKkexTVf2J/VLst+/HFbddVz0oZCK6JxgshwQfpY2IPF352l/ku9+4d6cv3Z3E07E4AqN6Y2JMbWi8X5jFP+FInCtyNyEq1wlLwIFJcXKx837ru2rV+ROgjRNyDiG8EVNGWiApSMwvJZ5EzSzdaX//ly6b+Qr/nIQGDwTql74eaRelmubrwmNkk2qrfC+/S/xP0FeC4OK+c3aJQ76O3M/WGwDE/nOP+83N0QLh3oPQar4+7cewVc13n3sWBJiCDbbI4xTYOOHlaVAM08aagKTOZaM8q6rPyZC/N8bVmYjiJNZiBFKpufxkFfZv3dshSautvNmQ==
*/