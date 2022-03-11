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