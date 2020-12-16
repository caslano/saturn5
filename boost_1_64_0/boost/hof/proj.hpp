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
53k9TdyLFssuda2MXQCyGAOdVtaKcSu5GLXNyhiRjDpiFwbtK2NEQShHA+6KWpG3Ud2EvK+dCrMOxyvmsCWybe5sUkbLSyUNOFqlV+UrJfRLUHarMmCUOexJOXbEFk0R510pw32tfJC+54hrb6fveSKMb/+t88jyZr64ncnI1VFtaBo3xKUC96ug/tVJ4fhnkQ+/qLtBReQ3gvnHfVvQ1zdshvaVP1ufTuY/W5vcyfwIz5J/XXBnSv7G7GL4r1LzK0PfmNtpsQb7+enqt//xKlIx/0BpCkz4fqmyBHKEtkHeIYKBDzQHhCpaztabcctNfLmgx9Ba2qyp5pS6T4Iw7C6egiLM7NIGM39cZCLbVxkP1n6d4VkBBlPWeA/5Sw2Cyv3k8jbQW0yVyruuHMTx+vARtVH/e1K230eqfT+5IxW8Rjo8q2+ILMPx+Kmsoqr9Ab+CVEZ/d2H8Qatw+GTENJzxpD79YlvFckwIB2mNpZU2/ZvB5cxaY90+YUXcFncr0dtqol8M/+WR+v+xhZg1OBut3BntjQmUUPzo8eoNeumQKCuKp9i+RCJZFzdS/hX/CMkmNLc/jXGx/q6U7Q+YbP+lt6eFi/KH072f1yfjsWCAnSKPhuGvHQcp8sKSuGYds+hfPcKDXYXKYEcx5FqRF/A65GE/Z9L66oT7FFsdReebSBQ7NsT9meG2eo34ziOGQAO4W3Tca9xV/5p2rlsdbCuIschE4iSvRnyPVMwfKA8wXgq0Ufy+WHavshI7C+vuCSCRXcLkQsXp70ahAcSXyMG+s9AoQyLsVmDCysm8kBj2I8QCIsvmW4A0J4SG/jEZAc+nqy5kAAGT3/niijXG9ZffIY39bFbloioXVcXhssXNelXU/i6uKrReDzHajniNYy7GSX20Kk8sW8C4tMYcI+6UeGSD4YG0ZOfy82E24f0RYfOKm4yzhwEwRgIZHhFdyAjG0RsiEDOI8ImrEhE0PIXlajIvV+S6qtIrvgUwgYTzuleSHVc7jCBHjmPuqK/4UfzG+CfevSNJfmwyw3couJoPJvhPkuGMX8mfz5kscBV+Bf+ZCa7wK/h1JjjzAyz7fIoZmTTTOtZtC/fAD5v08xO2W8KZZXgGy8/Rf5J39kU2/MiIhF2WMP3Kj4TBTM/ErzLN7YDDxnAPSAjOLdCIz+IEa7g3J5RZW/bhasKslRfxsj5DPIJlwoMz/sF+JuzY59f+epM99pgfmeyfVyU/59xjuv99l+n+t8n++g4TfORlyc8rTfVdaSp/v+m5oyn5efwlpvvZJnoHJ9e/tag6Wb6YQ88m/kx5xMc/SMV/GSY3jDenhYsND6Tjz6q88U90/iBpvM4xw/+YDOfyajx+/sBh43VOIvy1w+BbDyW/L/NXNvQiPvYYBc8eCy+ltIEdqY2hc2b65ZyGe0j0g07H6VsxK/+sSTigZudaKsK1R+y9hCV+8jQ03SrdkOVGSuDiPYDwVr+Vcb1qvTpvFj0lZ8rXWerrOksd0YatmF3c/m2D2bbGIZrb7iM/mpv/YiWJIQ/sv4HFQQrfe1EtSyXDf0j2Z8UUpFAqVQE6cx2WDzsAnqjfjmlz7zXK3uPSgAUgumdTUyVGSlzYpL1IXVAphiGBWWbDfeQyyisycVVa2e6e7rdsd7m4zs/uZM5bxM46bBa1OhTD2a5Va5tdT32BM/w+/nVoNoTtvZFfzu9S5X+L8v7nqV3HnA8B71z/3VLAu5yXHLgkputP/0HubP5I+Qj7QQrITzf/h/bUo9cvOd0rPuiuHoajg2TcjTF4XRf1FVo76y0r7YWt449wvd4bmCPfPUdcf5txfzA4Qvz6Lt2KPF/svRA/3SRt5IAcamk=
*/