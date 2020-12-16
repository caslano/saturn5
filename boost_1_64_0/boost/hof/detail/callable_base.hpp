/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    callable_base.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_CALLABLE_BASE_H
#define BOOST_HOF_GUARD_CALLABLE_BASE_H

#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/result_of.hpp>
#include <boost/hof/apply.hpp>

#ifndef BOOST_HOF_CALLABLE_BASE_USE_TEMPLATE_ALIAS
#if (defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7)
#define BOOST_HOF_CALLABLE_BASE_USE_TEMPLATE_ALIAS 0
#else
#define BOOST_HOF_CALLABLE_BASE_USE_TEMPLATE_ALIAS 1
#endif
#endif

namespace boost { namespace hof { namespace detail {

template<class F>
struct non_class_function
{
    F f;
    BOOST_HOF_DELEGATE_CONSTRUCTOR(non_class_function, F, f)

    template<class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(apply_f, id_<F>, id_<Ts>...) 
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        boost::hof::apply(f, BOOST_HOF_FORWARD(Ts)(xs)...)
    );
};

template<class F>
struct callable_base_type
: std::conditional<(BOOST_HOF_IS_CLASS(F) && !BOOST_HOF_IS_FINAL(F) && !BOOST_HOF_IS_POLYMORPHIC(F)), F, non_class_function<F>>
{};

#if BOOST_HOF_CALLABLE_BASE_USE_TEMPLATE_ALIAS
template<class F>
using callable_base = typename callable_base_type<F>::type;
#else
template<class F>
struct callable_base
: callable_base_type<F>::type
{
    typedef typename callable_base_type<F>::type base;
    BOOST_HOF_INHERIT_CONSTRUCTOR(callable_base, base)
};

template<class F>
struct callable_base_type<callable_base<F>>
: callable_base_type<F>
{};

#endif

}}} // namespace boost::hof

#endif

/* callable_base.hpp
biJzMZJBaZGJB06sZiBNRLe5ERZqd/K6h1N/+lNCPnWW8MliyLPm4LkaRiG1TyzCEWTYKf5+8XrGkEi/sG6MXMc/pnH4hRyY59aZ8ts+vzjnzlZlMy+YhSu1AnJm8p+r5KTkOT8HsreuhjVS2jJ74Q2W0mBXECkYEol9f5ZmKTt4xa6NsmtbcUqV1oiGt9Rxl69X5LAWvg8jSC6hqIxAF+2bCy1kNW2bYepSmoaBQ2RqZt0UObeXqzbZZJu82hMI9ovZv5UQRsG0Jx/naCrZ1bATWYzSbbJ0EiUhHdKKLExsT5572R7DVVZwkIwfk0e3gUXIz8dvfYYFxNx6eEKqoTyAcK9wBppPna6k6uiBP1sQPiFWyxpvBGQir0DuYQyGhBWIjNrdfhoBu/FeN1MO/eKYoe+91hh6mSIoR+EyFX0QVyG/CNwHBTsl5b36L7y2edyOX2z+hH0M/G+TPP9JPNxB+4KeRRtCTYUoYHKMXcAgzx8YPcskraUnNjCm4MZgHxnVa87eGo9/Z7yZQP94Pf69LS490xsdPj1ff7mx2urqa+qLPh/a1+Hq0XUdtNUYePjI90DIWqqfng995g6htR38+gWFCPRE3pBciHS+/yHSWqHCgl/WhvMZA2u30f8aJgACFAYt3CSjPfoF1ABqlf3qnnV27UVu1RuyRY7G8dbGsqSW/rE5KG3y1RfWJWuvxqYtbBxvY4tysvVJO6HabXYhjfSNxlgrqmPaj3bANcl3tvor7++Pviz5eW6v5LL6ath2BaH2zlujSHKW9pkJza+pC2Chd2tCRl7izb+UuzGHkGYSHZVWLODE5W4JenqE2mzBKeqYyKsRN37DtsNYqXSEcD9kqEv30g5Gjwyu5JFnpHDNCObzhuc78rHmyJFkOEWsZOaVm9lhp2l7zJwBzhlAzhql2jyEudWQN3xkOx029+FiqHVQ+ASUNJcrKln6CbxLy/Eeirr5HM+PYKAdIvKqSQjJIkF+GkO2npPNoEvcjuOI6aM12hWXYbXobWIrioic7xNFuGkbJqUXLkMPFtiBM6LQdAJ+pMXd+CMbbJKIu6JVkKkXmCApRaF6GwTwFzGQdp5N1LvAWKqH3eac0TjCBqsCVJ+oM2p74VGztq7LeDhbCr3azZymAmkoC6v8l7sJbcxs6SXtH3ChXm0eJ+zD6rxs9LLML5K4YawQcFkkQkhNDmLYkoF0fPLBFpN21yqVAaTg9QmaoYT5cjL+AxxdBF9X9K2T6y7VPprBKM2PDfmv1SaJy8kkLsZqFq83TnAS5CM7HjghOF8/lW/L01KC/xViNiqkJP8LkMzM2bIiimhNkt7l9YnFrxj0sdD1DqiFTKH4a9h22sV4XJmJMdbXtldvpjOpaLBSVQg/C4eUBoeSaqtfvIRFYXIl6Vij5erna54GIz2ExxToO/3isTe5B1S9kxiiA0jD9Y2fxmR+hDblFdNBpnz+XROjCdSHh1CvpEThxBWKXDSEmCkjfOKLV0xiWgesCkYTfGKbvJhmKMlWDHbd9TykjFu2TPOJIZgJRhcTZujyVZKRUac1Hh45GpF+8fO3ZZJKFKaSzPwne1cC32R5xpM0tAEKDVCgSoUKRdFyFMvdIuVKQRFTShMuCzqFz8hR8QsUhVJM6yihDJ2bbMODzW3MOTcVXVFUSuXyQJ2OOdkm29z21sxzG4cH2f953u/9knyl0DJ3/bbwI817v+/zXs/7nJHUwDLZwh2IVAV6PXsm6twbDzGdmDvN9JF+6Lf2nUlGqDtPrptpdv8aqY1z/9QPuD5Rf2GxJey+ITE80xLeYgm/lFheQ/2Svn1wr5W+baaLO3/VIn0b9cvytap883RR3HL5xao=
*/