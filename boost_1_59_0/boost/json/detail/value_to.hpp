//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
// Copyright (c) 2020 Krystian Stasiowski (sdkrystian@gmail.com)
// Copyright (c) 2021 Dmitry Arkhipov (grisumbras@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_DETAIL_VALUE_TO_HPP
#define BOOST_JSON_DETAIL_VALUE_TO_HPP

#include <boost/json/value.hpp>
#include <boost/json/detail/value_traits.hpp>
#include <boost/mp11/integer_sequence.hpp>

#include <type_traits>

BOOST_JSON_NS_BEGIN

template<class>
struct value_to_tag { };

template<class, class = void>
struct has_value_to;

template<class T, class U,
    typename std::enable_if<
        ! std::is_reference<T>::value &&
    std::is_same<U, value>::value>::type>
T value_to(U const&);

namespace detail {

template<class T, typename std::enable_if<
    (std::tuple_size<remove_cvref<T>>::value > 0)>::type* = nullptr>
void
try_reserve(
    T&,
    std::size_t size,
    priority_tag<2>)
{
    constexpr std::size_t N = std::tuple_size<remove_cvref<T>>::value;
    if ( N != size )
    {
        detail::throw_invalid_argument(
            "target array size does not match source array size",
            BOOST_JSON_SOURCE_POS);
    }
}

template<typename T, void_t<decltype(
    std::declval<T&>().reserve(0))>* = nullptr>
void
try_reserve(
    T& cont,
    std::size_t size,
    priority_tag<1>)
{
    cont.reserve(size);
}

template<typename T>
void
try_reserve(
    T&,
    std::size_t,
    priority_tag<0>)
{
}

template<class T, typename std::enable_if<
    (std::tuple_size<remove_cvref<T>>::value > 0)>::type* = nullptr>
typename remove_cvref<T>::iterator
inserter(
    T& target,
    priority_tag<1>)
{
    return target.begin();
}

template<class T>
std::insert_iterator<T>
inserter(
    T& target,
    priority_tag<0>)
{
    return std::inserter(target, end(target));
}

//----------------------------------------------------------
// Use native conversion

// identity conversion
inline
value
tag_invoke(
    value_to_tag<value>,
    value const& jv)
{
    return jv;
}

// object
inline
object
tag_invoke(
    value_to_tag<object>,
    value const& jv)
{
    return jv.as_object();
}

// array
inline
array
tag_invoke(
    value_to_tag<array>,
    value const& jv)
{
    return jv.as_array();
}

// string
inline
string
tag_invoke(
    value_to_tag<string>,
    value const& jv)
{
    return jv.as_string();
}

// bool
inline
bool
tag_invoke(
    value_to_tag<bool>,
    value const& jv)
{
    return jv.as_bool();
}

// integral and floating point
template<class T, typename std::enable_if<
    std::is_arithmetic<T>::value>::type* = nullptr>
T
tag_invoke(
    value_to_tag<T>,
    value const& jv)
{
    return jv.to_number<T>();
}

//----------------------------------------------------------
// Use generic conversion

// string-like types
// NOTE: original check for size used is_convertible but
// MSVC-140 selects wrong specialisation if used
template<class T, typename std::enable_if<
    std::is_constructible<T, const char*, std::size_t>::value &&
    std::is_convertible<decltype(std::declval<T&>().data()), const char*>::value &&
    std::is_integral<decltype(std::declval<T&>().size())>::value
>::type* = nullptr>
T
value_to_generic(
    const value& jv,
    priority_tag<3>)
{
    auto& str = jv.as_string();
    return T(str.data(), str.size());
}

// map-like containers; should go before other containers in order to be able
// to tell them apart
template<class T, typename std::enable_if<
    has_value_to<typename map_traits<T>::pair_value_type>::value &&
        std::is_constructible<typename map_traits<T>::pair_key_type,
    string_view>::value>::type* = nullptr>
T
value_to_generic(
    const value& jv,
    priority_tag<2>)
{
    using value_type = typename
        container_traits<T>::value_type;
    const object& obj = jv.as_object();
    T result;
    try_reserve(result, obj.size(), priority_tag<2>());
    for (const auto& val : obj)
        result.insert(value_type{typename map_traits<T>::
            pair_key_type(val.key()), value_to<typename
                map_traits<T>::pair_value_type>(val.value())});
    return result;
}

// all other containers; should go before tuple-like in order to handle
// std::array with this overload
template<class T, typename std::enable_if<
    has_value_to<typename container_traits<T>::
        value_type>::value>::type* = nullptr>
T
value_to_generic(
    const value& jv,
    priority_tag<1>)
{
    const array& arr = jv.as_array();
    T result;
    detail::try_reserve(result, arr.size(), priority_tag<2>());
    std::transform(arr.begin(), arr.end(),
        detail::inserter(result, priority_tag<1>()), [](value const& val) {
            return value_to<typename container_traits<T>::value_type>(val);
        });
    return result;
}

template <class T, std::size_t... Is>
T
make_tuple_like(const array& arr, boost::mp11::index_sequence<Is...>)
{
    return T(value_to<typename std::tuple_element<Is, T>::type>(arr[Is])...);
}

// tuple-like types
template<class T, typename std::enable_if<
    (std::tuple_size<remove_cvref<T>>::value > 0)>::type* = nullptr>
T
value_to_generic(
    const value& jv,
    priority_tag<0>)
{
    auto& arr = jv.as_array();
    constexpr std::size_t N = std::tuple_size<remove_cvref<T>>::value;
    if ( N != arr.size() )
    {
        detail::throw_invalid_argument(
            "array size does not match tuple size",
            BOOST_JSON_SOURCE_POS);
    }

    return make_tuple_like<T>(arr, boost::mp11::make_index_sequence<N>());
}

// Matches containers
template<class T, void_t<typename std::enable_if<
    !std::is_constructible<T, const value&>::value &&
        !std::is_arithmetic<T>::value>::type, decltype(
    value_to_generic<T>(std::declval<const value&>(),
        priority_tag<2>()))>* = nullptr>
T
tag_invoke(
    value_to_tag<T>,
    value const& jv)
{
    return value_to_generic<T>(
        jv, priority_tag<3>());
}

//----------------------------------------------------------

// Calls to value_to are forwarded to this function
// so we can use ADL and hide the built-in tag_invoke
// overloads in the detail namespace
template<class T, void_t<
    decltype(tag_invoke(std::declval<value_to_tag<T>&>(),
        std::declval<const value&>()))>* = nullptr>
T
value_to_impl(
    value_to_tag<T> tag,
    value const& jv)
{
    return tag_invoke(tag, jv);
}

} // detail
BOOST_JSON_NS_END

#endif

/* value_to.hpp
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
*/