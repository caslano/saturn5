/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    fix.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_FIX_H
#define BOOST_HOF_GUARD_FUNCTION_FIX_H

/// fix
/// ===
/// 
/// Description
/// -----------
/// 
/// The `fix` function adaptor implements a fixed-point combinator. This can be
/// used to write recursive functions. 
/// 
/// When using `constexpr`, a function can recurse to a depth that is defined by
/// `BOOST_HOF_RECURSIVE_CONSTEXPR_DEPTH`(default is 16). There is no limitiation on
/// recursion depth for non-constexpr functions. In addition, due to the
/// eagerness of `constexpr` to instantiation templates, in some cases, an
/// explicit return type must be specified in order to avoid reaching the
/// recursion limits of the compiler. This can be accomplished using
/// [`boost::hof::result`](/include/boost/hof/result):
/// 
///     int r = boost::hof::result<int>(factorial)(5);
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     constexpr fix_adaptor<F> fix(F f);
/// 
/// Semantics
/// ---------
/// 
///     assert(fix(f)(xs...) == f(fix(f), xs...));
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [ConstFunctionObject](ConstFunctionObject)
/// * MoveConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     int main() {
///         auto factorial = boost::hof::fix(
///             [](auto recurse, auto x) -> decltype(x) { 
///                 return x == 0 ? 1 : x * recurse(x-1); 
///             }
///         );
///         int r = boost::hof::result<int>(factorial)(5);
///         assert(r == 5*4*3*2*1);
///     }
/// 
/// References
/// ----------
/// 
/// * [Fixed-point combinator](https://en.wikipedia.org/wiki/Fixed-point_combinator)
/// * [Recursive](Recursive)
/// 

#include <boost/hof/always.hpp>
#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/reveal.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>
#include <boost/hof/indirect.hpp>
#include <boost/hof/result.hpp>
#include <boost/hof/detail/recursive_constexpr_depth.hpp>


namespace boost { namespace hof {

namespace detail{

template<class F>
struct compute_indirect_ref
{ typedef indirect_adaptor<const F*> type; };

template<class F>
struct compute_indirect_ref<indirect_adaptor<F*>>
{ typedef indirect_adaptor<F*> type; };

template<class F>
constexpr indirect_adaptor<const F*> make_indirect_ref(const F& f) noexcept
{
    return indirect_adaptor<const F*>(&f);
}

template<class F>
constexpr indirect_adaptor<const F*> make_indirect_ref(const indirect_adaptor<F*>& f) noexcept
{
    return f;
}

template<class F, class=void>
struct fix_result
{
    template<class... Ts>
    struct apply
    { 
        typedef decltype(std::declval<F>()(std::declval<Ts>()...)) type; 
    };
};

template<class F>
struct fix_result<F, typename holder<
    typename F::result_type
>::type>
{
    template<class...>
    struct apply
    { 
        typedef typename F::result_type type; 
    };
    
};

template<class F, class Result, int N>
struct fix_adaptor_base : F
{
    BOOST_HOF_INHERIT_CONSTRUCTOR(fix_adaptor_base, F);

    typedef typename compute_indirect_ref<F>::type base_ref_type;
    typedef fix_adaptor_base<base_ref_type, Result, N-1> derived;


    template<class... Ts>
    constexpr const F& base_function(Ts&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    template<class... Ts>
    constexpr derived derived_function(Ts&&... xs) const noexcept
    {
        return derived(boost::hof::detail::make_indirect_ref(this->base_function(xs...)));
    }

    struct fix_failure
    {
        template<class Failure>
        struct apply
        {
            template<class... Ts>
            struct of
            : Failure::template of<derived, Ts...>
            {};
        };
    };

    struct failure
    : failure_map<fix_failure, F>
    {};


    BOOST_HOF_RETURNS_CLASS(fix_adaptor_base);

    template<class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(const F&, id_<derived>, id_<Ts>...) 
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        BOOST_HOF_MANGLE_CAST(const F&)(BOOST_HOF_CONST_THIS->base_function(xs...))
            (
                BOOST_HOF_MANGLE_CAST(derived)(BOOST_HOF_CONST_THIS->derived_function(xs...)), 
                BOOST_HOF_FORWARD(Ts)(xs)...
            )
    );
};

template<class F, class Result>
struct fix_adaptor_base<F, Result, 0> : F
{
    BOOST_HOF_INHERIT_CONSTRUCTOR(fix_adaptor_base, F);

    template<class... Ts>
    const F& base_function(Ts&&...) const noexcept
    {
        return *this;
    }

    struct fix_failure
    {
        template<class Failure>
        struct apply
        {
            template<class... Ts>
            struct of
            : Failure::template of<fix_adaptor_base, Ts...>
            {};
        };
    };

    struct failure
    : failure_map<fix_failure, F>
    {};


    BOOST_HOF_RETURNS_CLASS(fix_adaptor_base);

