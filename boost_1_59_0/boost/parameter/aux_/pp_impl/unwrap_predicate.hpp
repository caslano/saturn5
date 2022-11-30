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
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
*/