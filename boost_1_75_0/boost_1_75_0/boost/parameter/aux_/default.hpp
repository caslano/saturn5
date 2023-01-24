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

        Value&& value;
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
#endif  // include guard


/* default.hpp
vVxg24V8+hxD3jbwDHuIXdbTzb5DsradgB4l6DNrfXGXk0toJWTZW21dooNZGrSubCt0fevH2b/BkzkEb24CAX7tw94GatM6x+hB7R37wjI1LpWjc6m4xuBfY0lVswevfb45DCMUVdj/mNEgNTx/lt4W89odC59Uz1YL76Q93LS6IxZv1l/1jp/18lxjf2BvpN21oAsOK2aqSHrvZNHII1xo4tGe7LeyxnUJkOOU9HGNaRCTLVAvfSfGKfL3VRZDwf8CbGkU5qdw7wn3h9VQrPt9cFNdfrlR5HAJqsTe6Oi8W/8UKWDeTbTRhZYX0tQDMa0uCGgcA5soQJ3pueHmmVQQkaeu2lqY5llhwYf5hcsWWVKa1i+aA157BblgwnQM5ULk36ek5cDjmNzZ81N34zgJwvXoEjmIt1Oe4WlKLdbm8yqx/IzTsBlvQ1q/4NTGfpRSYt7mi1svJNalxfMHud3+Wfg4uqOdLJqS8VItF2HV6GBX9EplexvJWWdwMlJYJc/hreMnSMLcH39iIyhvhlkgQAGCd2rGIbx5OquKYs5zaI3jK6jbe7MecguIEWrA3qFpC8rapa9XePChM3v0XNXMNuRy7At4Nb94oQKq+fP+XVCnUbpviRkfOzirTktr/s+CDw9fGapg3gK66hkcfYWdyYZYASAK5t52L4VWNNVeldyhwPfHJSaizOdeaWIjV0qk8NYRaPKjZeOq
*/