/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    limit.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_LIMIT_H
#define BOOST_HOF_GUARD_LIMIT_H

/// limit
/// =====
/// 
/// Description
/// -----------
/// 
/// The `limit` function decorator annotates the function with the max number
/// of parameters. The `limit_c` version can be used to give the max number
/// directly(instead of relying on an integral constant). The parameter limit
/// can be read by using the [`function_param_limit`](function_param_limit)
/// trait. Using `limit` is useful to improve error reporting with partially
/// evaluated functions.
/// 
/// Synopsis
/// --------
/// 
///     template<class IntegralConstant>
///     constexpr auto limit(IntegralConstant);
/// 
///     template<std::size_t N, class F>
///     constexpr auto limit_c(F);
/// 
/// Requirements
/// ------------
/// 
/// IntegralConstant must be:
/// 
/// * IntegralConstant
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
///     using namespace boost::hof;
/// 
///     struct sum_f
///     {
///         template<class T>
///         int operator()(T x, T y) const
///         {
///             return x+y;
///         }
///     };
///     BOOST_HOF_STATIC_FUNCTION(sum) = limit_c<2>(sum_f());
/// 
///     int main() {
///         assert(3 == sum(1, 2));
///     }
/// 
/// See Also
/// --------
/// 
/// * [Partial function evaluation](<Partial function evaluation>)
/// * [function_param_limit](function_param_limit)
/// 

#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/detail/forward.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/static_const_var.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/function_param_limit.hpp>

namespace boost { namespace hof {

namespace detail {
// TODO: Make this work with fit_rewritable1_tag
template<std::size_t N, class F>
struct limit_adaptor : detail::callable_base<F>
{
    typedef std::integral_constant<std::size_t, N> fit_function_param_limit;
    BOOST_HOF_INHERIT_CONSTRUCTOR(limit_adaptor, detail::callable_base<F>)

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    BOOST_HOF_RETURNS_CLASS(limit_adaptor);

    template<class... Ts, class=typename std::enable_if<(sizeof...(Ts) <= N)>::type>
    constexpr BOOST_HOF_SFINAE_RESULT(const detail::callable_base<F>&, id_<Ts>...) 
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        (BOOST_HOF_MANGLE_CAST(const detail::callable_base<F>&)(BOOST_HOF_CONST_THIS->base_function(xs...)))
            (BOOST_HOF_FORWARD(Ts)(xs)...)
    );

};

template<std::size_t N>
struct make_limit_f
{
    constexpr make_limit_f()
    {}
    template<class F>
    constexpr limit_adaptor<N, F> operator()(F f) const
    {
        return limit_adaptor<N, F>(static_cast<F&&>(f));
    }
};

struct limit_f
{
    template<class IntegralConstant, std::size_t N=IntegralConstant::type::value>
    constexpr make_limit_f<N> operator()(IntegralConstant) const
    {
        return {};
    }
};

}

template<std::size_t N, class F>
constexpr detail::limit_adaptor<N, F> limit_c(F f)
{
    return detail::limit_adaptor<N, F>(static_cast<F&&>(f));
}

BOOST_HOF_DECLARE_STATIC_VAR(limit, detail::limit_f);

}} // namespace boost::hof

#endif

/* limit.hpp
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
*/