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
/J9LHrfyf+FylP9Ll6P8X7kc5f9a8i4r/zcuR/m/dTnK/53LUf49kndb+b93Ocq/1+Uo/w8uR/n3Sb7Ryr/f5Sj/jy5H+Q+4HOU/KHhHn62fDzm8E/nDDo8j3+/wLuSPOLwb+Z8cvhH5ow7vQf5nh29C/pjMF+n/F4fT2kSH09pEh9PaRIfT2kSH09pEh9PaRMlJf6+W8zjpX+NwOkPS4XSOpMPpLEmH03mSDqczJR1O50o6
*/