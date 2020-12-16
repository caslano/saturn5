/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    can_be_called.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_CAN_BE_CALLED_H
#define BOOST_HOF_GUARD_CAN_BE_CALLED_H

#include <boost/hof/config.hpp>
#include <boost/hof/detail/and.hpp>
#include <boost/hof/detail/holder.hpp>
#include <boost/hof/detail/using.hpp>

namespace boost { namespace hof { namespace detail {

#if BOOST_HOF_NO_EXPRESSION_SFINAE
struct dont_care
{
    dont_care(...);
};

template<class T>
struct never_care
{
    typedef dont_care type;
};

struct cant_be_called_type
{};

struct no_type
{};

template<class F>
struct is_callable_wrapper_fallback
{
    template<class... Ts>
    auto operator()(Ts&&...) const 
    -> decltype(std::declval<F>()(std::declval<Ts>()...));
};

template<class T, class U=typename std::remove_cv<typename std::remove_reference<T>::type>::type>
struct is_callable_wrapper_base
: std::conditional<BOOST_HOF_IS_CLASS(U) && !BOOST_HOF_IS_FINAL(U), U, is_callable_wrapper_fallback<U>>
{};

template<class F, class... Ts>
struct is_callable_wrapper : is_callable_wrapper_base<F>::type
{
    is_callable_wrapper();
    typedef cant_be_called_type const &(*pointer_to_function)(typename never_care<Ts>::type...);
    operator pointer_to_function() const;
};

template<class T>
struct not_
: std::integral_constant<bool, !T::value>
{};

template<class F, class... Ts>
struct can_be_called
: not_<std::is_same<cant_be_called_type, typename std::decay<decltype(
    is_callable_wrapper<F, Ts...>()(std::declval<Ts>()...)
)>::type>>
{};

template<class F, class... Ts>
struct check_args;

template<class Res, class... Ts, class... Us>
struct check_args<Res(Us...), Ts...>
: and_<std::is_convertible<Ts, Us>...>
{};

template<class Res, class... Ts, class... Us>
struct can_be_called<Res(*)(Us...), Ts...>
: std::conditional<sizeof...(Ts) == sizeof...(Us), 
    check_args<Res(Us...), Ts...>, 
    std::false_type
>::type
{};

template<class Res, class... Ts, class... Us>
struct can_be_called<Res(Us...), Ts...>
: std::conditional<sizeof...(Ts) == sizeof...(Us), 
    check_args<Res(Us...), Ts...>, 
    std::false_type
>::type
{};

#else

template<class T>
T&& called_val() noexcept;

template<class... Ts>
struct callable_args
{};

template<class F, class Args, class=void>
struct can_be_called_impl
: std::false_type
{};

template<class F, class... Args>
struct can_be_called_impl<F, callable_args<Args...>, typename detail::holder<
    decltype( boost::hof::detail::called_val<F>()(boost::hof::detail::called_val<Args>()...) )
>::type>
: std::true_type
{};

template<class F, class... Ts>
BOOST_HOF_USING(can_be_called, can_be_called_impl<F, detail::callable_args<Ts...>>);

#endif

}}} // namespace boost::hof

#endif

/* can_be_called.hpp
/amnL88Lt0vL5d2q/faqfPN08dqRlunzqvzB51V5azrG32J5elsaOBLtz/AoyYPkawJGBoGN4zjGcxAr0rDjMmcD6trn2JmhZbiPpbjrU/E3bVKDVxY0uHi3oiDed6Ask/SbD9f46x2lbBcwJSPnAI1yehnhd7eKeRs33+Z/MeKA4keo+UpM75GYvtha/tj+hHS3tfzhxPSZ1vQnVbrqXzz/9y0rP4T7Z6bvap6+OL781ubp7vjyq5unz4xPn6fSLfdRFGuFbhm5um75ZcI1k1bNxjW+Sxn/9Mj7Sooz2AUK4OpYm9Q0Fr/l4hqG4izyqrCGHnb5hoRwHqw+sgWzspfM++gD6Y7N8aKBFz41jS6coDN8iO25nKf4MWxA3+Cv7GnG5xsgivHkh00YP2zCSNHvcNAFBHmViSC/UuybEVmzc9fCNtxnaTVfoZp6Qjymu9z6vjepGer7z/TC2p5sIifs0NtDw6MHa3jgx/mnbz16mbjoXtMCAhvLm2CP3R3V8ipw892VriY2U9gaeCPHjvf6eYti9gs7m/ZXpxv2V/ed1v6qgyZhJJCG8+Q4Nv3CmGSaYJ08YI0Ep1L0321MHk3cOnav+NgLSlJT9xPX5Zd245ntBznoG8yRd1MlVzC2JV1NTSzlaV6JoiTWwfiY1GKh+1jqLDyG2lkQuD37rWJNyXwFD6bsNQkU0AaoOL5pFZianjwja3Ub0A3ZSXGM+z+q6SGq7DKzsg1xlW09c2UzGaHNbdJQA7wk/Offsuf+YQkUZsQfEzsPKFLOOMypfO+CCTELB5wU93joUZPQpU8HY+P3fDowZRsa/7fK4tD4fyFmbMgvxoFhpl0Tt+5r5BxkPBHHv2zUSsyJ2oh0lekvO3hznOPj1KRPpO2W5528jUNvyKPHSQoiP4cQoWFmlJfwjv3mSbWe7TKKWfsMMsZT2XRSVcJVRGtPKRKiwM1ebaqo0ChrJ9ua0mi0o1CdX1zwtFKJXDt6shNb8iqs39rJTnk2/+L1uP15icMQ8An8yKyxu8MwYiXyJfekljcbbSIx97W4I/LPdCCsaH5Eitu38BkFywcFi6Rq/YanTL050rIjdfNRhWk1F+E3Wfst9JYwWdjE0F9SWjwlYuvJKNON8b408fo6lAutcdowtpsP8th8NIjvPmwOwitrdrN9UzkPA/eZz7oKMp6yxoYzI4vA9kebWilhOjM47tEYwq2F5NKpf+xMutM33y+3+EdU8Dlb7F7jY5q/zGeBqnHhGWvsY9R4P5V40aygNq6C/mes4Df3cQWRa7W3zdIb4kr/6dEzlX7AKN1vfll4LwmTaO/F3imqigcf5UnhbVAq7nnqny198u//GOcb30I5zICgTX8E4IBsnSIs+LRdvBWfh/QqrcyfgCr1FCWADrVzx950+Jd6oXiGT3uTc90nc+HAXN+odGRvU/5peWVftIcBCwrxMdC/Uxd2Q6l+axHHAtRuTXA9XWRMJKcER+u1YVPCWi8DceWvlTg1v6/ORAipP8gzh9o9okujOmjvpO3IeLlf7EEJovhQw2xvqmdseB9yg394muv4Qo2gGfxfrCT23Ixj1E/qGGLJHvMY3UcKvYQk0CxkYWwpDQbhaNqdMcJRWnUZ8pnEo0vjiEeDnpbEo033msSjn6+RZganS1RzoKIhOZAVFKO6q8jbllIjCA+gOX87cc5hrJJLvPqUnPNd6JSa7npkwJwfKPaSyKP2Jmf8vswIDv+dDWraKzbzcTxit5rvqJxvZM9bkzDfiLlQxkSG0HzfXGvON8ln8kVjW5M459XfVnNeJC5Am9K9Zx0dlAYYDq1mekYWNY7BStbpaHOIPO+gheyU9M+s09DSXjM=
*/