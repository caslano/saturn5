/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    reverse_fold.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_REVERSE_FOLD_H
#define BOOST_HOF_GUARD_REVERSE_FOLD_H

/// reverse_fold
/// ========
/// 
/// Description
/// -----------
/// 
/// The `reverse_fold` function adaptor uses a binary function to apply a
/// reverse [fold]
/// (https://en.wikipedia.org/wiki/Fold_%28higher-order_function%29)(ie right
/// fold in functional programming terms) operation to the arguments passed to
/// the function. Additionally, an optional initial state can be provided,
/// otherwise the first argument is used as the initial state.
/// 
/// The arguments to the binary function, take first the state and then the
/// argument.
/// 
/// Synopsis
/// --------
/// 
///     template<class F, class State>
///     constexpr reverse_fold_adaptor<F, State> reverse_fold(F f, State s);
/// 
///     template<class F>
///     constexpr reverse_fold_adaptor<F> reverse_fold(F f);
/// 
/// Semantics
/// ---------
/// 
///     assert(reverse_fold(f, z)() == z);
///     assert(reverse_fold(f, z)(x, xs...) == f(reverse_fold(f, z)(xs...), x));
///     assert(reverse_fold(f)(x) == x);
///     assert(reverse_fold(f)(x, xs...) == f(reverse_fold(f)(xs...), x));
/// 
/// Requirements
/// ------------
/// 
/// State must be:
/// 
/// * CopyConstructible
/// 
/// F must be:
/// 
/// * [BinaryInvocable](BinaryInvocable)
/// * MoveConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     struct max_f
///     {
///         template<class T, class U>
///         constexpr T operator()(T x, U y) const
///         {
///             return x > y ? x : y;
///         }
///     };
/// 
///     int main() {
///         assert(boost::hof::reverse_fold(max_f())(2, 3, 4, 5) == 5);
///     }
/// 
/// References
/// ----------
/// 
/// * [Projections](Projections)
/// * [Variadic print](<Variadic print>)
/// 

#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/compressed_pair.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof { namespace detail {

struct v_reverse_fold
{
    BOOST_HOF_RETURNS_CLASS(v_reverse_fold);
    template<class F, class State, class T, class... Ts>
    constexpr BOOST_HOF_SFINAE_MANUAL_RESULT(const F&, result_of<const v_reverse_fold&, id_<const F&>, id_<State>, id_<Ts>...>, id_<T>)
    operator()(const F& f, State&& state, T&& x, Ts&&... xs) const BOOST_HOF_SFINAE_MANUAL_RETURNS
    (
        f((*BOOST_HOF_CONST_THIS)(f, BOOST_HOF_FORWARD(State)(state), BOOST_HOF_FORWARD(Ts)(xs)...), BOOST_HOF_FORWARD(T)(x))
    );

    template<class F, class State>
    constexpr State operator()(const F&, State&& state) const noexcept
    {
        return BOOST_HOF_FORWARD(State)(state);
    }
};

}

template<class F, class State=void>
struct reverse_fold_adaptor
: detail::compressed_pair<detail::callable_base<F>, State>
{
    typedef detail::compressed_pair<detail::callable_base<F>, State> base_type;
    BOOST_HOF_INHERIT_CONSTRUCTOR(reverse_fold_adaptor, base_type)

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const noexcept
    {
        return this->first(xs...);
    }

    template<class... Ts>
    constexpr State get_state(Ts&&... xs) const noexcept
    {
        return this->second(xs...);
    }

    BOOST_HOF_RETURNS_CLASS(reverse_fold_adaptor);

    template<class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(detail::v_reverse_fold, id_<const detail::callable_base<F>&>, id_<State>, id_<Ts>...)
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        detail::v_reverse_fold()(
            BOOST_HOF_MANGLE_CAST(const detail::callable_base<F>&)(BOOST_HOF_CONST_THIS->base_function(xs...)), 
            BOOST_HOF_MANGLE_CAST(State)(BOOST_HOF_CONST_THIS->get_state(xs...)), 
            BOOST_HOF_FORWARD(Ts)(xs)...
        )
    )
};


template<class F>
struct reverse_fold_adaptor<F, void>
: detail::callable_base<F>
{
    BOOST_HOF_INHERIT_CONSTRUCTOR(reverse_fold_adaptor, detail::callable_base<F>)

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    BOOST_HOF_RETURNS_CLASS(reverse_fold_adaptor);

    template<class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(detail::v_reverse_fold, id_<const detail::callable_base<F>&>, id_<Ts>...)
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        detail::v_reverse_fold()(
            BOOST_HOF_MANGLE_CAST(const detail::callable_base<F>&)(BOOST_HOF_CONST_THIS->base_function(xs...)), 
            BOOST_HOF_FORWARD(Ts)(xs)...
        )
    )
};

BOOST_HOF_DECLARE_STATIC_VAR(reverse_fold, detail::make<reverse_fold_adaptor>);

}} // namespace boost::hof

#endif

/* reverse_fold.hpp
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
*/