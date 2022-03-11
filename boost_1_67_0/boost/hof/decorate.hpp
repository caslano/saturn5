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