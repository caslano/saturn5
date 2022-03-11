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