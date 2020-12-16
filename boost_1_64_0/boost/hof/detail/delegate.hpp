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
InyCdLiBBqC2AeIeTB/Cw5C3zmuX/B9XYfVBjHcPiGR1y+2gX03g8GEoIP4ZXa+7tV0SfMc13CufBzTVQT9jEj7R7cvkZaT8mz3dEMMH/kQ9z2VtkFyEArO4AoTFTSE8B1Y6J2KAU8Dzx1iQ0wthY2JV55IVPEyiLXgdkLwycQr3PT2WcIosADoygY/d6xsD16I6XkEb5Apav4kHLYt2xTtMai6Wiu8xrFz81lK1fLZV1oJgeXgvVY/IP8nI1k3kF/SR9JwhUPUU3R+M6ZfoanBhObgf1hlLE1+GHxYfWyvY+4C5EGiqN0OqT7uf3uYojqcvsPWYj5CuOK0lp+XdO0zRrc+pgXwsG+kAzYg9jNjwgcKc6excP+xh4+yMQdpYpgKiGVn0lyybPz5PrTY288zzIacaq5WO3snrTDdo+ipSD6nnEi7i6+iDtXtUfp+YsY7NJHwojzx6uA2Mt6SCsWt3qdyBlQo4m8Aa8yktr1mrMPq7Y1VGq5hCFMllucRIN+12laZ9hSLaB1ZbYD1uo6R0jJ9gk1Z+bnggRnxtG7Xri//UD0g8PzDRCv+723pfmemi+Ict3lezVPmpqnzzdNGlxfKo30r/3ZJwH82ypnsS0gm3iOZyB5at4g6wt6bGxPrVfTNNPscarf038X+kW/H/Byz4/70W/P8+C/4fsuD/WxPDyyz1TbLUN8pS31vfsr6PU3m0veUWtIJU2/xcFyhK07pT/8VXbkPWFpbdtr+W9yLfSoO1chQU5XyEOb9jxGYE4G9pJV9wGlb2DbVxVjGcMKRyu8KSnIELIz8/OzaH+53h/PU5MdX0TI0lJrmZhYEAmjm1Xt2jjdq3zbRRYuM9EqvEgwKlvmOmjOdSB2Kl0tzJtC6K07rY09wed1qX8W78zcLfrL+kVXpyF6YdHp8bmuq0QwO53s8jPitiEI8vhi6P6vlS3kHBr4eEX+634uGnX+DzimfXKbpAt9C+USgafNEw/Ry4IOIIXBgPYKccQyvwFHO+f4Jmo8OpPfG5xDj3t6OQ7XRzoeQLoiDaSCOMPjEf/fOKhhtVL8tgX2VWzCXp1TDTzOx45HwYpRh9qFhrXN/ShkNP2G/wsWYuyAHfu9sQ8ZndSHGp3nBResDGJgEQR5adz2rUx/wY9lp2VVEXe6su4kmBXjibvOimNX99AY2vD8aHtskMHRZCIRiVyXT1FTQa2yMwmAQqqHda+TjoeIvFFcYdpCeHbZTRmFf9AHuShNGaGyRJ8kRUf8JrwHvcFo5D9taPp4RZ9KEXo6E/pjGuGTpl168skc6DxCbdvG4rRoROOYMp8+s8n4O7hH3SoZ7MSDc9ia/QqXbBS0qQf0+Ae3D8TZA3jzrml02Z2xg6lYSXt8wEvyn4obxrMT389lIT8YJCz9V2Yw+xf9XIMjR7EdV7wz0E8AvmYb4p+DMeaEZCM+OAJIlvY8WRvDn6Wcbkcx9yv1zZrFP1C1H9MaAAoNFqC1WjXr5Ssew71XxxDmYtH+uZRKiPy58XBWp4IWmC0ozvt0UllpAeC81XdMBMMrweTiqMOPJ2+/KO1ewuTZv6odh0j8GvXXOrr1SM+DqRFEtFeiWBbcVCiX2g9mAHMGyG4DnRI/w5kb49pWKmKrl6X+Q8slBHzxxwzPfbyP8EtVqbF/6cHqK0UIDxdPSL88sNLoFfNM7gnyhwTSN6lrw/yeh7ZqzvSDw3Y1DNP9KejtuQwnDk2BvPIf1YodOud9OesKl5Fw+tbIlI27T5usT77zdfs9C/77HIf662yH/ebZGvXGSx37YlMfy8pf40S32HLelX3H06+291hvzhryoy3KAaX/htU9bAUIfT2fGh8H3NRLcZRWY=
*/