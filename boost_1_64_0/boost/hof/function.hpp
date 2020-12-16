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
BniBKi5X6VqCSAfwgotI61RgAS0CaGA6NxeztjPNWe4lBVOxgCGd3DiA3XNQDBWy2h6F2EXR+9IgO1kCcohvNVOYPUoam3dTwA4frfksynF6bIr2NioYCzpIsfW1a1GG7Asv3LHBLTzy81EON+QAXKmDP9tsuAgSr9EcAnZIgu89tyqx6Yyq6G0KhLe/JBe0CPhTC/Vy+NlFWUAqk84OfRgLDKM5p0Kavs6Vob5n3cb51GYqqwObuTbchw8m+IdlER4pRHU1lUasnggebqEfrzUaudHF7qGyEMQ9RzvfqvrZIZ78qrobi9WFDoE4p4zwWnstJdsaMZIFlpNWaWOg0SSoloBFR05dbd+YEV5tp3AKmGgEsAchUBDijXoT6ySpprEjfvZ141aS8/pOSHd3fSGhXt2bMLc0BWCtsG/jGYxmYY0L0VUqYidFXKEi8j3VvqLmZsb2ZuwZxMjSrcq0QNgGld3hmfboOC1mMVNGs7W3TddqzsfC+eTUiV6raLvD81CKkuYuBXFI9u/v5un3fx4O4bd9JC+bur8b/WVaxFnjTAsp1oTyIVh1J3zHNp71rtowaZjF+t8621JWGnC0QP9Qb0KL7fpvaFMRmU8rrWfCK86WvyBDzDpo7vziveoqWq2O5Lx/4Juvk++RKAF39CM1SAhyxVHe8izQDgZ0aUfQVVt3bmywF5pZ5Xx1IVGVmHuvulz7BF1aoYymmF5Xsy4Plyj/BuvyUGYytKfM0ZItmu4yFyxnC1PcmMDaAawdZFHuawBK26Ois2UarFTiUAsPL1raAqvIGHPgYq7D0FY122bxthNbrDCgooZ5BZQGbl8ouiK7Q3vcEh/7KzFm5+3gTBGpaDfH8InXEIUF0+ApE4VVIq94AEBorl1OnrRVqLSmx5e0CEOYl5DyK2ZxV3Jxv7nBuEfy798o8f2SeNWwUv8klFA3/z3JdXskxHU7jn0/i+4gkgFfS+m+dZlyAzBid7pE/qs4Z94vLELmqS3SFbs35f7H3Sn3P76a7HZuS7n/sTPZ3X1ZsntGSn6NKfk9c12yu09KfjtT8nsLgzqFXsSlEt1A00QrzveJ9V9NQyy+8jl4suqPh6/lhpDaoT/4LVON07Vcj7R+gQF0Z8SkGklJsZuTcRsGr000fxj3/8PDif5Fu0902LUdUvhJ9S9rPkSpgT4NYTi6tiFnH99k4Jsft99qXiaC4THS5C4Bt2m0VQPsB65Xl6hw90pqv/CJTd9AJvorolUuHrh6NUb7sZm2t0p7r0q7lBIDpe29S6G0hXUSn9UK7SuGulKddPUFBniZNFrtEl+W63q1Ptue5L9vq/SvrRLr7lII7LHztcW1ZHnq8zslcuxc+neqEjLkP3n/C6pfKQln2yHwJI2B77CVEKyS53XUiicQySuu/Kah9ZOIjN8gWh00XqyqNZZZF1GQnXJw5dFQaJQtCq1vK2U/kDWNabTFvtjA90DKt6xRVCSTLb5qsRVlqZSzOKVUerxf3IHxPTbmpJu0q4JOqJXsKxxLu9kYVPRi/0qjg6LnQCA8OJmS77s2PgD6+tfKCP2iE6m1fdTcQ1TpgXG0VEXz/FfLSCujvf31xmjxX4Hu/m6rYTfgTQyqWnHZjaaNUaIk/l7TJcfon7u+cAL9M5x2fOLFBxP65814/6y40eyf/Qn9c7Vq5cCFPffPlJDZPw/J/pm6Id4/0y5M7J/Dlx7VP9p5Rv+s0YhLoLpoMXXRVMohlNBF/TUqQvVSsdlL37lG9VIB99I4jbjeqqOyWY2x6qvV6KveYaOvtjdSX7Xf8M/vK8a3P/hSMv5tuzMF/9+R4Fb68p+5Oa4vX2tBJerFNhIAX0bs06/fx6g=
*/