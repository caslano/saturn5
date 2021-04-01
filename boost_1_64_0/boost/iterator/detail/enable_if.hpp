// (C) Copyright David Abrahams 2002.
// (C) Copyright Jeremy Siek    2002.
// (C) Copyright Thomas Witt    2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_ENABLE_IF_23022003THW_HPP
#define BOOST_ENABLE_IF_23022003THW_HPP

#include <boost/detail/workaround.hpp>
#include <boost/mpl/identity.hpp>

#include <boost/iterator/detail/config_def.hpp>

//
// Boost iterators uses its own enable_if cause we need
// special semantics for deficient compilers.
// 23/02/03 thw
//

namespace boost
{

  namespace iterators
  {
    //
    // Base machinery for all kinds of enable if
    //
    template<bool>
    struct enabled
    {
      template<typename T>
      struct base
      {
        typedef T type;
      };
    };

    //
    // For compilers that don't support "Substitution Failure Is Not An Error"
    // enable_if falls back to always enabled. See comments
    // on operator implementation for consequences.
    //
    template<>
    struct enabled<false>
    {
      template<typename T>
      struct base
      {
#ifdef BOOST_NO_SFINAE

        typedef T type;

        // This way to do it would give a nice error message containing
        // invalid overload, but has the big disadvantage that
        // there is no reference to user code in the error message.
        //
        // struct invalid_overload;
        // typedef invalid_overload type;
        //
#endif
      };
    };


    template <class Cond,
              class Return>
    struct enable_if
# if !defined(BOOST_NO_SFINAE) && !defined(BOOST_NO_IS_CONVERTIBLE)
      : enabled<(Cond::value)>::template base<Return>
# else
      : mpl::identity<Return>
# endif
    {
    };

  } // namespace iterators

} // namespace boost

#include <boost/iterator/detail/config_undef.hpp>

#endif // BOOST_ENABLE_IF_23022003THW_HPP

/* enable_if.hpp
YBX71t7KPQy28Ny0jMFzKsy11q8gpxfBaODqs2bCfdYY5oZAfhDw5nEmH89nwdd0/BVhZTGqyV1As3SO4yQeWMxGKMHr39GVESDgT67NP079YD9zKRRAqQZtTrpg9UAPlhBaEpC0NRG9KaTl8aNM7WaX1ZIdJ507KEpbwP22KbsIYBgBPAzu1wuzVdghNjvrlMI/DFj7DS98HDp3ucp52AqYyIJ55hP7EFEZFpeGJfJl4Y8ccbtATkb5twdjAJq4Jhze4PpYA7JzGCLZ+Let/Vv2UbXJULaVI0xABZ7ywjBh9USrJ+SlMVDKGw4jn8UBEQeAfgw3URbS9IAMuzScP246Z0C5HVIYANuAlrfXZfVykCKn06WWlBPAg51efb2OOiI/FxiFt827hXpcdUOQlWZd52jo9WX/ds4frA8ideMpP7tnnvOQ0XTFJM26FUQicv2E7j8Cyo9RULPE939+iu6McPOVH97QDKG0aVkPnFwxxglmjS0VjwrSq+UdFQtyFFt5IGE9rHQ/ys7m8tG/J/LOWNM2MQ3AG1b8RXABHwLIGRfNI+Zz/w0qtQ==
*/