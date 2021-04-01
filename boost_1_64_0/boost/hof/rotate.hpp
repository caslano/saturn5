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
rssxa9XH7OpztA4oBnQx28lTN9172EMQmeIliJO+w9Y58YQB6c2aMuLE6t2nddJHEBh9KJuNocGVOsLqCItC/Yu0MGM9IxN9WTMHlJ/VAQrdGAzZ8Ru1aq4mB/TCHzpmaKpdVjuDyeOjp7znAySQVEh71XtVYUIkR96RQVEIoYYK7T96d9JWvxaO54yZPNJUiLpShezY8jP7gR91PcLSFMlh+DInX1cDN8FIUq1J3EJ8mBlpC6w2PukkEZN+CogXmp+bOL6mYNrSu8v1Ebe/6Eft9MQ7TKc+lZWFci/OqgKl+DX6fJezXFdx4Xs83qq2AEcx7xjPXGKPsUr94pez5DoZ6v8UojwYPWV8upRK61VxJoIuSoPryE3J2vhtb6A1nnqWvghlZGhHw1RtxJfQN0mzmc0rjvSHnLRvNFxWSb4iBgNdk+5HhPiOWP+FmzNyAfPEj1F9yKUnvoHYiNHB8X/4SQNNSYbfAujD3FXOwHPynC3h4EOMt9znSJrtc1PgC5IMDJWbe+5nuxJ+A335m0wC3SyNEym9K3rlcYUaKLnn7hMcTRUSnzJMOw==
*/