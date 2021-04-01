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
4B4gq47hXVS3RH2r8058r7usI3LO+/NJKw5VT/dwjt4u6Uj+7Lo9rh1/JbUqd7hpV/K97Va76RaZXZKtGKX1vjAiA28XnkGKM+nSr2vy17EjJfbDyY0QNqweCbgT7cOSSgqIbbJ10eoq15pPoamJdi6SDIphibgJAxr36R2Rqo9quVHThciR00Z0gcKkCwgqNuQco9laAVhNCVI0g/XY3LVVW9hv/s9VXob0P5vIMYwPT3ib/o0pqbkimEjNPkrBB+WErZqFl4NO7eguCXfH+0vL/qYlcygSSkrEshR7epkKT3u0RXUHuLpeYxkRr05czgA3OAQes7K7Wj3dWc38vDARTNeoGNw1V0Ni8KelEPQW8DLMANp16ERAfk3p553q5kzsmkVUoLGANkHXEpsg2GEw/6Lb6YNoldRxKeBSDkZ7OPv1CkBA3TCsecWiW49LgNWWBPrW3wJIewCEUfWz+IdFfBeWZO+3bjo4ELCi7saNnN4D0MRLDQ4Qa9cirKYjiHxWHo0N0Rf5iuYn6FXq76GN7buYeICVNe+2FUiMmRKiJ28K5f8zIotPuQ==
*/