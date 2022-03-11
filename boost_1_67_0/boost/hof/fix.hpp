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