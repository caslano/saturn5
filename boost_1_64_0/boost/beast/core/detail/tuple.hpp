//
// Copyright (c) 2016-2019Damian Jarek (damian dot jarek93 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_TUPLE_HPP
#define BOOST_BEAST_DETAIL_TUPLE_HPP

#include <boost/mp11/integer_sequence.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/copy_cv.hpp>
#include <cstdlib>
#include <utility>

namespace boost {
namespace beast {
namespace detail {

template<std::size_t I, class T>
struct tuple_element_impl
{
    T t;

    tuple_element_impl(T const& t_)
        : t(t_)
    {
    }

    tuple_element_impl(T&& t_)
        : t(std::move(t_))
    {
    }
};

template<std::size_t I, class T>
struct tuple_element_impl<I, T&>
{
    T& t;

    tuple_element_impl(T& t_)
        : t(t_)
    {
    }
};

template<class... Ts>
struct tuple_impl;

template<class... Ts, std::size_t... Is>
struct tuple_impl<
    boost::mp11::index_sequence<Is...>, Ts...>
  : tuple_element_impl<Is, Ts>...
{
    template<class... Us>
    explicit tuple_impl(Us&&... us)
        : tuple_element_impl<Is, Ts>(
            std::forward<Us>(us))...
    {
    }
};

template<class... Ts>
struct tuple : tuple_impl<
    boost::mp11::index_sequence_for<Ts...>, Ts...>
{
    template<class... Us>
    explicit tuple(Us&&... us)
      : tuple_impl<
            boost::mp11::index_sequence_for<Ts...>, Ts...>{
          std::forward<Us>(us)...}
    {
    }
};

template<std::size_t I, class T>
T&
get(tuple_element_impl<I, T>& te)
{
    return te.t;
}

template<std::size_t I, class T>
T const&
get(tuple_element_impl<I, T> const& te)
{
    return te.t;
}

template<std::size_t I, class T>
T&&
get(tuple_element_impl<I, T>&& te)
{
    return std::move(te.t);
}

template<std::size_t I, class T>
T&
get(tuple_element_impl<I, T&>&& te)
{
    return te.t;
}

template <std::size_t I, class T>
using tuple_element = typename boost::copy_cv<
    mp11::mp_at_c<typename remove_cv<T>::type, I>, T>::type;

} // detail
} // beast
} // boost

#endif

/* tuple.hpp
5iPX0kMXI1/KLVxs7srwxbblTTdYj4Whaw3/EpddW8zR9DvqcTVE6A91ObXFEp0mWfzl8AdJmiPlHtEyzy9G4vU8/x9Cnyj+mTp9P7GZ96LQLzS1Kcaz3lfKffmMxnPKtz2ZaS8iLdcmyrEoop9TH0kZjzC1L2vaWiNflge9p9RdYtSq0rb6bpX0M9CDQuQe8+TZcfCiYj5TsnjvVfK8cS8oylCa/x08aV125wEZ5Ps966mDCWjfEfA3gdcTojxrG01w3ZP1b+QAGw69eZ5ST4zjcZ7fP9K2Z24r6x8HPmta/2A7Dhe7xtKOJAzo12dqHPrMCgOjJJx1HiV1BjkaeQoN6oXjNuqP6Wp1flJPei0GckWYyFXsBM6W8kq49cyCSOFL5rdTgYcCjX7T+Kyl33BY1l3Hqd8wXZbuB+l/snclYFUVUfg+UKC0QkLEJUXcUlxwDcuFskVTC8tc0gILFFIUFVPLisx2K9ptp1U0JTS0zcx2261s+9po36ysrGzvv+f9b7j3cgcePECtO5/jz9yZM2/m3PUsc+Z5s3xsmOa+YfvBUj4B5R7Sfpz7dzPYfziwvbSZGsb7iH0cYejum27SfqOP9w3bH8x6n3HUixKTW3cfsb361tXfR4628b7K95G6bxxtE2zfqXlzpspWUDjGb8n4F/z3epj/vuH3GE6H5VssTtGbmxam52ayD3VfqXp+37Pvb1+osC+uiFf3o3r2dRH+naTOieHyzvtS+khnuYKnbvfqTMXzg8lLzhnsNOvH4jcXSX+vq/ea4Xgvfy71KUaM+rZT7wr1rOoo454SdrJxopRjuedRc+BhwD/4fAgcWwe0PSv4nLiabZDRRt6Z8syIBP3vMTX71jOfHce+aH92bHd5dux0eXYYPvdnR5Sv8rMj2md/dsT7Kj87EnyVnx38rlN23Fa2uJDW68oei3NDdOW9T77H7yX77etmyG0MuC8+5yp/v/PZwbZtXL/XmwH7SH1L4bdRTTzRKMMWT1XZlB9sAJvyu3Fi233gpX+iBuc9fXbkM92/u/OBHTpbs87mu+ts0PVta75EbM0TX0/a/Oz6frdmvXHgyn+uyb1QZ2vW2Xx3nQ16V9mazRiUvPBFNs5Du3cMvw26QOlxRMclZfyske8LxOth/DbgocButD0nAacw3kke45ssYHyTsxhPaDGwH/BixhW6jHGFrgIeBFwPHAjcChwMfI9xhT4CDgV+BUxlfI3DgOazaRhwf+AxwFbAY4FHAccBbwZOAt7FuIEPAE8CPg08GbgFmAmMwvxzgNHA04AdgdOBE1i+iuV1LG9h+SOg2d82YC7wJ+AsYGS4f3zNgOOBLYETgO2BE4GdgLOBPYBzgP2Bi4BHA89iPBAlm1HOLXDE71rMeCznke/nk+5B9R0tMozQxRoVMUdvJt3twG6M7zIYeBfjVd4NzADeA8wCrmQcrVXA1cAS4FrGWXkJ+ADjojzI8/IQ8Hfgo4zT+BiwL3AT8Hjg48ATgE8CzwY+DbwA+CzHP1x9V8n1K+PvjL8HAQ3GY+nKOCy9gVsY1/I1YCrwDZOPjMNyGuOwzAK+A1zIeEDXAz8ArmQcn/sY1+cV4Me8/j7j9fcV5/U1MAZj+AbYAvgdMAH4PbAb8AdgL+BPwJHAHcDpwJ+BecCdwKXA34BXAn8HrgH+AVwP/Bu4EfgPsBxovuw+BjYCfg6MAP4FjAT2AV/2BqYDmwKnA/cBzgXuCzwduJ+K88P3Id+peWF2n5K38XsG+RPmiJfUgvGSWgPfB86oJ5+S4pWR9eZXsnllpOdbQt+SL1dG1ot/iXFvZK19TL6c37jWfiax90buNr4m/e6NDMnfZDjos5ELkcs=
*/