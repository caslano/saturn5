/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    proj.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_ON_H
#define BOOST_HOF_GUARD_FUNCTION_ON_H

/// proj
/// ====
/// 
/// Description
/// -----------
/// 
/// The `proj` function adaptor applies a projection onto the parameters of
/// another function. This is useful, for example, to define a function for
/// sorting such that the ordering is based off of the value of one of its
/// member fields. 
/// 
/// Also, if just a projection is given, then the projection will be called
/// for each of its arguments.
/// 
/// Note: All projections are always evaluated in order from left-to-right.
/// 
/// Synopsis
/// --------
/// 
///     template<class Projection, class F>
///     constexpr proj_adaptor<Projection, F> proj(Projection p, F f);
/// 
///     template<class Projection>
///     constexpr proj_adaptor<Projection> proj(Projection p);
/// 
/// Semantics
/// ---------
/// 
///     assert(proj(p, f)(xs...) == f(p(xs)...));
///     assert(proj(p)(xs...) == p(xs)...);
/// 
/// Requirements
/// ------------
/// 
/// Projection must be:
/// 
/// * [UnaryInvocable](UnaryInvocable)
/// * MoveConstructible
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
///     struct foo
///     {
///         foo(int x_) : x(x_)
///         {}
///         int x;
///     };
/// 
///     int main() {
///         assert(boost::hof::proj(&foo::x, _ + _)(foo(1), foo(2)) == 3);
///     }
/// 
/// References
/// ----------
/// 
/// * [Projections](Projections)
/// * [Variadic print](<Variadic print>)
/// 



#include <utility>
#include <boost/hof/always.hpp>
#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/detail/result_of.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>
#include <boost/hof/detail/compressed_pair.hpp>
#include <boost/hof/detail/result_type.hpp>
#include <boost/hof/apply_eval.hpp>

namespace boost { namespace hof {

namespace detail {

template<class T, class Projection>
struct project_eval
{
    T&& x;
    const Projection& p;

    template<class X, class P>
    constexpr project_eval(X&& xp, const P& pp) : x(BOOST_HOF_FORWARD(X)(xp)), p(pp)
    {}

    constexpr auto operator()() const BOOST_HOF_RETURNS
    (p(BOOST_HOF_FORWARD(T)(x)));
};

template<class T, class Projection>
constexpr project_eval<T, Projection> make_project_eval(T&& x, const Projection& p)
{
    return project_eval<T, Projection>(BOOST_HOF_FORWARD(T)(x), p);
}

template<class T, class Projection>
struct project_void_eval
{
    T&& x;
    const Projection& p;

    template<class X, class P>
    constexpr project_void_eval(X&& xp, const P& pp) : x(BOOST_HOF_FORWARD(X)(xp)), p(pp)
    {}

    struct void_ {};

    constexpr void_ operator()() const
    {
        return p(BOOST_HOF_FORWARD(T)(x)), void_();
    }
};

template<class T, class Projection>
constexpr project_void_eval<T, Projection> make_project_void_eval(T&& x, const Projection& p)
{
    return project_void_eval<T, Projection>(BOOST_HOF_FORWARD(T)(x), p);
}

template<class Projection, class F, class... Ts, 
    class R=decltype(
        std::declval<const F&>()(std::declval<const Projection&>()(std::declval<Ts>())...)
    )>
constexpr R by_eval(const Projection& p, const F& f, Ts&&... xs)
{
    return boost::hof::apply_eval(f, make_project_eval(BOOST_HOF_FORWARD(Ts)(xs), p)...);
}

#if BOOST_HOF_NO_ORDERED_BRACE_INIT
#define BOOST_HOF_BY_VOID_RETURN BOOST_HOF_ALWAYS_VOID_RETURN
#else
#if BOOST_HOF_NO_CONSTEXPR_VOID
#define BOOST_HOF_BY_VOID_RETURN boost::hof::detail::swallow
#else
#define BOOST_HOF_BY_VOID_RETURN void
#endif
#endif

template<class Projection, class... Ts>
constexpr BOOST_HOF_ALWAYS_VOID_RETURN by_void_eval(const Projection& p, Ts&&... xs)
{
    return boost::hof::apply_eval(boost::hof::always(), boost::hof::detail::make_project_void_eval(BOOST_HOF_FORWARD(Ts)(xs), p)...);
}

struct swallow
{
    template<class... Ts>
    constexpr swallow(Ts&&...)
    {}
};

}

template<class Projection, class F=void>
struct proj_adaptor;

template<class Projection, class F>
struct proj_adaptor : detail::compressed_pair<detail::callable_base<Projection>, detail::callable_base<F>>, detail::function_result_type<F>
{
    typedef proj_adaptor fit_rewritable_tag;
    typedef detail::compressed_pair<detail::callable_base<Projection>, detail::callable_base<F>> base;
    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const
    {
        return this->second(xs...);;
    }

