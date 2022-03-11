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