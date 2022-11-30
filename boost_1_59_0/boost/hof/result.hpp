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
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
*/