    template<class... Ts>
    constexpr const detail::callable_base<Projection>& base_projection(Ts&&... xs) const
    {
        return this->first(xs...);
    }

    struct by_failure
    {
        template<class Failure>
        struct apply
        {
            template<class... Ts>
            struct of
            : Failure::template of<decltype(std::declval<detail::callable_base<Projection>>()(std::declval<Ts>()))...>
            {};
        };
    };

    struct failure
    : failure_map<by_failure, detail::callable_base<F>>
    {};

    BOOST_HOF_INHERIT_CONSTRUCTOR(proj_adaptor, base)

    BOOST_HOF_RETURNS_CLASS(proj_adaptor);

    template<class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(const detail::callable_base<F>&, result_of<const detail::callable_base<Projection>&, id_<Ts>>...) 
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        boost::hof::detail::by_eval(
            BOOST_HOF_MANGLE_CAST(const detail::callable_base<Projection>&)(BOOST_HOF_CONST_THIS->base_projection(xs...)),
            BOOST_HOF_MANGLE_CAST(const detail::callable_base<F>&)(BOOST_HOF_CONST_THIS->base_function(xs...)),
            BOOST_HOF_FORWARD(Ts)(xs)...
        )
    );
};

template<class Projection>
struct proj_adaptor<Projection, void> : detail::callable_base<Projection>
{
    typedef proj_adaptor fit_rewritable1_tag;
    template<class... Ts>
    constexpr const detail::callable_base<Projection>& base_projection(Ts&&... xs) const
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    BOOST_HOF_INHERIT_DEFAULT(proj_adaptor, detail::callable_base<Projection>)

    template<class P, BOOST_HOF_ENABLE_IF_CONVERTIBLE(P, detail::callable_base<Projection>)>
    constexpr proj_adaptor(P&& p) 
    : detail::callable_base<Projection>(BOOST_HOF_FORWARD(P)(p))
    {}

    BOOST_HOF_RETURNS_CLASS(proj_adaptor);

    template<class... Ts, class=detail::holder<decltype(std::declval<Projection>()(std::declval<Ts>()))...>>
    constexpr BOOST_HOF_BY_VOID_RETURN operator()(Ts&&... xs) const 
    {
#if BOOST_HOF_NO_ORDERED_BRACE_INIT
        return boost::hof::detail::by_void_eval(this->base_projection(xs...), BOOST_HOF_FORWARD(Ts)(xs)...);
#else
#if BOOST_HOF_NO_CONSTEXPR_VOID
        return
#endif
        boost::hof::detail::swallow{
            (this->base_projection(xs...)(BOOST_HOF_FORWARD(Ts)(xs)), 0)...
        };
#endif
    }
};

BOOST_HOF_DECLARE_STATIC_VAR(proj, detail::make<proj_adaptor>);

}} // namespace boost::hof
#endif

/* proj.hpp
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
*/