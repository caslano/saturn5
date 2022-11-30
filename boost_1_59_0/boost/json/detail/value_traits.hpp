//
// Copyright (c) 2020 Krystian Stasiowski (sdkrystian@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_DETAIL_VALUE_TRAITS_HPP
#define BOOST_JSON_DETAIL_VALUE_TRAITS_HPP

#include <boost/json/detail/config.hpp>
#include <type_traits>
#include <utility>

BOOST_JSON_NS_BEGIN
namespace detail {

template<std::size_t N>
struct priority_tag
    : priority_tag<N - 1> { };

template<>
struct priority_tag<0> { };

using std::begin;
using std::end;
#ifdef __cpp_lib_nonmember_container_access
using std::size;
#endif

template<typename T, typename = void>
struct container_traits
{
    static constexpr bool is_container = false;
};

template<typename T>
struct container_traits<T, typename std::enable_if<
    std::is_same<decltype(begin(std::declval<T&>())),
        decltype(end(std::declval<T&>()))>::value>::type>
{
private:
    template<typename U, typename std::enable_if<
        std::is_convertible<decltype(std::declval<U&>().size()),
            std::size_t>::value>::type* = nullptr>
    static
    std::size_t
    size_impl(
        U&& cont,
        priority_tag<2>)
    {
        return cont.size();
    }

    template<typename U, typename std::enable_if<
        std::is_convertible<decltype(size(std::declval<U&>())),
            std::size_t>::value>::type* = nullptr>
    static
    std::size_t
    size_impl(
        U& cont,
        priority_tag<1>)
    {
        return size(cont);
    }

    template<typename U, std::size_t N>
    static
    std::size_t
    size_impl(
        U(&)[N],
        priority_tag<1>)
    {
        return N;
    }

    template<typename U>
    static
    std::size_t
    size_impl(U&, priority_tag<0>)
    {
        return 0;
    }

public:
    static constexpr bool is_container = true;
    using value_type = remove_cvref<
        decltype(*begin(std::declval<T&>()))>;

    template<typename U>
    static
    std::size_t
    try_size(U& cont)
    {
        return container_traits::size_impl(
            cont, priority_tag<2>());
    }
};

template<typename T, typename = void>
struct map_traits
{
    static constexpr bool is_map = false;
    static constexpr bool has_unique_keys = false;
};

template<typename T>
struct map_traits<T, void_t<typename remove_cvref<T>::key_type,
    typename std::enable_if<container_traits<T>::is_container &&
        std::tuple_size<typename remove_cvref<T>::
    value_type>::value == 2>::type>>
{
private:
    template<typename U, typename = void>
    struct unique_keys : std::false_type { };

    template<typename U>
    struct unique_keys<U, typename std::enable_if<
        (std::tuple_size<remove_cvref<decltype(std::declval<
            remove_cvref<U>&>().emplace(std::declval<typename
        remove_cvref<U>::value_type>()))>>::value > 0)>::type>
            : std::true_type { };
public:
    static constexpr bool is_map = true;
    static constexpr bool has_unique_keys = unique_keys<T>::value;
    using pair_key_type = typename std::tuple_element<
        0, typename remove_cvref<T>::value_type>::type;
    using pair_value_type = typename std::tuple_element<
        1, typename remove_cvref<T>::value_type>::type;
    static constexpr bool key_converts_to_string =
        std::is_convertible<pair_key_type, string_view>::value;
};

// does not include std::nullptr_t
template<class T>
using value_constructible = std::integral_constant<bool,
    std::is_same<detail::remove_cvref<T>, value>::value ||
        std::is_same<detail::remove_cvref<T>, object>::value ||
    std::is_same<detail::remove_cvref<T>, array>::value ||
        std::is_same<detail::remove_cvref<T>, string>::value ||
    std::is_same<detail::remove_cvref<T>, string_view>::value ||
        std::is_arithmetic<detail::remove_cvref<T>>::value ||
    std::is_same<detail::remove_cvref<T>, char const*>::value ||
    std::is_same<detail::remove_cvref<T>,
        std::initializer_list<value_ref>>::value ||
    std::is_same<detail::remove_cvref<T>, value_ref>::value>;

BOOST_STATIC_ASSERT(value_constructible<value>::value);

} // detail
BOOST_JSON_NS_END

#endif

/* value_traits.hpp
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
*/