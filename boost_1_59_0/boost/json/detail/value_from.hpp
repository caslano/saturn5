//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
// Copyright (c) 2020 Krystian Stasiowski (sdkrystian@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_DETAIL_VALUE_FROM_HPP
#define BOOST_JSON_DETAIL_VALUE_FROM_HPP

#include <boost/json/storage_ptr.hpp>
#include <boost/json/value.hpp>
#include <boost/json/detail/value_traits.hpp>

BOOST_JSON_NS_BEGIN

struct value_from_tag { };

template<class T, class = void>
struct has_value_from;

namespace detail {

// The integral_constant parameter here is an
// rvalue reference to make the standard conversion
// sequence to that parameter better, see
// http://eel.is/c++draft/over.ics.rank#3.2.6
template<std::size_t N, class T>
void
tuple_to_array(
    T&&,
    array&,
    std::integral_constant<std::size_t, N>&&)
{
}

template<std::size_t N, std::size_t I, class T>
void
tuple_to_array(
    T&& t,
    array& arr,
    const std::integral_constant<std::size_t, I>&)
{
    using std::get;
    arr.emplace_back(value_from(
        get<I>(std::forward<T>(t)), arr.storage()));
    return detail::tuple_to_array<N>(std::forward<T>(t),
        arr, std::integral_constant<std::size_t, I + 1>());
}

//----------------------------------------------------------
// User-provided conversion

template<class T, void_t<decltype(tag_invoke(value_from_tag(),
    std::declval<value&>(), std::declval<T&&>()))>* = nullptr>
void
value_from_helper(
    value& jv,
    T&& from,
    priority_tag<5>)
{
    tag_invoke(value_from_tag(), jv, std::forward<T>(from));
}


//----------------------------------------------------------
// Native conversion

template<class T, typename std::enable_if<
    detail::value_constructible<T>::value>::type* = nullptr>
void
value_from_helper(
    value& jv,
    T&& from,
    priority_tag<4>)
{
    jv = std::forward<T>(from);
}

template<class T, typename std::enable_if<
    std::is_same<detail::remove_cvref<T>,
        std::nullptr_t>::value>::type* = nullptr>
void
value_from_helper(
    value& jv,
    T&&,
    priority_tag<4>)
{
    // do nothing
    BOOST_ASSERT(jv.is_null());
    (void)jv;
}

//----------------------------------------------------------
// Generic conversions

// string-like types
// NOTE: original check for size used is_convertible but
// MSVC-140 selects wrong specialisation if used
template<class T, typename std::enable_if<
    std::is_constructible<remove_cvref<T>, const char*, std::size_t>::value &&
    std::is_convertible<decltype(std::declval<T&>().data()), const char*>::value &&
    std::is_integral<decltype(std::declval<T&>().size())>::value
>::type* = nullptr>
void
value_from_helper(
    value& jv,
    T&& from,
    priority_tag<3>)
{
    jv.emplace_string().assign(
        from.data(), from.size());
}

// map-like types; should go before ranges, so that we can differentiate
// map-like and other ranges
template<class T, typename std::enable_if<
    map_traits<T>::has_unique_keys &&
        has_value_from<typename map_traits<T>::pair_value_type>::value &&
    std::is_convertible<typename map_traits<T>::pair_key_type,
        string_view>::value>::type* = nullptr>
void
value_from_helper(
    value& jv,
    T&& from,
    priority_tag<2>)
{
    using std::get;
    object& obj = jv.emplace_object();
    obj.reserve(container_traits<T>::try_size(from));
    for (auto&& elem : from)
        obj.emplace(get<0>(elem), value_from(
            get<1>(elem), obj.storage()));
}

// ranges; should go before tuple-like in order for std::array being handled
// by this overload
template<class T, typename std::enable_if<
    has_value_from<typename container_traits<T>::
        value_type>::value>::type* = nullptr>
void
value_from_helper(
    value& jv,
    T&& from,
    priority_tag<1>)
{
    array& result = jv.emplace_array();
    result.reserve(container_traits<T>::try_size(from));
    for (auto&& elem : from)
        result.emplace_back(
            value_from(elem, result.storage()));
}

// tuple-like types
template<class T, typename std::enable_if<
    (std::tuple_size<remove_cvref<T>>::value > 0)>::type* = nullptr>
void
value_from_helper(
    value& jv,
    T&& from,
    priority_tag<0>)
{
    constexpr std::size_t n =
        std::tuple_size<remove_cvref<T>>::value;
    array& arr = jv.emplace_array();
    arr.reserve(n);
    detail::tuple_to_array<n>(std::forward<T>(from),
        arr, std::integral_constant<std::size_t, 0>());
}

//----------------------------------------------------------

// Calls to value_from are forwarded to this function
// so we can use ADL and hide the built-in tag_invoke
// overloads in the detail namespace
template<class T, class = void_t<
    decltype(detail::value_from_helper(std::declval<value&>(),
        std::declval<T&&>(), priority_tag<5>()))>>
value
value_from_impl(
    T&& from,
    storage_ptr sp)
{
    value jv(std::move(sp));
    detail::value_from_helper(jv, std::forward<T>(from), priority_tag<5>());
    return jv;
}

} // detail
BOOST_JSON_NS_END

#endif

/* value_from.hpp
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
*/