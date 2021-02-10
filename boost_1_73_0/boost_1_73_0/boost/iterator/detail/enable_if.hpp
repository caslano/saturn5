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
uGQdgsjxXH7HhCBxvbF8j63qpTcIFTrNKAZGfZ/bQj2PssxtCkaenjoXgzV67CX8xqKQcajnVRRUBDGP3Iq7iUMEwjygkBNhmuuwCR0ap8Jp5HuIPKdpgv/zaEp/HYhCdAaEvgG6IYBFmMfqcK8vvk2XC7jvz+f9yeIBpiPoTx64se/6ZIhH7yFYDPRlHVOG4DF4wdr3qJNj/ryrWTvxQtvfOBQun71wS+PG6qqkCUkU+SZSGa+ElVCrjfuTm2X/RgPAKpZqtROHul5IYT4w77S5oU8nAIPlfLx/M2/7v0/n9Tc0ffKONusvBt9Sk3dGQdQnoynkL/y5BjDSx1qBhFcJjMzZfDpcDhYFv8LkmqNx/8a47RvfURNxRiPdrJAxdBeykJzToXa9vLle6uMhjpDXgmym9LNDi5mtjFE7oT6jFa40RmKI1Z1Tp0Y2Pu6mhmne45FP7w2llTMXDzMtZY4WZn82y6nG8jploKnatXaj84Cux9PBdxAMrLbwaYQlqYduJHBGLlCISKrUk1RLEjJiwUaU/nipgTCIgjUJdxMSUKGecQTezPV3rf2YGylUOfAwnUBrPi+4usBHBlfAEqb2JuFj4kO9u6yy9pCHBQHCOw09xGYMiX/gZerkO8Epjh0PBTlEmAmngg10
*/