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