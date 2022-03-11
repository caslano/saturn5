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