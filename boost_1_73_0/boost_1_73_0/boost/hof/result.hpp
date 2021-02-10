/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    result.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_RESULT_H
#define BOOST_HOF_GUARD_RESULT_H

/// result
/// ======
/// 
/// Description
/// -----------
/// 
/// The `result` function adaptor sets the return type for the function, which
/// can be useful when dealing with multiple overloads. Since the return type
/// is no longer dependent on the parameters passed to the function, the
/// `result_adaptor` provides a nested `result_type` that is the return type
/// of the function.
/// 
/// Synopsis
/// --------
/// 
///     template<class Result, class F>
///     constexpr result_adaptor<Result, F> result(F f);
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
/// 
///     struct id
///     {
///         template<class T>
///         T operator()(T x) const
///         {
///             return x;
///         }
///     };
/// 
///     int main() {
///         auto int_result = boost::hof::result<int>(id());
///         static_assert(std::is_same<decltype(int_result(true)), int>::value, "Not the same type");
///     }
/// 

#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/is_invocable.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/reveal.hpp>

namespace boost { namespace hof {

template<class Result, class F>
struct result_adaptor : detail::callable_base<F>
{
    BOOST_HOF_INHERIT_CONSTRUCTOR(result_adaptor, detail::callable_base<F>)

    typedef Result result_type;

    struct failure
    : failure_for<detail::callable_base<F>>
    {};

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    template<class... Ts, class=typename std::enable_if<(boost::hof::is_invocable<F, Ts...>::value)>::type>
    constexpr result_type operator()(Ts&&... xs) const
    {
        return this->base_function(xs...)(BOOST_HOF_FORWARD(Ts)(xs)...);
    };
};

template<class F>
struct result_adaptor<void, F> : detail::callable_base<F>
{
    BOOST_HOF_INHERIT_CONSTRUCTOR(result_adaptor, detail::callable_base<F>)

    typedef void result_type;

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    template<class... Ts, class=typename std::enable_if<(boost::hof::is_invocable<F, Ts...>::value)>::type>
    constexpr typename detail::holder<Ts...>::type operator()(Ts&&... xs) const
    {
        return (typename detail::holder<Ts...>::type)this->base_function(xs...)(BOOST_HOF_FORWARD(Ts)(xs)...);
    };
};

#if BOOST_HOF_HAS_VARIABLE_TEMPLATES
namespace result_detail {
template<class Result>
struct result_f
{
    template<class F>
    constexpr result_adaptor<Result, F> operator()(F f) const
    {
        return result_adaptor<Result, F>(boost::hof::move(f));
    }
};

}

template<class Result>
static constexpr auto result = result_detail::result_f<Result>{};
#else
template<class Result, class F>
constexpr result_adaptor<Result, F> result(F f)
{
    return result_adaptor<Result, F>(boost::hof::move(f));
}
#endif

}} // namespace boost::hof

#endif

/* result.hpp
PTOjLcaLTy3nY+d3qxWpufWc+Cpsw4uiS9fDNPQLcmjSC0gIElyFbhvUH14Y+cH0OVQ70oUfxUE419IdnH9mTbzJ0As/WkucWtT05LVWwwg/XFvQRG65z2K7eHNqFArSIv1CbdpLsjpbPEdZ9ifDENt8B9NW7FvhJiba2j3rYcHPcPAOf+seb8WOsVyD7cEWwxw9L+s9YFsbjGJnPIm7pxoUu8abXTqu1z2de1GL4re1vzvHHiA4J580wrBmuXmx0yTN8B2Db23FxaavJXTpR1dDzKcWwPmb14TqgQdSpNhwUsnOv8o8Jv2wSfQQf4MnRu3BDFxj1T9QSwMECgAAAAgALWdKUicuSMRcGwAAvn4AACUACQBjdXJsLW1hc3Rlci9wYWNrYWdlcy9PUzQwMC9vczQwMHN5cy5jVVQFAAG2SCRg7T1pd9tGkt/1Kzqe9xySpixFmw87YeRZSmIcPutwRMm5HwYCmiJsEIDRoGVl4v++VdUHunGRkpxMvDvKQbDRXXdVV5/cGXy8vy02YGv/PPrPgz/4pBYv8/Q1D4rm2p73O5P/QKtf4HMdkh1WNvnd67P1TX5nPWriKSxf47PnrUP0C9KG/9vBlr94+Agl0AxbHqbZbR5dLwrWO+yzL/7+9/9m22xvd293
*/