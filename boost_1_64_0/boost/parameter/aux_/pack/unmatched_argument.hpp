// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_UNMATCHED_ARGUMENT_HPP
#define BOOST_PARAMETER_AUX_PACK_UNMATCHED_ARGUMENT_HPP

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct unmatched_argument
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        static_assert(::std::is_same<T,void>::value, "T == void");
#else
        BOOST_MPL_ASSERT((
            typename ::boost::mpl::if_<
                ::boost::is_same<T,void>
              , ::boost::mpl::true_
              , ::boost::mpl::false_
            >::type
        ));
#endif
        typedef int type;
    }; 
}}} // namespace boost::parameter::aux

#endif  // include guard


/* unmatched_argument.hpp
+Koac1CmeRqaAdRa/b5BXSRXBeoZNChxXAHCOCDmLL5a+GDHunYCZfaWGoC9VwcIu88SSF0Nt/7OiT06Yz8kLwhaVH3opBRcwT1YBtSdx9KRoIOpmAds6SwYCuv4+/QLqhe5PfojnhVrn1gvbSGxnUyOCIQf3OT+S62mnYW54PoVQPRccaFwMyt5YXxjEUni9ttkT0/UlMwJWjkdNSTW2KK5OzHOjQ5x187b0Xfd8lb9Q2ASRenpUHj1/83t+ukyELB8JPinx+fVF1i8kp69y0w3GhS6WEAMYWzOteT47B16TmMJxoL2RkprXyTL4Th10dd1wLWsyWMfADwWr6EkyLToIzSfqMyP9CaMHTqOd7wPVycG9lTCDXN0kYEMP3geJvZuhAV6wkagP8j37t+qCdFYlivNk4Nhm4KjmQWnglrV6Y2AogjTi8SkLl9CHDVBNBdirpiGoPAsaG9cgiXg8OFrFKqz5ajM1zYbOoU93l3J7+pdzcUgb5Nw3o2CfADCWRimPqwTTTckUcZeXsToVLKUc7rIcoFP15GMzfTPfFXU/Us+dpDAyyCyFA==
*/