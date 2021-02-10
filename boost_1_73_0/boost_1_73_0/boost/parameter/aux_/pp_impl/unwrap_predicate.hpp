// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PP_IMPL_UNWRAP_PREDICATE_HPP
#define BOOST_PARAMETER_AUX_PP_IMPL_UNWRAP_PREDICATE_HPP

namespace boost { namespace parameter { namespace aux {

    // Given Match, which is "void x" where x is an argument matching
    // criterion, extract a corresponding MPL predicate.
    template <typename Match>
    struct unwrap_predicate;
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/always_true_predicate.hpp>

namespace boost { namespace parameter { namespace aux {

    // Match anything
    template <>
    struct unwrap_predicate<void*>
    {
        typedef ::boost::parameter::aux::always_true_predicate type;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

#if BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))
#include <boost/parameter/aux_/void.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // A matching predicate is explicitly specified.
#if BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))
    template <typename Predicate>
    struct unwrap_predicate< ::boost::parameter::aux::voidstar(Predicate)>
    {
        typedef Predicate type;
    };
#else
    template <typename Predicate>
    struct unwrap_predicate<void *(Predicate)>
    {
        typedef Predicate type;
    };
#endif   // SunProCC workarounds needed.
}}} // namespace boost::parameter::aux

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>
#else
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_convertible.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // A type to which the argument is supposed to be convertible is
    // specified.
    template <typename Target>
    struct unwrap_predicate<void (Target)>
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        struct type
        {
            template <typename Argument, typename ArgumentPack>
            struct apply
              : ::boost::mpl::if_<
                    ::std::is_convertible<Argument,Target>
                  , ::boost::mpl::true_
                  , ::boost::mpl::false_
                >
            {
            };

            template <typename Argument, typename ArgumentPack>
            using fn = ::std::is_convertible<Argument,Target>;
        };
#else
        typedef ::boost::mpl::if_<
            ::boost::is_convertible< ::boost::mpl::_,Target>
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        > type;
#endif  // BOOST_PARAMETER_CAN_USE_MP11
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* unwrap_predicate.hpp
Xr9iv+6/eLH/7NVv7Ogx23/2G4z189Nnj0aMxzBTzvinZc4LmDln8WKZxDyiCW/RMhX1z3megOjDD8ExZyc8WRbsDGiAR/BPmQdpMc+AlekxMJCnLK/SFD+gnIE7RQk0pjDWr3F6b5ctk6DE5mKIX4pzWsHB+fFZnHo0Y845iB90dF6lISpXwRxoNk2DEvRwGsyKKc7sjKzH9AjlCmM4sypOoil+q1uzoCqziJfoNnD+gBT5GLqmtJA0WPDCY4+zJMnOkHzRSKlzUS2XWQ4yG6OZuztD5hfZgvvEAwbWChNlCSogPQHqX6fxp+2iPE849dgdskdjo09HD2KQ0eXekJlzQJecJ7Ra6kJt/ozDGq22xWi6IWgsyCHnaQmKB6ZcZvk5qp0QRpRjGxe7FD3uK4k/cOY8GjvEhjLnQSl8ATzzfGfI3DtDouQvQzaxWUJ/zHOwqTzLGvMroiw6aKT9JEHeg7lEzPFJpGAZ4QfmTBxWJAEYYmHREkcwUBwGSXIORhFy8BoJDyKQIYxGHZC5KM6CBIcDArWobI/lPOawBVoT2Ncyz0KwL+Eu0QRGaPspLCTnHytYC0wGys/AqwZLMdkcHQ8YSMLcKiXGEeFydDFzECKFMOrsXC4+lSLNs+M8WIADKDJUOmSDNoCc
*/