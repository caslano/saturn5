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
Z8a4psFX12WBZ03US74gEqqczmfMgD8w3xzAToC6AnVXt4F+3O08sGXQdEf+yMJQbeXHeAhrkylw63W+Smil8ISwqsufwq3qosaGYyK5Vn8uGz6Eho0Dpx0LldYm0TwRbdZmyAPSBMrvGgL4AQjg+EKjT1os478wZfyRbm3crEfYG3+EV0bXiBKpHfOR7dFB8+Y+YBs24Zt3UkPwWRwkW/FFYx4yEFXu+6/xH1Kj1Txj3kXo
*/