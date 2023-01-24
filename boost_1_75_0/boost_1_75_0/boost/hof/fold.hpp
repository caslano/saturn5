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
VRYY6VwjOZM8lmn8/CeAwI94iyuUbDrcVs4XD8NCohBpOuqchiLdKYjEh/pAVMt6/XUMUiSVFJlAmnTGaarfHWbTKXtxz9qepr2W2nCp3m9n4PL01Ep1xjJf7VFLWXB8ekbu6yZDdNvfHXe8AWIGpdIX3p729CqYvitSWW8d/4pj5z1QHfbmRyX7hvqbF6fZEvSFLK92nljbuQ0jiF7+U/1ACNrjRhGWMh4+/5F4XJ33F4cb1BRvFezr9maW3yJrBgw40phl4lzC6cpt9upl0hdeY55WVZvu71dwLNKfqJdFWIcv8fllWlFr9zR7T47XP/0Vk6FqNPhFM6BgsAr3HmAoJX3vWqeAjqx+idMCot05/au3b0iWvthHT2EdpaIWA+vVTV2k6VEff5GnTtOZEk3oDZO3T4cUy861eNTa/dwrMF9A08ZmkMpkdQ1p6djhLZqxak4//Jc2i5KxvFwN4gGmq4pLuLcSzd9feTujyfFbM8OF6Yeuzf3qDZBoT6C/mmfKd9S9fO+yFtVQzYEY+OEaR1j1xghRUI+iMvjOfsH2qXqwQcB5teviZ/bZTTYqOVJLOGufBL5dVTBUeaIF7rXIYZ8TBLMHgOiqBBHBLnKMGyUyqcwYTSh8tUSFOb6Whfg5sNWN6FJTQb45F5h3X2aeOSJVqRThetNU4TsxuUC4dxYlsjRb0/u0XFiSL7eo4Vo80LxsVO/dtGbN
*/