/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    and.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_AND_H
#define BOOST_HOF_GUARD_AND_H

#include <type_traits>
#include <boost/hof/detail/using.hpp>
#include <boost/hof/detail/intrinsics.hpp>

namespace boost { namespace hof { namespace detail {

constexpr bool and_c()
{
    return true;
}

template<class... Ts>
constexpr bool and_c(bool b, Ts... bs)
{
    return b && and_c(bs...);
}

#ifdef _MSC_VER

template<class... Ts>
struct and_;

template<class T, class... Ts>
struct and_<T, Ts...>
: std::integral_constant<bool, (T::value && and_<Ts...>::value)>
{};

template<>
struct and_<>
: std::true_type
{};

#define BOOST_HOF_AND_UNPACK(Bs) (boost::hof::detail::and_c(Bs...))
#else
template<bool...> struct bool_seq {};
template<class... Ts>
BOOST_HOF_USING(and_, std::is_same<bool_seq<Ts::value...>, bool_seq<(Ts::value, true)...>>);

#define BOOST_HOF_AND_UNPACK(Bs) BOOST_HOF_IS_BASE_OF(boost::hof::detail::bool_seq<Bs...>, boost::hof::detail::bool_seq<(Bs || true)...>)

#endif

}}} // namespace boost::hof

#endif

/* and.hpp
aL1YM8dvfXgwIt2Y7o44a0C4VyfHA7gum2N9+EtPFI/ycmNHOfagDajECFzqAZ75wKBaLyu+Pn5WmAapW+ZTcKmFO04byDP1CkyAlYVC3yvVVSv+nhiN8jKVgRYLQr4dJsc4Sbw20O6TYRmiICgvmiQnKkTuylcxW5828sVm3b0e0c6a/4G41Kne1AG5Q5xbtuINhzezjhRcYRkKI8SWPdyOr402+COYPtOzf+3a3Za6Yc36CDRcIVUqmrtCm5L4r42f7ZYwcLAULqPkndxPxYUDu4sGuHFE9DjutAg/MvCi+1VNrGC2/YnON+LPdvde1Lw3WpPS/FqGeUlZpKOf9702VQ2FEw7qcECU5hxYBvD8FmLN+yWmXNTFdnfQam9iHsX3jlEpWABkg8zDTHPooukqlb3bWYffNCSGHbfz2LK00JhW+vuVNM0onazN3xBXXHS+tRIv0R5RZmunKcgofsQsvM6z5QXi83duM73JLKDNXwTfjjsdgtgCd4ieWk2ZQEpK5FWm0iSK6m5cRu7N7E6fWIRebzQZTjpHepD7mwGAw0XhuTfyXUg4Tg==
*/