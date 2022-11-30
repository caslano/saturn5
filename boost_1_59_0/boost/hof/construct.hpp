/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    construct.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_CONSTRUCT_H
#define BOOST_HOF_GUARD_CONSTRUCT_H

/// construct
/// =========
/// 
/// Description
/// -----------
/// 
/// The `construct` function returns a function object that will construct the
/// object when the called. A template can also be given, which it will deduce
/// the parameters to the template. The `construct_meta` can be used to
/// construct the object from a metafunction.
/// 
/// Synopsis
/// --------
/// 
///     // Construct by decaying each value
///     template<class T>
///     constexpr auto construct();
/// 
///     template<template<class...> class Template>
///     constexpr auto construct();
/// 
///     // Construct by deducing lvalues by reference and rvalue reference by reference
///     template<class T>
///     constexpr auto construct_forward();
/// 
///     template<template<class...> class Template>
///     constexpr auto construct_forward();
/// 
///     // Construct by deducing lvalues by reference and rvalues by value.
///     template<class T>
///     constexpr auto construct_basic();
/// 
///     template<template<class...> class Template>
///     constexpr auto construct_basic();
/// 
///     // Construct by deducing the object from a metafunction
///     template<class MetafunctionClass>
///     constexpr auto construct_meta();
/// 
///     template<template<class...> class MetafunctionTemplate>
///     constexpr auto construct_meta();
/// 
/// Semantics
/// ---------
/// 
///     assert(construct<T>()(xs...) == T(xs...));
///     assert(construct<Template>()(xs...) == Template<decltype(xs)...>(xs...));
///     assert(construct_meta<MetafunctionClass>()(xs...) == MetafunctionClass::apply<decltype(xs)...>(xs...));
///     assert(construct_meta<MetafunctionTemplate>()(xs...) == MetafunctionTemplate<decltype(xs)...>::type(xs...));
/// 
/// Requirements
/// ------------
/// 
/// MetafunctionClass must be a:
/// 
/// * [MetafunctionClass](MetafunctionClass)
/// 
/// MetafunctionTemplate<Ts...> must be a:
/// 
/// * [Metafunction](Metafunction)
/// 
/// T, Template<Ts..>, MetafunctionClass::apply<Ts...>, and
/// MetafunctionTemplate<Ts...>::type must be:
/// 
/// * MoveConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     #include <vector>
/// 
///     int main() {
///         auto v = boost::hof::construct<std::vector<int>>()(5, 5);
///         assert(v.size() == 5);
///     }
/// 

#include <boost/hof/detail/forward.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/join.hpp>
#include <boost/hof/detail/remove_rvalue_reference.hpp>
#include <boost/hof/decay.hpp>

#include <initializer_list>

namespace boost { namespace hof { 

namespace detail {

template<class T, class=void>
struct construct_f
{
    typedef typename std::aligned_storage<sizeof(T)>::type storage;

    struct storage_holder
    {
        storage * s;
        storage_holder(storage* x) noexcept : s(x)
        {}

        T& data() noexcept
        {
            return *reinterpret_cast<T*>(s);
        }

        ~storage_holder() noexcept(noexcept(std::declval<T>().~T()))
        {
            this->data().~T();
        }
    };

    constexpr construct_f() noexcept
    {}
    template<class... Ts, BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(T, Ts...)>
    T operator()(Ts&&... xs) const BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(T, Ts&&...)
    {
        storage buffer{};
        new(&buffer) T(BOOST_HOF_FORWARD(Ts)(xs)...);
        storage_holder h(&buffer);
        return boost::hof::move(h.data());
    }

    template<class X, BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(T, std::initializer_list<X>&&)>
    T operator()(std::initializer_list<X>&& x) const BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(T, std::initializer_list<X>&&)
    {
        storage buffer{};
        new(&buffer) T(static_cast<std::initializer_list<X>&&>(x));
        storage_holder h(&buffer);
        return h.data();
    }

    template<class X, BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(T, std::initializer_list<X>&)>
    T operator()(std::initializer_list<X>& x) const BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(T, std::initializer_list<X>&)
    {
        storage buffer{};
        new(&buffer) T(x);
        storage_holder h(&buffer);
        return h.data();
    }

