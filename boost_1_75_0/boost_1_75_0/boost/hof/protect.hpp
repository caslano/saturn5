/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    protect.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_PROTECT_H
#define BOOST_HOF_GUARD_FUNCTION_PROTECT_H

/// protect
/// =======
/// 
/// Description
/// -----------
/// 
/// The `protect` function adaptor can be used to make a bind expression be
/// treated as a normal function instead. Both `bind` and
/// [`lazy`](/include/boost/hof/lazy) eargerly evaluates nested bind expressions.
/// The `protect` adaptor masks the type so `bind` or
/// [`lazy`](/include/boost/hof/lazy) no longer recognizes the function as bind
/// expression and evaluates it.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     constexpr protect_adaptor<F> protect(F f);
/// 
/// Semantics
/// ---------
/// 
///     assert(lazy(f)(protect(lazy(g)(_1)))() == f(lazy(g)(_1)))
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
///     using namespace boost::hof;
/// 
///     int main() {
///         auto lazy_id = lazy(identity)(_1);
///         auto lazy_apply = lazy(apply)(protect(lazy_id), _1);
///         assert(lazy_apply(3) == 3);
///     }
/// 
/// See Also
/// --------
/// 
/// * [lazy](lazy)
/// 

#include <utility>
#include <boost/hof/reveal.hpp>
#include <boost/hof/detail/forward.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof {

template<class F>
struct protect_adaptor : detail::callable_base<F>
{
    typedef protect_adaptor fit_rewritable1_tag;
    BOOST_HOF_INHERIT_CONSTRUCTOR(protect_adaptor, detail::callable_base<F>)
};

BOOST_HOF_DECLARE_STATIC_VAR(protect, detail::make<protect_adaptor>);

}} // namespace boost::hof
#endif

/* protect.hpp
CjqMhLnfoxQUZxLxZsQtxPLzTfNrUyTUPU+f042XFF0TIku7pncNGbIGBdEQ4HuX4iPC2dwsq0m6BsMcfi/tL031JZ8omWAkgKLllkahI93FUQ59kE4Udu/bDArHZTBEYbNmYvDeW5xSFLHLNW7/F2YZ0QEeqqCiGGwsInVXpv47RvTwAK/6gwG2p1/WLt8gpmAVrfWMxOX9uZItV30q6GYFQhGfF8we5q+2r7whBBtFsxPtb+yBfF8+yYzrCDqUS0S/ufjswnYs9w5cmfkAhgrdbMMMMXbQHGVnVgbddKB+h23mFKpFj7PkySWy5k0vgG54Ziff0VNUOEi2v3lMr4w5d+WAmVysDYZurm3+QpzkyvkT4IJJY29P8GM+n4KlUTjYQwY0DMr4hKLiWi6nxAyczJSo/J1EjxiiKaRRUexQsOamOY37NcsIYPv8YEnmuVgN6UvS+RC/5wLjStvB9dRHfs/Ja+hnSXfJ0NcC3wX3QJeuHc2FbdKOk/qS3Oe4oXzNNqzDhZUMuB3GuBQo75G8DbH9TCOt+9HfJsRokOXwBKwYRCZNlS1QdsV5obTE03NNmFiDg/RTD+2jGzHX7hzWoSRjA24v4cbRJwqhs0R1IXKhCh1ZsDstxEE3Wyg7KDvWZ/YkVL9BV+znd2uNWhuYamMa5H+BHjv58dogRz/saQ/br7c4xGfEyR19yZg0HWaNzPpxGPFzry0O
*/