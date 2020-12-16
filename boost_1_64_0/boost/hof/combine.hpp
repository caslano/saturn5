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
N7ufsPswiDa+RpReKrltp+uuHBijfHuM3Tv5AfxXJJYP4wbnqT1qM6FJO/YNm9zb1EEqzZLdaNBMR/4/jbSSn5wO0QJzvNwCvj3Nj239P3rIBiD38IBovbRf3819IZf+xKs+xXj5fhHqsNf02+kh97Js7qE2GGW9YKf650+xwcLymVSMYdFrg6RlecOyqd7hbXR42XCurUNLm2jUjTRN6BGHtzlHd3jhF9E3fDB7kcfPKUYVK0RG8hhwVdpm6Yl+xCWrZilAs7x3tmyWDW2UHUQvppTtkGVcXTNMUaoUXh1S0CKVLx0aK+BAwLkVGl6gcblCIyrtIa3Ch+SwNNrl2jUorIrZs5fCo3Z0ujGoO0AjtUUu/PUshlsjLpF7vuXqER2P95JDtjcZc0enq8fm4amF1avCjl1uKayGt9p2l7Mxs08dqhHvJlKd/rJdFRnYc3y7GtwkXLa1df9ZrVP6zwC9gHi4W4K1r1ufRwU1tlVKufw4ICh4bY34Q0c5OMXjtOH0510VR+bW/IUACa2DrG10BhYpNfIpZZIGF2k/lvScj94W0LyHEJYhxrEOjz2aQ81s//naZqK/3TRGjj/ugLZMMY/aB4eB/s0hio2GpWOj18FlyGdp+Z/0l8PL73mRuKxEDiAO+IkMScc69ScUcLksoPmGgFg7weg+oZekO+KPVcDCMtrujAa7qFxKmIlOWorRJ2K1cVoXlWs01IvSXor8PaBcTJ2glIsoKulmLXE6y/SAKK4ArghE6pnT0suNj4amYvtAP4nt+q3/9YfES9ChfWoViFoWWUlzoy2mz9BWH7CkL2olveSHmaNJ3+Oz/3dpIcCqtnKEePECJd7G+MV3io19VEt3pW/dPxeCXiFFr2rQK9RX0kurCVSBvTaOVw16GTUoFMfrxslFZSwrodHQpGUOkkGlNlMGhcZhO+Y1Y1SzwlP6XtL/KkVoPIeVHKx7WjXuzBncuNjPVW427vQWGjcjCVka/oHvS3kS36e2nvFHG91gGTduGGwQNv2c4Tr0Q2RIHirOzVNDBQ1+Ui25XW7fasPJbEnjfUArtPLVrkEKmzHpsHkX6/ycQWEzGNjc18eQ+ftGmdI86hdvTUqI1J5SW7jZf8II8ILM0zZNwYK/bz9JfdIIJmp+IBRg9PMGtSq1PIS+X6EfAO4f9DYmX4xyr04GV6bXqd+7IDX7r6zZuYqxyuQq7tU3tb1madun1No+Jee32j4jCcPSlPY51Mton3njErQmnvGL18YkeldPOUp//8IT2mjsuFNuoxPkkV3baa3Hg7aW5VHTA2OT/Q/vLU3+HjUm+TuUkl5LSd8hJf3MccnfRSnpF2GmlIK/+hPPFBi+L7jisPSZ7TRyLveM6m34pl5pH/VNQ094MWPJLoueMA1N1sPsrCP7Wxa+Gt5GKW1UWkImNmIEk9Dp23CqbZKOtY+Dr4h/Fd/kg2829mS+OaH4dIz3fJr8d7SQPz7iGvi+CUc71dl6axTgF7PIQ8czog/tov0m81zaVUnWCJrccnc1zjfmNXJ5nI/oeRZtetoEvdTYshG6XAfRMRz619OJGz8+HjM2GhTwaRs03006b+NmM0E73vjbnOHbH8zXHsnwYDCZJW1jAXHpCGOWP+00ugS7fwXYYPZ8R0WDdg3+Vd3cze39Yn42h5FO69ecmR5oKPeT0p7Pr6vwqt/qQN8JOmrEd87itNgydtFk+RYQgawE5dqEXcMSHv+HW/3byXdXpwuJ2b+df6UTeo5GUX7xLpRSfOb6tfdBmhpxdLjlauI8Bk5u5pUjyc18ycnmM07Q4vEOihYepoWsPLP6/cOZ7pDQ07hyDktcWMa1Us8qPksUeu5uxvQ=
*/