    template<class X, BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(T, const std::initializer_list<X>&)>
    T operator()(const std::initializer_list<X>& x) const BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(T, const std::initializer_list<X>&)
    {
        storage buffer{};
        new(&buffer) T(x);
        storage_holder h(&buffer);
        return h.data();
    }
};

template<class T>
struct construct_f<T, typename std::enable_if<BOOST_HOF_IS_LITERAL(T)>::type>
{
    constexpr construct_f() noexcept
    {}
    template<class... Ts, BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(T, Ts...)>
    constexpr T operator()(Ts&&... xs) const noexcept
    {
        return T(BOOST_HOF_FORWARD(Ts)(xs)...);
    }

    template<class X, BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(T, std::initializer_list<X>&&)>
    constexpr T operator()(std::initializer_list<X>&& x) const noexcept
    {
        return T(static_cast<std::initializer_list<X>&&>(x));
    }

    template<class X, BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(T, std::initializer_list<X>&)>
    constexpr T operator()(std::initializer_list<X>& x) const noexcept
    {
        return T(x);
    }

    template<class X, BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(T, const std::initializer_list<X>&)>
    constexpr T operator()(const std::initializer_list<X>& x) const noexcept
    {
        return T(x);
    }
};

template<template<class...> class Template, template<class...> class D>
struct construct_template_f
{
    constexpr construct_template_f() noexcept
    {}
    template<class... Ts, class Result=BOOST_HOF_JOIN(Template, typename D<Ts>::type...), 
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(Result, Ts...)>
    constexpr Result operator()(Ts&&... xs) const BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(Result, Ts&&...)
    {
        return construct_f<Result>()(BOOST_HOF_FORWARD(Ts)(xs)...);
    }
};

template<class MetafunctionClass>
struct construct_meta_f
{
    constexpr construct_meta_f() noexcept
    {}

    template<class... Ts>
    struct apply
    : MetafunctionClass::template apply<Ts...>
    {};

    template<class... Ts, 
        class Metafunction=BOOST_HOF_JOIN(apply, Ts...), 
        class Result=typename Metafunction::type, 
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(Result, Ts...)>
    constexpr Result operator()(Ts&&... xs) const BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(Result, Ts&&...)
    {
        return construct_f<Result>()(BOOST_HOF_FORWARD(Ts)(xs)...);
    }
};

template<template<class...> class MetafunctionTemplate>
struct construct_meta_template_f
{
    constexpr construct_meta_template_f() noexcept
    {}
    template<class... Ts, 
        class Metafunction=BOOST_HOF_JOIN(MetafunctionTemplate, Ts...), 
        class Result=typename Metafunction::type, 
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(Result, Ts...)>
    constexpr Result operator()(Ts&&... xs) const BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(Result, Ts&&...)
    {
        return construct_f<Result>()(BOOST_HOF_FORWARD(Ts)(xs)...);
    }
};


template<class T>
struct construct_id
{
    typedef T type;
};

}

template<class T>
constexpr detail::construct_f<T> construct() noexcept
{
    return {};
}
// These overloads are provide for consistency
template<class T>
constexpr detail::construct_f<T> construct_forward() noexcept
{
    return {};
}

template<class T>
constexpr detail::construct_f<T> construct_basic() noexcept
{
    return {};
}

template<template<class...> class Template>
constexpr detail::construct_template_f<Template, detail::decay_mf> construct() noexcept
{
    return {};
}

template<template<class...> class Template>
constexpr detail::construct_template_f<Template, detail::construct_id> construct_forward() noexcept
{
    return {};
}

template<template<class...> class Template>
constexpr detail::construct_template_f<Template, detail::remove_rvalue_reference> construct_basic() noexcept
{
    return {};
}

template<class T>
constexpr detail::construct_meta_f<T> construct_meta() noexcept
{
    return {};
}

template<template<class...> class Template>
constexpr detail::construct_meta_template_f<Template> construct_meta() noexcept
{
    return {};
}

}} // namespace boost::hof

#endif

/* construct.hpp
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
*/