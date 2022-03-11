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
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
*/