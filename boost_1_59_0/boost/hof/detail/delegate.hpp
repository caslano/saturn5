/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    delgate.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_DELGATE_H
#define BOOST_HOF_GUARD_FUNCTION_DELGATE_H

#include <type_traits>
#include <utility>
#include <boost/hof/config.hpp>
#include <boost/hof/detail/and.hpp>
#include <boost/hof/detail/holder.hpp>
#include <boost/hof/detail/forward.hpp>
#include <boost/hof/detail/using.hpp>
#include <boost/hof/detail/intrinsics.hpp>
#include <boost/hof/detail/noexcept.hpp>


#define BOOST_HOF_ENABLE_IF_CONVERTIBLE(...) \
    class=typename std::enable_if<BOOST_HOF_IS_CONVERTIBLE(__VA_ARGS__)>::type

#define BOOST_HOF_ENABLE_IF_CONVERTIBLE_UNPACK(...) \
    class=typename std::enable_if<BOOST_HOF_AND_UNPACK(BOOST_HOF_IS_CONVERTIBLE(__VA_ARGS__))>::type

#define BOOST_HOF_ENABLE_IF_BASE_OF(...) \
    class=typename std::enable_if<BOOST_HOF_IS_BASE_OF(__VA_ARGS__)>::type

#define BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(...) \
    class=typename std::enable_if<BOOST_HOF_IS_CONSTRUCTIBLE(__VA_ARGS__)>::type

#define BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(...) \
    BOOST_HOF_NOEXCEPT(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(__VA_ARGS__))

#define BOOST_HOF_INHERIT_DEFAULT(C, ...) \
    template<bool FitPrivateEnableBool_##__LINE__=true, \
    class=typename std::enable_if<FitPrivateEnableBool_##__LINE__ && boost::hof::detail::is_default_constructible_c<__VA_ARGS__>()>::type> \
    constexpr C() BOOST_HOF_NOEXCEPT(boost::hof::detail::is_nothrow_default_constructible_c<__VA_ARGS__>()) {}

#define BOOST_HOF_INHERIT_DEFAULT_EMPTY(C, ...) \
    template<bool FitPrivateEnableBool_##__LINE__=true, \
    class=typename std::enable_if<FitPrivateEnableBool_##__LINE__ && \
        boost::hof::detail::is_default_constructible_c<__VA_ARGS__>() && BOOST_HOF_IS_EMPTY(__VA_ARGS__) \
    >::type> \
    constexpr C() BOOST_HOF_NOEXCEPT(boost::hof::detail::is_nothrow_default_constructible_c<__VA_ARGS__>()) {}

#if BOOST_HOF_NO_TYPE_PACK_EXPANSION_IN_TEMPLATE

#define BOOST_HOF_DELGATE_PRIMITIVE_CONSTRUCTOR(constexpr_, C, T, var) \
    template<class... FitXs, typename boost::hof::detail::enable_if_constructible<C, T, FitXs...>::type = 0> \
    constexpr_ C(FitXs&&... fit_xs) \
    BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(T, FitXs&&...) \
    : var((FitXs&&)boost::hof::forward<FitXs>(fit_xs)...) {}
    
#else
#define BOOST_HOF_DELGATE_PRIMITIVE_CONSTRUCTOR(constexpr_, C, T, var) \
    template<class... FitXs, BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(T, FitXs&&...)> \
    constexpr_ C(FitXs&&... fit_xs) \
    BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(T, FitXs&&...) \
    : var(BOOST_HOF_FORWARD(FitXs)(fit_xs)...) {}

#endif

#define BOOST_HOF_DELEGATE_CONSTRUCTOR(C, T, var) BOOST_HOF_DELGATE_PRIMITIVE_CONSTRUCTOR(constexpr, C, T, var)

// Currently its faster to use `BOOST_HOF_DELEGATE_CONSTRUCTOR` than `using
// Base::Base;`
#if 1
#define BOOST_HOF_INHERIT_CONSTRUCTOR(Derived, Base) BOOST_HOF_DELEGATE_CONSTRUCTOR(Derived, Base, Base)
#else
#define BOOST_HOF_INHERIT_CONSTRUCTOR(Derived, Base) \
    using fit_inherit_base = Base; \
    using fit_inherit_base::fit_inherit_base; \
    Derived()=default; \
    template<class FitX, BOOST_HOF_ENABLE_IF_CONVERTIBLE(FitX, Base)> \
    constexpr Derived(FitX&& fit_x) : Base(BOOST_HOF_FORWARD(FitX)(fit_x)) {}
#endif

namespace boost { namespace hof {
namespace detail {

template<class... Xs>
constexpr bool is_nothrow_default_constructible_c()
{
    return BOOST_HOF_AND_UNPACK(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(Xs));
}

template<class... Xs>
constexpr bool is_default_constructible_c()
{
    return BOOST_HOF_AND_UNPACK(BOOST_HOF_IS_DEFAULT_CONSTRUCTIBLE(Xs));
}

template<class... Xs>
BOOST_HOF_USING(is_default_constructible, std::integral_constant<bool, is_default_constructible_c<Xs...>()>);

template<class C, class X, class... Xs>
struct enable_if_constructible
: std::enable_if<is_constructible<X, Xs&&...>::value, int>
{};

}
}} // namespace boost::hof

#endif

/* delegate.hpp
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
*/