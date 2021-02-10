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
0zDVpfhZa/ukPc5M14Lv4mChqnK3sT08W2zyCo516ZhJY/Fo9/9QSwMECgAAAAgALWdKUtrQbVl+DgAARCcAACgACQBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL2h0dHAyLXVwbG9hZC5jVVQFAAG2SCRgrVr7U9vGFv7df8UpHYhNjG1obifldS8NTuIpAQbITdOE0cjSCm+j10grsNvwv9/v7K5eNjT0Tp0JllZ7nnv2O2ePPNz85z4d2qRvfhz938EH35riPEt+F556eLbjfCXzD1Sf8f0tIUOqSb46Pfo2yVfqahLHStnna8f5lqDPrBv/GTLlZ4cvMQIypnyVpItM3swUdV/1aPunn17SFu2MdkZ9OnZjKUK6VCKeiuymT/u+HvnPzJ3PB7k47JNQ5IYDy+pqJnPKk0DduZkgXIfSE3EufHJz8kXuZXKKGxmTmgkKZCjo1dn5x8npmz7dzaQ3YyaLpKB8lhShTzP3VlAmPCFvDY/UzRQlAcjB3Je5AsNCySQeQLYgJbIoZx4s3g3zhNxbV4buFIJcRTOl0nx3OPSKLIT2Qz/x8qFXmj+Yqaiy5COUiNwFJakilVCRiz7xzD5FiS8D/oZDMJgW01Dms36tDUTF/jDJKBdhyLxAJ0Vu1BZ0ad3T
*/