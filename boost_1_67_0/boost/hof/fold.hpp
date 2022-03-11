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