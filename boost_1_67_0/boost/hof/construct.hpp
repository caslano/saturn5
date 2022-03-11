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