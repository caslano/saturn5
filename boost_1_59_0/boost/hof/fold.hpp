/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    fold.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FOLD_H
#define BOOST_HOF_GUARD_FOLD_H

/// fold
/// ========
/// 
/// Description
/// -----------
/// 
/// The `fold` function adaptor uses a binary function to apply a
/// [fold](https://en.wikipedia.org/wiki/Fold_%28higher-order_function%29)
/// operation to the arguments passed to the function. Additionally, an
/// optional initial state can be provided, otherwise the first argument is
/// used as the initial state.
/// 
/// The arguments to the binary function, take first the state and then the
/// argument.
/// 
/// Synopsis
/// --------
/// 
///     template<class F, class State>
///     constexpr fold_adaptor<F, State> fold(F f, State s);
/// 
///     template<class F>
///     constexpr fold_adaptor<F> fold(F f);
/// 
/// Semantics
/// ---------
/// 
///     assert(fold(f, z)() == z);
///     assert(fold(f, z)(x, xs...) == fold(f, f(z, x))(xs...));
///     assert(fold(f)(x) == x);
///     assert(fold(f)(x, y, xs...) == fold(f)(f(x, y), xs...));
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
///     int main() {
///         assert(boost::hof::fold(max_f())(2, 3, 4, 5) == 5);
///     }
/// 
/// References
/// ----------
/// 
/// * [Fold](https://en.wikipedia.org/wiki/Fold_(higher-order_function))
/// * [Variadic sum](<Variadic sum>)
/// 

#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/compressed_pair.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof { namespace detail {

struct v_fold
{
    BOOST_HOF_RETURNS_CLASS(v_fold);
    template<class F, class State, class T, class... Ts>
    constexpr BOOST_HOF_SFINAE_MANUAL_RESULT(const v_fold&, id_<const F&>, result_of<const F&, id_<State>, id_<T>>, id_<Ts>...)
    operator()(const F& f, State&& state, T&& x, Ts&&... xs) const BOOST_HOF_SFINAE_MANUAL_RETURNS
    (
        (*BOOST_HOF_CONST_THIS)(f, f(BOOST_HOF_FORWARD(State)(state), BOOST_HOF_FORWARD(T)(x)), BOOST_HOF_FORWARD(Ts)(xs)...)
    );

    template<class F, class State>
    constexpr State operator()(const F&, State&& state) const noexcept
    {
        return BOOST_HOF_FORWARD(State)(state);
    }
};

}

template<class F, class State=void>
struct fold_adaptor
: detail::compressed_pair<detail::callable_base<F>, State>
{
    typedef detail::compressed_pair<detail::callable_base<F>, State> base_type;
    BOOST_HOF_INHERIT_CONSTRUCTOR(fold_adaptor, base_type)

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

    BOOST_HOF_RETURNS_CLASS(fold_adaptor);

    template<class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(detail::v_fold, id_<const detail::callable_base<F>&>, id_<State>, id_<Ts>...)
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        detail::v_fold()(
            BOOST_HOF_MANGLE_CAST(const detail::callable_base<F>&)(BOOST_HOF_CONST_THIS->base_function(xs...)), 
            BOOST_HOF_MANGLE_CAST(State)(BOOST_HOF_CONST_THIS->get_state(xs...)), 
            BOOST_HOF_FORWARD(Ts)(xs)...
        )
    )
};


template<class F>
struct fold_adaptor<F, void>
: detail::callable_base<F>
{
    BOOST_HOF_INHERIT_CONSTRUCTOR(fold_adaptor, detail::callable_base<F>)

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    BOOST_HOF_RETURNS_CLASS(fold_adaptor);

    template<class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(detail::v_fold, id_<const detail::callable_base<F>&>, id_<Ts>...)
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        detail::v_fold()(
            BOOST_HOF_MANGLE_CAST(const detail::callable_base<F>&)(BOOST_HOF_CONST_THIS->base_function(xs...)), 
            BOOST_HOF_FORWARD(Ts)(xs)...
        )
    )
};

BOOST_HOF_DECLARE_STATIC_VAR(fold, detail::make<fold_adaptor>);

}} // namespace boost::hof

#endif

/* fold.hpp
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
*/