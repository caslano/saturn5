/*!
@file
Defines `boost::hana::detail::create`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_CREATE_HPP
#define BOOST_HANA_DETAIL_CREATE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @ingroup group-details
    //! Implementation of the generic `std::make_xxx` pattern for arbitrary
    //! `xxx`s.
    template <template <typename ...> class T>
    struct create {
        template <typename ...X>
        constexpr T<typename detail::decay<X>::type...>
        operator()(X&& ...x) const {
            return T<typename detail::decay<X>::type...>{
                static_cast<X&&>(x)...
            };
        }
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_CREATE_HPP

/* create.hpp
hjw8SyCS4CjDBY0g8RCz+K1RP1pQlZg0B5RtsGS/A7vsWf/6NQgUb9sfeLU/hUNb5VogIb35UzjpJsBInChNevlx6Sz9wMHsVQ4vp+dgS5weG9qQEsN4OruCIcUAWC+x1tyfYEBSyv1IRrOFCwoRg27RqzEp8CRzzqBH/BbeAuUZFgvyc6HQUCXzlsISJ0+UpEQ+Rk0jseNJXWaU9woL3FfRI3KLuuVR62FVh7g4atzX0EiQzCM8i+t03ANVtFzT3yTar7Ar1ozXu6+mdxi/oy16IuHqaTbCE8XjPUgaMdtYjlUb3jTbo1l4YhR+RWdbgAIMpI4TiTio7WBocJiF2Jmtg0ndPn692YZI3uCubtCiJPCJz7ZADEBzruckwY/s7cmWjL4Z/rGbeZIeCfvWNvl1NTUZScgEcn7lMoejvKQTe/7dLcjxtfR7LTp9Lds0R+t6ocVjiWyRvORE3Kqwqfr4Uu3W62Yw3izIiKA0NA0mJkImMDWapIaKosekymeWiJh5ypvo4F3QsTv5WJ1IKCwNry9ct2c166ozlhgHu7ZT40EW9EZ45kWx/PgUEsTk492cTgFKwEfEc75bXdBzXKTJp3z6WX7V+oQeTkykgFLF4Y9DzpVgw6qOk5V75yhSzkBOZB5pV3OTVzt1
*/