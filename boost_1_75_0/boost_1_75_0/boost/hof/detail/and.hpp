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
WeVuT7/ABK/n9uf5XB2VS7mPeEp+uZoQzq4ryUaF9z/lahaiLjJQkOfxD88CP4duB4IXvt90LzJEPa51L+MkJI3JluwWvjUjR6d9yW0/2Oux1Q/qstb/+W5NYDPfgfWTSh4hA+7/3Ja00xVGLqloACc7uWI4LVOtACvReDKWvw2y+OD7bqJ7jxZ5yTd88NE3kjN4iUm7+vNkbqwjmH+mYMN+zmQY42gqGKifmCvPjhQ23T75aG5CYOCwKfkc2Bmx9nCzVqTsZ/f1Lb3bvnit7eMkp4EyWzMER+Uu2EqpYlv6/DVCjW+zUl2Kb3MJuX2xKlO7CyVlVbykdgwEKwXzb5qol1+WP0rz0B+XUBfYm5GUMpUAcX+Ldmzm+ylXbRGYiI+uA4FjHc8f/jS6jVx/uCMSt4b6S/gXY0RqdY7ZfRvE52CeEr21t7IgUwmwL5gWWSQwIaJ0SUGaU6e/gOdEmD1Eiqjg+Ab8M9qC21Rq3UvfV1kghKtndrZPHdXPDcep1c+NxxeQDhZR79msqoRRaFVBlqp5UMnK5GKUCWt4VqSvPylrQPlcgEUFm56Glv2cNqnNh9Od4VPP8r3may5rQVkEXUGk2Xim//Reuep88WejtPwnlG+HDBuD+7sZkWUpmESFks/NwtGOrcPHi2bxejCxthtbMynH1+3nDlJ3vpLXund7B1vFrVhs6VVGFPKI3vMV8MLy40Kna93r
*/