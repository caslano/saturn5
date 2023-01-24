/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    function.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_FUNCTION_H
#define BOOST_HOF_GUARD_FUNCTION_FUNCTION_H

/// BOOST_HOF_STATIC_FUNCTION
/// ===================
/// 
/// Description
/// -----------
/// 

/// The `BOOST_HOF_STATIC_FUNCTION` macro allows initializing a function object from a
/// `constexpr` expression. It uses the best practices as outlined in
/// [N4381](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4381.html).
/// This includes using `const` to avoid global state, compile-time
/// initialization of the function object to avoid the [static initialization
/// order fiasco](https://isocpp.org/wiki/faq/ctors#static-init-order), and an
/// external address of the function object that is the same across translation
/// units to avoid possible One-Definition-Rule(ODR) violations.
/// 
/// In C++17, this achieved using the `inline` keyword. However, on older
/// compilers it is initialized using a reference to a static member variable.
/// The static member variable is default constructed, as such the user variable
/// is always default constructed regardless of the expression.
/// 
/// By default, all functions defined with `BOOST_HOF_STATIC_FUNCTION` use the
/// [`boost::hof::reveal`](/include/boost/hof/reveal) adaptor to improve error messages.
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     struct sum_f
///     {
///         template<class T, class U>
///         T operator()(T x, U y) const
///         {
///             return x+y;
///         }
///     };
/// 
///     BOOST_HOF_STATIC_FUNCTION(sum) = sum_f();
///     BOOST_HOF_STATIC_FUNCTION(partial_sum) = boost::hof::partial(sum_f());
/// 
///     int main() {
///         assert(sum(1, 2) == partial_sum(1)(2));
///     }
/// 

#include <boost/hof/reveal.hpp>
#if !BOOST_HOF_HAS_INLINE_VARIABLES
#include <boost/hof/detail/static_const_var.hpp>
#include <boost/hof/detail/constexpr_deduce.hpp>
#endif

namespace boost { namespace hof {

namespace detail {

struct reveal_static_const_factory
{
    constexpr reveal_static_const_factory()
    {}
    template<class F>
    constexpr reveal_adaptor<F> operator=(const F& f) const
    {
#if BOOST_HOF_HAS_INLINE_VARIABLES
#else
        static_assert(BOOST_HOF_IS_DEFAULT_CONSTRUCTIBLE(F), "Static functions must be default constructible");
#endif
        return reveal_adaptor<F>(f);
    }
};
}}} // namespace boost::hof

#if BOOST_HOF_HAS_INLINE_VARIABLES
#define BOOST_HOF_STATIC_FUNCTION(name) inline const constexpr auto name = boost::hof::detail::reveal_static_const_factory()
#else
#define BOOST_HOF_STATIC_FUNCTION(name) BOOST_HOF_STATIC_CONST_VAR(name) = BOOST_HOF_DETAIL_MSVC_CONSTEXPR_DEDUCE boost::hof::detail::reveal_static_const_factory()
#endif

#endif

/* function.hpp
0ZDSlmC6bWBqbnzCLJCafeJw7O2h39bmaM2kXm2PY5d1FD8dw1kGPlH/Xuhqw7jI1Or/0opwuVJSb5Y2OZmZwAQPMM9X+fuPGG3FwraSkcQWRLqu9iYW2Cl8N7tv9lGzJJbV9BS0uH0x/vSnUh5U6LbPhVzqlWkbZhGadiwXL/75lM5SIsuiSuU90Fep32KszLD+F4XmP2SBvYWoTS9V8lIkt8bo0S2+aL7sSrQaflBdCBbzcgqqMy78etcUq8v7dvAPSwiCVy/g1meh7TD2z3tf54NA0IDn1MnNtAmWQyN70Z+TUkmhDjdiHWd2D+8KsfrM7NEPJvFvRU4SzyQQDQUrIS2oqEepSNSiw6Ka+oV91tYO8R9qGGMlq+htn2nD8Q9yjcqtzhpxMa58iJd+i9O1/oGQ7ETkLFBqFLYXrg8xKzf/kWPHXW93v9dCbPioNk1/VkAutuNSRcANzo+xNSRBMh9QIEF3lzDX6OBZptk2H7QKNNJYtkcDg0NHu6WF5WUXYQ/oaododNzHUe6uQIFVNmt8iEu7hscpNkG5cTtf4KnB+VY8x9MG7Aw3iFMvQJ/cXzuSgMG+E30O+bclD10cT+vXE0XO00zhpXE7yBOdzSmuvTOQw9H+pjmrnX6lhE4JWbPNbyQJ8JcuT10jLIu+8MofVzbuDqQPG7C73B+4Z9YdR30Bhh/QvzMg2bstn/jS3i0G5X3Vv2p5
*/