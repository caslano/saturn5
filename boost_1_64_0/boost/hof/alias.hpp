/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    alias.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_ALIAS_H
#define BOOST_HOF_GUARD_ALIAS_H

#include <boost/hof/returns.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/holder.hpp>
#include <boost/hof/config.hpp>

/// alias
/// =====
/// 
/// Description
/// -----------
/// 
/// The `alias` class wraps a type with a new type that can be tagged by the
/// user. This allows defining extra attributes about the type outside of the
/// type itself. There are three different ways the value can be stored: as a
/// member variable, by inheritance, or as a static member variable. The value
/// can be retrieved uniformily using the `alias_value` function.
/// 
/// Synopsis
/// --------
/// 
///     // Alias the type using a member variable
///     template<class T, class Tag=void>
///     class alias;
/// 
///     // Alias the type by inheriting
///     template<class T, class Tag=void>
///     class alias_inherit;
/// 
///     // Alias the type using a static variable
///     template<class T, class Tag=void>
///     class alias_static;
/// 
///     // Retrieve tag from alias
///     template<class Alias>
///     class alias_tag;
/// 
///     // Check if type has a certian tag
///     template<class T, class Tag>
///     class has_tag;
/// 
///     // Retrieve value from alias
///     template<class Alias>
///     constexpr auto alias_value(Alias&&);
/// 

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4579)
#endif

namespace boost { namespace hof {

template<class T>
struct alias_tag;

template<class T, class Tag, class=void>
struct has_tag
: std::false_type
{};

template<class T, class Tag>
struct has_tag<T, Tag, typename detail::holder<
    typename alias_tag<T>::type
>::type>
: std::is_same<typename alias_tag<T>::type, Tag>
{};

namespace detail {

template<class T>
constexpr T& lvalue(T& x) noexcept
{
    return x;
}

template<class T>
constexpr const T& lvalue(const T& x) noexcept
{
    return x;
}

}

#define BOOST_HOF_UNARY_PERFECT_FOREACH(m) \
    m(const&, boost::hof::detail::lvalue) \
    m(&, boost::hof::detail::lvalue) \
    m(&&, boost::hof::move) \

template<class T, class Tag=void>
struct alias
{
    T value;
    BOOST_HOF_DELEGATE_CONSTRUCTOR(alias, T, value)
};

#define BOOST_HOF_DETAIL_ALIAS_GET_VALUE(ref, move) \
template<class Tag, class T, class... Ts> \
constexpr auto alias_value(alias<T, Tag> ref a, Ts&&...) BOOST_HOF_RETURNS(move(a.value))
BOOST_HOF_UNARY_PERFECT_FOREACH(BOOST_HOF_DETAIL_ALIAS_GET_VALUE)

template<class T, class Tag>
struct alias_tag<alias<T, Tag>>
{ typedef Tag type; };


template<class T, class Tag=void>
struct alias_inherit 
#if (defined(__GNUC__) && !defined (__clang__))
: std::conditional<(std::is_class<T>::value), T, alias<T>>::type
#else
: T
#endif
{
    BOOST_HOF_INHERIT_CONSTRUCTOR(alias_inherit, T)
};

#define BOOST_HOF_DETAIL_ALIAS_INHERIT_GET_VALUE(ref, move) \
template<class Tag, class T, class... Ts, class=typename std::enable_if<(BOOST_HOF_IS_CLASS(T))>::type> \
constexpr T ref alias_value(alias_inherit<T, Tag> ref a, Ts&&...) BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT(move(a)) \
{ \
    return move(a); \
}
BOOST_HOF_UNARY_PERFECT_FOREACH(BOOST_HOF_DETAIL_ALIAS_INHERIT_GET_VALUE)

template<class T, class Tag>
struct alias_tag<alias_inherit<T, Tag>>
{ typedef Tag type; };

namespace detail {

template<class T, class Tag>
struct alias_static_storage
{
#ifdef _MSC_VER
    // Since we disable the error for 4579 on MSVC, which leaves the static
    // member unitialized at runtime, it is, therefore, only safe to use this
    // class on types that are empty with constructors that have no possible
    // side effects.
    static_assert(BOOST_HOF_IS_EMPTY(T) && 
        BOOST_HOF_IS_LITERAL(T) && 
        BOOST_HOF_IS_DEFAULT_CONSTRUCTIBLE(T), "In-class initialization is not yet implemented on MSVC");
#endif
    static constexpr T value = T();
};

template<class T, class Tag>
constexpr T alias_static_storage<T, Tag>::value;

}

template<class T, class Tag=void>
struct alias_static
{
    template<class... Ts, BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(T, Ts...)>
    constexpr alias_static(Ts&&...) noexcept
    {}
};

template<class Tag, class T, class... Ts>
constexpr const T& alias_value(const alias_static<T, Tag>&, Ts&&...) noexcept
{
    return detail::alias_static_storage<T, Tag>::value;
}

template<class T, class Tag>
struct alias_tag<alias_static<T, Tag>>
{ typedef Tag type; };

namespace detail {

template<class T, class Tag>
struct alias_try_inherit
: std::conditional<(BOOST_HOF_IS_CLASS(T) && !BOOST_HOF_IS_FINAL(T) && !BOOST_HOF_IS_POLYMORPHIC(T)), 
    alias_inherit<T, Tag>, 
    alias<T, Tag>
>
{};

#if BOOST_HOF_HAS_EBO
template<class T, class Tag>
struct alias_empty
: std::conditional<(BOOST_HOF_IS_EMPTY(T)), 
    typename alias_try_inherit<T, Tag>::type, 
    alias<T, Tag>
>
{};
#else
template<class T, class Tag>
struct alias_empty
: std::conditional<
        BOOST_HOF_IS_EMPTY(T) && 
        BOOST_HOF_IS_LITERAL(T) && 
        BOOST_HOF_IS_DEFAULT_CONSTRUCTIBLE(T),
    alias_static<T, Tag>,
    alias<T, Tag>
>
{};
#endif

}

}} // namespace boost::hof

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif

