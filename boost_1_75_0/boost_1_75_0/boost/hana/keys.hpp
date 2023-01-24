/*!
@file
Defines `boost::hana::keys`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_KEYS_HPP
#define BOOST_HANA_KEYS_HPP

#include <boost/hana/fwd/keys.hpp>

#include <boost/hana/accessors.hpp>
#include <boost/hana/concept/struct.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Map>
    constexpr auto keys_t::operator()(Map&& map) const {
        return keys_impl<typename hana::tag_of<Map>::type>::apply(
            static_cast<Map&&>(map)
        );
    }
    //! @endcond

    template <typename T, bool condition>
    struct keys_impl<T, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename S>
    struct keys_impl<S, when<hana::Struct<S>::value>> {
        template <typename Object>
        static constexpr auto apply(Object const&) {
            return hana::transform(hana::accessors<S>(), hana::first);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_KEYS_HPP

/* keys.hpp
VpZlKTAb1SgbdiPWeJaHGRRKTo/3szHj5NXKsgq0Zm2uQf9PzPMOV209yuvBi0uK9CrzutrQWfoSs7YAxN1oNjqM0OonGmzqHAiC5ZOeaR2GYqNDTpcIIZfN6gnylr8HkF4Fzx6QrqK9OvJsBhjgiGYr9T/qdu3468Dt1lkytUVao0PmNzBsEFOnQz+gjjbYdTajVRCjjkR6o0xau132BLihDlY8i8CxF0QQzjgjJGvT5ZV4JQfPLQVWLkPJ2eOheOoEHM6JOtOaLeaSAovTrgaeG+xWkCz01xbAuBzeFWvBXAej5bOmEJhB2eH/Ij5aDRE6GgPYcK0rm9H6TAiMWHvA/2QY+6e4dhjv0m4BKWZPMLSHMJ+naeaj5F5ib7oyPfrhOy/WZI8w8VP2Cr9Ym8Egdw82OGDk7FT4pUl+PsIv3i2WUTawQX2nAedg/BpTzONhuGbMs67jJxDHlC0YrfvUY/Q5ABxf4JgI3/sBAgMF1hbP6sieNRNxERuIdFXCD8cGjYRB/7bCv49wRwh3lHCniDipwj9N4AiR/iiRt0n44wo8Ci6emcPxhk3QWlOEdwmapwmcLp4/LZ7PEOksAIOfOlgm3MsFPStEfm8L/08EfYfE89PieYtaxIua+M8Hy+9Xk9X0VfnHxMTUwF+f7rxsLFjdP2VkrQDWr3v3ESkQSa0OQH4GZOVlwQ8GvNZi+AXUAt9aLCAAeAx2
*/