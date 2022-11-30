/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    combine.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_COMBINE_H
#define BOOST_HOF_GUARD_COMBINE_H

/// combine
/// =======
/// 
/// Description
/// -----------
/// 
/// The `combine` function adaptor combines several functions together with
/// their arguments. It essentially zips each function with an argument before
/// calling the main function.
/// 
/// Synopsis
/// --------
/// 
///     template<class F, class... Gs>
///     constexpr combine_adaptor<F, Gs...> combine(F f, Gs... gs);
/// 
/// Semantics
/// ---------
/// 
///     assert(combine(f, gs...)(xs...) == f(gs(xs)...));
/// 
/// Requirements
/// ------------
/// 
/// F and Gs must be:
/// 
/// * [ConstInvocable](ConstInvocable)
/// * MoveConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     #include <tuple>
///     #include <utility>
/// 
///     int main() {
///         auto f = boost::hof::combine(
///             boost::hof::construct<std::tuple>(),
///             boost::hof::capture(1)(boost::hof::construct<std::pair>()),
///             boost::hof::capture(2)(boost::hof::construct<std::pair>()));
///         assert(f(3, 7) == std::make_tuple(std::make_pair(1, 3), std::make_pair(2, 7)));
///     }
/// 

#include <boost/hof/pack.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/detail/make.hpp>

namespace boost { namespace hof { namespace detail {

template<class S, class F, class... Gs>
struct combine_adaptor_base;

template<std::size_t... Ns, class F, class... Gs>
struct combine_adaptor_base<seq<Ns...>, F, Gs...>
: F, pack_base<seq<Ns...>, Gs...>
{
    typedef pack_base<seq<Ns...>, Gs...> base_type;

    BOOST_HOF_INHERIT_DEFAULT(combine_adaptor_base, base_type, F)

    template<class X, class... Xs, 
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(F, X),
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(base_type, Xs...)>
    constexpr combine_adaptor_base(X&& x, Xs&&... xs) 
    : F(BOOST_HOF_FORWARD(X)(x)), base_type(BOOST_HOF_FORWARD(Xs)(xs)...)
    {}

    template<class... Ts>
    constexpr const F& base_function(Ts&&... xs) const
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    BOOST_HOF_RETURNS_CLASS(combine_adaptor_base);

// Result needs to be calculated in a separate class to avoid confusing the
// compiler on MSVC
#if BOOST_HOF_NO_EXPRESSION_SFINAE || BOOST_HOF_HAS_MANUAL_DEDUCTION
    template<class... Ts>
    struct combine_result
    : result_of<const F&,  result_of<const Gs&, id_<Ts>>...>
    {};
#endif

    template<class... Ts>
#if BOOST_HOF_NO_EXPRESSION_SFINAE || BOOST_HOF_HAS_MANUAL_DEDUCTION
    constexpr typename combine_result<Ts...>::type
#else
    constexpr auto
#endif
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_MANUAL_RETURNS
    (
        (BOOST_HOF_MANGLE_CAST(const F&)(BOOST_HOF_CONST_THIS->base_function(xs...)))
            (boost::hof::alias_value<pack_tag<seq<Ns>, Gs...>, Gs>(*BOOST_HOF_CONST_THIS, xs)(BOOST_HOF_FORWARD(Ts)(xs))...)
    );
};

}

template<class F, class... Gs>
struct combine_adaptor
: detail::combine_adaptor_base<typename detail::gens<sizeof...(Gs)>::type, detail::callable_base<F>, detail::callable_base<Gs>...>
{
    typedef detail::combine_adaptor_base<typename detail::gens<sizeof...(Gs)>::type, detail::callable_base<F>, detail::callable_base<Gs>...> base_type;
    BOOST_HOF_INHERIT_CONSTRUCTOR(combine_adaptor, base_type)
};

BOOST_HOF_DECLARE_STATIC_VAR(combine, detail::make<combine_adaptor>);

}} // namespace boost::hof

#endif

/* combine.hpp
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
*/