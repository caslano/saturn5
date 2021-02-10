/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    rotate.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_ROTATE_H
#define BOOST_HOF_GUARD_ROTATE_H

/// rotate
/// ====
/// 
/// Description
/// -----------
/// 
/// The `rotate` function adaptor moves the first parameter to the last
/// parameter.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     rotate_adaptor<F> rotate(F f);
/// 
/// Semantics
/// ---------
/// 
///     assert(rotate(f)(x, xs...) == f(xs..., x));
/// 
/// Requirements
/// ------------
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
/// 
///     int main() {
///         int r = boost::hof::rotate(boost::hof::_ - boost::hof::_)(2, 5);
///         assert(r == 3);
///     }
/// 

#include <boost/hof/detail/result_of.hpp>
#include <boost/hof/reveal.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof {

template<class F>
struct rotate_adaptor : detail::callable_base<F>
{
    typedef rotate_adaptor fit_rewritable1_tag;
    BOOST_HOF_INHERIT_CONSTRUCTOR(rotate_adaptor, detail::callable_base<F>);

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    struct rotate_failure
    {
        template<class Failure>
        struct apply
        {
            template<class T, class... Ts>
            struct of
            : Failure::template of<Ts..., T>
            {};
        };
    };

    struct failure
    : failure_map<rotate_failure, detail::callable_base<F>>
    {};

    BOOST_HOF_RETURNS_CLASS(rotate_adaptor);

    template<class T, class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(const detail::callable_base<F>&, id_<Ts>..., id_<T>) 
    operator()(T&& x, Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        (BOOST_HOF_MANGLE_CAST(const detail::callable_base<F>&)(BOOST_HOF_CONST_THIS->base_function(xs...)))
            (BOOST_HOF_FORWARD(Ts)(xs)..., BOOST_HOF_FORWARD(T)(x))
    );
};

BOOST_HOF_DECLARE_STATIC_VAR(rotate, detail::make<rotate_adaptor>);

}} // namespace boost::hof

#endif

/* rotate.hpp
E9rFnsPY0rIUCM/09RoGg4mM3whTjyYh48khV2ISNY2upGJLzwQb63RGNuO6FAdZ4Gz4AVKQgCJIxJRfktlqI+iIU52xuHRZoU2k5udGFz0pYBX6qqnMaaqldMuL0vrhzRhNE7oW/V6OwjNI4oSRqCu6srliLJDmTZRhl6j6QmkF6bxHSuuXMUVy1EW+8c2NuiIJ3u10rZ6iDYfsg5UT1y36Lua8LvsjWwZhH8lE2DJaGEoUfDlExJvZsmSpxaDvYMsSTptBt9qym0kCYW96j+m5r73yiMt0BeMTjpQhTOPAQ7fc1npkoV/4Vv/Vmc3o/MAYNHSvqwSUkFxDxwKDKBwnIDUquZd2ZicmATxBYvJYW4+TZPS1NXalCjpmScuhCKxNrkxG1vqCzmKMcSKhutAArAp6lbii1rXaLVvatqbUNOjOhVwWVYIKYnsfFT2ThJZZ3ToaFXV1nL1urwJv1/XlrEbNtWBECkYtqwuVECeUqVcyMZSucFKieqTBnB7wxDzpgQqesC9Guuduo/xk/IN3eHb6ypv88HJ8OpuenbIBgIGmJmyX3TqC/w4nWA7lMHqyN4a3wH4bnCGLlIqD7OfoV2j++S+7n48qoUp35cD3FtEJbpv4Sx4l89Tze1JCqsvBySb0ZhCWP1ST
*/