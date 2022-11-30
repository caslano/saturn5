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
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
*/