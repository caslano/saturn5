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