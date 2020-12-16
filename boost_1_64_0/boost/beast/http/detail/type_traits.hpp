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
LM1NkZ/DQth1nsNydlPHzmHZRXj9THh9QtriA2ITtdLPqzKULQ01vQzpc33NHI8jDjPtDOomwaan/CzTxPDt07wL63BzLHnIHP/I0F99jeUIPV3sN4eJzejsRue9UEVy+MKWUo4cay1M8dTkYhyq37tqDeiPnuvkT8lSrb1Jfm2S3zaSX67IzThe8vMwRiWEsrMrIf5z0OfIRu4Q6d7FCOEp4jm0NbYUbebOV6GfL5hSNm5z59cF8jqHvP7qGb5+7O+pHyWfncV2YTvJZ2kgnyqspxud7ynv9bq7VLzh9BV9NhJjmqzTRaAbtfe/os39HpkigwxpC23CW8D4NzAnb+kVWf1b7W215DFC8thEyp91QnAeut7VuFZCvLuhr81xrdfGtvwjr2s9hm/h9zhIeKiw6lrzoCyT7ZvEFQ9ryH8n4raZPKTuqHm4zHVsjazvwpe2m+67pd/jbHm3nAAdYupxNF+R6dv94Xvr8eVj5V7gue7xmfKvk/eJFb+vKvMCypuba62D5Iaug0iYxbnWOkipEck6SM9FznWQTOXeXa2gB9ZAontHmen+rnjfF+63W1fbnxjtO8pqv61SR11seybmwVfzIquOpHrUR1xp5Zw6/5hfpmRQLu8pK3wXm1+FyF/7hf3m7CbvKOLDa7lyp2l3hYPvi7fS4456doJqCbfUlW8lVje+JXy2fNc77++owf9q5Z+HXLqF2FqajFyh/AdFXTZ7P1mwjT/g6eQ3EDwCPJBwbf6yBGx6DiuvnV/d4LifpFL3Eyv8SH3HT58TTXeFLxC+cV6dhO+pww8z0mWO20uFP5XRd5TYgZDDSaruXHV3hT4rjSFa95BOGsTyBenutG1Wd+W/l+8Ly6ZHp5Gp7wMqUXn2CdHnZUidjVdp9PINZkXwYSTv0Gsscug1gnV8ul9NUWn8QI99V5dloso3XaeXG5QeHTO4nWg73ytVek84dXnSRuYpv4Gk0cXoL2dOXqB+e9bYnHIfS+s60xgT+o0v+stMFXZ/XxRzkomhOhjaSogOhvbwL9kmWW27eVu520feAROhCvObXsm6SQY+ZcvDDT9zbH20SvqoFTZDy+Nn5d7FVTexVvltp8b6hdvQn7YVXURKbog+JKDriGxMtvhJUedQbBxW/mJDL32+yvHdWLWdP2AGtLFQFeEKVdpNtTWl/m1FU/bce4/ScWOnjZXPKIK5voPgS+JmhMhwkt1Pz5/W9S7PcrxPJin+JS95n0iZHHOIpLzQMh1BuDqvMqnPEu/y1AXxfFk7ebbLfbULj42Ebfbkcfbchur6Rm+5W3EzpD065S5+gW+IdpbBkjvph8h9xfahZaon7nLPMnHFo5RnjipPzYFzdXkknpyXWaf8K7X/JJu//naKokxzVJlUfoE9Jeo38giqq8U7uPeRVs9yMSazY/Iw7zZFXO8+In6BcSKKcq2jj6zX8z3dz9OM/tzPaM/xjPac0M46x7NBnSVUkXPr+W+uemzExe8UXz9+n6RfvM4P/X+c77k49HxP5jOEJw5VZ7TZ/n7X9ventr9fs/3NOoA6T4nqMj6Xvw1otfw9CHpD/r4X+lr+Pp74cu+T7G9ljDbdQfc+EabJxJ/AgeIeBq4FdwN/BevA38ELwD9s52uukXS3kHTt52s+FOe/V+RhcDj4CDgKfAw046/U+0HVOqSK39scLyX+k4QbAD4LDgGfA3cAnwd3B18Cp4EvgweAL4IV4CvgweBr4DzwdfBM8A1wCbgKbAHfBFeAb4H3gO+C94NrwOcl3VfBD8E28CPQZPZtsDe4GhQ5yN5Exl4XORzGYDgUPBIcCx4NngE2gRJf9gDSj1zib0Y+/cCtwNHgGHBzcBs=
*/