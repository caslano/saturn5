/* Copyright 2003-2014 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_CONS_STDTUPLE_HPP
#define BOOST_MULTI_INDEX_DETAIL_CONS_STDTUPLE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/if.hpp>
#include <boost/tuple/tuple.hpp>
#include <tuple>

namespace boost{

namespace multi_index{

namespace detail{

/* std::tuple wrapper providing the cons-based interface of boost::tuple for
 * composite_key interoperability.
 */

template<typename StdTuple,std::size_t N>
struct cons_stdtuple;

struct cons_stdtuple_ctor_terminal
{
  typedef boost::tuples::null_type result_type;

  template<typename StdTuple>
  static result_type create(const StdTuple&)
  {
    return boost::tuples::null_type();
  }
};

template<typename StdTuple,std::size_t N>
struct cons_stdtuple_ctor_normal
{
  typedef cons_stdtuple<StdTuple,N> result_type;

  static result_type create(const StdTuple& t)
  {
    return result_type(t);
  }
};

template<typename StdTuple,std::size_t N=0>
struct cons_stdtuple_ctor:
  boost::mpl::if_c<
    N<std::tuple_size<StdTuple>::value,
    cons_stdtuple_ctor_normal<StdTuple,N>,
    cons_stdtuple_ctor_terminal
  >::type
{};

template<typename StdTuple,std::size_t N>
struct cons_stdtuple
{
  typedef typename std::tuple_element<N,StdTuple>::type head_type;
  typedef cons_stdtuple_ctor<StdTuple,N+1>              tail_ctor;
  typedef typename tail_ctor::result_type               tail_type;
  
  cons_stdtuple(const StdTuple& t_):t(t_){}

  const head_type& get_head()const{return std::get<N>(t);}
  tail_type get_tail()const{return tail_ctor::create(t);}
    
  const StdTuple& t;
};

template<typename StdTuple>
typename cons_stdtuple_ctor<StdTuple>::result_type
make_cons_stdtuple(const StdTuple& t)
{
  return cons_stdtuple_ctor<StdTuple>::create(t);
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* cons_stdtuple.hpp
K+MsdcJrfkK31V0/JEy9wR2qPJaJ9xjsS+hfYIThUAgcyynNy+HEif0oy2KRFjm2DXLnKHc6jAKrtItAPJaQsYyPN8voBr4dBtfsb0YXEm0iWT5Lz82D1E+FadfchrVp/lA5oag9B9iHNDtLtV1bKMOt2fyQehNeXlp5ivzYTC1U69K8xsDBWRbNRY/ymv4NuTOrbeK8QdmFqZVKNhnEOpv6zJTYptxxFGoK+hfx/TEC4Y9FAN9WUeGQ/yod9Os+iuHMz5g7huGqTHiGO67DodmJrSuGY15xrXFmB2DSX4lU9vW6zS1g0X7QezLtB0Wchl6cC6nZf9DUQJ95BuUe8d1cdi/fEjcQNnKfx+L1Cyux7dKCiI8cNs+BT7N4XS9OYjeHaIdwzzJu4sdWmqWxeOywPLyRch8clCG4IZBcmmE8M2bxlr5l53HuQbyYCeSeY/G6ZWF7gSO5JMe4lrt48xG5loN2b27JppGqQNVAj9X4W28NOLQzx3Ntg0bTclJRuLnlBu4124qaY+8Sa5fI9svY9aNq7JHB18Y1COPHWZr6iV3W/K0+X9dNY5OeYZVZEJReHCs+xq6544xb2JHj5nmhuBizngO+tQvmAKiiB03JWQDDr2D4kcMQDmP4UQ9V+sIsyrxm6Fmudww1kQp/zCAO4w/xJxJcvf9JFJWAL5p4JY74ymD8GAHgawPymD2cS34AY3hUddR6LsF9MoRDR2Phn1ThN2gBDL/fqArXAhj+RhX+2AH+njEVrvn43XlGFd5PgL6JilglxHxzjgNWtRuMAop1dlAMdLXkvVOCmbbDyxMEgxmSYGInwQzb4U8STM+UmJddGpNFMPO5m2BmPilm5vNGBDPzeWOCmfkkWJ1P/BYf7hj3A8rMjyLvmm1E9XxA1xt3rtYTeLDK1xsMZ+uNAx1mDxgWETyZI+woyG/IjDnzIOU+OIxSL8mcSDhIJmP99K7qfPuE/GzBmL5dHf4eFb6AAP0m/0Tpf6rYaL89PgLhTh9okO+vwubXob1pOPhthXDz7bT9Y1W4bkv0C6rDjbfTyvEq3OxrjR11ePUWKCSP2AWOQZQ4d+/aYHdJbD8scresF+BWGhTHuG+Zdxr8vLCz2E+E2qyt9JbXulwf/0HKz0SWFWmQegGJf3bgXuuFDbZHtQIrDqNQmBfHBezdbn5rWYeKT2KUbdJeg30B2aMbHL1zuBPRMd9llMfRYPs6jjcXqvfEUN7EF7cYvjjKcXPfeMHE1e6kQedKjhP73UsGZvq7TccNvKviRvzyELy5toj46R2Aq30Mctg+cWIQnyX4OwHHvc6g/IGdiBN51J3DZhfWMzDN1MdgG+o8XqriFuTri8g7T3jdQR76yzxjxCfdHqzKxwjBWHHhdnoN9d4+R55qtxbnG6saE+cYBrpWXJtNvr+Ptft6yJ7Gz72P49ANKH7GkN9sqzev+/F/gOPd1lPaTLe/3mDv6NmO46XuNZs466mc3dO46yipBrr3HQGMVQNi7xxFDIuJ5+pjFOO26J9HjBUfZXvjiGPx74m6BsSGdRPcv5znPIgHGh/1GuUE4kb3IDYiyBna1fDc7F2rDfZms1O6WQ7nbnozmc9ZdupJw6hIb5JHpvQZ/Sr3teJGfplaZSU6d+QQFUJfOFwmsf3ct1O7komsaSKDefzFquHLK8uCNMjcSijwcu+YlVLBRj+P42vsrngRgbsTL6tEb5hz4B1EJUT8VOxb43WSlbFfRKHD0ose67l94REtO7nG8xpmmZPbQZ3XR0WzkVGbjb5saKTrZq7r23lcZzaPpGPyWV5SLOcilS2FE0ZOGUZ5JWpnJQqRb+UpKnM0D33fKZOkEkFzQ6LbfB4=
*/