/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    static.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_STATIC_H
#define BOOST_HOF_GUARD_FUNCTION_STATIC_H

/// static
/// ======
/// 
/// Description
/// -----------
/// 
/// The `static_` adaptor is a static function adaptor that allows any
/// default-constructible function object to be static-initialized. Functions
/// initialized by `static_` cannot be used in `constexpr` functions. If the
/// function needs to be statically initialized and called in a `constexpr`
/// context, then a `constexpr` constructor needs to be used rather than
/// `static_`.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     class static_;
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [ConstFunctionObject](ConstFunctionObject)
/// * DefaultConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     using namespace boost::hof;
/// 
///     // In C++ this class can't be static-initialized, because of the non-
///     // trivial default constructor.
///     struct times_function
///     {
///         double factor;
///         times_function() : factor(2)
///         {}
///         template<class T>
///         T operator()(T x) const
///         {
///             return x*factor;
///         }
///     };
/// 
///     static constexpr static_<times_function> times2 = {};
/// 
///     int main() {
///         assert(6 == times2(3));
///     }
/// 

#include <boost/hof/detail/result_of.hpp>
#include <boost/hof/reveal.hpp>

namespace boost { namespace hof { 

template<class F>
struct static_
{

    struct failure
    : failure_for<F>
    {};

    const F& base_function() const
    BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(F)
    {
        static F f;
        return f;
    }

    BOOST_HOF_RETURNS_CLASS(static_);

    template<class... Ts>
    BOOST_HOF_SFINAE_RESULT(F, id_<Ts>...) 
    operator()(Ts && ... xs) const
    BOOST_HOF_SFINAE_RETURNS(BOOST_HOF_CONST_THIS->base_function()(BOOST_HOF_FORWARD(Ts)(xs)...));
};


}} // namespace boost::hof

#endif

/* static.hpp
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
*/