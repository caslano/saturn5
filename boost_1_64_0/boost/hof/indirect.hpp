/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    indirect.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_INDIRECT_H
#define BOOST_HOF_GUARD_FUNCTION_INDIRECT_H

/// indirect
/// ========
/// 
/// Description
/// -----------
/// 
/// The `indirect` function adaptor dereferences the object before calling it.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     constexpr indirect_adaptor<F> indirect(F f);
/// 
/// Semantics
/// ---------
/// 
///     assert(indirect(f)(xs...) == (*f)(xs...));
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * MoveConstructible
/// * Dereferenceable
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     #include <memory>
///     using namespace boost::hof;
/// 
///     struct sum
///     {
///         template<class T, class U>
///         T operator()(T x, U y) const
///         {
///             return x+y;
///         }
///     };
/// 
///     int main() {
///         int r = indirect(std::make_unique<sum>())(3,2);
///         assert(r == 5);
///     }
/// 

#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/result_of.hpp>
#include <boost/hof/reveal.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof {
// TODO: Support non-classes as well
template<class F>
struct indirect_adaptor : F
{
    typedef indirect_adaptor fit_rewritable1_tag;
    BOOST_HOF_INHERIT_CONSTRUCTOR(indirect_adaptor, F);

    template<class... Ts>
    constexpr const F& base_function(Ts&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    struct failure
    : failure_for<decltype(*std::declval<F>())>
    {};

    BOOST_HOF_RETURNS_CLASS(indirect_adaptor);

    template<class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(decltype(*std::declval<F>()), id_<Ts>...) 
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        (*BOOST_HOF_MANGLE_CAST(const F&)(BOOST_HOF_CONST_THIS->base_function(xs...)))(BOOST_HOF_FORWARD(Ts)(xs)...)
    );
};

template<class F>
struct indirect_adaptor<F*>
{
    typedef indirect_adaptor fit_rewritable1_tag;
    F* f;
    constexpr indirect_adaptor() noexcept
    {}

    constexpr indirect_adaptor(F* x) noexcept
    : f(x)
    {}

    template<class... Ts>
    constexpr F& base_function(Ts&&...) const noexcept
    {
        return *f;
    }

    struct failure
    : failure_for<F>
    {};

    BOOST_HOF_RETURNS_CLASS(indirect_adaptor);

    template<class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(F, id_<Ts>...) 
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        (BOOST_HOF_MANGLE_CAST(F&)(BOOST_HOF_CONST_THIS->base_function(xs...)))(BOOST_HOF_FORWARD(Ts)(xs)...)
    );
};

BOOST_HOF_DECLARE_STATIC_VAR(indirect, detail::make<indirect_adaptor>);

}} // namespace boost::hof

#endif

/* indirect.hpp
C+EvVB27vSjOnRXHaA+Ezz1O+NtXpGkv+C8tPtH2KhHuk3tuL7YvWuEgpp1e7sEnMwyf2AHa1hw3ft6njJ97AvFRPxzXY7c6SJ/jxic71GjH/j9M9f49UvWUf9DOBvfLc+JlpMM/ip/q0asMoByUQFqN9edrbUV0Pv7WbNMUZY/lWVFY9jEL4/L8QzhPf44YdWFc/wwTCLiuLw32jpLFszKaXAOEz88+IePAyfC4jg+PUf9iPZNM+jnxCg4mJvcHONiMOujfFyW3WPsacjCA+VVl+vYw9+O9QyXWoDJanT7cpsKPaT9bSlOqR/xmUAprVbteQeV3iOdXMFi8y7/B9K/QbpU79FvPUTv0TniktEb68i6T5YHA4UVaLtxTJCmVtg9Y9JcJ9hyIcH9noiFAHToSC2Y2nM8HAFlEPwwi1lJ/3PZ7a4Wk3WGBH3d3xl1o7Gs2Nsn7rYixb4Vx3KAP0Z+b4AxeCLVQgYF4BUdDkQP10JF5JGRmOPIXKbJiKhcV7GcE/P4kxEJVwHQ1fCqnmWLguBf4wAXKgHLrcgPUvfjz9+3XlT13a2AovQzdBrEr7WLc+Vwc/78gaWPU83hQ+9vTz5P6HLPpTmpGbHWNeAO1JhEettalZ9T5rcSY/9YAi8U4qXKGybJD0nD58vK4AfCR6QbMRfOl1GtmZyaNF1nSEyUMK+bMcB+Kge5BjuXyocVd4sY8DlUbUrEFbplu1iKp2DIOnWuAaRV2w2AZ6XyZOYsyU/JJkMBjlUOuqQEI2k/cofetpwbbRaBrdtyWwvpaRwfloopXH0J3o6uqSxG76WWZZ2/kSYKXyFfmKr3/MgUpxZM4tdPyzrG4mNZ8cIWhw+ofu4nu8af4uw318n6xqMD4T+wjXF77YNlxeumZs5N6iYTl/0Tf96WyTbpqiZGB/a7fVif6qMNgZ8uzvDs6MArZz7ZQi9wNoSbm78CNyNRFlznjXTTKiPb4ZAArHjzVOGlXt2WL3kcXuTadQYkp6QCMbyA4L7OAp0I8hcUZxF2VqpvyuJtcTT8x8r1Akoh6h8rR8J8Df7ZnuhLTVQucQUoWbA1cjXjp6VB48TSFwn/uOwqFDz2LcSWuPY83hty/5dqv0f/E7E2am1bjjJlsEZ+crtefnaMMNzcQ0MzSkMcBnVnM2OqczUhenEKyKSRv5sXWjzSmisy5nJTRMNgTuUb9UX3OCshRr/LU8hpMC3qxPwYvnwhpimdxkl6Nfp1tEfdjc4p71bnx6woqk3pxHXz1zCLSLODm+e8lN8sjyek/oJ/Fwlc8sDg4W8KEYPrT3D5pmVoDGqHPMbOW4v5giSEMFTrLGjwf4Ai9lDeIdLvqUrXqVUrQiR1pQj8KsPohpw1wOzESCUbx+OdVioF65ixGlEsV7t9OS5eeSRDvL0Kh8y3wJxW0C8X3p3MkVBGs+H/5SEkcL6fXmvKc9XpJbD3w/4JuqUt2vV3a2qvziYf7Wizcz/KcJRsCSU18expohdJ0G5vWV3Fg8rEt6IcSMrDE7lmiuL7V0Bflg6eokqkkHTpG0qHDmQ7Ngd0517ksuO6NvSjZwaOQpEosW6K4v09C8Km/XBCo0SLLpKoyPSNs1Wvt4YV2mrUjaNaOPle45ExNuod/rqgoU6sKB/wDp6kvadbp9XFcOzrdrKutUtJsLKubI1GuUiMgHkKwbIR+EMwYxkBLivVEOSR1fBzyFNWSpA5Iv1RHMox/9MVhHJMOxm/PNmAE8dIhAQxP1DPDm7ih++FFFte/geU4mlkv3pzGUFKptTQo7sQCgU7H9ByvpnuuNsUs5SJ/E4qYJ4vAoBrMcZ8jCTZR9CoRU+84v9BBGd1UaIwuEum8ys0=
*/