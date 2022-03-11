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