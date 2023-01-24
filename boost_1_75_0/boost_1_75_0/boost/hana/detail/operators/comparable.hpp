/*!
@file
Defines operators for Comparables.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_COMPARABLE_HPP
#define BOOST_HANA_DETAIL_OPERATORS_COMPARABLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/fwd/equal.hpp>
#include <boost/hana/fwd/not_equal.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Tag>
    struct comparable_operators {
        static constexpr bool value = false;
    };

    namespace operators {
        template <typename X, typename Y, typename = typename std::enable_if<
            detail::comparable_operators<typename hana::tag_of<X>::type>::value ||
            detail::comparable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator==(X&& x, Y&& y)
        { return hana::equal(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::comparable_operators<typename hana::tag_of<X>::type>::value ||
            detail::comparable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator!=(X&& x, Y&& y)
        { return hana::not_equal(static_cast<X&&>(x), static_cast<Y&&>(y)); }
    } // end namespace operators
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_COMPARABLE_HPP

/* comparable.hpp
42hBapSRwwvCKL06zGWEEiWsG5YL+mk6glHY0mSE+fDRRqHemnDo2tOuRnl5WBQMoErBHvTTRKNsjUehdqSpA6cH97Dly0hFuTaMunG6cw9bxIxUrNCGUU9O1j3o/gTDblDCrqG2qdGT07hL2KtWXTllD7M8nEwtVdsHqtOVF63NakUWjYDx3d5iT8e1rfBCbncSY2S0WT0ZbVaPh/AkCMd1M2q0ehJQGZgcZFIbbxSL0mO8D/lZO/phOkF9jv0vn/8vn/9/hs8hkXeuzZ4Ogx1PXSh8XZHKm2yNzE9CMug/6UYYhaMxXg7lqqax5yQzlwgwyPXGBrkoDHJ9fbFB7nTxPzvIRXCQu/8sDj3d6iBXfDY2yCkOOW5+VFGG7OnQU28WogY2xM2WaotjQ9xbRdS/AfW6gbNJOsyZ0WwXW3NTPXScW888HkQwYppobx+iFO2LKUW99W5Zqv9a1YtOXF4vGgVioGHKUogPqTSDn2bIe0qHl1r/FR0JJi/8HZ6UUtGeHnY0JC2tt3dDEaAmTQM1abJGKMl8N7aTO4mKJSBVeJwimWgqud5OcfuMBKlF/WMFLo/skUVQEtctQh8dJxucsujuwraVxKLuf8lFRw+66FhvK0qvXIvWWu3MeHvUxndXzMQjjVLFZPjHjwIAn2Zzd1G77UUnFbvt0fC4YphCdMr8MenBReipowc9dURGn2ngltY7Ef3Q/dT+
*/