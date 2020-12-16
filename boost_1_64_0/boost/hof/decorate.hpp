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
kM1YuJjPUduvSjyHhRA/3ZEa6arcd5xkliFbXD3S+jHQV1eJ2RtNG2Do+hoaX/ngJvGvDGlePbigLzYQ/gxT7Wq/uICHW7e8+7syvMke2gFuy5zSnBneFj/w7sZ/9Sddr0oM6WTspgwEq9l5OduAkgtL4/0zqkTnTmoL9mkdcWV51PrjTYdjvH6kxqR88fTHiTGpvW+/b0/T7xBlDE1ATo1NHhqbxoDP2JMVp1VhTopa1dFIofeD1e/ntr1sb8wyxG3tt6rEdrvSchaODNTX2sULMqBk08IBUEKul1mGqizzz8ehHavtann9A5380p6zE+Idm7nTqfOXnFGK0z5TmgtY7Xo6/+qfMek79/7nieRnZuWuwW0n+/ehmEV/zbGz/pqLH2jKRTTuwlug4QUIdBtFxZS2yhd4Q+vbV5HJNYXrxzVkeT1udy0J4KUqfDxrXic970nnyD5usqnzSOH2dPTwkfARm7Jd96LPx0AvdaFxDq2JHSbPlUVOm2tJHQ1/TLG/eFFUfO5RMtvN3Kr6UxWMur3roQlMWV5pr19kh0vV/llrHNgOMCvSDobkPXo3/Ut5v0vGOPK3orSDdkyZtQLpKxFwUH9lY1PGvt/qr4Q/ztz3AC1kh6POO45cC2h1K6Yvxrettuc+18Is2t6wphT/zXLtKJc3fmoNZmf+blBDey2AgkkuMnQvol8r6OhB/2qgjK4JUb9Wim8aIrUr8BLMFue8B8I+r4qoEq/tpmqNnkaqmH4Xtwb0y1fA4ne8RK0VRSC1DQsKef+VEfd/oHs25Ljp/Kv9Vn5yuiU/4Qeoe9x8W2w+fqrQGfXV/IrFFyzv4Nox/ooM9UfgmRO5AgT2ibnPgJz4JNaw06FYmOxNfY2WIn/cSP8PeUWa9nPABd/V7KakXsgu8GiPPZ8b/ac78CK/VRTgJ3bOV2njPlHzEccVIKH0nPJt4OP8FM7GrZLjDhGtqZbRapEnJ83o4msJQc2pyvNH7KIvUvLl6rxi0F5G8YrDtZDU4tk3pLsU4lyWuImIw6yt+E1zEWgCQtS0Jw/Tnt88rXb1F85a4edAbEDLNi+87p6S/haVftGbmI754JuxKabSNmF9okYcl9VghmrqFP9fLlk05LH+D4QS/mYeDHV8aT5fDOykeezTxnXnf7aRjKLRhuTQGPQ7CN6id+FsZiPXtJvwVo3Fif488uaDZDWBatGI7iKPb+wWHpVbO0K/3EklPO+mxu5Q4qwdQMrMBqnPSP1oBNkq/YLWtaXE8VZXii0YhXmUrPsDmINuiCLlCDzSj+c6efL+QxXYXgXCCRNpmZm+lo5wZ7DX8vozawU1ATmWD2As1Vj+KpgSY/m3nk03lkNFiPOSqaxOW3Quw//nSzn+0g4MWkDdL/4IGkvZPhwjYjWg6qJaLEYfWx+Pu8i+MujVko2LLqkWsxFWWhHI3Clu4zxODJFbtTcS8vCdr2MJQ0Pt2dqbMopXO25A73ZhWiGnFIZvS8C3C7PaQSYG46rgLXtQYnD8Q1UYZPJCx6bsIRVY+XtZGkT8uGDhSrhTZULtHY9bkw8xkbBs+jwJjZmbsm1natg1HrW/BbT/Np8AFA99E7r7nENqQlp7KTYsIiT3oMGy4RJHbSFkQDM4nTa8PuRU+h18vx+Chsa39LzcYC5C0KEe0+SxIvL/k/NPLh1IBLl7PVqGV7PP1eCBYNL8e6D5L/7ONMey6quMqjSRGSfi5OHPExAeDM/S21Cj7RUDoFNia/E2xiwAaTRenOuAGeEps+hrqWi03BgUXiPugs3Irz0QyaXz4zJYHBYQZ219xQJRnPcBf0Uyn5fzzz+p2NOcMnD/YUbO1Q9AX80Nfk+7FuM=
*/