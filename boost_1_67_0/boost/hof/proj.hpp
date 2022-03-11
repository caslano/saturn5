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