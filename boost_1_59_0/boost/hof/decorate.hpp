/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    decorate.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_DECORATE_H
#define BOOST_HOF_GUARD_DECORATE_H

/// decorate
/// ========
/// 
/// Description
/// -----------
/// 
/// The `decorate` function adaptor helps create simple function decorators. 
/// 
/// A function adaptor takes a function and returns a new functions whereas a
/// decorator takes some parameters and returns a function adaptor. The
/// `decorate` function adaptor will return a decorator that returns a
/// function adaptor. Eventually, it will invoke the function with the user-
/// provided parameter and function.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     constexpr decorate_adaptor<F> decorate(F f);
/// 
/// Semantics
/// ---------
/// 
///     assert(decorate(f)(x)(g)(xs...) == f(x, g, xs...));
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [ConstInvocable](ConstInvocable)
/// * MoveConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     #include <iostream>
///     #include <string>
///     using namespace boost::hof;
/// 
///     struct logger_f
///     {
///         template<class F, class... Ts>
///         auto operator()(const std::string& message, F&& f, Ts&&... xs) const 
///             -> decltype(f(std::forward<Ts>(xs)...))
///         {
///             // Message to print out when the function is called
///             std::cout << message << std::endl;
///             // Call the function
///             return f(std::forward<Ts>(xs)...);
///         }
///     };
///     // The logger decorator
///     BOOST_HOF_STATIC_FUNCTION(logger) = boost::hof::decorate(logger_f());
///     
///     struct sum_f
///     {
///         template<class T, class U>
///         T operator()(T x, U y) const
///         {
///             return x+y;
///         }
///     };
///     
///     BOOST_HOF_STATIC_FUNCTION(sum) = sum_f();
///     int main() {
///         // Use the logger decorator to print "Calling sum" when the function is called
///         assert(3 == logger("Calling sum")(sum)(1, 2));
///     }
/// 

#include <boost/hof/reveal.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/detail/static_const_var.hpp>
#include <boost/hof/detail/compressed_pair.hpp>

namespace boost { namespace hof { namespace detail {

template<class D, class T, class F>
struct decorator_invoke
// : compressed_pair<compressed_pair<F, T>, D>
: compressed_pair<compressed_pair<D, T>, F>
{
    // typedef compressed_pair<F, T> base;
    typedef compressed_pair<compressed_pair<D, T>, F> base;

    BOOST_HOF_INHERIT_CONSTRUCTOR(decorator_invoke, base)

    template<class... Ts>
    constexpr const compressed_pair<D, T>& get_pair(Ts&&... xs) const noexcept
    {
        return this->first(xs...);
    }

    template<class... Ts>
    constexpr const F& base_function(Ts&&... xs) const noexcept
    {
        return this->second(xs...);
    }

    template<class... Ts>
    constexpr const D& get_decorator(Ts&&... xs) const noexcept
    {
        return this->get_pair(xs...).first(xs...);
    }

    template<class... Ts>
    constexpr const T& get_data(Ts&&... xs) const noexcept
    {
        return this->get_pair(xs...).second(xs...);
    }

    BOOST_HOF_RETURNS_CLASS(decorator_invoke);

    struct decorator_invoke_failure
    {
        template<class Failure>
        struct apply
        {
            template<class... Ts>
            struct of
            : Failure::template of<const T&, const F&, Ts...>
            {};
        };
    };

    struct failure
    : failure_map<decorator_invoke_failure, D>
    {};

    template<class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(const D&, id_<const T&>, id_<const F&>, id_<Ts>...) 
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        BOOST_HOF_MANGLE_CAST(const D&)(BOOST_HOF_CONST_THIS->get_decorator(xs...))(
            BOOST_HOF_MANGLE_CAST(const T&)(BOOST_HOF_CONST_THIS->get_data(xs...)),
            BOOST_HOF_MANGLE_CAST(const F&)(BOOST_HOF_CONST_THIS->base_function(xs...)),
            BOOST_HOF_FORWARD(Ts)(xs)...
        )
    );
};

template<class D, class T>
struct decoration
: compressed_pair<D, T>
{
    typedef compressed_pair<D, T> base;
    BOOST_HOF_INHERIT_CONSTRUCTOR(decoration, base)

    template<class... Ts>
    constexpr const D& get_decorator(Ts&&... xs) const noexcept
    {
        return this->first(xs...);
    }

    template<class... Ts>
    constexpr const T& get_data(Ts&&... xs) const noexcept
    {
        return this->second(xs...);
    }

    template<class F>
    constexpr decorator_invoke<D, T, detail::callable_base<F>> operator()(F f) const
    BOOST_HOF_NOEXCEPT(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(decorator_invoke<D, T, detail::callable_base<F>>, compressed_pair<D, T>, detail::callable_base<F>&&))
    {
        return decorator_invoke<D, T, detail::callable_base<F>>(
            *this, static_cast<detail::callable_base<F>&&>(f)
        );
    }
};

}

template<class F>
struct decorate_adaptor : detail::callable_base<F>
{
    typedef decorate_adaptor fit_rewritable1_tag;
    typedef detail::callable_base<F> base;
    BOOST_HOF_INHERIT_CONSTRUCTOR(decorate_adaptor, detail::callable_base<F>)

    template<class... Ts>
    constexpr const base& base_function(Ts&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    // TODO: Add predicate for constraints

    template<class T>
    constexpr detail::decoration<base, T> operator()(T x) const 
    BOOST_HOF_NOEXCEPT(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(base, const base&) && BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(T, T&&))
    {
        return detail::decoration<base, T>(this->base_function(x), static_cast<T&&>(x));
    }

};

BOOST_HOF_DECLARE_STATIC_VAR(decorate, detail::make<decorate_adaptor>);

}} // namespace boost::hof

#endif

/* decorate.hpp
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
*/