    template<class... Ts>
    typename Result::template apply<fix_adaptor_base, Ts...>::type
    operator()(Ts&&... xs) const
    {
        return this->base_function(xs...)(*this, BOOST_HOF_FORWARD(Ts)(xs)...);
    }
};
}

template<class F>
struct fix_adaptor : detail::fix_adaptor_base<F, detail::fix_result<F>, BOOST_HOF_RECURSIVE_CONSTEXPR_DEPTH>
{
    typedef fix_adaptor fit_rewritable1_tag;
    typedef detail::fix_adaptor_base<F, detail::fix_result<F>, BOOST_HOF_RECURSIVE_CONSTEXPR_DEPTH> base;
    BOOST_HOF_INHERIT_CONSTRUCTOR(fix_adaptor, base);
};

template<class Result, class F>
struct result_adaptor<Result, fix_adaptor<F>>
: fix_adaptor<result_adaptor<Result, F>>
{
    typedef fix_adaptor<result_adaptor<Result, F>> base;
    BOOST_HOF_INHERIT_CONSTRUCTOR(result_adaptor, base)
};

BOOST_HOF_DECLARE_STATIC_VAR(fix, detail::make<fix_adaptor>);

}} // namespace boost::hof

#endif

/* fix.hpp
cZJ4z0ni3SeJd54QD0HY9V7LXpiaYB/J1B7xq7/GLOcB9lMyQAOvz95i9g3x1avGDsPac4Jea6JKJIIdTXbazc+Z+oRxRWW3BGtGf2qwZiRb9fxbNigJlBscYpSxhMvIOalO0tpTzR3+ubdpjNCz9VI2q9YYBsxFnZ77FBFwf2PP+AMVblI7Qp1rtO13uNziTwyfdqvBBWH1LrUcPVTPDs932kK9+ES1UUS1zv4avcxJpbqRYBjCK8V3dynvgm0EOIcOpQRgebRQyEOy/rkcF0Nv/tZzBzvLt8ALtBu12V9FUHcBrteEW8L22Ozi+e5QP4oWL7ynQLsZNJVbTK7CiBwvmuUGA6x+v+qLTyMUcmlwNuveg8D1eM5joPCBBLwjHI/XDtT2KGEHUXcz2va7jTCAaIORFou5I9Zx27J3xOm1Stsf6o9SilnlV49npPxKXc9S54X1f9M6P8lnV/RC4oTR+ock3EfXX6rmB5njaX4Qvs59fNB7eju6gJLnCAczXD+CxyFeMl1Lv4UQrBsR72pkPW0iPWMTjH9j4NtWTpF9S38s76t0PZ+NpaPc+FvSnF4pvz3q21NRlF27C3RTZ3k9wVMJb1Sv9OhTMGAst01fZvdtUNGrzOjcdNG1RnR8Hh1e5tXeb+jmDnbyi/MeiMWBRVJY9we41UpmuhdcjrORVPteF77MbQ/egDb+ISnKw9HEyFbg18rlW6lfm0TNniXGsI1jsPQtURjse8tEsGQnjvDtYhZ8bfNvgTLmCr21XmbgDQyp78vS73xdqb9mqsiT3ZxmUL4NxvRp9Vux/855Zqf6GOfXwq7QRaz7K0k+B138yJ4YJJjSpt9fkWcPVQaLuM7UU5+R/hzhMZm1hcESI9gt1iI4ONr4zBWr6PNi49MjlnImb3C8IQ5rZSGtC0K+NA06dF++pFZN0GaD6A9GlR43PVolT5PE6Z2rU1LdaaaaNj26eAF7kH4dGqFfLBmc+bsq/q40PHq0NWZ2jbOPl9kr0DNq3yaVGuTw0K/lr6BGUM+i2YOHdrMwdfuKmvcUdbsExJN80pUDDgmML81AcK5v5KbcyEwPi13t2Zi6LGoR0i+V6esroNwDcfZzOCOySdmreiXbq6a9qDzbmZb51Ox58JsNdQgfzwhlhY9n1vYHffsEZxl8z7kGqlwzps2MJqxc67arUzv7+LZE5juK4XAWKXTdszFyZU5kYh71NBw3OmPa6ViipH8SLcOn/tWIfAj85FboI7a/q1rBFRBDjjFVecpEbeBFG+CnAGvh+BkcqZRt8f4zibbYERCHjqq2aIP+25DP/t9b2YIyGA4SBMbVBWfgkeJod3WB8QfXsGYRw5TyqdX1ud7LYVViDlzUDrhBqKEr4v90wJriO2LJ53+9lfy9+e3kb9czyd/fxFCSyg84vehDuR4v4Cndg/ys8Ra6lj6XxsmFfcTsOX0wKXWsR71GfLGqj5sddXYAaRX1JByfZKAMiXePcbIcOuzinjdk8bvt/oDcgOdgX3QYIwPiz5ADfu0uCGWZU5RAI0suJJfOCvKnFuJGIVJDeTogfJhV0eaxcWzacC53jups3GM80T5qsnFv2KbUe4xDXu3XCcAvvpIKGMoacJwhXZujqq7Hnjbq2p1IkZKDUP3tdguqfNZqJqN6Ohx/ag9v7AjTQWEbjkqXvXkFEkHeGje+Rczbdr2hPH+dLn25gkbXdbjaW/sUBGzMmoOSKH+8+zqUpo94RJa5liCg9+HSTGIXB39r1+C/4P5496tXYmkB8FdwmrO0BiovhvLWUnGyKDTmWk0VYovv4A/yDj6t86mDQJBQ0zsZxZRsDnWYGu/+rORpYGlEz04XrW7H+ek=
*/