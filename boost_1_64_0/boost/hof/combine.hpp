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
Ejkr42d+1SOQbC1sJgfSsrVAlfZ1geAMU5uURRSUCdYoyl6h1D4VGZg1lpxXb7k3wpuC5Th0GLIYCS39S6LiOSfAhPMc7km3SmkRaahyvdrIfu2FeWWj0bhmIl+xerBAM1Wh9ke1+44MSrNp4Qax0Skcluj1uvKjX9U/Ddqkc1ogCreDE5vYQfqpdrO0CZjuE7b4Q4wb1TRdPI1eTbm4B2vA66eJx3TzkMcLlvFXYrCrUJAHS+nJpw1JAiNTAW3/9aGPgbqBedhMsMAryz3lu3zmU8aCUP/wCddCfTi53xhV+/6NQjQVjwcq+vn3QTYqQF+XLBg9du/34EzfOQTWipiwiNdXFKDQNdjioKenEahMN0H5C8HMC5L4wSKnL0OAnh/fQxyU4W/0cFy1t+2JBHyT2JMRTRdpfHnqqxGw8SFX5f27irVDrVVPF31m83DvoUKmXc94heCIvfwwYXjFn8Dsx9Ga5n5wZFXkO0yki2hnsSgaBZTR4U8UpkcqW0bkRdZ/mmgrzolf322FyPez9iPLqD5aBwdmTYej3wF1XCxe9bmXkdUSrCEBew==
*/