/* alias.hpp
ECSf9s2v8ExYEo9Xp+szYdu+TdbrxdO1Xh3XA7b+bJzf2JTEM5Be88zvP9Xc5LXwBKvXetGnvvulJq+dpyK9ji+Ypt3X5HXyjKTXteVfnz2/yZvOE5Nezw2fUG9o8mbw/KQ3867xT9zT5M3iaUpv9qDPWLc3eXN4ttKbf0HpkyVNXi8fPOwtkrdSeZvIt2Ub6MZPf8f/LPxWmU6XyER6J9/aTW9cXrPv7YO8liXKa0Owt7wOz4vL67y5PeT18pdPIK+LvvW+5BWfr/SJHxJr9CnLuZiyXNZjRvIbO+JTlmstcspybo8Et+zgKUs65jZUfLuY5BUlRbbHopbQNUvxgkkl+W4PXbOE3+3y3Rm6ZvHjtM8rpqFEiVe7E9PkoeKvP56BF4Rqt/H71wC5OFS8CLeSUPFC3EpDxQvEpFJRMlEWchteuJCJspBqfrfjXRYSpEImciGl2mgGOp8KKUWoNoTfbwXYa2gedR4eJtE86lztxRQ+DN0lz/7XZ0vFXaQ7tYezbHVVyfTgrX5V+LHfoBglmmk6rb/cQLDYJLceLMaWhIxFhUKx11DKZkKTEl3TTzTYHtuAVP1Ds1Kw0ThA7LFgT3G5GWGxRYc1QIc10ICVyrCsPWANMmANDs2yYa9vHZZDh2XXYQ3RYZ1nwEpjWI4EWKIhdM35EtbHACM0ayg22Eb8bKcksdipwxqmwxpuwBrBsFw98LrAwGtkaNYo7H6t4+XR8UrXYY3WYV1owHIzLE8PWB83YH0iNOuT2H5ah5Wpw8rQYX1Kh3WRAWsMw8rsReOnJazPMI2fxX7PRGOWTmOWDmusDutiA5bKsLJ74HWJgdfnQrMuxYbMOl75Ol45OqxcHdY4A1Yew8o3YM3WEbtMAruczVNo1hWzAG16wzk1+2irGXQMYP4XZtY/Gpfsf1iee/pN9D944t9ryfvFujr0P9ivyGsfc/jbx9D/YA8Ar7PrcxfMRv+DHQG86W13vPob9D/YH8CbMarq8jHof7BbgDfrpr8WvI3+B3sHeHMWjV6a1uRl36PT6X94z7T/keBvMPZ4fwPjfPUKmq2SDf1XfXS665+oS9L4Fwtuh15WSrxp/qI8f9EC26398kq88y21JaWmWv/EpDDa4LsI47C/CIew+v7KfQKtdrVPaco7MH8EHW8/tz3BB+FPG4wj08sRVY6oMQeaAEFeyg4UX2kq92vLk7gLUXOMAN46FPMxWoqvzK/dTKl2Alztq7eP2QlnhCEVZeXaIFlE2IB+FivPKotC7lF3JvbXzAhC/8qBW5n4HgYdeGg5e/lztrpR/XE0sXjM40RYhb92TbJQrhZlZjGf9kjPwc8lCi20ooY3ry+zAtrfyaOq0I7B8S30VOZA2Isc5kTYbg5zIewVDvOIwwjVODSTxh5EYQYi3+LILEQd5qhshL3DYTkIS1IoLB9zUR48Re72PJ/Mk35F+HnCGL7TiUJSIpec5kgctGtGp0UgDTQDM+hXHXtIbAkv8vCU5x7bIzss4Xnp0X9grw1v7KHULal7KIKCOSzp+CCv6QRhyScIU04QZj5BWD8jDCulwibc08PY1rnR9kj9UJqaCt9YJPZFdw8Vx2ioUz0YnuZVt0dfH5BKI6D2VA0ZPLC750VfGxzdc17q/tSjFKLuolgsYTisHkTs4OhriIruGYzYAppysyMBhg95h0v7oc3uRVmHNrnnZYvJmCynwS4B9qk8eKbsS9upZK4J7R1qT3OtuRs35cYcRGelTctX1oTpYaO40SKmOZUtvPitwJVWD1Q9yJwOdFEW03YYaLjENCvQeM1MIdE9rlRay+CUCXmE7iioHhndhxnIkalvUHjq4bGLkeIoZRhL6zM=
*/