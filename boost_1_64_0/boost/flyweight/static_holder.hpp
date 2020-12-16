/* Copyright 2006-2009 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_STATIC_HOLDER_HPP
#define BOOST_FLYWEIGHT_STATIC_HOLDER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/static_holder_fwd.hpp>
#include <boost/flyweight/holder_tag.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

/* Simplest holder storing the T object as a local static variable.
 */

namespace boost{

namespace flyweights{

template<typename C>
struct static_holder_class:holder_marker
{
  static C& get()
  {
    static C c;
    return c;
  }

  typedef static_holder_class type;
  BOOST_MPL_AUX_LAMBDA_SUPPORT(1,static_holder_class,(C))
};

/* static_holder_class specifier */

struct static_holder:holder_marker
{
  template<typename C>
  struct apply
  {
    typedef static_holder_class<C> type;
  };
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* static_holder.hpp
Mnr9wPpZ6Qy07y1bHT2FLU0Sqw0z7R+/XbkAWedIGTDZSImnEiX7v5KULHaSjIZAgZooo03VXOKaqnNiIqaQvgUKhjz1OYie4grsJnmII0iZuhURpCAgu5A/BMWk2kW1wQ77069dtEcMRMHTNQH+hAcPKQwfHMziGK0oBTUO40TN0kzsQtSHF21TqtoSlM2B+xG3p6g+3pMB3PLlx7AykXSGr8aor3bAK/+jQX0JULMXOxjpAxmOiUh6Eifdy0h/5Ev+xEhH3JiLjpBDnRnFuzL5YP/qFYXk8YeB5AdEGaQuo5q9oYJlApjUK+agXjHb84fpFc/VRz++L3WyAYfTKJy0T+0Kk50b/nf5IgK12bAJRLA+i0ucPHs/kz1PNjP3kphzSzV3Iuof5dE/HM/F4QtDqhNT6XqfrwU3UzUAuBAA190QuQK7qojamaNNry3Oeu+j7QxPfz1ajUAiTRRwdU8Wu6vj5EPgYCnbXd0NXUJrBrINgiA5IifO753d+WROJ5zec211HDPtKLnIxbTpLIf/RZydBqJ7+/QaxsCGYTJicYoIl96CQFTDaGGDlIpbnRGUTrHHF8FKQgNYAKfx2ONpLO5kBi4VRJYIsXK9nyl3XBRUMIWYsxXV8/LqRIowqPHUR4Oa38fdxhk/lvFhT4JCjTpcztSt4YunfhIe8kppObPPxTRKgEHe5hXsIdqFIMuYQ4BdJGJCKgEtqTEStXe+JfgUSjXFrqcAsjLkY7buWGcc5GPRJHer0gGbb8pVVxmGV7vc6ismi0wskBB4gkzKdah9KqZg304vwcESvX5PevH+N38s3kM6/FSYAz0tSgU6gIS8e7zDD+LDrNA6EikdFcAJAZRfs9RMmXQ4brAVa/px2VlYWf36T3B/F9/+zDoB+YowKiQKtLdBpypcVjgKG2UUMy9f0sZh+S8gFHlD0MzkQOW+cWGI7BtOY9/AeSNNzBvraN546CU2b9R82Q12LuAxA0GcbDF8lVB79UAdoht5sRttdim9hA3tJG3wN5QnS77gIVpoX4XZpqvZiKxWWgueL9uQL1uUl40ZM3VZytL3y8SGlOBdxHiIKyqbHd6TOKnTExshQMnXvLvjBKqU6zD1eJgmqWtJAOr3JgCiYXQlGmaR/9RUJ+vy3OnbJhwAb35ZvKdFKWzWohT1+YdqQaKnp1JPNxZYJS+aCjqEeICkXIalAkcOmjhCXY/Ui2O+4lwpUycBi4nAPBnoE4IZhCgqNFPEmdMe5UjBnPaQtaPCHMPjpaW+KF0dGNhnKFqwqiOxyoLKPMuJIbQMJ4b/ngsNv/PHyhT2mvIyC1PYV0DvbIxeTgsKGTqnKIbOKdKMWT7RW5ycnhaig9DY15VP+FXmMh+P+1Og9QqvbDsyDNUeor+TV584ly8mkABTWniECIVRBjkDdSApQybtCVcI0GfIFKPx9FlftKqOPPDFScZwlMxyUCLTmZ7YiplQ4bydIubta2je/mQDm7frlcC83Q7MwOmQ19ocD1sSzfCK4qX0l4XDj12nYMWBCWvkpaUwN+xBWLrPwMXUXVLJUNgKsyfI7Oi+Q6ZkqzPMDszJSuS2GZFAmkibGIWUgc7BfwKgq6KoQymd/fNbdEbbuol3jmTWdMCE5SvIE1JyNvOEFJXNPSGhwB2OvOiOv2rgr874Kwx/XYi/2MYhEX8xUb0x/nLhrzpSO8cvUvUxEsosCXD2zm8mX2QrL9gfmLEiKHcttslNwP41N3QX61nzxl4T7yiA7z3wnQPfB+G7BL4r4fs8fB3hzvDwcFc4fULCjZ/Q8Ko/YeFn96mx98/4UeMfHy/T4yX8vLXMTryEIZRHie4QethufIY4tbyaW8o=
*/