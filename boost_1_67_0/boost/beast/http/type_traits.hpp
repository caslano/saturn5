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
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
*/