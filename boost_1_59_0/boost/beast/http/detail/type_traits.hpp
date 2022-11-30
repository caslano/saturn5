//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_DETAIL_TYPE_TRAITS_HPP
#define BOOST_BEAST_HTTP_DETAIL_TYPE_TRAITS_HPP

#include <boost/beast/core/detail/type_traits.hpp>
#include <boost/optional.hpp>
#include <cstdint>

namespace boost {
namespace beast {
namespace http {

template<bool isRequest, class Fields>
class header;

template<bool, class, class>
class message;

template<bool isRequest, class Body, class Fields>
class parser;

namespace detail {

template<class T>
class is_header_impl
{
    template<bool b, class F>
    static std::true_type check(
        header<b, F> const*);
    static std::false_type check(...);
public:
    using type = decltype(check((T*)0));
};

template<class T>
using is_header = typename is_header_impl<T>::type;

template<class T>
struct is_parser : std::false_type {};

template<bool isRequest, class Body, class Fields>
struct is_parser<parser<isRequest, Body, Fields>> : std::true_type {};

struct fields_model
{
    struct writer;
    
    string_view method() const;
    string_view reason() const;
    string_view target() const;

protected:
    string_view get_method_impl() const;
    string_view get_target_impl() const;
    string_view get_reason_impl() const;
    bool get_chunked_impl() const;
    bool get_keep_alive_impl(unsigned) const;
    bool has_content_length_impl() const;
    void set_method_impl(string_view);
    void set_target_impl(string_view);
    void set_reason_impl(string_view);
    void set_chunked_impl(bool);
    void set_content_length_impl(boost::optional<std::uint64_t>);
    void set_keep_alive_impl(unsigned, bool);
};

template<class T, class = beast::detail::void_t<>>
struct has_value_type : std::false_type {};

template<class T>
struct has_value_type<T, beast::detail::void_t<
    typename T::value_type
        > > : std::true_type {};

/** Determine if a <em>Body</em> type has a size

    This metafunction is equivalent to `std::true_type` if
    Body contains a static member function called `size`.
*/
template<class T, class = void>
struct is_body_sized : std::false_type {};

template<class T>
struct is_body_sized<T, beast::detail::void_t<
    typename T::value_type,
        decltype(
    std::declval<std::uint64_t&>() =
        T::size(std::declval<typename T::value_type const&>())
    )>> : std::true_type {};

template<class T>
struct is_fields_helper : T
{
    template<class U = is_fields_helper>
    static auto f1(int) -> decltype(
        std::declval<string_view&>() = std::declval<U const&>().get_method_impl(),
        std::true_type());
    static auto f1(...) -> std::false_type;
    using t1 = decltype(f1(0));

    template<class U = is_fields_helper>
    static auto f2(int) -> decltype(
        std::declval<string_view&>() = std::declval<U const&>().get_target_impl(),
        std::true_type());
    static auto f2(...) -> std::false_type;
    using t2 = decltype(f2(0));

    template<class U = is_fields_helper>
    static auto f3(int) -> decltype(
        std::declval<string_view&>() = std::declval<U const&>().get_reason_impl(),
        std::true_type());
    static auto f3(...) -> std::false_type;
    using t3 = decltype(f3(0));

    template<class U = is_fields_helper>
    static auto f4(int) -> decltype(
        std::declval<bool&>() = std::declval<U const&>().get_chunked_impl(),
        std::true_type());
    static auto f4(...) -> std::false_type;
    using t4 = decltype(f4(0));

    template<class U = is_fields_helper>
    static auto f5(int) -> decltype(
        std::declval<bool&>() = std::declval<U const&>().get_keep_alive_impl(
            std::declval<unsigned>()),
        std::true_type());
    static auto f5(...) -> std::false_type;
    using t5 = decltype(f5(0));

    template<class U = is_fields_helper>
    static auto f6(int) -> decltype(
        std::declval<bool&>() = std::declval<U const&>().has_content_length_impl(),
        std::true_type());
    static auto f6(...) -> std::false_type;
    using t6 = decltype(f6(0));

    template<class U = is_fields_helper>
    static auto f7(int) -> decltype(
        void(std::declval<U&>().set_method_impl(std::declval<string_view>())),
        std::true_type());
    static auto f7(...) -> std::false_type;
    using t7 = decltype(f7(0));

    template<class U = is_fields_helper>
    static auto f8(int) -> decltype(
        void(std::declval<U&>().set_target_impl(std::declval<string_view>())),
        std::true_type());
    static auto f8(...) -> std::false_type;
    using t8 = decltype(f8(0));

    template<class U = is_fields_helper>
    static auto f9(int) -> decltype(
        void(std::declval<U&>().set_reason_impl(std::declval<string_view>())),
        std::true_type());
    static auto f9(...) -> std::false_type;
    using t9 = decltype(f9(0));

    template<class U = is_fields_helper>
    static auto f10(int) -> decltype(
        void(std::declval<U&>().set_chunked_impl(std::declval<bool>())),
        std::true_type());
    static auto f10(...) -> std::false_type;
    using t10 = decltype(f10(0));

    template<class U = is_fields_helper>
    static auto f11(int) -> decltype(
        void(std::declval<U&>().set_content_length_impl(
            std::declval<boost::optional<std::uint64_t>>())),
        std::true_type());
    static auto f11(...) -> std::false_type;
    using t11 = decltype(f11(0));

    template<class U = is_fields_helper>
    static auto f12(int) -> decltype(
        void(std::declval<U&>().set_keep_alive_impl(
            std::declval<unsigned>(),
            std::declval<bool>())),
        std::true_type());
    static auto f12(...) -> std::false_type;
    using t12 = decltype(f12(0));

    using type = std::integral_constant<bool,
         t1::value &&  t2::value && t3::value &&
         t4::value &&  t5::value && t6::value &&
         t7::value &&  t8::value && t9::value &&
        t10::value && t11::value && t12::value>;
};

} // detail
} // http
} // beast
} // boost

#endif

/* type_traits.hpp
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
*/