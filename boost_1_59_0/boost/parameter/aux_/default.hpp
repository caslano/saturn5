// Copyright Daniel Wallin, David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_DEFAULT_HPP
#define BOOST_PARAMETER_AUX_DEFAULT_HPP

namespace boost { namespace parameter { namespace aux {

    // A wrapper for the default value passed by the user when resolving
    // the value of the parameter with the given Keyword
    template <typename Keyword, typename Value>
    struct default_
    {
        inline BOOST_CONSTEXPR default_(Value& x) : value(x)
        {
        }

        Value& value;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

namespace boost { namespace parameter { namespace aux {

    // lazy_default -- A wrapper for the default value computation function
    // passed by the user when resolving the value of the parameter with the
    // given keyword.
#if BOOST_WORKAROUND(__EDG_VERSION__, <= 300)
    // These compilers need a little extra help with overload resolution;
    // we have empty_arg_list's operator[] accept a base class
    // to make that overload less preferable.
    template <typename KW, typename DefaultComputer>
    struct lazy_default_base
    {
        inline BOOST_CONSTEXPR lazy_default_base(DefaultComputer& x)
          : compute_default(x)
        {
        }

        DefaultComputer& compute_default;
    };

    template <typename KW, typename DefaultComputer>
    struct lazy_default
      : ::boost::parameter::aux::lazy_default_base<KW,DefaultComputer>
    {
        inline BOOST_CONSTEXPR lazy_default(DefaultComputer& x)
          : ::boost::parameter::aux::lazy_default_base<KW,DefaultComputer>(x)
        {
        }
    };
#else   // !BOOST_WORKAROUND(__EDG_VERSION__, <= 300)
    template <typename KW, typename DefaultComputer>
    struct lazy_default
    {
        inline BOOST_CONSTEXPR lazy_default(DefaultComputer& x)
          : compute_default(x)
        {
        }

        DefaultComputer& compute_default;
    };
#endif  // EDG workarounds needed.
}}} // namespace boost::parameter::aux

#if BOOST_WORKAROUND(__EDG_VERSION__, <= 300)
#define BOOST_PARAMETER_lazy_default_fallback \
    ::boost::parameter::aux::lazy_default_base
/**/
#else
#define BOOST_PARAMETER_lazy_default_fallback \
    ::boost::parameter::aux::lazy_default
/**/
#endif

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

#include <utility>

namespace boost { namespace parameter { namespace aux {

    template <typename Keyword, typename Value>
    struct default_r_
    {
        inline BOOST_CONSTEXPR default_r_(Value&& x)
          : value(::std::forward<Value>(x))
        {
        }

#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
        // MSVC 2015 miscompiles moves for classes containing rvalue ref members
        // using the default generated move constructor
        // when moving into a function
        // https://github.com/boostorg/parameter/pull/109
        inline BOOST_CONSTEXPR default_r_(default_r_&& x)
          : value(::std::forward<Value>(x.value))
        {
        }
#endif

        Value&& value;
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
#endif  // include guard


/* default.hpp
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
*/