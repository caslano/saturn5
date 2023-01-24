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
7giWnb3k+3ybJ5Z2WbCM2Z6QMk02svdwoj053HzcTD2lfdtrlcOz07NqlUZEXBfsm84fVASplnmXjZdZUNDKb07WWMThdF/97fx1ysPZxeGdCgPpUF6koR8DzePN0tRUPj8bPZbZSWwsZo2jW/d2sOEjqbI630d5kCeL7yQx8S/pE5aGSRs/BnIOnTftK/cV1qNx/W271t7VgqREHHvek00TMRm+312T4iQxU5IKVwS94J25wmxA5HhOTseDnq4+67PDuiYQmDUBdXQ5tb1wh9l6OHlxMJR479Rr8/UlF7pCTNhDLoI+yAMK3Zz7cMmaRnveRKN7r8B5KY5PD0VnVzbswgqfQenfZ85yVgyeA7HDCz0pSesnxL5yeU/i6ui4O7l3GNSQrLFp2cnL+xnROJ7a2cB4QlTt8qp4yX2jCQS6lEHY8KYqFjt8QKvBQe+pwPKCsJq//4YC4uWVCxcF748dbgkqZlTF+PSihwwtV38jxMLx/dFw4tQ3tPVj+6OgU926T5IT4j/s20hY16yX8AXGZnxw1ewEi1ygHgIwssB+jKWuVlHNfKhMn4BZ+I4qt0SJue2RkFmYabMbMtHbXTuxyuaMjBsiPizzSRVzTE2zznjyeRQ9WqjdC2i2c7HEpEzaPKDO26B6YmffJ2cMf6YKeD9dX2HTXvR+XnGQgphl3Sz1V/mXpWH8ktkpIqz+ghEJkNJP9+FhnQqr
*/