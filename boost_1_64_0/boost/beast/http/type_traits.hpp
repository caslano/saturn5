//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_TYPE_TRAITS_HPP
#define BOOST_BEAST_HTTP_TYPE_TRAITS_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/string.hpp>
#include <boost/beast/http/detail/type_traits.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/optional.hpp>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {
namespace http {

template<bool, class, class>
class message;

/** Determine if a type meets the <em>Body</em> named requirements.

    This alias template is `std::true_type` if `T` meets
    the requirements, otherwise it is `std::false_type`.

    @tparam T The type to test.

    @par Example
    @code
    template<bool isRequest, class Body, class Fields>
    void check_body(message<isRequest, Body, Fields> const&)
    {
        static_assert(is_body<Body>::value,
            "Body type requirements not met");
    }
    @endcode
*/
template<class T>
#if BOOST_BEAST_DOXYGEN
using is_body = __see_below__;
#else
using is_body = detail::has_value_type<T>;
#endif

/** Determine if a type has a nested <em>BodyWriter</em>.

    This alias template is `std::true_type` when:

    @li `T` has a nested type named `writer`

    @li `writer` meets the requirements of <em>BodyWriter</em>.

    @tparam T The body type to test.

    @par Example
    @code
    template<bool isRequest, class Body, class Fields>
    void check_can_serialize(message<isRequest, Body, Fields> const&)
    {
        static_assert(is_body_writer<Body>::value,
            "Cannot serialize Body, no reader");
    }
    @endcode
*/
#if BOOST_BEAST_DOXYGEN
template<class T>
using is_body_writer = __see_below__;
#else
template<class T, class = void>
struct is_body_writer : std::false_type {};

template<class T>
struct is_body_writer<T, beast::detail::void_t<
    typename T::writer,
    typename T::writer::const_buffers_type,
        decltype(
    std::declval<typename T::writer&>().init(std::declval<error_code&>()),
    std::declval<boost::optional<std::pair<
            typename T::writer::const_buffers_type, bool>>&>() =
            std::declval<typename T::writer>().get(std::declval<error_code&>())
        )>> : std::integral_constant<bool,
    net::is_const_buffer_sequence<
        typename T::writer::const_buffers_type>::value && (
    (std::is_constructible<typename T::writer,
        header<true, detail::fields_model>&,
        typename T::value_type&>::value &&
    std::is_constructible<typename T::writer,
        header<false, detail::fields_model>&,
        typename T::value_type&>::value)
    )
    > {};
#endif

/** Determine if a type has a nested <em>BodyWriter</em>.

    This alias template is `std::true_type` when:

    @li `T` has a nested type named `writer`

    @li `writer` meets the requirements of <em>BodyWriter</em>.

    @tparam T The body type to test.
*/
#if BOOST_BEAST_DOXYGEN
template<class T>
using is_mutable_body_writer = __see_below__;
#else
template<class T, class = void>
struct is_mutable_body_writer : std::false_type {};

template<class T>
struct is_mutable_body_writer<T, beast::detail::void_t<
    typename T::writer,
    typename T::writer::const_buffers_type,
        decltype(
    std::declval<typename T::writer&>().init(std::declval<error_code&>()),
    std::declval<boost::optional<std::pair<
            typename T::writer::const_buffers_type, bool>>&>() =
            std::declval<typename T::writer>().get(std::declval<error_code&>())
        )>> : std::integral_constant<bool,
    net::is_const_buffer_sequence<
        typename T::writer::const_buffers_type>::value && ((
            std::is_constructible<typename T::writer,
                header<true, detail::fields_model>&,
                typename T::value_type&>::value &&
            std::is_constructible<typename T::writer,
                header<false, detail::fields_model>&,
                typename T::value_type&>::value &&
            ! std::is_constructible<typename T::writer,
                header<true, detail::fields_model> const&,
                typename T::value_type const&>::value &&
            ! std::is_constructible<typename T::writer,
                header<false, detail::fields_model> const&,
                typename T::value_type const&>::value
            ))
    >{};
#endif

/** Determine if a type has a nested <em>BodyReader</em>.

    This alias template is `std::true_type` when:

    @li `T` has a nested type named `reader`

    @li `reader` meets the requirements of <em>BodyReader</em>.

    @tparam T The body type to test.

    @par Example
    @code
    template<bool isRequest, class Body, class Fields>
    void check_can_parse(message<isRequest, Body, Fields>&)
    {
        static_assert(is_body_reader<Body>::value,
            "Cannot parse Body, no reader");
    }
    @endcode
*/
#if BOOST_BEAST_DOXYGEN
template<class T>
using is_body_reader = __see_below__;
#else
template<class T, class = void>
struct is_body_reader : std::false_type {};

template<class T>
struct is_body_reader<T, beast::detail::void_t<decltype(
    std::declval<typename T::reader&>().init(
        boost::optional<std::uint64_t>(),
        std::declval<error_code&>()),
    std::declval<std::size_t&>() =
        std::declval<typename T::reader&>().put(
            std::declval<net::const_buffer>(),
            std::declval<error_code&>()),
    std::declval<typename T::reader&>().finish(
        std::declval<error_code&>())
    )>> : std::integral_constant<bool,
        (std::is_constructible<typename T::reader,
            header<true, detail::fields_model>&,
                typename T::value_type&>::value &&
        std::is_constructible<typename T::reader,
            header<false,detail::fields_model>&,
                typename T::value_type&>::value)
        >
{
};
#endif

/** Determine if a type meets the <em>Fields</em> named requirements.

    This alias template is `std::true_type` if `T` meets
    the requirements, otherwise it is `std::false_type`.

    @tparam T The type to test.

    @par Example
    Use with `static_assert`:
    @code
    template<bool isRequest, class Body, class Fields>
    void f(message<isRequest, Body, Fields> const&)
    {
        static_assert(is_fields<Fields>::value,
            "Fields type requirements not met");
    ...
    @endcode

    Use with `std::enable_if` (SFINAE):
    @code
    template<bool isRequest, class Body, class Fields>
    typename std::enable_if<is_fields<Fields>::value>::type
    f(message<isRequest, Body, Fields> const&);
    @endcode
*/
#if BOOST_BEAST_DOXYGEN
template<class T>
using is_fields = __see_below__;
#else
template<class T>
using is_fields = typename detail::is_fields_helper<T>::type;
#endif

} // http
} // beast
} // boost

