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
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
*/