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
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
*/