#endif

/* type_traits.hpp
tFUNKfCLM/2+3+ppv/p5gV8j0371uOXXQrmnW+6mv5v96iVp493EfrWD2HsmmH2Fp/2q9Tz3UXFaGPaq0u4lHTFCuXcBcu9Cr5Ft6iSx9x8m/VpXxLDfXPKIWVb2Y85xsU3NcrJNlXhVLFtNwsenSng3KzzcemYfUu52+OhOz6wy8rDa/CYVp6VWUfq0NCufUM9nSdr3dhVeSyshfcH4gmcJdzvusxnnBqvfox6xs7hy/bnZwKrrl75P7B0d1xzisle+XJP4jVd+lMe9P5QfqQFS/x1NW+ftUv+Xtw0mnqtt8CfK3Ya60z3rStrYlypOA+oKe1Pqwk5Y+bLXziY4Qr592I+EIdulTa17WK7J0ybYKtshFWcZ7b+kXKOZrpove2AJr2L1xfuV+z5+N4u62wJb36s9peIs1iL4/ybtemlnZl6Vre/Xuqg2U97dnlPCuQYVfr1nfNe6t2yczqr8Uz37cmnHX6jwYVoYz0h17k0xp746V/roqmXFLrIQ98rHb7aHnW4CdLLTdbmfJ8Qe/30kFHkdwS4XhY/cT7HL9XY/16s4e9C3Fpf7aaar5ssmV8KrWL+Ta5V7PzYPdnd7XOt3fbWK8xx6ZrHFtfKp7NUWNwyuVOHPs96fzfNZETu3I0YcSj+UGB73TNrbMRVnutaTJ1hsAa17tsblnl3dffP8bfK0Ye0F3W1YL8C5fluvP93W6z219uyOIy+uTx+S2jd2WdI/b3jGnvLXW3vW+77j184GzNqfe6dv+67r8DIYC4vBRk77XjOe8WkHdASvMHgURsJXYXX4D9gAvgHjxN3GcEu+Ueb7uYxB8sQmtjw09+GuBxdI+rtgK7gEdha7j0y4HE6B98AFcCW8Cx6C6+FhuAE+D5+F+fBVuBaegPfDN+E6+BZcD0/CjfBd+CD8FG6Cn8Et8Fv4ELQZ7z2wDNwBq8KdsC7cBRvCPfAG+DjsCPfCvnAfHASfgknwaZgDn4GT4PNST0lIgtR/N6n/4rCf0/7UIfBGWBG2h+GwK6wKO8AY2BE2g51gAuwCCSOeeZ/lHQ8O83KfT6p8xS4Fnoa14QcwGn4Km8CPIHniNvOVdyQ4wEu+TcUup7nk2wLWgG1gQ9gaIlo87Cj+Yico7wrqPcfDTrAHXtVgHylnXylnKrwe9oft4ADYAw6CA+FQOAoOgzlwOJwIE+E8mAQXw5FwNUyR9jUKboaD4XYo+5PTHuR3EL4v5SwHN0o50+X6b5XyjpV6HCfly4a9YA4cAnPhrXACRLSJ8DY4CS6Et8F74RQp1yy4C06Hj8M8/j0HZ8CX4Uz4GsyEr0v8rTbHWq3n6wReE3sH9iG/ZjYP7FX+f2H3wL7of5rtA/up/2H2D4WxfQiKDtRqIu2RYUgushDZiDwd7bdz8B/+w3/4D//hP/yH//Af/x3HH6T/HzVWbQB4bfT/WaWc9f9kLfr/qkymNhb9f00f+v+ELQX6f9kRsJA2AI58m8p6ev9CIpH3kO/qMsdQkG/OqFzJ2X1tAJkPn6ziPilz4WbauiruK2WJK9+gd7PCalu6gwnK/ayKG6DyHS06fzNuDeXuhztHuV9zipsuemkzbpT1LXeWcr9KXHNufZT1ffU6FTaPueYOZW9SezCZ6XX13X8W7hDSHa6kcZg2EAXfX29QcReoufPv67rqQ9R3Zyr8gItus7fooW3l3NZ6KMQ6JKVFN0td4qYuZZ2HABU+WrnTLHe6cmdZc+ij1Pfzh40y4eaalLvyQ5ZbtYdWohfJC/BuE3J6s2oPNE5XoxAf6/dJfJ92IYS72oVc2nxlu5CLmz3sQiQf33YhP2/+8+xCDhd3ZBjOM1ZLmE9I3gNmXfq0q5E4TS0=
*/