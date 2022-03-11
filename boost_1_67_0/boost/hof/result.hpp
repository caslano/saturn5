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